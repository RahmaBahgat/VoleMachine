#include "Machine.h"
#include <iostream>
#include <iomanip>

using namespace std;

Machine::Machine() : processor(), memory(256) {}

void Machine::loadProgramFile(const string& program) {
    istringstream programStream(program);
    string line;
    int address = 0;

    while (getline(programStream, line) && address < 256) {
        if (!line.empty() && line.length() == 4) {
            // Split the 4-digit instruction into two 2-digit parts
            string firstPart = line.substr(0, 2);
            string secondPart = line.substr(2, 2);

            memory.setCell(address++, firstPart);   // Store the first 2 digits
            if (address < 256) {                    // Check to avoid overflow
                memory.setCell(address++, secondPart);  // Store the second 2 digits
            }
        }
    }
}

void Machine::outputState() const {
    cout << "\n--- Machine State ---" << endl;

    // Output Register State
    cout << "Registers:" << endl;
    for (int i = 0; i < 16; ++i) {
        cout << "R" << hex << i << ": " << processor.getRegister().getCell(i) << " ";
        if ((i + 1) % 8 == 0) cout << endl;  // Print 8 registers per line
    }

    // Output Memory State
    cout << "\nMemory:" << endl;
    for (int i = 0; i < 256; ++i) {
        cout << setw(2) << setfill('0') << hex << i << ": " << memory.getCell(i) << " ";
        if ((i + 1) % 8 == 0) cout << endl;  // Print 8 memory cells per line
    }
    cout << "---------------------\n" << endl;
}

int Machine::executeNextInstruction() {
    return processor.runNextStep(memory);
}
