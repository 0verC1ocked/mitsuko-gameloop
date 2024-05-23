#pragma once
#include <string>
#include <vector>
#include "bracket.h"

enum struct Skulls : int {
    GREEN = 1,
    YELLOW = 2,
    RED = 3
};

struct TBall {
  int id;
  std::string name;
  double value;
  Skulls skulls;
  std::vector<BracketData> shots_possible;
};

struct IBallDistribution {
    int green = 2;
    int yellow = 3;
    int red = 1;
};

struct ISKullBalls {
  std::vector<TBall> green_skull;
  std::vector<TBall> yellow_skull;
  std::vector<TBall> red_skull;
};
