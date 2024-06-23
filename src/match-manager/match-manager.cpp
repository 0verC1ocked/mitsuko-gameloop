#include "../server.h"

MatchManager* MatchManager::m_instance = nullptr;

MatchManager* MatchManager::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new MatchManager();
    }
    return m_instance;
}

MatchManager::MatchManager() { }

std::unique_ptr<Player> MatchManager::_dummy_player = nullptr;

std::unique_ptr<Player> MatchManager::dummyPlayer() {
    if (_dummy_player == nullptr) {
        _dummy_player = std::make_unique<Player>();
    }
    return std::make_unique<Player>(*_dummy_player);
}

void MatchManager::unpackPlayer(const PAYLOAD::Player& payloadPlayer, Player& player) {
    const Character* character = CharacterHelper::getCharacter(static_cast<int>(payloadPlayer.character_id()));
    short int level = payloadPlayer.level();
    short int lineup_number = payloadPlayer.lineup_number();
    short int power = payloadPlayer.power();

    std::vector<Passive> passives;
    for (int i = 0; i < payloadPlayer.passives().size(); i++) {
        passives.push_back(static_cast<Passive>(payloadPlayer.passives(i)));
    }
    Player::fromCharacterToPlayer(*character, player, level, lineup_number, power, passives);

    for (int i = 0; i < payloadPlayer.equipment_slots().size(); i++) {
        player.equipment_slots[i] = payloadPlayer.equipment_slots(i);
    }

    for (int i = 0; i < payloadPlayer.props().size(); i++) {
        if (payloadPlayer.props(i) >= static_cast<int>(Prop::Min) && payloadPlayer.props(i) <= static_cast<int>(Prop::Max)) {
            player.props.push_back({
                payloadPlayer.props(i),
                false
                });
        }
    }
}


void MatchManager::createMatch(const MATCH::CreateMatchRequest* request) {

    MatchModel* match = new (__FILE__, __LINE__) MatchModel();

    std::string home_id = request->homeuserid();
    std::string away_id = request->awayuserid();

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(static_cast<int>(BotProfileType::Defensive), static_cast<int>(BotProfileType::Aggressive));

    bool isHomeBot = request->ishomebot() ? true : false;
    bool isAwayBot = request->isawaybot() ? true : false;

    bool isFtueMatch = request->isftuematch() ? true : false;

    BotProfileType homeBotProfile = static_cast<BotProfileType>(distribution(generator));
    BotProfileType awayBotProfile = static_cast<BotProfileType>(distribution(generator));
    std::string first_batting_user = request->firstbattinguser();
    PlayStates home_play_state = PlayStates::Batting;
    PlayStates away_play_state = PlayStates::Bowling;
    std::string user_on_batting;
    std::string user_on_bowling;
    bool is_rps_enabled = request->isrpsenabled();
    bool is_passives_enabled = request->ispassivesenabled();
    int batsman_mana_required = request->batsmanmanarequired() ? request->batsmanmanarequired() : 5;
    int bowler_mana_required = request->bowlermanarequired() ? request->bowlermanarequired() : 5;
    int number_of_overs = request->maxovers() ? request->maxovers() : 5;

    Logger::Log(DEBUG, "No. of overs for the match: " + std::to_string(number_of_overs));

    if (first_batting_user == home_id) {
        home_play_state = PlayStates::Batting;
        away_play_state = PlayStates::Bowling;

        user_on_batting = home_id;
        user_on_bowling = away_id;
    } else {
        home_play_state = PlayStates::Bowling;
        away_play_state = PlayStates::Batting;

        user_on_batting = away_id;
        user_on_bowling = home_id;
    }


    auto home_players = request->home_lineup();
    for (int i = 0; i < home_players.size(); i++) {
        Player player;
        MatchManager::unpackPlayer(request->home_lineup(i), player);
        match->home_lineup.push_back(player);
    }

    auto away_players = request->away_lineup();
    for (int i = 0; i < away_players.size(); i++) {
        Player player;
        MatchManager::unpackPlayer(request->away_lineup(i), player);
        match->away_lineup.push_back(player);
    }

    BallDistributionForInningsDAO m_bD = BallDistributionForInningsDAO { 0, 0, 0 };
    MatchEngine::getEngine()->get_ball_distribution_for_innings(m_bD, number_of_overs);

    match->matchId = request->matchid();
    match->created_at = std::chrono::high_resolution_clock::now();
    
    match->users.emplace(home_id, UserInfo {
        home_play_state,
        ConnectionState::NotConnected,
        away_id,
        ACK::None,
        false,
        2,
        isHomeBot,
        homeBotProfile
    });
    match->users.emplace(away_id, UserInfo {
        away_play_state,
        ConnectionState::NotConnected,
        home_id,
        ACK::None,
        false,
        2,
        isAwayBot,
        awayBotProfile
    });
    match->home = home_id;
    match->away = away_id;
    match->joinState = JoinStates::NoJoins;
    match->matchState = MatchStates::WaitingForUsers;
    match->currentInnings = Innings{
        Inning::First,
        0,
        0,
        0,
        0,
        6,
        number_of_overs,
        0,
        0,
        0,
        m_bD.number_of_green_balls,
        m_bD.number_of_yellow_balls,
        m_bD.number_of_red_balls,
        user_on_batting,
        user_on_bowling
    };
    match->previousInnings = match->currentInnings;
    match->currentBall = CurrentBall{
        BallStates::None,
        {},
        {},
        {},
        {},
        {},
        0,
    };
    match->selectedFirstBatsman = MatchManager::dummyPlayer();
    match->selectedSecondBatsman = MatchManager::dummyPlayer();
    match->selectedBowler = MatchManager::dummyPlayer();
    match->currentBall.shots = {
    { 0, "None", 0, Brackets::Zero, 0.0f, 0.0f, 0.0, 0.0 },
    { 0, "None", 0, Brackets::One, 0.0f, 0.0f, 0.0, 0.0 },
    { 0, "None", 0, Brackets::Two, 0.0f, 0.0f, 0.0, 0.0 },
    { 0, "None", 0, Brackets::Four, 0.0f, 0.0f, 0.0, 0.0 },
    { 0, "None", 0, Brackets::Six, 0.0f, 0.0f, 0.0, 0.0 },
    };
    match->is_rps_enabled = is_rps_enabled;
    match->is_passives_enabled = is_passives_enabled;
    match->batsman_mana_required = batsman_mana_required;
    match->bowler_mana_required = bowler_mana_required;
    match->is_ftue_match = isFtueMatch;

    m_matches.emplace(match->matchId, std::shared_ptr<MatchModel>(match));

    Logger::Log(DEBUG, "Match created with ID: " + match->matchId);
    Logger::Log(DEBUG, "Users count in the match: " + std::to_string(match->users.size()));
}

bool MatchManager::pushIntoMatchBuffers(const std::string& serialized_data, const std::string& matchId) {
    try {
        if (matchId.empty()) {
            Logger::Log(ERROR, "Match ID is empty!");
            return false;
        }

        // Find the match from the m_matches map
        MatchModel* match = nullptr;
        auto it = m_matches.find(matchId);
        if (it != m_matches.end()) {
            match = it->second.get();
        } else {
            Logger::Log(ERROR, "Match not found!");
            return false;
        }

        match->message_buffer.push_back(EventMessage { serialized_data });
        return true;
    } catch (const std::exception& e) {
        Logger::Log(ERROR, "Encountered some issue with pushin data into buffer");
        return false;
    }
    
}

void MatchManager::updateMatches(ArenaAllocator &allocator) {
    if (m_matches.empty()) {
        return;
    }
    for (auto& match : m_matches) {
        if (match.second == nullptr) {
            continue;
        }
        match.second->stateMachine.update(*match.second.get(), allocator);
    }
}
