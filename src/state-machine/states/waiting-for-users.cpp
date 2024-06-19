#include "../../server.h"

void WaitingForUsers::preUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &match_model, PayloadBuilder* payloadBuilder) {
    if (match_model->has_any_bot_client()) {
        botPlay(condition, match_model, payloadBuilder);
    }
}

void WaitingForUsers::onUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &match_model, PayloadBuilder* payloadBuilder) {
    try {
        if (match_model->reachedCancelTimeout()) {
            if (match_model->joinState == JoinStates::NoJoins) {
                match_model->canceled = true;
                condition = TransitionalCondition::CanEndMatch;
            } else if (match_model->joinState == JoinStates::FirstJoin) {
                if (match_model->isHomeNotConnected() || match_model->isAwayNotConnected()) {
                    match_model->canceled = true;
                    condition = TransitionalCondition::CanEndMatch;
                } else if (match_model->isHomeDisconnected() && match_model->isAwayConnected()) {
                    match_model->users[match_model->home].playState = PlayStates::Forfiet;
                    condition = TransitionalCondition::CanEndMatch;
                } else if (match_model->isHomeConnected() && match_model->isAwayDisconnected()) {
                    match_model->users[match_model->away].playState = PlayStates::Forfiet;
                    condition = TransitionalCondition::CanEndMatch;
                } else {
                    match_model->canceled = true;
                    condition = TransitionalCondition::CanEndMatch;
                }
            }
        }
    if (match_model->message_buffer.size() <= 0) return;
    for (EventMessage &em: match_model->message_buffer) {
        if (em.checkIfExpired()) {
            Logger::Log(ERROR,"[" + match_model->matchId + "] WaitingForUsers::onUpdate " + "Message has expired!");
            em.processed = true;
        }
        PAYLOAD::Payload* payload = payloadBuilder->newPayload();
        payload->ParseFromString(em.message);
        if (match_model->checkIfUserIdBelongsToThisMatch(payload->data().userid())) {
            if (match_model->joinState == JoinStates::NoJoins) {
                match_model->joinState = JoinStates::FirstJoin;
                match_model->first_join_at = std::chrono::high_resolution_clock::now();
                Logger::Log(INFO, "[" + match_model->matchId + "] WaitingForUsers::onUpdate " + "FirstJoin by " + payload->data().userid());
                match_model->stateStartTime = std::chrono::high_resolution_clock::now();
            } else if (match_model->joinState == JoinStates::FirstJoin) {
                match_model->joinState = JoinStates::SecondJoin;
                match_model->second_join_at = std::chrono::high_resolution_clock::now();
                Logger::Log(INFO,"[" + match_model->matchId + "] WaitingForUsers::onUpdate " +  "SecondJoin by " + payload->data().userid());
            }
            em.processed = true;
        }
    }

    match_model->removeProcessedMessages();
    
    if (match_model->joinState == JoinStates::SecondJoin) {
        condition = TransitionalCondition::BothUsersJoined;
    }

    } catch (const std::exception& e) {
        Logger::Log(ERROR, e.what());
    }

}

void WaitingForUsers::postUpdate(TransitionalCondition& condition, const std::shared_ptr<MatchModel> &match_model, PayloadBuilder* payloadBuilder) {
    try {
        if (match_model->joinState == JoinStates::SecondJoin && condition == TransitionalCondition::BothUsersJoined) {
            for (auto& u : match_model->users) {
                PAYLOAD::Payload* payload = payloadBuilder->newPayload();
                payloadBuilder->setEvent(PAYLOAD::Events::MATCH_READY);
                payloadBuilder->setTeam(match_model->home == u.first ? PAYLOAD::TeamPosition::HOME_TEAM : PAYLOAD::AWAY_TEAM);
                payloadBuilder->build(payload);
                std::string serializedData = payload->SerializeAsString();
                if (u.second.canSendPacket()) {
                    IPC::IPCMessage* ipcMessage = payloadBuilder->newIPCMessage();
                    ipcMessage->set_type(IPC::IPCMessageType::IPC_ENET_SEND);
                    ipcMessage->set_userid(u.first);
                    ipcMessage->set_data(payload->SerializeAsString());
                    GameLoop::getGameLoopInstance()->queueData(ipcMessage->SerializeAsString());
                    u.second.ack = ACK::UserReady;
                    Logger::Log(INFO, "[" + match_model->matchId + "] WaitingForUsers::postUpdate " + "Queued " + getEventString(PAYLOAD::Events::MATCH_READY) + " event packet to peer " + u.first);
                    u.second.previous_event = PAYLOAD::Events::MATCH_READY;  
                } else {
                    if (!u.second.is_bot)
                        Logger::Log(ERROR, "[" + match_model->matchId + "] WaitingForUsers::postUpdate " + " Peer is null for user " + u.first);
                }
            }
        }
    } catch (const std::exception& e) {
        Logger::Log(ERROR, e.what());
    }
}

void WaitingForUsers::autoPlay(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &match_model, PayloadBuilder *pb) {

}

void WaitingForUsers::botPlay(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &match_model, PayloadBuilder *pb) {
    std::string bot_team;
    std::string real_team;
    if (match_model->is_home_bot()) {
        bot_team = match_model->home;
        real_team = match_model->away;
    } else if (match_model->is_away_bot()) {
        bot_team = match_model->away;
        real_team = match_model->home;
    } else {
        return;
    }
    if (!match_model->users[bot_team].auto_play) {
        match_model->users[bot_team].setConnectionState(ConnectionState::Connected);
    
        PAYLOAD::Payload* payload = pb->newPayload();

        pb->setEvent(PAYLOAD::Events::JOINED_MATCH);
        pb->setRoomId(match_model->matchId);
        pb->setUserId(bot_team);
        pb->setOpponentId(real_team);
        pb->build(payload);
        Logger::Log(NOTICE, "Bot joined the match");
        
        match_model->message_buffer.push_back(EventMessage { payload->SerializeAsString() });

        match_model->users[bot_team].auto_play = true;
    }
}
