#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <vector>

using namespace std;

class Register {
private:
    vector<string> memory;
    int size;

public:
    Register(int size = 16);
    string getCell(int address) const;
    void setCell(int address, const string& val);
};

#endif
