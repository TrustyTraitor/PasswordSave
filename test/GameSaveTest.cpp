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
            uint level : 5 = 0; // Max level is 31
            uint health : 4 = 0; // Max hearts are 15
            uint playerClass : 2 = 0;

            uint potionQuality: 2 = 0; // Max potion quality is 3
            uint potionCount : 3 = 0; // Max potion count is 7

            // Sword/Armor follows basc quality for 0-3, beyond that is unique weapons/armors.
            uint weaponQuality : 3 = 0; // Max sword quality is 7
            uint armorQuality : 3 = 0; // Max armor quality is 7

            // Main dungeons are linear
            uint storyDungeonCompletion : 3 = 0; // Max (linear) dungeons are 7.

            // Simple boolean on if the dungeon has been completed.
            // Side dungeons are optional and may be completed in different orders, and as such, require separate boolean flags
            uint sideDungeon1 : 1 = 0;
            uint sideDungeon2 : 1 = 0;
            uint sideDungeon3 : 1 = 0;
            uint sideDungeon4 : 1 = 0;
            uint sideDungeon5 : 1 = 0;
            uint sideDungeon6 : 1 = 0;
            uint sideDungeon7 : 1 = 0;

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

    inline std::string getClass(const int playerClass) {
        switch (playerClass) {
            case 0:
                return "Warrior";
            case 1:
                return "Wizard";
            case 2:
                return "Rogue";
            case 3:
                return "Ranger";
            default:
                return "Error.";
        }
    }

    inline void printSave(const SaveData SD) {
        std::cout
        << "Player Info:" << "\n"
        << " - Level: " << SD.level << " (Max: 13)"  << "\n"
        << " - Health: " << SD.health << " (Max: 15)" << "\n"
        << " - Class: " << SD.playerClass << " (" << getClass(SD.playerClass) << ")" << "\n"
        << "Item Info:"
            << " Possible quality levels are: " << getQuality(0) << ", " << getQuality(1)
            << ", " << getQuality(2) << ", or " << getQuality(4) << "\n"
        << " - Potion Count: " << SD.potionCount << " (Max: 7)" << "\n"
        << " - Potion Quality: " << SD.potionQuality << " (" << getQuality(SD.potionQuality) << ") " << "\n"
        << " - Weapon Quality: " << SD.weaponQuality << " (" <<getQuality(SD.weaponQuality) <<  ") " << "\n"
        << " - Armor Quality: " << SD.armorQuality << " (" << getQuality(SD.armorQuality) << ") " << "\n"
        << "Dungeons Completed: " << "\n"
        << " - " << SD.storyDungeonCompletion << "\n"
        << " - Side Dungeon Completion: " << "\n"
        << "   - Side Dungeon 1: " << SD.sideDungeon1 << "\n"
        << "   - Side Dungeon 2: " << SD.sideDungeon2 << "\n"
        << "   - Side Dungeon 3: " << SD.sideDungeon3 << "\n"
        << "   - Side Dungeon 4: " << SD.sideDungeon4 << "\n"
        << "   - Side Dungeon 5: " << SD.sideDungeon5 << "\n"
        << "   - Side Dungeon 6: " << SD.sideDungeon6 << "\n"
        << "   - Side Dungeon 7: " << SD.sideDungeon7 << "\n"
        << std::endl;
    }

    inline void printSaveTechnical(const SaveData SD) {
        std::cout << "Technical Info:" << std::endl;
        std::cout << "sizeof(SaveData): " << sizeof(SaveData) << "Bytes (" << sizeof(SaveData)*8 << "bits" << ")\n" << std::endl;

        std::cout << "Save/Password as:" << std::endl;
        std::cout << "\tBinary: " << std::bitset<sizeof(SD.container)*8>(SD.container) << std::endl;
        std::cout << "\t   Int: " << SD.container << std::endl;
        std::cout << "\t   Hex: " << std::format("{:x}", SD.container) << std::endl;

        const std::string password = PasswordSave::serialize<std::uint32_t>(SD.container);
        std::cout << "\n" << "Note: This isn't a standard base 26 that starts at 0. Instead 0 is represented as A" << std::endl;
        std::cout << "Base26 Password: " << password << std::endl;

        auto deserializedSave = PasswordSave::deserialize<std::uint32_t>(password);
        std::cout << "Deserialized Save: " << std::endl;
        std::cout << "\tBinary: " << std::bitset<sizeof(deserializedSave)*8>(deserializedSave) << std::endl;
        std::cout << "\t   Int: " << deserializedSave << std::endl;
        std::cout << "\t   Hex: " << std::format("{:x}", deserializedSave) << std::endl;

    }
}

int main() {

    // Some random fake save data
    Savedata::SaveData sd = {
        .level = 2,
        .health = 1,
        .playerClass = 1,

        .potionQuality = 1,
        .potionCount = 6,

        .weaponQuality = 2,
        .armorQuality = 2,

        .storyDungeonCompletion = 2,
        .sideDungeon1 = 1,
        .sideDungeon2 = 1,
        .sideDungeon3 = 0,
        .sideDungeon4 = 0,
        .sideDungeon5 = 0,
        .sideDungeon6 = 0,
        .sideDungeon7 = 0,
    };

    Savedata::printSave(sd);
    Savedata::printSaveTechnical(sd);

    return 0;
}

