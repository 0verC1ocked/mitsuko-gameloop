#pragma once

#include <string>
#include <vector>
#include "rps.h"
#include "sa.h"
#include "passive.h"
#include "ball.h"

enum struct Rarity : int {
    NONE = 0,
    COMMON = 1,
    RELIABLE = 2,
    BRILLIANT = 3,
    WORLD_CLASS = 4,
};


enum struct Classification : int {
    NONE = 0,
    BATSMAN = 1,
    BOWLER = 2
};

enum struct Trait : int {
    NONE = 0,
    SEAMER_AGGRESSIVE = 1,
    SEAMER_DEFENSIVE = 2,
    BOWLER_NUETRAL = 3,
    COMMON_NUETRAL = 4
};

enum struct Gender : int {
    NONE = 0,
    MALE = 1,
    FEMALE = 2,
};

enum struct BattingStyle : int {
    RIGHT_HAND = 0,
    LEFT_HAND = 1,
};

enum struct BowlingStyle : int {
    FAST = 0,
    SPIN = 1,
    NONE = 3
};


struct Character {
    int character_id;
    bool status;
    std::string nickname;
    Rarity rarity;
    int image_number;
    Classification classification;
    Gender gender;
    Trait trait;
    BattingStyle batting_style;
    BowlingStyle bowling_style;
    SA sa;
    RPS::Type rps = RPS::Type::None;
    std::vector<Passive> passives = {};
};

enum struct Strike {
    None = 0,
    OnStrike = 1,
    OffStrike = 2
};

struct PassiveInfo {
    Passive passive;
    bool applied = false;
    int applied_count = 0;
};

struct AttributeBoosts {
    double lhb_rhb_debuff = 0.0;
    double lhb_rhb_debuff_ka_nerf = 0.0;
    double confidence_boost = 0.0;
    double confidence_boost_buff = 0.0;
    double passive_boost = 0.0;
    double permanent_passive_boost = 0.0;
    double confidence_nerf = 0.0;
    double prop_boost = 0.0;
    double prop_nerf = 0.0;
    bool reducing_odds_six_nerf = false;
    bool reducing_odds_four_nerf = false;
    bool negate_first_two_ball_nerf = false;
    void reset() {
        lhb_rhb_debuff = 0.0;
        confidence_boost = 0.0;
        passive_boost = 0.0;
        prop_boost = 0.0;
        prop_nerf = 0.0;
        permanent_passive_boost = 0.0;
        confidence_boost_buff = 0.0;
        lhb_rhb_debuff_ka_nerf = 0.0;
        reducing_odds_six_nerf = false;
        reducing_odds_four_nerf = false;
        negate_first_two_ball_nerf = false;
    }

    void reset_passive_attributes() {
        prop_nerf = 0.0;
        prop_boost = 0.0;
        passive_boost = 0.0;
        confidence_boost_buff = 0.0;
        confidence_nerf = 0.0;
        lhb_rhb_debuff_ka_nerf = 0.0;
        reducing_odds_six_nerf = false;
        reducing_odds_four_nerf = false;
        negate_first_two_ball_nerf = false;
    }
};

struct PropInfo {
    int prop_id;
    bool applied = false;
};

struct Player : Character {
    short int level;
    short int lineup_number = -1;
    int power = 0;
    IBallDistribution ball_distribution;
    Strike strike = Strike::None;
    bool out = false;
    bool used_player = false;
    int balls_faced = 0;
    int fours_hit = 0;
    int sixs_hit = 0;
    int hits = 0;
    int misses = 0;
    AttributeBoosts attribute_boosts;
    int equipment_slots[4] = { -1, -1, -1, -1 };
    std::vector<PassiveInfo> passives_info;
    int selected_position = -1;
    std::vector<PropInfo> props = {};
    int runs_scored = 0;
    int wickets_taken = 0;
    int balls_bowled = 0;
    int runs_conceded = 0;
    static void fromCharacterToPlayer(const Character& character, Player& player, short int level, short int lineup_number, int power, std::vector<Passive>& passives) {
        player.level = level;
        player.lineup_number = lineup_number;
        player.character_id = character.character_id;
        player.status = character.status;
        player.nickname = character.nickname;
        player.rarity = character.rarity;
        player.image_number = character.image_number;
        player.classification = character.classification;
        player.gender = character.gender;
        player.trait = character.trait;
        player.batting_style = character.batting_style;
        player.bowling_style = character.bowling_style;
        if (player.classification == Classification::BOWLER) {
            player.ball_distribution = { 1, 3, 2 }; 
        }
        player.power = power;
        player.out = false;
        player.used_player = false;
        player.strike = Strike::None;
        player.sa = character.sa;

        for (auto passive : passives) {
            player.passives_info.push_back({ passive, false, 0 });
        }

        player.rps = character.rps;
    }
    void reset_fields_on_inning_switch() {
        used_player = false;
        out = false;
        strike = Strike::None;
        attribute_boosts.reset();
        for (auto& passive: passives_info) {
            passive.applied = false;
        }

        for (auto& prop: props) {
            prop.applied = false;
        }
        selected_position = -1;
    }

    void reset_attributes_on_ball_change() {
        attribute_boosts.reset_passive_attributes();
    }
};
