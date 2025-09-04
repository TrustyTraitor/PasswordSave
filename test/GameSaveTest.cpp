//
// Created by Mikey on 9/2/2025.
//
#include <cstdint>
#include <bitset>
#include <format>
#include <iostream>

#include "PasswordSave.h"

namespace Savedata {
    #define uint unsigned int
    union SaveData {
        struct {
            uint level : 4 = 0; // Max level is 15; Level should maybe be lower, like 3 bits to match with dungeon count.
            uint health : 3 = 0; // Max hearts is 7

            uint potionQuality: 2 = 0; // Max potion quality is 3
            uint potionCount : 3 = 0; // Max potion count is 7

            // Sword/Armor follows basc quality for 0-3, beyond that is unique weapons/armors.
            uint swordQuality : 3 = 0; // Max sword quality is 7
            uint armorQuality : 3 = 0; // Max armor quality is 7

            // Main dungeons are linear
            uint storyDungeonCompletion : 3 = 0; // Max (linear) dungeons are 7.
            /* If dungeons are non-linear, then individual bits will be required. This will also take more bits.
            * uint storyDungeon1 : 1 = 0;
            * uint storyDungeon2 : 1 = 0;
            * uint storyDungeon3 : 1 = 0;
            * uint storyDungeon4 : 1 = 0;
             */

            // Simple boolean on if the dungeon has been completed.
            // Side dungeons are optional and may be completed in different orders, and as such, require separate boolean flags
            uint sideDungeon1 : 1 = 0;
            uint sideDungeon2 : 1 = 0;
            uint sideDungeon3 : 1 = 0;
            uint sideDungeon4 : 1 = 0;
            // 8 + 18 = 26 bit used above. 7 remaining
            // Maybe status effects? Side quests? Skills/Class?
            // Leaning towards Class: Classes could be linear, with new skills being obtained simply by leveling up.
            uint playerClass : 2 = 0;
        };

        std::uint32_t container;
    };

    inline std::string getQuality(const int quality) {
        switch (quality) {
            case 0:
                return "Common";
            case 1:
                return "Rare";
            case 2:
                return "Epic";
            case 3:
                return "Legendary";
            default:
                return "Fabled";
        }
    }

    inline void printSave(const SaveData SD) {
        std::cout
        << "Player Info:" << "\n"
        << " - Level: " << SD.level << " (Max: 15)"  << "\n"
        << " - Health: " << SD.health << " (Max: 7)" << "\n"
        << "Item Info:"
            << " Possible quality levels are: " << getQuality(0) << ", " << getQuality(1)
            << ", " << getQuality(2) << ", or " << getQuality(4) << "\n"
        << " - PotionCount: " << SD.potionCount << " (Max: 7)" << "\n"
        << " - PotionQuality: " << SD.potionQuality << " (" << getQuality(SD.potionQuality) << ") " << "\n"
        << " - Sword Quality: " << SD.swordQuality << " (" <<getQuality(SD.swordQuality) <<  ") " << "\n"
        << " - Armor Quality: " << SD.armorQuality << " (" << getQuality(SD.armorQuality) << ") " << "\n"
        << "Dungeons Completion: " << "\n"
        << " - " << SD.storyDungeonCompletion << "\n"
        << std::endl;
    }

    inline void printSaveTechnical(const SaveData SD) {
        std::cout << "Technical Info:" << std::endl;
        std::cout << "sizeof(SaveData): " << sizeof(SaveData) << "Bytes (" << sizeof(SaveData)*8 << "bits" << ")\n" << std::endl;


        std::cout << "Save/Password as:" << std::endl;
        std::cout << "\tBinary: " << std::bitset<sizeof(SD.container)*8>(SD.container) << std::endl;
        std::cout << "\t   Int: " << SD.container << std::endl;
        std::cout << "\t   Hex: " << std::format("{:x}", SD.container) << std::endl;

        const std::string password = PasswordSave::uitob26(SD.container);
        std::cout << "\n" << "Note: This isn't a standard base 26 that starts at 0. Instead 0 is represented as A" << std::endl;
        std::cout << "Base26 Password: " << password << std::endl;

        std::uint32_t deserializedSave = PasswordSave::b26toui(password);
        std::cout << "Deserialized Save: " << std::endl;
        std::cout << "\tBinary: " << std::bitset<sizeof(deserializedSave)*8>(deserializedSave) << std::endl;
        std::cout << "\t   Int: " << deserializedSave << std::endl;
        std::cout << "\t   Hex: " << std::format("{:x}", deserializedSave) << std::endl;
    }

}

int main() {

    // Some random fake save data
    constexpr Savedata::SaveData sd = {
        .level = 3,
        .health = 3,
        .potionQuality = 2,
        .potionCount = 6,
        .swordQuality = 3,
        .armorQuality = 4,
        .storyDungeonCompletion = 4,
        .sideDungeon1 = true,
        .sideDungeon2 = false,
        .sideDungeon3 = false,
        .sideDungeon4 = false
    };

    Savedata::printSave(sd);
    Savedata::printSaveTechnical(sd);

    return 0;
}

