#ifndef CU_H
#define CU_H

#include "Register.h"
#include "Memory.h"

class CU {
public:
    void load(int idxReg, int intMem, Register& reg, Memory& mem);
    void loadImmediate(int idxReg, const std::string& val, Register& reg);
    void store(int idxReg, int idxMem, Register& reg, Memory& mem);
    void move(int idxReg1, int idxReg2, Register& reg);
};

#endif
