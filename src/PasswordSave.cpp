//
// Created by Mikey on 9/2/2025.
//
#include <string>
#include <cmath> // Would be nice if this could be replaced

namespace PasswordSave {
    std::string uitob26(unsigned int input) {
        constexpr int base = 26;
        std::string output = "AAAAAAA"; // TODO: This shouldn't be hard coded.

        // Finds the maximum necessary exponent
        int exponent = 0;
        while (input > std::pow(base, exponent++)){};
        --exponent;

        size_t idx = 6;
        while (input != 0) {
            const unsigned int remainder = input % base;
            input /= base;

            output[idx--] = static_cast<char>(remainder + 'A');
        }

        return output;
    }

    unsigned int b26toui(const std::string& input) {
        unsigned int output = 0;

        unsigned int place = input.length()-1;
        for (const auto v: input) {
            const unsigned int val = static_cast<unsigned int>(v) - 'A';
            output += val * static_cast<unsigned int>(std::pow(26, place--));
        }

        return output;
    }
}