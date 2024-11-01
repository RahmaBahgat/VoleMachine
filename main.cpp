#include "MainUI.h"
#include <iostream>

int main() {
    MainUI ui;
    char choice;

    do {
        ui.displayMenu();
        choice = ui.inputChoice();

        switch (choice) {
            case '1':
                ui.inputFileName();
                break;
            case '2':
                ui.inputInstruction();
                break;
            case '3':
                ui.runProgram();
                break;
            case '4':
                std::cout << "Exiting the simulator." << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
        }
    } while (choice != '4');

    return 0;
}
