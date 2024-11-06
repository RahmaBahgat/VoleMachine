#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

using namespace std;

class Memory {
private:
    vector<string> memory;
    int size;

public:
    Memory(int size = 256);
    string getCell(int address) const;
    void setCell(int address, const string& val);
};

#endif
