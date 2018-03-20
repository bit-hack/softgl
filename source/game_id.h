#pragma once

enum game_id_t {
  e_unknown,
  e_nehe_lesson_01,
  e_quake_2,
  e_quake_3,
  e_half_life
};

game_id_t getGameId();
