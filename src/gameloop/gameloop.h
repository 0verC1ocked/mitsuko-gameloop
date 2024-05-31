#pragma once


#include <string>
#include <vector>
#include <chrono>
#include "../../inc/zmq.hpp"
#include "../match-engine/daos/event-message.h"

class GameLoop {
public:
    zmq::socket_t subscriber;
    zmq::socket_t publisher;
    GameLoop();
    static GameLoop* getGameLoopInstance() noexcept;
    ~GameLoop();
    void ExitThread() noexcept;

    bool isRunning() noexcept;

    // getters


    void reset_loop_start();
    long get_loop_elapsed_time();
    bool m_running { false };
    
    void Start();
    void Update();
    void Stop();

    void queueData(const std::string& data) noexcept;

private:

    static GameLoop* gLInstance;
    
    std::vector<zmq::message_t> read_buffer;

    std::vector<EventMessage> message_queue;

    std::vector<std::string> m_pub_queue;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> loop_start;
    
    long dt;
    void Run(zmq::pollitem_t* items);
    void Initialize() noexcept;

    void processQueue() noexcept;
};
