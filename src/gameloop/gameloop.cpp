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

void GameLoop::Start() {
    zmq::pollitem_t items[] = { { static_cast<void*>(subscriber), 0, ZMQ_POLLIN, 0 } };

    Run(items);
}

void GameLoop::Update() {
    ArenaAllocator allocator;
    for (const zmq::message_t& msg : read_buffer) {
        IPC::IPCMessage* ipcMessage = allocator.newIPCMessage();
        ipcMessage->ParseFromArray(msg.data(), msg.size());
        
        Logger::Log(DEBUG, "Received message: " + ipcMessage->ShortDebugString());
        switch (ipcMessage->type()) {
            case IPC::IPCMessageType::IPC_CREATE_MATCH_REQUEST: {
                MATCH::CreateMatchRequest* createMatchRequest = allocator.newCreateMatchRequest();
                createMatchRequest->ParseFromString(ipcMessage->data());
                MatchManager::getInstance()->createMatch(createMatchRequest);
                break;
            }
            case IPC::IPCMessageType::IPC_P0_MATCH_REQUEST: { // Push into its own buffer
                PAYLOAD::Payload* payload = allocator.newPayload();
                payload->ParseFromString(ipcMessage->data());
                message_queue.push_back(EventMessage{ payload->SerializeAsString() });
                break;
            }
            case IPC::IPCMessageType::IPC_P1_MATCH_REQUEST: { // Push into its own buffer
                MatchManager::getInstance()->pushIntoMatchBuffers(ipcMessage->data(), ipcMessage->matchid());
                break;
            }
            default:
                break;
        }

    }
    read_buffer.clear();

    for (EventMessage& em : message_queue) {
        PAYLOAD::Payload* payload = allocator.newPayload();
        payload->ParseFromString(em.message);
        bool processed = EventHandler::getEventHandlerInstance()->handleEvent(allocator, payload);
        em.processed = processed;

        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - em.created_at).count() > 7) {
            Logger::Log(ERROR, "GameLoop::main() -> Message has expired!");
            em.processed = true;
        }
    }

    message_queue.erase(std::remove_if(message_queue.begin(), message_queue.end(), [](const EventMessage& em) {
        return em.processed;
    }), message_queue.end());

    MatchManager::getInstance()->updateMatches(allocator);
    // Logger::printProgress(MatchManager::getInstance()->m_matches.size(), 100);
}

void GameLoop::Stop() {
    if (isRunning()) {
        gLInstance->m_running = false;
    }
}

void GameLoop::Run(zmq::pollitem_t* items) {
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

        processQueue();

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

void GameLoop::queueData(const std::string& data) noexcept {
    m_pub_queue.push_back(data);
}

void GameLoop::processQueue() noexcept {
    for (const std::string& data : m_pub_queue) {
        zmq::message_t message(data.size());
        memcpy(message.data(), data.data(), data.size());
        publisher.send(message);
        Logger::Log(DEBUG, "Publishing data: " + data);
    }
    m_pub_queue.clear();
}
