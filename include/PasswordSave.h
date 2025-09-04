//
// Created by Mikey on 9/2/2025.
//
#ifndef PASSWORDSAVE_H
#define PASSWORDSAVE_H

#include <string>

namespace PasswordSave {
    template<typename T>
    std::string uitob26(T input);

    template<typename T>
    T b26toui(const std::string& input);

    // Aliases
    template<typename T>
    constexpr std::string(*serialize)(T) = &uitob26<T>;

    template<typename T>
    constexpr T(*deserialize)(const std::string&) = &b26toui<T>;

}

#include "PasswordSave.cpp"

#endif //PASSWORDSAVE_H
