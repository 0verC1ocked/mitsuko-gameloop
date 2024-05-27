#pragma once

struct RPS { 
    enum Type: int {
        None = 0,
        Powerful = 1,
        Balanced = 2,
        Technical = 3
    };

    // Called for checking the advantage of bowler RPS over other RPS
    static bool bowlerHasClassAdvantage(RPS::Type bowler, RPS::Type batsman) {
        if (batsman == RPS::Type::None || bowler == RPS::Type::None)
            return false;
        if (static_cast<int>(bowler) % 3 == static_cast<int>(batsman) - 1)
            return true;
        return false;
    }
};
