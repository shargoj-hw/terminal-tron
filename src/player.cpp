#include <string>
#include "color.h"
#include "direction.h"
#include "game_object.h"
#include "player.h"
#include "pos.h"

namespace CH {

  static player_id g_ids = 0;

  player::player(std::string name, color col, pos initial_pos, direction initial_dir)
    : name(name), col(col), id(g_ids++), position(initial_pos), dir(initial_dir), alive(true) { }

  color player::get_color() const { return col; }
  std::string player::get_name() const { return name; }
  pos player::get_position() const { return position; } 
  char player::get_graphic() const {
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

  player_id player::get_id() const { return id; }
  direction player::get_direction() const { return dir; }
  bool player::is_alive() const { return alive; }
  unsigned int player::get_score() const { return score; }

  void player::update_position(pos p) { position = p; }
  void player::update_direction(direction d) { dir = d; }
  void player::kill() { alive = false; }
  void player::add_to_score(unsigned int points) { score += points; }

}
