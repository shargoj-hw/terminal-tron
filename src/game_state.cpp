#include <map>
#include <stdexcept>
#include "game_state.h"
#include "pos.h"

namespace CH {

  game_state::game_state(unsigned int width, unsigned int height, std::list<player> players)
    : width(width), height(height), players(players) { }


  player& game_state::player_by_id(player_id id) {
    for (auto& p: players) {
      if (p.id == id) return p;
    }
    
    throw std::runtime_error("no player found");
  }

  void game_state::update(const std::map<player_id, direction> new_player_directions) {
    update_player_directions(new_player_directions);
    add_tails();
    move_players_forward();
  }

  void game_state::update_player_directions(const std::map<player_id, direction> new_player_directions) {
    for (auto& player_to_direction:  new_player_directions) {
      player_by_id(player_to_direction.first).dir = player_to_direction.second;
    }    
  }

  void game_state::add_tails() {
    for (auto& p: players) {
      tails.insert(std::pair<pos, tail>(p.position, tail(p)));
    }
  }

  void game_state::move_players_forward() {
    for (auto& p: players) {
      switch (p.dir) {
      case UP:
	p.position = pos(p.position.x, p.position.y - 1);
	break;
      case DOWN:
	p.position = pos(p.position.x, p.position.y + 1);
	break;
      case LEFT:
	p.position = pos(p.position.x - 1, p.position.y);
	break;
      case RIGHT:
	p.position = pos(p.position.x + 1, p.position.y);
	break;
      }
    }
  }
}
