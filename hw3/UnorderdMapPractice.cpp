/* 
 * File:   UnorderedMapPractice.cpp
 * Copyright 2018 gianakps
 *
 * Created on September 25, 2018, 11:49 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include "gianakps_hw3.h"

using namespace std;

//  Put the information from proc_info1.txt into two unordered_maps
//  We have instance variables for these defined in the header
//  pidData:     key: PID value: PPID
//  cmdData:     key: PID value: CMD
//  Won't return anything, just changes values of instance variables
void ProcInfo::loadData(ProcInfo& info, std::string paras, std::ostream& os) {
    std::ifstream file(info.fileName);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream s(line);
        std::string pid, ppid, cmd, dummy;
        s >> dummy >> pid >> ppid;
        cmd = line.substr(47);
        info.pidData[pid] = ppid;
        info.cmdData[pid] = cmd;
    }
}

//  Put all the pids we need to print information for into a vector
//  Easier to do for me, and prevents the problem of printing them backwards
void ProcInfo::findPids(ProcInfo& info, std::string paras) {
    loadData(info, paras, std::cout);
    //  find where paras is the key, if possible
    //  push that key into the vector
    //  check if the value of the previous key exists as a key somewhere
    //  if it does push that value in the vector
    //  repeat until the key doesn't exist
    if (info.pidData.find(paras) != info.pidData.end()) {
        info.pids.push_back(paras);
        std::string value = info.pidData[paras];
        while (info.pidData.find(value) != info.pidData.end()) {
            info.pids.push_back(value);
            value = info.pidData[value];
        }
    }
}

void ProcInfo::printData(ProcInfo& info, std::string paras) {
    loadData(info, paras, std::cout);
    std::cout << "Process tree for PID: " << paras << std::endl;
    std::cout << "PID\tPPID\tCMD" << std::endl;
    
    for (int i = info.pids.size() - 1; i >= 0; i--) {
         std::cout << info.pids[i] << "\t" << 
                 info.pidData.at(info.pids[i]) << "\t"
              << info.cmdData.at(info.pids[i]) << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string paras = argv[2];
    ProcInfo info(argv[1]);
    info.findPids(info, paras);
    info.printData(info, paras);
    return 0;
}