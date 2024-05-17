#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>
#include <chrono>
#include <thread>

#include "../inc/zmq.hpp"
#include "gameloop/gameloop.h"
