#pragma once
#include "../../../lib/payloadbuilder/src/proto/payload.pb.h"

extern std::string getEventString(PAYLOAD::Events event);
extern int roundToNearest10(double number);
