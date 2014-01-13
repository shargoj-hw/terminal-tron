#include <ncurses.h>
#include "renderer.h"
#include "pos.h"

using namespace CH;

bool g_curses_on = false; 

/* Initialize ncurses  */
void init_ncurses() {
  initscr();
  start_color();

  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(WALL, COLOR_BLACK, COLOR_WHITE);

  noecho();
  curs_set(0);

  timeout(100);
  
  g_curses_on = true;
}

void shutdown_ncurses() {
  endwin();
  
  g_curses_on = false;
}

#include <list>
int main(int argc, char** argv) {
  init_ncurses();
  
  player player1 = player("p1", 'y', BLUE, pos(COLS/2, LINES/2), RIGHT);
  
  std::list<player> players;
  players.push_front(player1);

  game_state gs(COLS, LINES, players);
  renderer renderer;

  char c = 's';

  std::map<player_id, direction> player_moves;
  while (c != 'q') {
    player_moves.clear();
    c = getch();
    
    switch (c) {
    case 'h':
      player_moves.insert(std::pair<player_id, direction>(player1.id, LEFT));
      break;
    case 'j':
      player_moves.insert(std::pair<player_id, direction>(player1.id, DOWN));
      break;
    case 'k':
      player_moves.insert(std::pair<player_id, direction>(player1.id, UP));
      break;
    case 'l':
      player_moves.insert(std::pair<player_id, direction>(player1.id, RIGHT));
      break;
    }
        
    gs.update(player_moves);
    renderer.render(gs);
  }

  shutdown_ncurses();
  return 0;
}
