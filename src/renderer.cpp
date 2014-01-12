#include <ncurses.h>
#include <stdexcept>
#include "renderer.h"
#include "game_state.h"
#include "pos.h"

extern bool g_curses_on;

namespace CH {

  void renderer::render(game_state gs) {
    if (!g_curses_on) {
      throw std::runtime_error("ncurses not initialized");
    }

    clear();
    
    move(gs.player.y, gs.player.x);
    addch('@');

    refresh();
  }

}
