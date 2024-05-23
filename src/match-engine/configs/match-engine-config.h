#pragma once

#include <unordered_map>
#include "../daos/bracket.h"

enum MatchConfig : int {
    MAX_SELECTION_MISSES = 499
};

extern std::unordered_map <Brackets, BracketConfig> BracketsConfig;

