#include "CPU.h"
#include <iostream>

CPU::CPU() : programCounter(0), reg(Register()) {}

void CPU::fetch(Memory& memory) {
    // Fetch two memory cells to form a 4-digit instruction
    std::string firstHalf = memory.getCell(programCounter);
    std::string secondHalf = memory.getCell(programCounter + 1);

    instructionRegister = firstHalf + secondHalf; // Combine cells for full instruction
    programCounter += 2; // Advance by two cells for the next instruction
}

std::pair<std::string, std::string> CPU::decode() {
    // Split instruction into opcode (1 digit) and operands (remaining 3 digits)
    return {instructionRegister.substr(0, 1), instructionRegister.substr(1)};
}

int CPU::execute(const std::string& opcode, const std::string& operands, Memory& memory) {
    int op = std::stoi(opcode, nullptr, 16);  // Convert opcode to integer
    int regR = std::stoi(operands.substr(0, 1), nullptr, 16);  // Register R
    int regS, regT, address;

    switch (op) {
        case 0x1:  // LOAD RXY: Load value from memory at address XY into register R
            address = std::stoi(operands.substr(1, 2), nullptr, 16);
            cu.load(regR, address, reg, memory);
            break;
        case 0x2:  // LOAD immediate RXY: Load immediate value XY directly into register R
            cu.loadImmediate(regR, operands.substr(1, 2), reg);
            break;
        case 0x3:  // STORE RXY: Store value in register R to memory at address XY
            address = std::stoi(operands.substr(1, 2), nullptr, 16);
            cu.store(regR, address, reg, memory);
            break;
        case 0x4:  // MOVE 0RS: Move value from register R to register S
            regS = std::stoi(operands.substr(1, 1), nullptr, 16);
            cu.move(regR, regS, reg);
            break;
        case 0x5:  // ADD RST: Integer addition of registers S and T, store result in R
            regS = std::stoi(operands.substr(1, 1), nullptr, 16);
            regT = std::stoi(operands.substr(2, 1), nullptr, 16);
            alu.add(regR, regS, regT, reg);
            break;
        case 0x6:  // Floating-point addition of registers S and T, store result in R
            regS = std::stoi(operands.substr(1, 1), nullptr, 16);
            regT = std::stoi(operands.substr(2, 1), nullptr, 16);
            alu.addFloatingPoint(regR, regS, regT, reg);
            break;
        case 0xB:  // JUMP RXY: Jump to address XY if register R equals register 0
            address = std::stoi(operands.substr(1, 2), nullptr, 16);
            if (reg.getCell(regR) == reg.getCell(0)) {
                programCounter = address;
                return 0;  // Return to indicate jump occurred
            }
            break;
        case 0xC:  // HALT: Stop program execution
            std::cout << "Program halted." << std::endl;
            return -1;
        default:
            std::cout << "Unknown opcode: " << opcode << std::endl;
            return -1;  // Return error for unknown opcode
    }
    return 0;
}

int CPU::runNextStep(Memory& memory) {
    fetch(memory);  // Fetch instruction
    auto [opcode, operands] = decode();  // Decode instruction
    return execute(opcode, operands, memory);  // Execute instruction
}

const Register& CPU::getRegister() const {
    return reg;
}
