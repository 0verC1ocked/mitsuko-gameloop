#pragma once

#include "../../lib/payloadbuilder/src/proto/payload.pb.h"
#include "../memory/pool-allocator.h"
#include "../../lib/matchengine/inc/match-engine-config.h"
#include "../state-machine/timeouts.h"
#include "event-message.h"
#include "../../lib/matchengine/src/daos/ball.h"
#include "../../lib/matchengine/src/daos/bot.h"
#include "../../lib/matchengine/src/daos/bracket.h"
#include "../../lib/matchengine/src/daos/character.h"
#include "../state-machine/match-states.h"
#include "../../lib/matchengine/src/daos/sa.h"
#include "../../lib/matchengine/src/daos/shot.h"
#include "../state-machine/state-machine.h"
#include <algorithm>
#include <cstdint>
#include <string>

enum struct PlayStates { MatchMaked, Ready, Bowling, Batting, Forfiet, Crash };

enum struct ConnectionState {
  NotConnected,
  Connected,
  Disconnected,
  Reconnecting
};

enum struct ACK : int16_t {
  None,
  UserReady,
  MatchSceneAck,
  MatchReady,
  TossStart,
  InningsStart,
  InningsReady,
  PlayerSelected,
  NextBowlerSelection,
  NextBowlerSelected,
  StartBallSent,
  StartBallAcked,
  EndBall,
  EndInnings,
  Reconnected,
};

enum struct Inning { First, Second };

enum struct JoinStates { NoJoins, FirstJoin, SecondJoin };

enum struct BallStates {
  None,
  StartBall,
  BallPublished,
  BallSelected,
  ShotPublished,
  ShotSelected,
  Outcome,
  Ended
};

enum struct ShotOutcomes { None, Hit, Miss, Wicket };

enum struct WicketType { None, Bowled, Caught };

enum struct AnticipationType {
  None,
  HighProbabilitySixSuccess,
  HighProbabilitySixMiss,
  HighProbabilityFourOut,
  HighProbabilityFourMiss,
  AnticipationOut
};

struct TOutcome {
  ShotOutcomes outcome;
  int runs;
  double random;
  WicketType wicket_type;
  AnticipationType anticipation_type;

  static std::string getOutcomeString(ShotOutcomes outcome) {
    switch (outcome) {
    case ShotOutcomes::Hit:
      return "Hit";
    case ShotOutcomes::Miss:
      return "Miss";
    case ShotOutcomes::Wicket:
      return "Wicket";
    default:
      return "None";
    }
  }
};

struct PreviousBallDTO {
  Inning inning;
  int total_runs;
  int total_balls;
  int total_wickets;
  int over_number;
  int over_ball_number;
  TOutcome outcome;
  TBall selectedBall;
  TShot selectedShot;
  ISaInfo o_sa_info;
};

struct UserInfo {
  PlayStates playState;
  ConnectionState connectionState;
  std::string opponentUID;
  ACK ack;
  bool auto_play = false;
  int mana_fill = 2;
  bool is_bot = false;
  BotProfileType bot_profile_type = BotProfileType::NoBot;
  int wicket_cooldown = 2;
  SAInfo sa_info;
  std::vector<PreviousBallDTO> missed_balls = {};
  PAYLOAD::Events previous_event;
  int selection_by_bot_delay = 0;
  int number_of_missed_selections = 0;
  std::chrono::high_resolution_clock::time_point last_disconnection_at;
  bool timed_out = false;
  std::string result_reason = "";
  bool mana_filled_for_this_ball = false;
  int reconnection_count = 0;
  bool reconnect_pkt_sent = false;
  void setConnectionState(ConnectionState s) {
    this->connectionState = s;
    if (s == ConnectionState::Disconnected) {
      this->last_disconnection_at = std::chrono::high_resolution_clock::now();
    }
  }
  bool canSendPacket() { return connectionState == ConnectionState::Connected; }
};

struct CurrentBall {
  BallStates state;
  TOutcome outcome;
  std::vector<TShot> shots = {
      {0, "None", 0, Brackets::Zero, 0.0f, 0.0f, 0.0, 0.0},
      {0, "None", 0, Brackets::One, 0.0f, 0.0f, 0.0, 0.0},
      {0, "None", 0, Brackets::Two, 0.0f, 0.0f, 0.0, 0.0},
      {0, "None", 0, Brackets::Four, 0.0f, 0.0f, 0.0, 0.0},
      {0, "None", 0, Brackets::Six, 0.0f, 0.0f, 0.0, 0.0},
  };
  std::vector<TBall> balls;
  TBall selectedBall;
  TShot selectedShot;
  int over_ball_number;
  bool did_bowler_auto_play = false;
  bool did_batsman_auto_play = false;
};

struct Innings {
  Inning inning;
  int runs;
  int balls;
  int wickets;
  int over_number;
  int max_balls_per_over;
  int max_overs;
  int boundary_counter;
  int green_shot_missed_counter;
  int yellow_shot_missed_counter;
  int number_of_green_balls = 0;
  int number_of_yellow_balls = 0;
  int number_of_red_balls = 0;
  std::string user_on_batting;
  std::string user_on_bowling;
  IBallDistribution previousOverBallDistribution;
  int partnership_runs = 0;
  int batsmen_used = 0;
  int zero_one_counter_per_over = 0;
  Player *strongest_bowler;
  Player *strongest_batsman;
  int sixes_counter = 0;
  int fours_counter = 0;
  int extra_balls = 0;
  int green_probability_miss_counter = 0;
  int yellow_probability_miss_counter = 0;
};

struct IBowlerMatchDataForPlayerSelection {
  BallStates state;
  std::vector<TBall> balls;
};

struct IOutcome {
  int total_runs;
  int total_balls;
  int extra_balls;
  int wickets_taken;
  int runs_scored;
  int original_runs_scored;
  Brackets bracket_id;
  int over_ball_number;
  int over_number;
  ShotOutcomes outcome;
  WicketType wicket_type;
  AnticipationType anticipation_type;
  Inning inning;
  ISaInfo o_sa_info;
};

struct PlayersOnPitch {
  Player *onStrikeBatsman;
  Player *offStrikeBatsman;
  Player *bowler;
};

class MatchModel {
public:
  MatchModel() {
    home_lineup.reserve(11);
    away_lineup.reserve(11);
  }
  std::string matchId;
  std::unordered_map<std::string, UserInfo> users;
  std::string home;
  std::string away;
  JoinStates joinState;
  MatchStates matchState;
  Innings currentInnings;
  Innings previousInnings;
  std::vector<Player> home_lineup;
  std::vector<Player> away_lineup;
  CurrentBall currentBall;
  std::vector<CurrentBall> previousBalls = {{}, {}, {}};
  std::unique_ptr<Player> selectedFirstBatsman;
  std::unique_ptr<Player> selectedSecondBatsman;
  std::unique_ptr<Player> selectedBowler;
  std::chrono::high_resolution_clock::time_point stateStartTime;
  std::chrono::high_resolution_clock::time_point both_disconnect_time_point;
  std::string winner = "";
  bool is_rps_enabled = true;
  bool is_passives_enabled = true;
  int batsman_mana_required = 5;
  int bowler_mana_required = 5;
  std::chrono::high_resolution_clock::time_point created_at;
  std::chrono::high_resolution_clock::time_point first_join_at;
  std::chrono::high_resolution_clock::time_point second_join_at;
  bool canceled = false;
  bool is_ftue_match = false;

  std::vector<EventMessage> message_buffer;
  MatchStateMachine stateMachine;

  bool has_reconnecting_client() {
    if (users[home].connectionState == ConnectionState::Reconnecting ||
        users[away].connectionState == ConnectionState::Reconnecting) {
      return true;
    } else {
      return false;
    }
  }
  bool has_disconnected_client() {
    if (users[home].connectionState == ConnectionState::Disconnected ||
        users[away].connectionState == ConnectionState::Disconnected) {
      return true;
    } else {
      return false;
    }
  }

  bool has_forfieted_user() {
    if (users[home].playState == PlayStates::Forfiet ||
        users[away].playState == PlayStates::Forfiet) {
      return true;
    } else {
      return false;
    }
  }

  bool has_crash_user() {
    if (users[home].playState == PlayStates::Crash ||
        users[away].playState == PlayStates::Crash) {
      return true;
    } else {
      return false;
    }
  }

  bool has_timed_out_user() {
    return users[home].timed_out || users[away].timed_out;
  }
  bool all_clients_disconnected() {
    if (users[home].connectionState == ConnectionState::Disconnected &&
        users[away].connectionState == ConnectionState::Disconnected) {
      return true;
    } else {
      return false;
    }
  }
  bool all_clients_connected() {
    return isHomeConnected() && isAwayConnected();
  }
  bool isHomeNotConnected() {
    return users[home].connectionState == ConnectionState::NotConnected;
  }
  bool isAwayNotConnected() {
    return users[away].connectionState == ConnectionState::NotConnected;
  }
  bool isHomeConnected() {
    return users[home].connectionState == ConnectionState::Connected;
  }
  bool isAwayConnected() {
    return users[away].connectionState == ConnectionState::Connected;
  }
  bool isHomeDisconnected() {
    return users[home].connectionState == ConnectionState::Disconnected;
  }
  bool isAwayDisconnected() {
    return users[away].connectionState == ConnectionState::Disconnected;
  }

  int getStateTimeout() {
    if (is_ftue_match) {
      return STATE_TIMEOUT_SECONDS *
             3; // stateMachine.getCurrentStateTimeout() * 3;
    } else {
      return STATE_TIMEOUT_SECONDS; // stateMachine.getCurrentStateTimeout();
    }
  }

  bool isStateExpired() { return remainingStateSeconds() <= 0; }

  bool checkIfUserIdBelongsToThisMatch(const std::string& uid) {
      return (uid == home || uid == away);
  }

  int64_t remainingStateSeconds() {
    return std::max(0L,
                    getStateTimeout() -
                        std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now() - stateStartTime)
                            .count());
  }

  bool reachedCancelTimeout() {
    if (joinState == JoinStates::NoJoins) {
      return std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now() - created_at)
        .count() >= FIRST_JOIN_TIMEOUT_SECONDS;
    } else if (joinState == JoinStates::FirstJoin) {
      return std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now() - first_join_at)
        .count() >= SECOND_JOIN_TIMEOUT_SECONDS;
    } else {
      return false;
    }
  }

  bool is_stale() {
    bool is_stale_timeout =
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now() - both_disconnect_time_point)
            .count() >= STALE_MATCH_TIMEOUT_SECONDS;
    bool both_disconnected = all_clients_disconnected();
    return both_disconnected && is_stale_timeout;
  }
  void save_current_ball() {
    previousBalls[2] = previousBalls[1];
    previousBalls[1] = previousBalls[0];
    previousBalls[0] = currentBall;
  }

  bool has_any_bot_client() {
    if (users[home].is_bot || users[away].is_bot) {
      return true;
    } else {
      return false;
    }
  }

  void removeProcessedMessages() {
    message_buffer.erase(
        std::remove_if(message_buffer.begin(), message_buffer.end(),
                       [](const EventMessage& em) { return em.processed; }),
        message_buffer.end());
  }

  bool is_home_bot() { return users[home].is_bot; }

  bool is_away_bot() { return users[away].is_bot; }

  bool has_home_missed_selections_exceeded() {
    return users[home].number_of_missed_selections > MAX_SELECTION_MISSES;
  }

  bool has_away_missed_selections_exceeded() {
    return users[away].number_of_missed_selections > MAX_SELECTION_MISSES;
  }

  void delete_match_model(const char *file, int line) {
    this->users.clear();
    this->home_lineup.clear();
    this->away_lineup.clear();
    this->previousBalls.clear();
    this->currentBall.balls.clear();
    this->currentBall.shots.clear();
    delete this;
  }

  void *operator new(size_t size, const char *file, int line) {
    g_match_model_allocator->number_of_allocs++;
    return g_match_model_allocator->allocate(size);
    // return malloc(size);
  }

  void operator delete(void *ptr, size_t size) {
    g_match_model_allocator->number_of_deallocs++;
    return g_match_model_allocator->deallocate(ptr, size);
  }
};
