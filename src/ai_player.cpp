#include "ai_player.h"

namespace CH {

  ai_player::ai_player(player_id id) : id(id) { };

  player_id ai_player::get_player_id() const { return id; }


  random_ai_player::random_ai_player(player_id id) : ai_player(id) { }

  direction random_ai_player::next_move(const game_state gs) {
    player me = gs.player_by_id(get_player_id());
      
    float rand = std::generate_canonical<float, 32>(gen);

    if (rand < .30) {
      return me.get_direction();
    }
      
    rand = std::generate_canonical<float, 32>(gen);

    if (rand < .25) {
      return LEFT;
    } else if (rand < .50) {
      return RIGHT;
    } else if (rand < .75) {
      return UP;
    } else {
      return DOWN;
    }
  }
}
