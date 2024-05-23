#pragma once

enum struct Brackets {
    Zero = 1,
    One = 2,
    Two = 3,
    Four = 4,
    Six = 5
};

struct BracketData {
    Brackets bracket_id;
    int shot_id;
};

struct BracketConfig {
    int runs;
    int modifier;
    double less_factor;
    double more_factor;
    double wicket_chance;
};
