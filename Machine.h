#ifndef MACHINE_H
#define MACHINE_H

#include "CPU.h"
#include "Memory.h"

using namespace std;

class Machine {
private:
    CPU processor;
    Memory memory;
    bool isASCII(const string& str) const;
    bool isHex(const string& str) const;

public:
    Machine();
    void loadProgramFile(const string& program);
    void outputState() const;
    int executeNextInstruction();


};

#endif
