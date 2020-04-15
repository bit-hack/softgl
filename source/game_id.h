#pragma once

enum game_id_t {
  e_unknown,
  e_nehe_lesson_01,
  e_quake_2,
  e_quake_3,
  e_half_life,
  e_half_life_of_demo,
  e_ut99_goty,
  e_ut2003_demo,
  e_unreal_gold
};

game_id_t getGameId();
