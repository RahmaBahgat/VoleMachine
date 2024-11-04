//
// Created by habeb on 11/4/2024.
//

#include "ALU.h"
#include "ALU.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

int ALU::hexToDec(const std::string& hexStr) {
    int decimal = 0;
    int len = hexStr.length();
    for (int i = 0; i < len; i++) { // loop on hexadecinal
        char c = hexStr[len - i - 1]; //get elements of hexadecimal from the end
        int value;
        if (c >= '0' && c <= '9') {//cheek if it is number
            value = c - '0'; // Convert to integer
        }else { // if it is charachter
            value = c - 'A' + 10; // Convert A-F to 10-15 by -65 (return it to integer)+ 10(to be the coresponding integer)
        }
        decimal += value * pow(16, i); // Add the value multiplied by the power of 16
    }
    return decimal;
}

std::string ALU::decToHex(int decimal) {
    string hex = "";
    while (decimal > 0) {
        int remainder = decimal % 16;//get reminder
        if (remainder < 10) {// cheek it can  be the same number in hexadecimal
            hex += (remainder + 48); // Convert to character to be stored in string
        }else { // it needs to convert to letter
            hex += (remainder - 10 + 'A'); // Convert to character A-F by -10(to be sutibale number from 0 to 5 ) + 65(to convert it to letter)
        }
        decimal /= 16;
    }
    reverse(hex.begin(), hex.end()); // Reverse to get the correct order
    return hex;
}

bool ALU::isValid(const std::string& hexStr) {
    bool flage = true;
    for(int i = 0 ; i < hexStr.size() ; i++){
        if((hexStr[i] <= '9' && hexStr[i] >= '0') || (hexStr[i] >='A' && hexStr[i] <= 'F')){ // cheek that every char is between 0 & 9 or A & F
            continue;
        }else{
            flage = false;
            return flage;
        }
    }
    return flage;
}

void ALU::add(int regR, int regS, int regT, Register& reg) {
    //A3 -> 10 3  1010 0011 
    // Retrieve values from registers and convert hex to integers
    int valueS = hexToDec(reg.getCell(regS));
    int valueT = hexToDec(reg.getCell(regT));
    //int valueS = std::stoi(reg.getCell(regS), nullptr, 16);
    //int valueT = std::stoi(reg.getCell(regT), nullptr, 16);

    // Convert values to two's complement signed integers
    if (valueS & 0x80) valueS -= 0x100;  // If MSB is set, make valueS negative
    if (valueT & 0x80) valueT -= 0x100;  // If MSB is set, make valueT negative

    // Perform addition
    int result = valueS + valueT;

    // Handle overflow for 8-bit result
    if (result > 127) result -= 256;     // Overflow for positive
    else if (result < -128) result += 256; // Overflow for negative

    // Convert result back to 8-bit two's complement format
    result &= 0xFF;  // Mask to 8 bits

    // Convert result to hex and store it in register R
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << (result & 0xFF);
    reg.setCell(regR, ss.str());
}

void ALU::addFloatingPoint(int regR, int regS, int regT, Register& reg) {
    // Step 1: Get the values from registers
    int valueS = std::stoi(reg.getCell(regS), nullptr, 16);
    int valueT = std::stoi(reg.getCell(regT), nullptr, 16);

    // Step 2: Extract parts from each register (sign, exponent, mantissa)
    int signS = (valueS >> 7) & 1;
    int exponentS = (valueS >> 4) & 0x7;
    int mantissaS = valueS & 0xF;

    int signT = (valueT >> 7) & 1;
    int exponentT = (valueT >> 4) & 0x7;
    int mantissaT = valueT & 0xF;

    // Step 3: Convert mantissas to floating-point numbers
    float floatMantissaS = 1.0f + mantissaS / 16.0f;
    float floatMantissaT = 1.0f + mantissaT / 16.0f;

    // Step 4: Align the exponents
    if (exponentS > exponentT) {
        floatMantissaT /= (1 << (exponentS - exponentT));
        exponentT = exponentS;
    } else if (exponentT > exponentS) {
        floatMantissaS /= (1 << (exponentT - exponentS));
        exponentS = exponentT;
    }

    // Step 5: Add or subtract the mantissas based on the signs
    float resultMantissa;
    int resultSign;
    if (signS == signT) {
        resultMantissa = floatMantissaS + floatMantissaT;
        resultSign = signS;
    } else {
        if (floatMantissaS > floatMantissaT) {
            resultMantissa = floatMantissaS - floatMantissaT;
            resultSign = signS;
        } else {
            resultMantissa = floatMantissaT - floatMantissaS;
            resultSign = signT;
        }
    }

    // Step 6: Normalize the result if necessary
    int resultExponent = exponentS;
    if (resultMantissa >= 2.0f) {
        resultMantissa /= 2.0f;
        resultExponent++;
    } else if (resultMantissa < 1.0f) {
        resultMantissa *= 2.0f;
        resultExponent--;
    }

    // Step 7: Convert the result back to 8-bit format
    int resultMantissaInt = static_cast<int>((resultMantissa - 1.0f) * 16) & 0xF;
    int resultExponentInt = resultExponent & 0x7;
    int result = (resultSign << 7) | (resultExponentInt << 4) | resultMantissaInt;

    // Step 8: Store the result in register R
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << result;
    reg.setCell(regR, ss.str());
}
