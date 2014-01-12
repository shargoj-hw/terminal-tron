#include <ncurses.h>
#include "renderer.h"

bool g_curses_on = false; 

/* Initialize ncurses  */
void init_ncurses() {
  initscr();
  noecho();
  curs_set(0);
  
  g_curses_on = true;
}

void shutdown_ncurses() {
  endwin();

  g_curses_on = false;
}

int main(int argc, char** argv) {
  init_ncurses();

  CH::game_state gs;
  gs.player = CH::pos(50, 50);
  CH::renderer renderer;

  char c;
  while (c != 'q') {
    c = getch();

    switch (c) {
    case 'h':
      gs.player = CH::pos(gs.player.x - 1, gs.player.y);
      break;
    case 'j':
      gs.player = CH::pos(gs.player.x, gs.player.y + 1);
      break;
    case 'k':
      gs.player = CH::pos(gs.player.x, gs.player.y - 1);
      break;
    case 'l':
      gs.player = CH::pos(gs.player.x + 1, gs.player.y);
      break;
    }

    renderer.render(gs);
  }

  shutdown_ncurses();
  return 0;
}
