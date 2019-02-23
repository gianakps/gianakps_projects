/* 
 * File:   gianakps_hw3.h
 * Copyright: 2018 gianakps
 *
 * Created on September 25, 2018, 11:50 AM
 */

#include <string>
#include <vector>

#ifndef GIANAKPS_HW3_H
#define GIANAKPS_HW3_H

class ProcInfo {
    public:
        std::string fileName;
        ProcInfo(std::string file) {this->fileName = file;}
        std::unordered_map<std::string, std::string> pidData;
        std::unordered_map<std::string, std::string> cmdData;
        std::vector<std::string> pids;
        void loadData(ProcInfo&, std::string, std::ostream&);
        void printData(ProcInfo&, std::string);
        void findPids(ProcInfo&, std::string);
};

#endif /* GIANAKPS_HW3_H */