#include "../../server.h"

std::unordered_map <Brackets, BracketConfig> BracketsConfig = {
    { Brackets::Zero, { 0, 90, 0.33, 0.2, 14 } },
    { Brackets::One, { 1, 60, 0.1, 0.6, 21 } },
    { Brackets::Two, { 2, 40, 0.25, 0.6, 21 } },
    { Brackets::Four, { 4, 40, 0.25, 0.6, 31.25 } },
    { Brackets::Six, { 6, 30, 0.2, 0.6, 50 } }
};
