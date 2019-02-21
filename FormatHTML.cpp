// Copyright (C) 2017 gianakps@miamiOH.edu
// Reads input from a file and changes it into HTML format

#include <iostream>
#include <string>
#include <fstream>


std::string convert(const std::string& line) {
    // Format the line into a HTML fragment enclosed in 'div' tags
    return "<div class='line'>" + line + "</div>";
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Specify input & output files";
        return 1;
    }
        
        std::ifstream inFile(argv[1]);
        std::ofstream outFile(argv[2]);
        std::string line;
        
        if (!inFile.good() || !outFile.good()) {
            std::cout << "Errpr opening input or output streams.";
        }
        
    // First print standard simple HTML header
    outFile << "<!DOCTYPE html>\n<html>\n<head>\n"
              << "<link type='text/css' rel='stylesheet' "
              << "href='http://ceclnx01.cec.miamiOH.edu/~bravosad/ex4.css'/>\n"
              << "</head>\n"
              << "<body>\n";
    // Read line-by-line and process it
    std::string input;
    while (std::getline(inFile, input)) {
        outFile << convert(input) << std::endl;
    }
    // Wrap-up the HTML format
    outFile << "</body>\n</html>\n";
    
    return 0;
}
