#include "../server.h"

EventHandler* EventHandler::eHInstance = nullptr;

EventHandler* EventHandler::getEventHandlerInstance() noexcept {
    if (eHInstance == nullptr) {
        eHInstance = new EventHandler();
    }
    return eHInstance;
}

EventHandler::EventHandler() { }

bool EventHandler::handleEvent(ArenaAllocator& allocator, PAYLOAD::Payload* received_payload) {
    switch (received_payload->event()) {
        case PAYLOAD::Events::CONNECT_ACK: {
            std::shared_ptr<MatchModel> match;
            auto match_it = MatchManager::getInstance()->m_matches.find(received_payload->data().roomid());
            if (match_it != MatchManager::getInstance()->m_matches.end()) {
                match = match_it->second;
            } else {
                return false;
            }

            auto user_it = match->users.find(received_payload->data().userid());
            UserInfo* user = nullptr;
            if (user_it != match->users.end()) {
                user = &user_it->second;
            } else {
                return false;
            }

            if (user->connectionState == ConnectionState::NotConnected) {
                PAYLOAD::Payload* payload = allocator.newPayload();
                payload->set_event(PAYLOAD::Events::CONNECTED);
                payload->mutable_data()->set_roomid(received_payload->data().roomid());
                payload->mutable_data()->set_userid(received_payload->data().userid());
                payload->mutable_data()->set_opponentid(received_payload->data().opponentid());
                
                match->users[received_payload->data().userid()].connectionState = ConnectionState::Connected;
                IPC::IPCMessage* ipcMessage = allocator.newIPCMessage();
                ipcMessage->set_type(IPC::IPCMessageType::IPC_ENET_SEND);
                ipcMessage->set_userid(received_payload->data().userid());
                ipcMessage->set_data(payload->SerializeAsString());
                GameLoop::getGameLoopInstance()->queueData(ipcMessage->SerializeAsString());
                return true;
            } else if (user->connectionState == ConnectionState::Disconnected) {
            }
           break;
        }
        default: {
            break;
        }
    }
    return false;
}
