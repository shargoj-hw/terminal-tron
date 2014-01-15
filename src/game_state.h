#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <stdexcept>
#include <list>
#include <string>
#include <map>
#include "pos.h"

namespace CH {

#define WALL_CHARACTER ('#')

  enum color {
    RED, YELLOW, GREEN, BLUE, WALL
  };

  enum direction {
    UP, DOWN, LEFT, RIGHT
  };

  class game_object {
  public:
    virtual char get_graphic() const = 0;
    virtual color get_color() const = 0;
    virtual pos get_position() const = 0;
  };

  typedef unsigned int player_id;
  
  static player_id g_ids = 0;

  class player : public game_object {
    const std::string name;
    const color col;
    const player_id id;
    pos position;
    direction dir;
    bool alive;
    unsigned int score;

  public:
    player(std::string name, color col, pos initial_pos, direction initial_dir)
      : name(name), col(col), id(g_ids++), position(initial_pos), dir(initial_dir), alive(true) { }

    virtual color get_color() const { return col; }
    virtual pos get_position() const { return position; } 
    virtual char get_graphic() const {
      switch(dir) {
      case UP:
	return '^';
      case DOWN:
	return 'v';
      case LEFT:
	return '<';
      case RIGHT:
	return '>';
      default:
	throw std::runtime_error("bad direction");
      }
    }

    player_id get_id() const { return id; }
    direction get_direction() const { return dir; }
    bool is_alive() const { return alive; }
    unsigned int get_score() const { return score; }

    void update_position(pos p) { position = p; }
    void update_direction(direction d) { dir = d; }
    void kill() { alive = false; }
    void add_to_score(unsigned int points) { score += points; }
  };

  class tail : public game_object { 
    const color col;
    const pos position;

  public:
    const player_id laid_by;
    tail(player p) : col(p.get_color()), position(p.get_position()), laid_by(p.get_id()) { }

    virtual color get_color() const { return col; }
    virtual pos get_position() const { return position; } 
    virtual char get_graphic() const { return WALL_CHARACTER; }    
  };

  struct game_state {
    const unsigned int width, height;
    std::map<pos, tail> tails; // map to support fast lookups
    std::list<player> players;

    game_state(const unsigned int width, const unsigned int height, std::list<player> players);

    void update(const std::map<player_id, direction> player_moves);

    bool is_game_over();

  private:
    player& player_by_id(player_id id);

    void update_player_directions(const std::map<player_id, direction> player_moves);
    void add_tails();
    void move_players_forward();
    void check_collisions_and_update_scores();
  };
  
}

#endif /* _GAMESTATE_H_ */
