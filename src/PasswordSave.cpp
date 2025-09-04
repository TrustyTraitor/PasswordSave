//
// Created by Mikey on 9/2/2025.
//
#include <string> // Would be nice if this could be replaced
#include <cmath> // and this
#include <algorithm> // and this too

namespace PasswordSave {

    namespace {
        template<unsigned int BASE, typename T>
        std::string uitobX(T input) {
            std::string output;

            // Finds the maximum necessary exponent
            unsigned int exponent = 0;
            while (input > std::pow(BASE, exponent++)){};
            --exponent;

            while (input != 0) {
                const unsigned int remainder = input % BASE;
                input /= BASE;

                output += static_cast<char>(remainder + 'A');
            }

            //
            std::ranges::reverse(output);

            return output;
        }

        template<unsigned int BASE, typename T>
        T bXtoui(const std::string& input) {
            T output = 0;

            unsigned int place = input.length()-1;
            for (const auto v: input) {
                const unsigned int val = static_cast<unsigned int>(v) - 'A';
                output += val * static_cast<unsigned int>(std::pow(BASE, place--));
            }

            return output;
        }
    }

    template<typename T>
    std::string uitob26(const T input) {
        return uitobX<26, T>(input);
    }

    template<typename T>
    T b26toui(const std::string& input) {
        return bXtoui<26, T>(input);
    }

}
