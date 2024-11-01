#include "MainUI.h"
#include <iostream>
#include <fstream>

MainUI::MainUI() : enterFileOrInstructions(false) {}

void MainUI::displayMenu() {
    std::cout << "Welcome to the Vole Machine Simulator" << std::endl;
    std::cout << "1. Enter a program file" << std::endl;
    std::cout << "2. Enter instructions manually" << std::endl;
    std::cout << "3. Run the program" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

void MainUI::inputFileName() {
    std::string fileName;
    std::cout << "Enter the program file name: ";
    std::cin >> fileName;

    std::ifstream file(fileName);
    if (file) {
        std::string program((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        machine.loadProgramFile(program);
        std::cout << "Program loaded successfully from file." << std::endl;
    } else {
        std::cout << "Failed to open file." << std::endl;
    }
}

void MainUI::inputInstruction() {
    std::string instruction;
    std::cout << "Enter the program instructions (type 'END' to finish):" << std::endl;
    std::string program;
    while (true) {
        std::cin >> instruction;
        if (instruction == "END") break;
        program += instruction + "\n";
    }
    machine.loadProgramFile(program);
    std::cout << "Program loaded successfully from manual input." << std::endl;
}

void MainUI::runProgram() {
    int result;
    do {
        result = machine.executeNextInstruction();
        machine.outputState();
    } while (result != -1);  // -1 indicates halt
    std::cout << "Program execution completed." << std::endl;
}

char MainUI::inputChoice() {
    char choice;
    std::cin >> choice;
    return choice;
}
