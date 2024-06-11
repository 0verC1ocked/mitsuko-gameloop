#include "../server.h"

EventHandler* EventHandler::eHInstance = nullptr;

EventHandler* EventHandler::getEventHandlerInstance() noexcept {
    if (eHInstance == nullptr) {
        eHInstance = new EventHandler();
    }
    return eHInstance;
}

EventHandler::EventHandler() { }

bool EventHandler::handleEvent(PayloadBuilder& pb, PAYLOAD::Payload* received_payload) {
    switch (received_payload->event()) {
        case PAYLOAD::Events::CONNECT_ACK: {
            std::shared_ptr<MatchModel> match;
            auto it = MatchManager::getInstance()->m_matches.find(received_payload->data().roomid());
            if (it != MatchManager::getInstance()->m_matches.end()) {
                match = it->second;
            } else {
                return false;
            }
            if (match->users[received_payload->data().userid()].connectionState == ConnectionState::NotConnected) {
                PAYLOAD::Payload* payload = pb.newPayload();
                pb.setEvent(PAYLOAD::Events::CONNECTED)
                    .setRoomId(received_payload->data().roomid())
                    .setUserId(received_payload->data().userid())
                    .setOpponentId(received_payload->data().opponentid())
                    .build(payload);
                
                match->users[received_payload->data().userid()].connectionState = ConnectionState::Connected;
                IPC::IPCMessage* ipcMessage = pb.newIPCMessage();
                ipcMessage->set_type(IPC::IPCMessageType::IPC_ENET_SEND);
                ipcMessage->set_userid(received_payload->data().userid());
                ipcMessage->set_data(payload->SerializeAsString());
                GameLoop::getGameLoopInstance()->queueData(ipcMessage->SerializeAsString());
                return true;
            } else if (match->users[received_payload->data().userid()].connectionState == ConnectionState::Disconnected) {
            }
           break;
        }
        default: {
            break;
        }
    }
    return false;
}
