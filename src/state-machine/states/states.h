#pragma once

#include "../../../lib/arenaallocator/inc/arena-allocator.h"
#include "../timeouts.h"
#include "../conditions.h"
#include "../match-states.h"

class MatchModel;

struct NoState {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator) {
    
  };
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator) {};
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator) {};
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator) {};
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator) {};

  MatchStates getState() { return MatchStates::NoState; };

  void handleP0Events(MatchModel &match_model, ArenaAllocator &allocator);
};

struct WaitingForUsers {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::WaitingForUsers; };
};

struct WaitingForMatchReady {
  long time_out_seconds = START_INNINGS_TIMEOUT_SECONDS;
  void reset_default_timeout() {
    time_out_seconds = START_INNINGS_TIMEOUT_SECONDS;
  }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::WaitingForMatchReady; };
};

struct StartInnings {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::StartInnings; };
};

struct PlayerSelection {
  long time_out_seconds = PLAYER_SELECTION_TIMEOUT_SECONDS;
  void reset_default_timeout() {
    time_out_seconds = PLAYER_SELECTION_TIMEOUT_SECONDS;
  }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::PlayerSelection; };
};

struct StartBall {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::StartBall; };
};

struct BallSelection {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::BallSelection; };
};

struct ShotSelection {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::ShotSelection; };
};

struct Outcome {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  MatchStates getState() { return MatchStates::Outcome; };
};

struct EndBall {
  long time_out_seconds = END_BALL_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = END_BALL_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }

  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);

  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::EndBall; };
};

struct EndOver {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::EndOver; };
};

struct EndInnings {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::EndInnings; };
};

struct MatchEnded {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::MatchEnded; };
};

struct Reconnecting {
  long time_out_seconds = STATE_TIMEOUT_SECONDS;
  void reset_default_timeout() { time_out_seconds = STATE_TIMEOUT_SECONDS; }
  void set_timeout(long timeout) { time_out_seconds = timeout; }
  void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator);
  void postUpdate(TransitionalCondition &condition, MatchModel &match_model,
                  ArenaAllocator &allocator);
  void onUpdate(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void autoPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);
  void botPlay(TransitionalCondition &condition, MatchModel &match_model,
                ArenaAllocator &allocator);

  MatchStates getState() { return MatchStates::Reconnecting; };
};
