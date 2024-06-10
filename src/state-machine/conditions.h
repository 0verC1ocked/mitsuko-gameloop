#pragma once

enum struct TransitionalCondition {
    NoConditionsMet,
    BothUsersJoined,
    BothMatchReady,
    BothInningsReady,
    BatsmanAndBowlerSelected,
    CanDoPlayerSelection,
    CanStartBall,
    CanDoBallSelection,
    CanDoShotSelection,
    OutcomeCalculation,
    CanEndBall,
    CanEndOver,
    OverEnded,
    CanStartShot,
    CanEndFirstInnings,
    CanEndSecondInnings,
    CanEndInnings,
    CanEndMatch,
    CanReconnect,
    Reconnected,
    PreviousState
};


