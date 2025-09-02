//
// Created by Mikey on 9/2/2025.
//
#ifndef PASSWORDSAVE_H
#define PASSWORDSAVE_H

#include <string>

namespace PasswordSave {
    std::string uitob26(unsigned int input);
    unsigned int b26toui(const std::string& input);

}

#endif //PASSWORDSAVE_H
