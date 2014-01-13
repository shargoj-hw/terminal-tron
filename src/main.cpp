#include <ncurses.h>
#include "renderer.h"
#include "pos.h"

using namespace CH;

bool g_curses_on = false; 

#include <string>
// figlet -f isometric3 JIMS TRON
std::string JIM_TRON_LOGO[] = 
  { "    ___                      ___           ___          ",
    "   /  /\\       ___          /__/\\         /  /\\         ",
    "  /  /:/      /  /\\        |  |::\\       /  /:/_        ",
    " /__/::\\     /  /:/        |  |:|:\\     /  /:/ /\\       ",
    " \\__\\/\\:\\   /__/::\\      __|__|:|\\:\\   /  /:/ /::\\      ",
    "    \\  \\:\\  \\__\\/\\:\\__  /__/::::| \\:\\ /__/:/ /:/\\:\\     ",
    "     \\__\\:\\    \\  \\:\\/\\ \\  \\:\\~~\\__\\/ \\  \\:\\/:/~/:/     ",
    "     /  /:/     \\__\\::/  \\  \\:\\        \\  \\::/ /:/      ",
    "    /__/:/      /__/:/    \\  \\:\\        \\__\\/ /:/       ",
    "    \\__\\/       \\__\\/      \\  \\:\\         /__/:/        ",
    "                            \\__\\/         \\__\\/         ",
    "                  ___           ___           ___       ",
    "      ___        /  /\\         /  /\\         /__/\\      ",
    "     /  /\\      /  /::\\       /  /::\\        \\  \\:\\     ",
    "    /  /:/     /  /:/\\:\\     /  /:/\\:\\        \\  \\:\\    ",
    "   /  /:/     /  /:/~/:/    /  /:/  \\:\\   _____\\__\\:\\   ",
    "  /  /::\\    /__/:/ /:/___ /__/:/ \\__\\:\\ /__/::::::::\\  ",
    " /__/:/\\:\\   \\  \\:\\/:::::/ \\  \\:\\ /  /:/ \\  \\:\\~~\\~~\\/  ",
    " \\__\\/  \\:\\   \\  \\::/~~~~   \\  \\:\\  /:/   \\  \\:\\  ~~~   ",
    "      \\  \\:\\   \\  \\:\\        \\  \\:\\/:/     \\  \\:\\       ",
    "       \\__\\/    \\  \\:\\        \\  \\::/       \\  \\:\\      ",
    "                 \\__\\/         \\__\\/         \\__\\/      ",
    "              --Press any key to continue--             "
  };

void display_logo(unsigned int start_x, unsigned int start_y) {
  for (std::string& logo_line: JIM_TRON_LOGO) {
    move(start_y++, start_x);
    printw(logo_line.c_str());
  }
}

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
}

void shutdown_ncurses() {
  endwin();
  
  g_curses_on = false;
}

#include <iostream>
#include <list>
int main(int argc, char** argv) {
  init_ncurses();
  
  display_logo(COLS/2 - JIM_TRON_LOGO[0].length() / 2, LINES/8);
  getch();

  player player1 = player("p1", 'X', BLUE, pos(COLS/4, LINES/2), RIGHT);
  player player2 = player("p2", 'O', RED, pos(3*COLS/4, LINES/2), LEFT);

  std::list<player> players;
  players.push_front(player1);
  players.push_front(player2);

  game_state gs(COLS, LINES, players);
  renderer renderer;

  int c = 's';

  timeout(100);

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
