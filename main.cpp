/**
 * These questions are desgined to facilitate students to gain practice for
 * upcoming job interviews -- at times also called exam(s).
 *
 * Copyright (C) 2018 raodm@miamiOH.edu
 * Solutions by Peter Gianakas
 */

// All the necessary includes are already here
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


// Convenience for namespace
using namespace std;

/**
 * The threadMain method below is called (from main.cpp) on many
 * threads, with id (i.e., 0, 1, 2, ...) indicating the logical number
 * of the thread. Implement threadMain to print data in order of id
 * value (see sample outputs in document for expected outputs)
 */
void threadMain(const int id, const std::string data) {
    static std::mutex mut;
    static int count = 0;
    while (count != id) {}
    std::cout << "id " << id << ": " << data << std::endl;
    std::lock_guard<std::mutex> guard(mut);
    count++;
}


const int READ = 0, WRITE = 1;
// Accomplish "ls -l /tmp | grep raodm"

void anonPipes() {
    int pipefd[2];
    if (pipe(pipefd) != 0) {
        std::cerr << "Error creating pipe!\n";
        return;
    }
    int pid2 = -1, pid1 = -1;
    pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[READ]);
        dup2(pipefd[WRITE], WRITE);
        execlp("ls", "ls", "-l", "/tmp", nullptr);
    } else {
        // Run "grep raodm"
        pid2 = fork();
        if (pid2 == 0) {
            close(pipefd[WRITE]);
            dup2(pipefd[READ], READ);
            execlp("grep", "grep", "raodm", nullptr);
        }
    }
    // In parent process.
    // Wait for ps -fea command to finish
    waitpid(pid1, nullptr, 0);
    // Close write-end of input stream
    // to grep Otherwise grep will *not*
    // terminate!
    close(pipefd[1]);
    // Wait for grep command to finish
    waitpid(pid2, nullptr, 0);
}