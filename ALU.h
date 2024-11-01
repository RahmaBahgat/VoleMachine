#ifndef ALU_H
#define ALU_H

#include "Register.h"
#include <string>

class ALU {
public:
    // Add two's complement values from two registers and store the result in the destination register
    void add(int regR, int regS, int regT, Register& reg);

    // Add floating-point values from two registers and store the result in the destination register
    void addFloatingPoint(int regR, int regS, int regT, Register& reg);

    // Helper functions for hexadecimal to decimal conversion and vice versa
    int hexToDec(const std::string& hex);
    std::string decToHex(int dec);

    static bool isValid(const std::string& hexStr);
};

#endif
