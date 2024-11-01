#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

class Memory {
private:
    std::vector<std::string> memory;
    int size;

public:
    Memory(int size = 256);
    std::string getCell(int address) const;
    void setCell(int address, const std::string& val);
};

#endif
