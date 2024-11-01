#ifndef MACHINE_H
#define MACHINE_H

#include "CPU.h"
#include "Memory.h"

class Machine {
private:
    CPU processor;
    Memory memory;

public:
    Machine();
    void loadProgramFile(const std::string& program);
    void outputState() const;
    int executeNextInstruction();
};

#endif
