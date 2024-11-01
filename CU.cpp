#include "CU.h"
#include <iostream>

void CU::load(int idxReg, int intMem, Register& reg, Memory& mem) {
    reg.setCell(idxReg, mem.getCell(intMem));
}

void CU::loadImmediate(int idxReg, const std::string& val, Register& reg) {
    reg.setCell(idxReg, val);
}

void CU::store(int idxReg, int idxMem, Register& reg, Memory& mem) {
    mem.setCell(idxMem, reg.getCell(idxReg));
}

void CU::move(int idxReg1, int idxReg2, Register& reg) {
    reg.setCell(idxReg2, reg.getCell(idxReg1));
}

int CU::jump(int idxReg, int idxMem, Register& reg, int PC) {
    if (reg.getCell(idxReg) == reg.getCell(0))
        return idxMem;
    return PC + 1;
}

int CU::halt() {
    std::cout << "Program halted." << std::endl;
    return -1;
}
