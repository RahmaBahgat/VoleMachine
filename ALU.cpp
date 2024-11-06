//
// Created by habeb on 11/6/2024.
//

#include "ALU.h"
#include <string>
#include <cmath>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;
int ALU::BinaryToHex(const std::string& binary) {
    int hexValue = 0;
    int length = binary.length();
    // Process the binary string in chunks of 4 bits
    for (int i = 0; i < length; i += 4) {
        // Get 4 bits, if not enough bits left, pad with zeros
        string fourBits = binary.substr(i, 4);
        if (fourBits.length() < 4) {
            fourBits = std::string(4 - fourBits.length(), '0') + fourBits; // pad with leading zeros
        }
        // Convert 4-bit binary string to decimal
        int decimalValue = std::bitset<4>(fourBits).to_ulong();
        // Update the hexValue
        hexValue = (hexValue << 4) | decimalValue; // Shift hexValue left by 4 bits and add decimalValue
    }
    return hexValue; // Return the accumulated integer value
}
int ALU::hexToDec(const string& hexStr) {
    int value = 0;
    int base = 1;
    // Loop through the string from right to left
    for (int i = hexStr.size() - 1; i >= 0; i--) {
        char hexDigit = hexStr[i];  // Get the current character (hex digit)
        int decimalDigit;
        // Check if the digit is a number
        if (hexDigit >= '0' && hexDigit <= '9') {
            decimalDigit = hexDigit - '0';
        }
        // Check if the digit is a letter (A-F or a-f)
        else if (hexDigit >= 'A' && hexDigit <= 'F') {
            decimalDigit = hexDigit - 'A' + 10;
        }
        else if (hexDigit >= 'a' && hexDigit <= 'f') {
            decimalDigit = hexDigit - 'a' + 10;
        }
        value += decimalDigit * base;
        base *= 16;
    }
    return value;
}
string ALU::decToHex(int decimal) {
    string hex = "";
    while (decimal > 0) {
        int remainder = decimal % 16;//get reminder
        if (remainder < 10) {// cheek it can  be the same number in hexadecimal
            hex += (remainder + '0'); // Convert to character
        }else { // it needs to convert to letter
            hex += (remainder - 10 + 'A'); // Convert to character A-F by -10(to be suitable number from 0 to 5 ) + 65(to convert it to letter)
        }
        decimal /= 16;
    }
    reverse(hex.begin(), hex.end()); // Reverse to get the correct order
    return hex;
}

bool ALU::isValid(const string& hexStr) {//cheek valid hexa decimal
    for (char c : hexStr) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    return true;
}

string ALU::hexToBinary(const string& hex){
    string binary = "";
    for(int i = 0 ; i < hex.size() ; i++){
        int dec  = 0 ;
        if(hex[i] >='0' && hex[i] <= '9'){
            dec = hex[i] - '0';//convert to number
        }else{
            dec = hex[i] -'A' + 10;//convert to numbers from 10 to 15
        }
        binary += bitset<4>(dec).to_string();//set in 4 bits
    }
    return binary;
}

void ALU::OR(int regR, int regS, int regT, Register& reg){
    string b1 = hexToBinary(reg.getCell(regS));
    string b2 = hexToBinary(reg.getCell(regT));
    // Perform bitwise OR operation on each bit
    string resultBinary = "";
    for (int i = 0; i < b1.size(); i++) {
        if (b1[i] == '1' || b2[i] == '1') {
            resultBinary += '1';
        } else {
            resultBinary += '0';
        }
    }
    // Convert the binary result back to hex
    int resultDecimal = BinaryToHex(resultBinary);
    string resultHex = decToHex(resultDecimal);

    reg.setCell(regR, resultHex);
}

void ALU::AND(int regR, int regS, int regT, Register& reg) {
    string b1 = hexToBinary(reg.getCell(regS));
    string b2 = hexToBinary(reg.getCell(regT));

    //Perform bitwise AND operation on each bit
    string resultBinary = "";
    for (int i = 0; i < b1.size(); i++) {
        if (b1[i] == '1' && b2[i] == '1') {
            resultBinary += '1';
        } else {
            resultBinary += '0';
        }
    }

    //Convert the binary result back to hex
    int resultDecimal = BinaryToHex(resultBinary);
    string resultHex = decToHex(resultDecimal);

    reg.setCell(regR, resultHex);
}

void ALU::XOR(int regR, int regS, int regT, Register& reg) {
    string b1 = hexToBinary(reg.getCell(regS));
    string b2 = hexToBinary(reg.getCell(regT));

    //Perform bitwise XOR operation on each bit
    string resultBinary = "";
    for (int i = 0; i < b1.size(); i++) {
        if (b1[i] != b2[i]) {
            resultBinary += '1';
        } else {
            resultBinary += '0';
        }
    }


    int resultDecimal =  BinaryToHex(resultBinary);
    string resultHex = decToHex(resultDecimal);

    reg.setCell(regR, resultHex);
}



void ALU::add(int regR, int regS, int regT, Register& reg) {
    // Retrieve values from registers and convert hex to integers
    int valueS = hexToDec(reg.getCell(regS));
    int valueT = hexToDec(reg.getCell(regT));

    // Convert values to two's complement signed integers
    if (valueS & 0x80) valueS -= 0x100;
    if (valueT & 0x80) valueT -= 0x100;

    // Perform addition
    int result = valueS + valueT;

    // Handle overflow for 8-bit result
    if (result > 127) result -= 256;     // Overflow for positive
    else if (result < -128) result += 256; // Overflow for negative

    // Convert result back to 8-bit two's complement format
    result &= 0xFF;

    reg.setCell(regR , decToHex(result) );
}

void ALU::addFloatingPoint(int regR, int regS, int regT, Register& reg) {
    //Get the values from registers and convert them to hex
    int valueS = hexToDec(reg.getCell(regS));
    int valueT = hexToDec(reg.getCell(regT));

    //Extract parts from each register (sign, exponent, mantissa)
    int signS = (valueS >> 7) & 1;
    int exponentS = (valueS >> 4) & 0x7;
    int mantissaS = valueS & 0xF;

    int signT = (valueT >> 7) & 1;
    int exponentT = (valueT >> 4) & 0x7;
    int mantissaT = valueT & 0xF;

    //Convert mantissas to floating-point numbers
    float floatMantissaS = 1.0f + mantissaS / 16.0f;
    float floatMantissaT = 1.0f + mantissaT / 16.0f;

    if (exponentS > exponentT) {
        floatMantissaT /= (1 << (exponentS - exponentT));
        exponentT = exponentS;
    } else if (exponentT > exponentS) {
        floatMantissaS /= (1 << (exponentT - exponentS));
        exponentS = exponentT;
    }

    //Add or subtract the mantissas based on the signs
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

    int resultExponent = exponentS;
    if (resultMantissa >= 2.0f) {
        resultMantissa /= 2.0f;
        resultExponent++;
    } else if (resultMantissa < 1.0f) {
        resultMantissa *= 2.0f;
        resultExponent--;
    }

    //Convert the result back to 8-bit format
    int resultMantissaInt = static_cast<int>((resultMantissa - 1.0f) * 16) & 0xF;
    int resultExponentInt = resultExponent & 0x7;
    int result = (resultSign << 7) | (resultExponentInt << 4) | resultMantissaInt;

    reg.setCell(regR , decToHex(result) );
}
void ALU::Rotate(int regR, int steps, Register& reg) {
    int value = hexToDec(reg.getCell(regR));

    //Ensure steps are within the 8-bit limit
    steps = steps % 8;

    //Perform the cyclic right rotation
    int rotatedValue = (value >> steps) | (value << (8 - steps)) & 0xFF;

    //Convert the rotated value back to hex
    string rotatedHex = decToHex(rotatedValue);

    reg.setCell(regR,rotatedHex);
}
