#ifndef CPU_H
#define CPU_H

#include "ALU.h"
#include "CU.h"
#include "Register.h"
#include "Memory.h"
#include <string>
#include <utility>

class CPU {
private:
    int programCounter;                
    std::string instructionRegister;    
    Register reg;                      
    ALU alu;                           
    CU cu;                             

public:
    CPU();// Constructor to initialize the CPU

    // Fetches the next instruction from memory based on the program counter
    void fetch(Memory& memory);

    // Decodes the fetched instruction into an opcode and its operands
    std::pair<std::string, std::string> decode();

    // Executes the instruction using the appropriate methods from CU or ALU
    int execute(const std::string& opcode, const std::string& operands, Memory& memory);

    // Runs one complete cycle: fetch, decode, and execute the instruction
    int runNextStep(Memory& memory);

    // Returns the current state of the registers
    const Register& getRegister() const;
};

#endif
