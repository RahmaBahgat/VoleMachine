#ifndef ALU_H
#define ALU_H

#include "Register.h"
#include <string>

using namespace std;

class ALU {
public:
    int hexToDec(const std::string& hex);
    std::string decToHex(int dec);

    static bool isValid(const std::string& hexStr);
    // Add two's complement values from two registers and store the result in the destination register
    void add(int regR, int regS, int regT, Register& reg);

    // Add floating-pstd::stringalues from two registers and store the result in the destination register
    void addFloatingPoint(int idx1, int idx2, int resultIdx, Register& reg);

    // Helper functions for hexadecimal to decimal conversion and vice versa

};

#endif
