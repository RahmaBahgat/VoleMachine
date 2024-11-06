#include "Machine.h"
#include <iostream>
#include <iomanip>
#include <cctype>

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

bool Machine::isASCII(const string& str) const {
    for (char c : str) {
        if (!isprint(c)) return false;  // Ensure all characters are printable ASCII
    }
    return true;
}

bool Machine::isHex(const string& str) const {
    for (char c : str) {
        if (!isxdigit(c)) return false;  // Non-hex character found
    }
    return true;
}

void Machine::outputState() const {
    cout << "\n--- Machine State ---" << endl;

    // Print Register State
    cout << "Registers:" << endl;
    for (int i = 0; i < 16; ++i) {
        string regValue = processor.getRegister().getCell(i);

        // Detect type and display accordingly
        if (isASCII(regValue)) {
            cout << "R" << hex << i << ": HEX = '" << regValue << "', ASCII = ";
            for (char c : regValue) {
                cout << dec << int(c) << " ";  // Print ASCII code in decimal
            }
            cout << endl;
        } else if (isHex(regValue)) {
            cout << "R" << hex << i << ": HEX = " << regValue << endl;
        } else {
            cout << "R" << hex << i << ": UNRECOGNIZED FORMAT" << endl;
        }

        if ((i + 1) % 8 == 0) cout << endl;
    }

    // Print Memory State
    cout << "\nMemory:" << endl;
    for (int address = 0; address < 256; ++address) {
        string memValue = memory.getCell(address);

        // Detect type and display accordingly
        if (isASCII(memValue)) {
            cout << "Address " << hex << address << ": HEX = '" << memValue << "', ASCII = ";
            for (char c : memValue) {
                cout << dec << int(c) << " ";  // Print ASCII code in decimal
            }
            cout << endl;
        } else if (isHex(memValue)) {
            cout << "Address " << hex << address << ": HEX = " << memValue << endl;
        } else {
            cout << "Address " << hex << address << ": UNRECOGNIZED FORMAT" << endl;
        }

        if ((address + 1) % 8 == 0) cout << endl;
    }
}

int Machine::executeNextInstruction() {
    return processor.runNextStep(memory);
}
