#include "../server.h"

GameLoop* GameLoop::gLInstance = nullptr;

GameLoop* GameLoop::getGameLoopInstance() noexcept {
    if (gLInstance == nullptr) {
        gLInstance = new GameLoop();
        gLInstance->Initialize();
    }
    return gLInstance;
}

GameLoop::GameLoop() {
    m_running = false;
}

void GameLoop::Initialize() noexcept {
    gLInstance->m_running = true;
}

void GameLoop::ExitThread() noexcept {
    gLInstance->m_running = false;
}

bool GameLoop::isRunning() noexcept {
    return gLInstance->m_running;
}

void GameLoop::Start(zmq::socket_t& subscriber) {
    zmq::pollitem_t items[] = { { static_cast<void*>(subscriber), 0, ZMQ_POLLIN, 0 } };
    Run(items, subscriber);
}

void GameLoop::Update() {
    PayloadBuilder pb;
    for (const zmq::message_t& msg : read_buffer) {
        Logger::Log(DEBUG, "Received message");
        IPC::IPCMessage* ipcMessage = pb.newIPCMessage();
        ipcMessage->ParseFromArray(msg.data(), msg.size());
        if (ipcMessage->type() == IPC::IPCMessageType::IPC_CREATE_MATCH_REQUEST || ipcMessage->type() == IPC::IPCMessageType::IPC_P0_MATCH_REQUEST) {
            serialized_p0_buffer.push_back(ipcMessage->data());
        } else {
            serialized_p1_buffer.push_back(ipcMessage->data());
        }
        Logger::Log(DEBUG, "Received message: " + ipcMessage->ShortDebugString());
    }
    read_buffer.clear();
}

void GameLoop::Stop() {
    if (isRunning()) {
        gLInstance->m_running = false;
    }
}

void GameLoop::Run(zmq::pollitem_t* items, zmq::socket_t& subscriber) {
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    while (isRunning()) {
        reset_loop_start();
        zmq::poll(&items[0], 1, std::chrono::milliseconds(0));
        if (items[0].revents & ZMQ_POLLIN) {
            zmq::message_t message;
            if (subscriber.recv(message)) {
                read_buffer.push_back(std::move(message));
            }
        }

        Update();
        
        dt = get_loop_elapsed_time();
        
        if (dt < GAME_LOOP_TIME) {
            std::this_thread::sleep_for(std::chrono::milliseconds(GAME_LOOP_TIME - dt));
        } else if (dt > GAME_LOOP_TIME) {
            Logger::Log(ALERT, "Game loop is running behind by " + std::to_string(dt - GAME_LOOP_TIME) + "ms");
            std::this_thread::sleep_for(std::chrono::milliseconds(GAME_LOOP_TIME - (dt - GAME_LOOP_TIME)));
        }
    }
}

void GameLoop::reset_loop_start() {
    loop_start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
}

long GameLoop::get_loop_elapsed_time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - loop_start).count();
}

GameLoop::~GameLoop() {
    ExitThread();
}
