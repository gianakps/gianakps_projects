/* 
 * File:   main.cpp
 * Copyright 2018 gianakps
 *
 * Created on October 16, 2018, 10:54 AM
 */

#include<ext/stdio_filebuf.h>
#include<unistd.h>
#include<sys/wait.h>
#include <cstdlib>
#include<iostream>
#include<cstring>
#include <vector>

using namespace std;
const int READ = 0;
const int WRITE = 1;

void bash(std::vector<char*> args1, std::vector<char*> args2) {
    int pipefd[2];
    pipe(pipefd);
    
    int pid2, pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[READ]);
        dup2(pipefd[WRITE], WRITE);
        execvp(args1[0], &args1[0]);
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            close(pipefd[WRITE]);
            dup2(pipefd[READ], READ);
            execvp(args2[0], &args2[0]);
        }
    }
}

int main(int argc, char** argv) {
    std::vector<char*> args1;
    std::vector<char*> args2;
    
    bool two = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "|") {
            two = true;
            continue;
        }
        if (two) {
           args2.push_back(&argv[i][0]);
        } else {
            args1.push_back(&argv[i][0]);
        }       
    }
    args1.push_back(nullptr);
    args2.push_back(nullptr);
    
    bash(args1, args2);
    return 0;
}