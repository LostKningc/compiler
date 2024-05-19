#include "../include/IRtoAsm.hpp"
#include <fstream>

int main(){
    std::string inputfile = "test.kp";
    std::string outputfile = "test.s";
    IRanalysis(inputfile, outputfile);
    return 0;
}