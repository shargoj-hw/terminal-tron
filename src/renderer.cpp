#include <ncurses.h>
#include <stdexcept>
#include "renderer.h"
#include "game_state.h"
#include "pos.h"

extern bool g_curses_on;

namespace CH {
  
  void draw_game_object(const game_object &go) {
    move(go.get_position().y, go.get_position().x);
    attron(COLOR_PAIR(go.get_color()));
    addch(go.get_graphic());
  }
  
  void renderer::render(const game_state gs) {
    if (!g_curses_on) {
      throw std::runtime_error("ncurses not initialized");
    }

    clear();

    attron(COLOR_PAIR(WALL));
    for(int x = 0; x < gs.width; x++) {
      move(0, x); addch('#');
      move(gs.height-1, x); addch('#');
    }

    for(int y = 0; y < gs.height; y++) {
      move(y, 0); addch('#');
      move(y, gs.width-1); addch('#');
    }
    
    for (auto& pos_to_tail: gs.tails) {
      draw_game_object(pos_to_tail.second);
    }

    for (auto& player: gs.players) {
      draw_game_object(player);
    }

    int score_y = gs.height/8;
    int score_x = gs.width/8;
    attron(COLOR_PAIR(WALL));
    for (auto& player: gs.players) {
      move(score_y++, score_x);
      printw("Player %s: %d", player.get_name().c_str(), player.get_score());
    }

    refresh();
  }
}
