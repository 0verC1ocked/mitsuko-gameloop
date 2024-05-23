#pragma once
#include <string>
#include <vector>
#include "bracket.h"

struct TShot {
  int id;
  std::string name;
  int run;
  Brackets bracket;
  float probability;
  float wicket_chance;
  double ball_value;
  double shot_value;

  bool locked = false;
  bool shot_hidden = false;
  bool probability_hidden = false;
  std::vector<int> batsman_equipments_applied = {};
  std::vector<int> bowler_equipments_applied = {};
  bool reduce_probability = true;
};

