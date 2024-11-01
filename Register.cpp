#include "Register.h"

Register::Register(int size) : size(size), memory(size, "00") {}

std::string Register::getCell(int address) const {
    return memory[address];
}

void Register::setCell(int address, const std::string& val) {
    memory[address] = val;
}
