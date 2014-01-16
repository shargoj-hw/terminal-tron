#include <iostream>
#include <list>
#include <cstdlib>
#include <ncurses.h>
#include "renderer.h"
#include "pos.h"
#include "game_state.h"
#include "ai_player.h"

using namespace CH;

bool g_curses_on = false; 

#include <string>
// figlet -f isometric3 JIMS TRON
std::string JIM_TRON_LOGO[] = 
  { 
    "    ___                      ___           ___           ___     ",
    "   /  /\\         ___        /  /\\         /  /\\         /__/\\    ",
    "  /  /:/        /  /\\      /  /::\\       /  /::\\        \\  \\:\\   ",
    " /__/::\\       /  /:/     /  /:/\\:\\     /  /:/\\:\\        \\  \\:\\  ",
    " \\__\\/\\:\\     /  /:/     /  /:/~/:/    /  /:/  \\:\\   _____\\__\\:\\ ",
    "    \\  \\:\\   /  /::\\    /__/:/ /:/___ /__/:/ \\__\\:\\ /__/::::::::\\",
    "     \\__\\:\\ /__/:/\\:\\   \\  \\:\\/:::::/ \\  \\:\\ /  /:/ \\  \\:\\~~\\~~\\/",
    "     /  /:/ \\__\\/  \\:\\   \\  \\::/~~~~   \\  \\:\\  /:/   \\  \\:\\  ~~~ ",
    "    /__/:/       \\  \\:\\   \\  \\:\\        \\  \\:\\/:/     \\  \\:\\     ",
    "    \\__\\/         \\__\\/    \\  \\:\\        \\  \\::/       \\  \\:\\    ",
    "                            \\__\\/         \\__\\/         \\__\\/    ",
    "              --Press any key to continue--             "
  };

void display_logo(unsigned int start_x, unsigned int start_y) {
  for (std::string& logo_line: JIM_TRON_LOGO) {
    move(start_y++, start_x);
    printw(logo_line.c_str());
  }
}

void shutdown_ncurses();

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

  g_curses_on = true;

  atexit(shutdown_ncurses);
}

void shutdown_ncurses() {
  endwin();
  
  g_curses_on = false;
}

int main(int argc, char** argv) {
  init_ncurses();
  
  display_logo(COLS/2 - JIM_TRON_LOGO[0].length() / 2, LINES/8);
  getch();

  player player1 = player("p1", BLUE, pos(COLS/4, LINES/2), RIGHT);
  player player2 = player("p2", GREEN, pos(3*COLS/4, LINES/2), LEFT);
  
  random_ai_player ai(player2.get_id());

  std::list<player> players;
  players.push_front(player1);
  players.push_front(player2);

  game_state gs(COLS, LINES, players);
  renderer renderer;

  int c = 's';

  timeout(100);

  std::map<player_id, direction> player_moves;
  while (c != 'Q' && !gs.is_game_over()) {
    player_moves.clear();
    c = getch();
    
    switch (c) {
    case 'w':
      player_moves.insert(std::pair<player_id, direction>(player1.get_id(), UP));
      break;
    case 's':
      player_moves.insert(std::pair<player_id, direction>(player1.get_id(), DOWN));
      break;
    case 'a':
      player_moves.insert(std::pair<player_id, direction>(player1.get_id(), LEFT));
      break;
    case 'd':
      player_moves.insert(std::pair<player_id, direction>(player1.get_id(), RIGHT));
      break;
      /* TODO: uncomment these when I add 2 player back in.
	case 'i':
      player_moves.insert(std::pair<player_id, direction>(player2.get_id(), UP));
      break;
    case 'k':
      player_moves.insert(std::pair<player_id, direction>(player2.get_id(), DOWN));
      break;
    case 'j':
      player_moves.insert(std::pair<player_id, direction>(player2.get_id(), LEFT));
      break;
    case 'l':
      player_moves.insert(std::pair<player_id, direction>(player2.get_id(), RIGHT));
      break;
      */
    }

    player_moves.insert(std::pair<player_id, direction>(player2.get_id(), ai.next_move(gs)));

    gs.update(player_moves);
    renderer.render(gs);
  }

  return 0;
}
