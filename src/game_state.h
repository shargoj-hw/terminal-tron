#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include <string>
#include <map>
#include "pos.h"

namespace CH {

#define WALL_CHARACTER ('X')

  enum color {
    RED, YELLOW, GREEN, BLUE, PURPLE, ORANGE
  };

  enum direction {
    UP, DOWN, LEFT, RIGHT
  };

  struct game_object {
    char graphic;
    color col;
    pos position;

    game_object(char graphic, color col, pos position) : 
      graphic(graphic), col(col), position(position) { }
  };

  typedef unsigned int player_id;
  
  static player_id g_ids = 0;

  struct player : game_object {
    const std::string name;
    const player_id id;

    direction dir;
    unsigned int score;

    player(std::string name, char graphic, color col, pos initial_pos, direction initial_dir)
      : game_object(graphic, col, initial_pos), name(name), id(g_ids++), dir(initial_dir) { }
  };

  struct tail : game_object { 
    player_id laid_by;

    tail(player p) : game_object(WALL_CHARACTER, p.col, p.position), laid_by(p.id) { }
  };

  struct game_state {
    const unsigned int width, height;
    std::map<pos, tail> tails; // map to support fast lookups
    std::list<player> players;

    game_state(const unsigned int width, const unsigned int height, std::list<player> players);

    void update(const std::map<player_id, direction> player_moves);

  private:
    player& player_by_id(player_id id);

    void update_player_directions(const std::map<player_id, direction> player_moves);
    void add_tails();
    void move_players_forward();
  };
  
}

#endif /* _GAMESTATE_H_ */
