#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <vector>

class Register {
private:
    std::vector<std::string> memory;
    int size;

public:
    Register(int size = 16);
    std::string getCell(int address) const;
    void setCell(int address, const std::string& val);
};

#endif
