//
// Created by Mikey on 9/2/2025.
//
#include <string> // Would be nice if this could be replaced
#include <cmath> // and this
#include <algorithm> // and this too

namespace PasswordSave {

    namespace {
        std::string uitobX(unsigned int input, const unsigned int BASE) {
            std::string output;

            // Finds the maximum necessary exponent
            int exponent = 0;
            while (input > std::pow(BASE, exponent++)){};
            --exponent;

            while (input != 0) {
                const unsigned int remainder = input % BASE;
                input /= BASE;

                output += static_cast<char>(remainder + 'A');
            }

            std::ranges::reverse(output);

            return output;
        }

        unsigned int bXtoui(const std::string& input, const unsigned int BASE) {
            unsigned int output = 0;

            unsigned int place = input.length()-1;
            for (const auto v: input) {
                const unsigned int val = static_cast<unsigned int>(v) - 'A';
                output += val * static_cast<unsigned int>(std::pow(BASE, place--));
            }

            return output;
        }
    }

    std::string uitob26(const unsigned int input) {
        return uitobX(input, 26);
    }

    unsigned int b26toui(const std::string& input) {
        return bXtoui(input, 26);
    }
}
