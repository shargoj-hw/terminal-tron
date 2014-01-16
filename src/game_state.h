#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include "color.h"
#include "direction.h"
#include "game_object.h"
#include "player.h"
#include "pos.h"
#include "tail.h"

namespace CH {

  struct game_state {
    const unsigned int width, height;
    std::map<pos, tail> tails; // map to support fast lookups
    std::list<player> players;

    game_state(const unsigned int width, const unsigned int height, std::list<player> players);

    void update(const std::map<player_id, direction> player_moves);

    bool is_game_over();

    player player_by_id(player_id id) const; 
  private:
    player& player_ref_by_id(player_id id);

    void update_player_directions(const std::map<player_id, direction> player_moves);
    void add_tails();
    void move_players_forward();
    void check_collisions_and_update_scores();
  };  

}

#endif /* _GAMESTATE_H_ */
