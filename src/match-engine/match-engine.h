#pragma once
/**
 * @file match-engine.h
 * @brief This file contains the MatchEngine Class definition.
*/

#include "daos/daos.h"

/**
 * @class MatchEngine
 * @brief This class is responsible for the match engine logic.
 * @details This class is a singleton class and is responsible for the match engine logic.
 */

class MatchEngine {
    private:
        static MatchEngine* instance;
        MatchEngine();
        ~MatchEngine();
    public:
        static MatchEngine* getEngine();
        void get_ball_distribution_for_innings(BallDistributionForInningsDAO& m_bD ,const int number_of_overs);

};
