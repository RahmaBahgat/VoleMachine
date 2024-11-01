#include "ALU.h"
#include <sstream>
#include <iomanip>

int ALU::hexToDec(const std::string& hexStr) {
    int value;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> value;
    return value;
}

std::string ALU::decToHex(int decimal) {
    std::stringstream ss;
    ss << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << decimal;
    return ss.str();
}

bool ALU::isValid(const std::string& hexStr) {
    std::stringstream ss;
    ss << std::hex << hexStr;
    int value;
    return (ss >> value) ? true : false;
}

void ALU::add(int regR, int regS, int regT, Register& reg) {
    // Retrieve integer values from registers
    int valueS = std::stoi(reg.getCell(regS), nullptr, 16);
    int valueT = std::stoi(reg.getCell(regT), nullptr, 16);

    // Perform integer addition
    int result = valueS + valueT;

    // Convert result back to hexadecimal, ensure two-digit format
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << (result & 0xFF);
    reg.setCell(regR, ss.str());
}

void ALU::addFloatingPoint(int regR, int regS, int regT, Register& reg) {
    // Retrieve floating-point values from registers
    int valueS = std::stoi(reg.getCell(regS), nullptr, 16);
    int valueT = std::stoi(reg.getCell(regT), nullptr, 16);

    // Convert values to floating-point (assume fixed-point or simple conversion)
    float floatValS = static_cast<float>(valueS) / 16.0;
    float floatValT = static_cast<float>(valueT) / 16.0;

    // Perform floating-point addition
    float result = floatValS + floatValT;

    // Convert the result back to hexadecimal and store in register R
    int hexResult = static_cast<int>(result * 16); // Simple fixed-point scaling

    std::stringstream ss;
    ss << std::hex << hexResult;
    std::string resultHex = ss.str();

    // Ensure it’s formatted to two hex digits
    if (resultHex.length() < 2) resultHex = "0" + resultHex;

    reg.setCell(regR, resultHex);
}
