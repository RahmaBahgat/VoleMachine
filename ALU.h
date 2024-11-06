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
    void add(int regR, int regS, int regT, Register& reg);
    void addFloatingPoint(int idx1, int idx2, int resultIdx, Register& reg);
    void OR(int regR, int regS, int regT, Register& reg);
    void AND(int regR, int regS, int regT, Register& reg);
    void XOR(int regR, int regS, int regT, Register& reg);
    void Rotate(int regR, int regS, Register& reg);
    string hexToBinary(const string& hex);
};

#endif
