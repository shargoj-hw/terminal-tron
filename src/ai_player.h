#include "player.h"
#include "game_state.h"

#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

namespace CH {

  class ai_player {
    const player_id id;

  public:
    ai_player(player_id id);

    player_id get_player_id() const;

    virtual direction next_move(const game_state gs) = 0;
  };

  class random_ai_player : public ai_player {
    std::mt19937 gen;

  public:
    random_ai_player(player_id id);

    virtual direction next_move(const game_state gs);
  };

}
#endif /* _AI_PLAYER_H_ */
