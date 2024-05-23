#pragma once

enum struct SA : int {
    None = 0,
    Smash = 1,
    TwoX = 2,
    BowlerSteal = 3,
    Yorker = 4,
    BatsmanSteal = 5,
    Rage = 6,
    Boomerang = 7,
    HalfRuns = 8,
    Hex = 9,
    Immortal = 10,
    Doom = 11,
    FiftyFifty = 12,
    Hit = 13,
    Choke = 14,
    Flashbang = 15,
    Assault = 16,
    AllIn = 17,
    Powersteal = 18,
    Triplet = 19,
    Overload = 20,
    Purge = 21
};

enum struct DeadShotStatus : int {
    NoStatus = 0,
    Inactive = 1,
    Success = 2,
    Failed = 3
};

struct ISaInfo {
    DeadShotStatus dead_shot_status = DeadShotStatus::Inactive;
    int batsman_active_sa = 0;
    int bowler_active_sa = 0;
    bool immortal_active_wicket_changed_to_miss = false;
};

struct SAInfo {
  SA type = SA::None;
  int duration_left = 0;
  bool applied_for_current_ball = false;
  int max_duration = 0;
  double steal = 0.0;

  DeadShotStatus dead_shot_status = DeadShotStatus::Inactive;
  bool immortal_active_wicket_changed_to_miss = false;

  void reset() {
    type = SA::None;
    duration_left = 0;
    applied_for_current_ball = false;
    max_duration = 0;
    steal = 0.0;
    dead_shot_status = DeadShotStatus::Inactive;
    immortal_active_wicket_changed_to_miss = false;
  }
};

