#include <map>
#include <stdexcept>
#include "direction.h"
#include "game_state.h"
#include "pos.h"

namespace CH {

  game_state::game_state(unsigned int width, unsigned int height, std::list<player> players)
    : width(width), height(height), players(players) { }

  player game_state::player_by_id(player_id id) const {
    for (auto& p: players) {
      if (p.get_id() == id) return p;
    }

    throw std::runtime_error("no player found");
  }

  player& game_state::player_ref_by_id(player_id id) {
    for (auto& p: players) {
      if (p.get_id() == id) return p;
    }
    
    throw std::runtime_error("no player found");
  }

  void game_state::update(const std::map<player_id, direction> new_player_directions) {
    update_player_directions(new_player_directions);
    add_tails();
    move_players_forward();
    check_collisions_and_update_scores();
  }

  void game_state::update_player_directions(const std::map<player_id, direction> new_player_directions) {
    for (auto& player_to_direction:  new_player_directions) {
      player& p = player_ref_by_id(player_to_direction.first);
      if (!p.is_alive()) continue;
      if (direction_opposite(p.get_direction()) == player_to_direction.second) continue;
      p.update_direction(player_to_direction.second);
    }    
  }

  void game_state::add_tails() {
    for (auto& p: players) {
      if (!p.is_alive()) continue;
      tails.insert(std::pair<pos, tail>(p.get_position(), tail(p)));
    }
  }

  void game_state::move_players_forward() {
    for (auto& p: players) {
      if (!p.is_alive()) continue;

      switch (p.get_direction()) {
      case UP:
	p.update_position(pos(p.get_position().x, p.get_position().y - 1));
	break;
      case DOWN:
	p.update_position(pos(p.get_position().x, p.get_position().y + 1));
	break;
      case LEFT:
	p.update_position(pos(p.get_position().x - 1, p.get_position().y));
	break;
      case RIGHT:
	p.update_position(pos(p.get_position().x + 1, p.get_position().y));
	break;
      }
    }
  }

  void game_state::check_collisions_and_update_scores() {
    for (auto& p: players) {
      if (!p.is_alive()) continue;

      // Check the bounds of the map
      pos ppos = p.get_position();
      if (ppos.x <= 0
	  || ppos.x >= width - 1
	  || ppos.y <= 0
	  || ppos.y >= height - 1) {
	p.kill();
	return;
      }

      // Check collisions with tails.
      auto tail_iter = tails.find(p.get_position());
      if (tail_iter != tails.end()) {
	p.kill();
	if (tail_iter->second.laid_by != p.get_id())
	  player_ref_by_id(tail_iter->second.laid_by).add_to_score(100);
      }

      // Check that players haven't hit each other.
      for (auto& p2 : players) {
	if (p.get_id() != p2.get_id() && p.get_position() == p2.get_position()) {
	  p.kill();
	  p2.kill();
	}
      }

      // Add to score if the player's still alive!
      if (p.is_alive()) p.add_to_score(10);
    }
  }

  bool game_state::is_game_over() {
    int num_alive = 0;
    
    for (auto& p: players) 
      if (p.is_alive()) num_alive++;
    
    return num_alive <= 1;
 }
}
