#pragma once


#include <string>
#include <vector>
#include <chrono>
#include "../../inc/zmq.hpp"

class GameLoop {
public:
    GameLoop();
    static GameLoop* getGameLoopInstance() noexcept;
    ~GameLoop();
    void ExitThread() noexcept;

    bool isRunning() noexcept;

    // getters


    void reset_loop_start();
    long get_loop_elapsed_time();
    bool m_running { false };
    
    void Start(zmq::socket_t& subscriber);
    void Update();
    void Stop();

private:

    static GameLoop* gLInstance;
    std::vector<zmq::message_t> read_buffer;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> loop_start;
    
    long dt;
    void Run(zmq::pollitem_t* items, zmq::socket_t& subscriber);
    void Initialize() noexcept;

};
