
#ifndef CPU_H
#define CPU_H

#include "ALU.h"
#include "CU.h"
#include "Register.h"
#include "Memory.h"
#include <string>
#include <utility>

using namespace std;

class CPU {
private:
    int programCounter;
    string instructionRegister;
    Register reg;
    ALU alu;
    CU cu;

public:
    CPU();
    void fetch(Memory& memory);
    pair<string, string> decode();
    int execute(const string& opcode, const string& operands, Memory& memory);
    int runNextStep(Memory& memory);
    const Register& getRegister() const;
};

#endif
