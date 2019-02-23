* 
 * File:   main.cpp
 * Copyright: gianakps
 *
 * Created on October 2, 2018, 10:19 AM
 */

// Copyright (C) 2018 raodm@miamioh.edu.
// Implementation by Peter Gianakas

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Convenience for using methods in standard namespace
using namespace std;

/** An OS operation requires removal of all wildcards (.ie., ''
    characters) in each line of a given input stream.  Coplete teh
    following cleanUp method to remove all *' characters from a given
    string and rpint each line to a given output stream.

    \param[in] is The input stream from where lines are to be read.

    \param[out] os The output stream to where lines are to be written.
 */
void cleanUp(std::istream& is, std::ostream& os) {
    //  Implement this method.
    std::string line;
    std::string result;
    while (std::getline(is, line)) {
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c != '*')
                result += c;
        }
        std::cout << result << std::endl;
        result = "";
    }
}

// Alias for an unordered map used in merge method below.
using UserMap = std::unordered_map<std::string, std::string>;

/** Complete the following method that merges values (with a '-'
   between values) with the same key in both maps (while ignoring keys
   that are not present in both). Example maps (in key, value format)
   are shown in the supplied document. NOTE: order of entries in the
   unordered maps is random.

   \param[in] m1 The first unordered map to be used for merging.
 * 
   \param[in] m2 The second unordered map to be used for merging.

   \return An unordered map with values merged with a '-' for keys
   present in both unordered maps (m1 and m2).
 */
UserMap merge(const UserMap& m1, const UserMap& m2) {
    // Implement this method. For now this method returns an empty map
    // to avoid compiler warnings
    UserMap result;
    for (auto n : m1) {
        for (auto x : m2) {
            if (n.first == x.first) {
                result[n.first] = n.second + "-" + x.second;
            }
        }
    }
    return result;
}

/** Complete the following method to run the Linux command 'head -num
    GPL.txt' with different values of 'num' supplied as the
    argument. For example, if numList = {1, 17, 3}, then this method
    should run head 3 times, in a serial manner, as: "head -1
    GPL.txt", "head -17 GPL.txt", "head -3 GPL.txt"
 
    @param[in] numList The list of numbers to be used to run the head
    command.
 */
void serial(std::vector<int> numList) {
    // Implement this method
    std::vector<char*> args;
        for (auto n : numList) {
            std::string arg = "-" + std::to_string(n);
            std::string cmd = "head";
            std::string file = "GPL.txt";
            std::vector<char*> args = {&cmd[0], &arg[0], &file[0], nullptr};
            if (int pid = fork() == 0) {
            execvp(args[0], &args[0]);        
            } else {
                waitpid(pid, nullptr, 0);
            }
    }
}