#pragma once

#include "../../match-manager/match-model.h"


struct ProbabilityCalculationDAO {
    double ball_value;
    double shot_value;
    Brackets bracket_id;
    Skulls skull;
    int boundary_counter;
    PlayersOnPitch players_on_pitch;
};

struct BallDistributionForInningsDAO {
    int number_of_green_balls;
    int number_of_yellow_balls;
    int number_of_red_balls;
};

struct IShotsMatchupWithSaPassivesEqpDAO {
    MatchModel* matchModel;
    PlayersOnPitch players_on_pitch;
    std::vector<BracketData> shots_possible;
    Trait trait;
    TBall selectedBall;
    int boundary_counter;
    int level;
    float balls_completion;
    short wickets;
};

struct IBotBestShotDAO {
    MatchModel* matchModel;
    std::string bot_team;
};

struct IBotBestBallDAO {
    MatchModel* matchModel;
    std::string bot_team;
};

struct IBotBestBowlerDAO {
    MatchModel* matchModel;
    std::string bot_team;
};

struct IBotBestBatsmanOnWicketDAO {
    MatchModel* matchModel;
    std::string bot_team;
};

struct IBotBestOpenerDAO {
    MatchModel* matchModel;
    std::string bot_team;
};

struct IBotActivateSpecialAbilityDAO {
    MatchModel* matchModel;
    std::string bot_team;
    std::string real_team;
};


struct IGetOutcomeDAO {
    TShot shot_selected;
    TBall ball_selected;
    Player *bowler;
    Player *onstrike;
    MatchModel* match_model;
};
