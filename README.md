# PasswordSave
A simple library to serialize and deserialize game state into a short(ish) password. 
This is inspired by [older games](https://www.ign.com/games/feature/password-save)
that used 'passwords' instead of storing game saves in non-volatile memory.

## How to Use
The game state must be contained in a single unsigned integer. 

Use `std::string serialize<T>(T)` for serialization 
and `T deserialize<T>(std::string)` for deserialization.

### Example
```c++
union SaveData {
    struct {
        uint level : 4 = 0; 
        uint health : 3 = 0;

        uint potionQuality: 2 = 0;
        uint potionCount : 3 = 0; 
        
        uint swordQuality : 3 = 0;
        
        uint armorQuality : 3 = 0;
        uint storyDungeonCompletion : 3 = 0;

        uint sideDungeon1 : 1 = 0;
        uint sideDungeon2 : 1 = 0;
        uint sideDungeon3 : 1 = 0;
        uint sideDungeon4 : 1 = 0;
        
        uint playerClass : 2 = 0;
    };

    std::uint32_t container;
};

SaveData sd = {...} // Initialize the game state

std::string password = PasswordSave::serialize<std::uint32_t>(sd.container);

SaveData sd2;
sd2.container = PasswordSave::deserialize<std::uint32_t>(password);
```