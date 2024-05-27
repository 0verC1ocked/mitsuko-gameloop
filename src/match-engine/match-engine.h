#pragma once
#include "daos/daos.h"

class MatchEngine {
    private:
        static MatchEngine* instance;
        MatchEngine();
        ~MatchEngine();
    public:
        static MatchEngine* getEngine();
        void get_ball_distribution_for_innings(BallDistributionForInningsDAO& m_bD ,const int number_of_overs);

};
