#include <ncurses.h>
#include <stdexcept>
#include "renderer.h"
#include "game_state.h"
#include "pos.h"

extern bool g_curses_on;

namespace CH {

  void renderer::render(const game_state gs) {
    if (!g_curses_on) {
      throw std::runtime_error("ncurses not initialized");
    }

    clear();
    
    for (auto tail_iter = gs.tails.begin(); tail_iter != gs.tails.end(); tail_iter++) {
      tail t = tail_iter->second;
      move(t.position.y, t.position.x);
      addch(t.graphic);
    }

    for (auto player_iter = gs.players.begin(); player_iter != gs.players.end(); player_iter++) {
      player p = *player_iter;
      move(p.position.y, p.position.x);
      addch(p.graphic);
    }

    refresh();
  }

}
