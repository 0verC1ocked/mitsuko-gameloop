#pragma once
#include <vector>
#include <memory>
#include "../../lib/matchengine/src/daos/character.h"

class CharacterHelper {
    public:
        static const Character* getCharacter(int id);
        static const CharacterHelper* getHelper();
    protected:
        static CharacterHelper* _characterHelperInstance;
        CharacterHelper();
        ~CharacterHelper();

};

extern std::vector<Character> Characters;
