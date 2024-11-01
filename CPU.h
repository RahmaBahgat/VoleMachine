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
    int programCounter;               // Points to the current memory cell address for fetching instructions
    std::string instructionRegister;  // Holds the fetched instruction
    Register reg;                     // CPU registers
    ALU alu;                          // Arithmetic Logic Unit for operations
    CU cu;                            // Control Unit for handling instructions

public:
    CPU();

    // Fetches the instruction from memory based on the current program counter.
    void fetch(Memory& memory);

    // Decodes the instruction in the instruction register into an opcode and operands.
    std::pair<std::string, std::string> decode();

    // Executes the instruction by calling the appropriate function from CU or ALU.
    int execute(const std::string& opcode, const std::string& operands, Memory& memory);

    // Runs a single fetch-decode-execute cycle and advances program counter.
    int runNextStep(Memory& memory);

    // Accessor for the registers for checking state.
    const Register& getRegister() const;
};

#endif
