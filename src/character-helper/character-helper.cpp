#include "../server.h"

CharacterHelper* CharacterHelper::_characterHelperInstance = nullptr;

CharacterHelper::CharacterHelper() {}

CharacterHelper::~CharacterHelper() {}

const CharacterHelper* CharacterHelper::getHelper() {
    if (_characterHelperInstance == nullptr) {
        _characterHelperInstance = new CharacterHelper();
    }
    return _characterHelperInstance;
}

const Character* CharacterHelper::getCharacter(int id) {
    int len = Characters.size();
    int max = len - 1;
    int min = 0;
    int p;
    while (min <= max) {
        p = (min + max) / 2;
        if (Characters[p].character_id == id) {
            break;
        } else if (Characters[p].character_id < id) {
            min = p + 1;
        } else {
            max = p - 1;
        }
    }
    if (min > max) {
        Logger::Log(ERROR, "No character found with id ");
        return &(Characters[0]);
    } else {
        return &(Characters[p]);
    }
}


