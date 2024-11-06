#ifndef MAINUI_H
#define MAINUI_H

#include "Machine.h"
#include <string>

class MainUI {
private:
    Machine machine;

public:
    MainUI();
    void displayMenu();
    void inputFileName();
    void inputInstruction();
    void runProgram();
    char inputChoice();
    void OutputMachineState();
};

#endif
