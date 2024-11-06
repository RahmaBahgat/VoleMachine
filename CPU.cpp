#include "CPU.h"
#include <iostream>

using namespace std;

CPU::CPU() : programCounter(0), reg(Register()) {}

void CPU::fetch(Memory& memory) {
    // Fetch two memory cells to form a 4-digit instruction
    string firstHalf = memory.getCell(programCounter);
    string secondHalf = memory.getCell(programCounter + 1);

    instructionRegister = firstHalf + secondHalf; // Combine cells for full instruction
    programCounter += 2; // Advance by two cells for the next instruction
}

pair<string, string> CPU::decode() {
    // Split instruction into opcode and operands
    return {instructionRegister.substr(0, 1), instructionRegister.substr(1)};
}

int CPU::execute(const string& opcode, const string& operands, Memory& memory) {
    if (!ALU::isValid(opcode) || !ALU::isValid(operands)) {
        cout << "Invalid hexadecimal input in instruction: " << opcode << operands << endl;
        return -1;  // Or any error code indicating invalid input
    }
    int op = alu.hexToDec(opcode);
    int regR = alu.hexToDec(operands.substr(0, 1));
    int regS, regT, address;

    switch (op) {
        case 0x1:  // LOAD RXY: Load value from memory at address XY into register R
            address = alu.hexToDec(operands.substr(1, 2));
            cu.load(regR, address, reg, memory);
            break;
        case 0x2:  // LOAD immediate RXY: Load immediate value XY directly into register R
            cu.loadImmediate(regR, operands.substr(1, 2), reg);
            break;
        case 0x3:  // STORE RXY: Store value in register R to memory at address XY
            address = alu.hexToDec(operands.substr(1, 2));
            cu.store(regR, address, reg, memory);
            break;
        case 0x4:  // MOVE 0RS: Move value from register R to register S
            regS = alu.hexToDec(operands.substr(1, 1));
            cu.move(regR, regS, reg);
            break;
        case 0x5:  // ADD RST: Integer addition of registers S and T, store result in R
            regS = alu.hexToDec(operands.substr(1, 1));
            regT = alu.hexToDec(operands.substr(2, 1));
            alu.add(regR, regS, regT, reg);
            break;
        case 0x6:  // Floating-point addition of registers S and T, store result in R
            regS = alu.hexToDec(operands.substr(1, 1));
            regT = alu.hexToDec(operands.substr(2, 1));
            alu.addFloatingPoint(regR, regS, regT, reg);
            break;
        case 0x7: //doing OR operation bitwise for register S and T, store it in R
            regS = alu.hexToDec(operands.substr(1, 1));
            regT = alu.hexToDec(operands.substr(2, 1));
            alu.OR(regR, regS, regT, reg);
            break;
        case 0x8://doing AND operation bitwise for register S and T, store it in R
            regS = alu.hexToDec(operands.substr(1, 1));
            regT = alu.hexToDec(operands.substr(2, 1));
            alu.AND(regR, regS, regT, reg);
            break;
        case 0x9://doing XOR operation bitwise for register S and T, store it in R
            regS = alu.hexToDec(operands.substr(1, 1));
            regT = alu.hexToDec(operands.substr(2, 1));
            alu.XOR(regR, regS, regT, reg);
            break;
        case 0xA: //Rotate the content in the Register R cyclically right by register T steps
            regR = alu.hexToDec(operands.substr(1, 1));
            regT = alu.hexToDec(operands.substr(2, 1));
            alu.Rotate(regR, regT, reg);
        case 0xB:  // JUMP RXY: Jump to address XY if register R equals register 0
            address = alu.hexToDec(operands.substr(1, 2));
            if (reg.getCell(regR) == reg.getCell(0)) {
                programCounter = address;
                return 0;  // Return to indicate jump occurred
            }
            break;
        case 0xD:  // Conditional jump if register R > register 0
            address = alu.hexToDec(operands.substr(1, 2));
            {
                int valueR = alu.hexToDec(reg.getCell(regR));
                int value0 = alu.hexToDec(reg.getCell(0));

                // Interpret as two's complement signed integers
                if (valueR & 0x80) valueR -= 0x100;
                if (value0 & 0x80) value0 -= 0x100;

                if (valueR > value0) {
                    programCounter = address;  // Jump to address XY
                    return 0;
                }
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

const Register& CPU::getRegister() const {
    return reg;
}
int CPU::runNextStep(Memory& memory) {
    fetch(memory);
    auto [opcode, operands] = decode();
    return execute(opcode, operands, memory);
}
