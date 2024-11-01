#include "Machine.h"
#include <iostream>
#include <iomanip>

Machine::Machine() : processor(), memory(256) {}

void Machine::loadProgramFile(const std::string& program) {
    std::istringstream programStream(program);
    std::string line;
    int address = 0;

    while (std::getline(programStream, line) && address < 256) {
        if (!line.empty() && line.length() == 4) {
            // Split the 4-digit instruction into two 2-digit parts
            std::string firstPart = line.substr(0, 2);
            std::string secondPart = line.substr(2, 2);

            memory.setCell(address++, firstPart);   // Store the first 2 digits
            if (address < 256) {                    // Check to avoid overflow
                memory.setCell(address++, secondPart);  // Store the second 2 digits
            }
        }
    }
}

void Machine::outputState() const {
    std::cout << "\n--- Machine State ---" << std::endl;

    // Output Register State
    std::cout << "Registers:" << std::endl;
    for (int i = 0; i < 16; ++i) {
        std::cout << "R" << std::hex << i << ": " << processor.getRegister().getCell(i) << " ";
        if ((i + 1) % 8 == 0) std::cout << std::endl;  // Print 8 registers per line
    }

    // Output Memory State
    std::cout << "\nMemory:" << std::endl;
    for (int i = 0; i < 256; ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << i << ": " << memory.getCell(i) << " ";
        if ((i + 1) % 8 == 0) std::cout << std::endl;  // Print 8 memory cells per line
    }
    std::cout << "---------------------\n" << std::endl;
}

int Machine::executeNextInstruction() {
    return processor.runNextStep(memory);
}
