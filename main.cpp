#include <iostream>
#include <string>

char digitToChar(uint8_t b) {
    static const char digits[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    static const auto nDigits = sizeof(digits) / sizeof(digits[0]) - 1;
    if (b >= nDigits) return '?';
    return digits[b];
}

std::string uintToString(uint32_t num, uint8_t base) {
    std::string result;
    while (num > 0) {
        auto reminder = num % base;
        result.insert(0, 1, digitToChar(reminder));
        num /= base;
    }
    return result;
}

std::string doubleToString(double num, uint8_t base, uint8_t precision) {
    std::string result;
    auto integer = static_cast<uint32_t>(num);
    result += uintToString(integer, base);
    result += ".";
    auto fractional = num - integer;
    for (auto i = 0; (i < precision) && (fractional > 0); i++) {
        auto scaled = fractional * base;
        auto digit = static_cast<uint8_t>(scaled);
        fractional = scaled - digit;
        result += digitToChar(digit);
    }
    return result;
}

int main() {
    double num1 = 35.141, num2 = 35.625;
    auto precision = 15;
    for (auto base = 2; base <= 36; base++) {
        std::cout << base
                  << ":\t"
                  << doubleToString(num1, base, precision)
                  << "\t"
                  << doubleToString(num2, base, precision)
        << std::endl;
    }
    return 0;
}
