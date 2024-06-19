#include "../../server.h"


int roundToNearest10(double number) {
    return round((number / 10) * 10);
}

std::string getEventString(PAYLOAD::Events event) {
    switch (event) {
        case PAYLOAD::Events::NONE: return "NONE";
        case PAYLOAD::Events::OPP_JOINED: return "OPP_JOINED";
        case PAYLOAD::Events::MATCH_READY: return "MATCH_READY";
        case PAYLOAD::Events::MATCH_CREATE_FAILED: return "MATCH_CREATE_FAILED";
        case PAYLOAD::Events::JOINED_MATCH: return "JOINED_MATCH";
        case PAYLOAD::Events::MATCH_STARTED: return "MATCH_STARTED";
        case PAYLOAD::Events::MATCH_SCENE_LOADED: return "MATCH_SCENE_LOADED";
        case PAYLOAD::Events::TOSS_START: return "TOSS_START";
        case PAYLOAD::Events::TOSS_ACK: return "TOSS_ACK";
        case PAYLOAD::Events::TOSS_RESULT: return "TOSS_RESULT";
        case PAYLOAD::Events::BAT_BALL_SELECTION: return "BAT_BALL_SELECTION";
        case PAYLOAD::Events::MATCH_INNINGS_DETAILS: return "MATCH_INNINGS_DETAILS";
        case PAYLOAD::Events::INNINGS_INTRO: return "INNINGS_INTRO";
        case PAYLOAD::Events::INNINGS_INTO_ACK: return "INNINGS_INTO_ACK";
        case PAYLOAD::Events::SERVER_INNINGS_READY: return "SERVER_INNINGS_READY";
        case PAYLOAD::Events::OPENERS_SELECTED: return "OPENERS_SELECTED";
        case PAYLOAD::Events::CLIENT_INNINGS_READY: return "CLIENT_INNINGS_READY";
        case PAYLOAD::Events::INNINGS_START: return "INNINGS_START";
        case PAYLOAD::Events::INNINGS_START_ACK: return "INNINGS_START_ACK";
        case PAYLOAD::Events::START_CURRENT_OVER: return "START_CURRENT_OVER";
        case PAYLOAD::Events::START_BALL_EVENT: return "START_BALL_EVENT";
        case PAYLOAD::Events::DELIVEIRES_DATA_CREATAED: return "DELIVEIRES_DATA_CREATAED";
        case PAYLOAD::Events::DELIVERY_SELECTED: return "DELIVERY_SELECTED";
        case PAYLOAD::Events::SHOTS_DATA: return "SHOTS_DATA";
        case PAYLOAD::Events::BRACKET_SELECTED: return "BRACKET_SELECTED";
        case PAYLOAD::Events::SHOT_RESULT: return "SHOT_RESULT";
        case PAYLOAD::Events::OUTCOME_UPDATED_DATA: return "OUTCOME_UPDATED_DATA";
        case PAYLOAD::Events::SHOT_ANIMATIONS_FINISHED: return "SHOT_ANIMATIONS_FINISHED";
        case PAYLOAD::Events::END_CURRENT_BALL_EVENT: return "END_CURRENT_BALL_EVENT";
        case PAYLOAD::Events::NEXT_BATSMAN_SELECTED: return "NEXT_BATSMAN_SELECTED";
        case PAYLOAD::Events::END_CURRENT_BALL_EVENT_ACK: return "END_CURRENT_BALL_EVENT_ACK";
        case PAYLOAD::Events::END_CURRENT_OVER: return "END_CURRENT_OVER";
        case PAYLOAD::Events::NEXT_BOWLER_SELECTED: return "NEXT_BOWLER_SELECTED";
        case PAYLOAD::Events::END_OVER_ACK: return "END_OVER_ACK";
        case PAYLOAD::Events::PASSIVES_DATA: return "PASSIVES_DATA";
        case PAYLOAD::Events::UPDATE_LOCAL_PLAYER_STRENGTHS: return "UPDATE_LOCAL_PLAYER_STRENGTHS";
        case PAYLOAD::Events::ACTIVATE_BATSMAN_SA: return "ACTIVATE_BATSMAN_SA";
        case PAYLOAD::Events::BATSMAN_SA_ACTIVATED: return "BATSMAN_SA_ACTIVATED";
        case PAYLOAD::Events::ACTIVATE_BOWLER_SA: return "ACTIVATE_BOWLER_SA";
        case PAYLOAD::Events::BOWLER_SA_ACTIVATED: return "BOWLER_SA_ACTIVATED";
        case PAYLOAD::Events::BATSMAN_INSTANT_SA_ACTIVATE: return "BATSMAN_INSTANT_SA_ACTIVATE";
        case PAYLOAD::Events::BOWLER_INSTANT_SA_ACTIVATE: return "BOWLER_INSTANT_SA_ACTIVATE";
        case PAYLOAD::Events::MATCH_MISSION_UPDATED: return "MATCH_MISSION_UPDATED";
        case PAYLOAD::Events::MATCH_ARENAS_UPDATED: return "MATCH_ARENAS_UPDATED";
        case PAYLOAD::Events::END_FIRST_INNINGS: return "END_FIRST_INNINGS";
        case PAYLOAD::Events::END_FIRST_INNINGS_ACK: return "END_FIRST_INNINGS_ACK";
        case PAYLOAD::Events::END_MATCH: return "END_MATCH";
        case PAYLOAD::Events::ABORT_MATCH: return "ABORT_MATCH";
        case PAYLOAD::Events::FORFIET_MATCH: return "FORFIET_MATCH";
        case PAYLOAD::Events::REMATCH_JOIN: return "REMATCH_JOIN";
        case PAYLOAD::Events::REMATCH_START: return "REMATCH_START";
        case PAYLOAD::Events::TURN_START: return "TURN_START";
        case PAYLOAD::Events::TURN_END: return "TURN_END";
        case PAYLOAD::Events::TURN_MISS: return "TURN_MISS";
        case PAYLOAD::Events::DISCONNECT_TIMER_DATA: return "DISCONNECT_TIMER_DATA";
        case PAYLOAD::Events::CHAT_EMOJI: return "CHAT_EMOJI";
        case PAYLOAD::Events::PING: return "PING";
        case PAYLOAD::Events::BATSMAN_INSTANT_SA_INACTIVATE: return "BATSMAN_INSTANT_SA_INACTIVATE";
        case PAYLOAD::Events::BOWLER_INSTANT_SA_INACTIVATE: return "BOWLER_INSTANT_SA_INACTIVATE";
        case PAYLOAD::Events::FIELDING_MODE_CHANGED: return "FIELDING_MODE_CHANGED";
        case PAYLOAD::Events::DATA_UPDATE: return "DATA_UPDATE";
        case PAYLOAD::Events::SPECTATOR_JOINED: return "SPECTATOR_JOINED";
        case PAYLOAD::Events::SPECTATOR_JOIN_ACK: return "SPECTATOR_JOIN_ACK";
        case PAYLOAD::Events::FAST_MODE_SPEED_UP: return "FAST_MODE_SPEED_UP";
        case PAYLOAD::Events::FAST_MODE_SPEED_UP_ACK: return "FAST_MODE_SPEED_UP_ACK";
        case PAYLOAD::Events::THREAD_EXIT: return "THREAD_EXIT";
        case PAYLOAD::Events::MESSAGE: return "MESSAGE";
        case PAYLOAD::Events::INNINGS_READY: return "INNINGS_READY";
        case PAYLOAD::Events::START_BALL_EVENT_ACK: return "START_BALL_EVENT_ACK";
        case PAYLOAD::Events::RECONNECT: return "RECONNECT";
        case PAYLOAD::Events::CONNECT: return "CONNECT";
        case PAYLOAD::Events::CONNECT_ACK: return "CONNECT_ACK";
        case PAYLOAD::Events::CONNECTED: return "CONNECTED";
        case PAYLOAD::Events::PONG: return "PONG";
        case PAYLOAD::Events::RECONNECTED: return "RECONNECTED";
        case PAYLOAD::Events::DISCONNECT: return "DISCONNECT";
        case PAYLOAD::Events::MATCH_SCENE_LOADED_ACK: return "MATCH_SCENE_LOADED_ACK";
        default: return "UNKNOWN";
    }
}
