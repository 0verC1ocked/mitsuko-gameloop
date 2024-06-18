#pragma once

#include <string>
#include <unordered_map>
#include "match-model.h"
#include "../../lib/matchengine/src/daos/passive.h"
#include "../../lib/payloadbuilder/src/proto/match.pb.h"
#include "../../lib/matchengine/src/daos/prop.h"
#include "../../lib/matchengine/src/daos/ball.h"

class MatchManager {
    private:
        static MatchManager* m_instance;
        MatchManager();
    public: 
        static MatchManager* getInstance();
        static std::unique_ptr<Player> dummyPlayer();
        static std::unique_ptr<Player> _dummy_player;
        void createMatch(const MATCH::CreateMatchRequest* request);
        void unpackPlayer(const PAYLOAD::Player& payloadPlayer, Player& player);
        bool pushIntoMatch(const std::string& serialized_data, const std::string& match_id);

        void updateMatches(PayloadBuilder *pb);
        
        // Unordered map from string to MatchModel pointers
        std::unordered_map<std::string, std::shared_ptr<MatchModel>> m_matches;

};
