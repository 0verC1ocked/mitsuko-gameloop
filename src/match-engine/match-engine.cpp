#include "../server.h"

MatchEngine* MatchEngine::instance = nullptr;

MatchEngine* MatchEngine::getEngine() {
    if (instance == nullptr) {
        instance = new MatchEngine();
    }
    return instance;
}

MatchEngine::MatchEngine() { }

MatchEngine::~MatchEngine() { }

void MatchEngine::get_ball_distribution_for_innings(BallDistributionForInningsDAO& m_bD, const int number_of_overs) {
    m_bD.number_of_green_balls = roundToNearest10(0.33 * number_of_overs * 6);
    m_bD.number_of_yellow_balls = roundToNearest10(0.4 * number_of_overs * 6);
    m_bD.number_of_red_balls = number_of_overs * 6 - m_bD.number_of_green_balls - m_bD.number_of_yellow_balls;
}
