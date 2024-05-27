#pragma once

#include <string>
#include <unordered_map>
#include "../match-engine/daos/match-model.h"
#include "../match-engine/daos/passive.h"
#include "../../lib/payloadbuilder/src/proto/match.pb.h"
#include "../match-engine/daos/prop.h"

class MatchManager {
    private:
        static MatchManager* m_instance;
        // Unordered map from string to MatchModel pointers
        std::unordered_map<std::string, std::shared_ptr<MatchModel>> m_matches;
        MatchManager();
    public: 
        static MatchManager* getInstance();
        static std::unique_ptr<Player> dummyPlayer();
        static std::unique_ptr<Player> _dummy_player;
        void createMatch(const MATCH::CreateMatchRequest* request);
        void unpackPlayer(const PAYLOAD::Player& payloadPlayer, Player& player);
};
