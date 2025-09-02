//
// Created by Mikey on 9/2/2025.
//
#include <cstdint>
#include <bitset>
#include <format>

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

            // Simple boolean on if the dungeon has been completed
            uint storyDungeon1 : 1 = 0;
            uint storyDungeon2 : 1 = 0;
            uint storyDungeon3 : 1 = 0;
            uint storyDungeon4 : 1 = 0;

            uint sideDungeon1 : 1 = 0;
            uint sideDungeon2 : 1 = 0;
            uint sideDungeon3 : 1 = 0;
            uint sideDungeon4 : 1 = 0;
            // 8 + 18 = 26 bit used above. 6 remaining
            // Maybe status effects? Side quests? Skills/Class?
            // Leaning towards Class: Classes could be linear, with new skills being obtained simply by leveling up.
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
        << "Dungeon Completion: (0 is uncompleted, 1 is completed)" << "\n"
        << " - Main Dungeon 1: " << SD.storyDungeon1 << "\n"
        << "  -- Side Dungeon 1: " << SD.sideDungeon1 << "\n"
        << " - Main Dungeon 2: " << SD.storyDungeon2 << "\n"
        << "  -- Side Dungeon 2: " << SD.sideDungeon2 << "\n"
        << " - Main Dungeon 3: " << SD.storyDungeon3 << "\n"
        << "  -- Side Dungeon 3: " << SD.sideDungeon3 << "\n"
        << " - Main Dungeon 4: " << SD.storyDungeon4 << "\n"
        << "  -- Side Dungeon 4: " << SD.sideDungeon4 << std::endl;
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
    }

}

int main() {

    // Some random fake save data
    constexpr Savedata::SaveData sd = {
        .level = 2,
        .health = 3,
        .potionQuality = 2,
        .potionCount = 6,
        .swordQuality = 3,
        .armorQuality = 4,
        .storyDungeon1 = 1,
        .storyDungeon2 = 1,
        .storyDungeon3 = 0,
        .storyDungeon4 = 0,
        .sideDungeon1 = 1,
        .sideDungeon2 = 0,
        .sideDungeon3 = 0,
        .sideDungeon4 = 0
    };

    Savedata::printSave(sd);
    std::cout << std::endl << std::endl;
    Savedata::printSaveTechnical(sd);

    return 0;
}

