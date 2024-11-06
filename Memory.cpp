#include "Memory.h"

Memory::Memory(int size) : size(size), memory(size, "00") {}

string Memory::getCell(int address) const {
    return memory[address];
}

void Memory::setCell(int address, const string& val) {
    memory[address] = val;
}
