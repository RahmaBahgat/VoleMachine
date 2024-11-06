#include "MainUI.h"
#include <iostream>
#include <fstream>

using namespace std;

MainUI::MainUI() {}

void MainUI::displayMenu() {
    cout << "Welcome to the Vole Machine Simulator" << endl;
    cout << "1. Enter a program file" << endl;
    cout << "2. Enter instructions manually" << endl;
    cout << "3. Output Machine State" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

void MainUI::inputFileName() {
    string fileName;
    cout << "Enter the program file name: ";
    cin >> fileName;

    ifstream file(fileName);
    if (file) {
        string program((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        machine.loadProgramFile(program);
        cout << "Program loaded successfully from file." << endl;
    } else {
        cout << "Failed to open file." << endl;
    }
}

void MainUI::inputInstruction() {
    string instruction;
    cout << "Enter the program instructions (type 'C000' to finish):" << endl;
    string program;
    while (true) {
        cin >> instruction;
        if (instruction == "C000") break;
        program += instruction + "\n";
    }
    machine.loadProgramFile(program);
    cout << "Program loaded successfully from manual input." << endl;
}

void MainUI::runProgram() {
    int result;
    do {
        result = machine.executeNextInstruction();
    } while (result != -1);  // -1 indicates halt
    cout << "Program execution completed." << endl;
}

char MainUI::inputChoice() {
    char choice;
    cin >> choice;
    return choice;
}

void MainUI::OutputMachineState() {
    return machine.outputState();
}
