#pragma once

enum struct MatchStates {
    NoState,                // 0
    WaitingForUsers,        // 1 Match model created with both the user ids. Once User joins send an join ack and update match model
    WaitingForMatchReady,   // 2 Waiting to match scene to load and other animations to finish
    StartInnings,           // 3 Both the users are sent Innings start event and player selection page is shown
    PlayerSelection,        // 4 Once the start innings is done ack is sent to users and state of match is changed to PlayerSelection
    StartBall,              // 5 Once player is selected the state is changed to StartBall and the bowler is sent the set of balls, Change to ball selection
    BallSelection,          // 6 Once the ball is selected, validate that and send the shots available to batsman
    ShotSelection,          // 7 Once the shot is selected, validate that and then calculate the outcome and send the result to both and change the state to EndBall
    Outcome,                // 8 Based on the Outcome change state to PlayerSelection or StartBall
    EndBall,                // 9 Based on the Outcome change state to PlayerSelection or StartBall
    EndOver,                // 10 
    EndInnings,             // 11 If overs done or If 1st innings and target reached or all out then end innings
    MatchEnded,             // 11
    Reconnecting,           // 12 When client is trying to reconnect
    Min = NoState,
    Max = Reconnecting
};
