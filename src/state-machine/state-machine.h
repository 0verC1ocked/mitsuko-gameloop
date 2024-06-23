#pragma once
#include <iostream>
#include <variant>
#include <vector>
#include <unordered_map>
#include "conditions.h"
#include "states/states.h"
#include "../utils/logger/logger.h"
#include <chrono>

// Define a base class for all states

template <typename... TMatchStates>
class StateMachine {
private:

    std::tuple<TMatchStates...> m_states;
    std::variant<TMatchStates*...> m_currentState;
    std::variant<TMatchStates*...> m_previousState;

    std::vector<std::unordered_map<TransitionalCondition, std::variant<TMatchStates*...>>> m_transitions;
    std::unordered_map<TransitionalCondition, std::variant<TMatchStates*...>> universal_transitions;
    void instantiateTransionalConditionsMap() {
        m_transitions = {
            { }, // NoState
            { { TransitionalCondition::BothUsersJoined, &std::get<WaitingForMatchReady>(m_states) }, { TransitionalCondition::CanEndMatch, &std::get<MatchEnded>(m_states) } }, // WaitingForUsers
            { { TransitionalCondition::BothMatchReady, &std::get<StartInnings>(m_states) }, { TransitionalCondition::CanEndMatch, &std::get<MatchEnded>(m_states) } }, // WaitingForMatchReady
            { { TransitionalCondition::BothInningsReady, &std::get<PlayerSelection>(m_states) }, }, // StartInnings
            { { TransitionalCondition::BatsmanAndBowlerSelected, &std::get<StartBall>(m_states) } }, // PlayerSelection
            { { TransitionalCondition::CanDoBallSelection, &std::get<BallSelection>(m_states) } }, // StartBall
            { { TransitionalCondition::CanDoShotSelection, &std::get<ShotSelection>(m_states) } }, // BallSelection
            { { TransitionalCondition::OutcomeCalculation, &std::get<Outcome>(m_states) } }, // ShotSelection
            { { TransitionalCondition::CanEndBall, &std::get<EndBall>(m_states) } }, //Outcome
            { { TransitionalCondition::CanDoPlayerSelection, &std::get<PlayerSelection>(m_states) }, { TransitionalCondition::CanEndOver, &std::get<EndOver>(m_states) }, { TransitionalCondition::CanStartBall, &std::get<StartBall>(m_states)}, { TransitionalCondition::CanEndInnings, &std::get<EndInnings>(m_states)} }, // EndBall
            { { TransitionalCondition::OverEnded, &std::get<PlayerSelection>(m_states) }, { TransitionalCondition::CanEndInnings, &std::get<EndInnings>(m_states) } }, // EndOver
            { { TransitionalCondition::CanEndFirstInnings, &std::get<StartInnings>(m_states) }, { TransitionalCondition::CanEndSecondInnings, &std::get<MatchEnded>(m_states) } }, // EndInnings
            { { TransitionalCondition::CanEndMatch, &std::get<MatchEnded>(m_states) } }, // MatchEnded
        };

        universal_transitions = {
            { TransitionalCondition::CanEndMatch, &std::get<MatchEnded>(m_states) },
            { TransitionalCondition::CanReconnect, &std::get<Reconnecting>(m_states) },
        };
    }

public:
    StateMachine() {
        m_currentState = &std::get<1>(m_states);
        m_previousState = &std::get<1>(m_states);
        instantiateTransionalConditionsMap();
    };
    ~StateMachine() {};
    template <typename MatchState>
    void setState() {
        m_currentState = &std::get<MatchState>(m_states);
    };

    void setState(std::variant<TMatchStates*...> state) {
        m_currentState = state;
    };

    long getCurrentStateTimeout() {
        return std::visit([this](auto currentState) { return currentState->time_out_seconds; }, m_currentState);
    }

    int getCurrentState() {
        return m_currentState.index();
    };

    int getPreviousState() {
        return m_previousState.index();
    };

    void preUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator) {
        auto executeOnCall = [this, &condition, &match_model, &allocator](auto currentState) {
            currentState->preUpdate(condition, match_model, allocator);
        };
        std::visit(executeOnCall, m_currentState);
    };

    void onUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator) {
        std::visit([this, &condition, &match_model, &allocator](auto currentState) {
                return currentState->onUpdate(condition, match_model, allocator);
        }, m_currentState);
    };

    void postUpdate(TransitionalCondition &condition, MatchModel &match_model, ArenaAllocator &allocator) {
        auto executeOnCall = [this, &condition, &match_model, &allocator](auto currentState) {
            currentState->postUpdate(condition, match_model, allocator);
        };
        std::visit(executeOnCall, m_currentState);
    };

    void update(MatchModel &match_model, ArenaAllocator &allocator) {
        TransitionalCondition condition = TransitionalCondition::NoConditionsMet;
        preUpdate(condition, match_model, allocator);
        onUpdate(condition, match_model, allocator);
        postUpdate(condition, match_model, allocator);
    };
};

// NOTE: should follow match state sequence

using MatchStateMachine = StateMachine<NoState, WaitingForUsers, WaitingForMatchReady, StartInnings, PlayerSelection, StartBall, BallSelection, ShotSelection, Outcome, EndBall, EndOver, EndInnings, MatchEnded, Reconnecting>;
