#include <string>
#include "color.h"
#include "direction.h"
#include "game_object.h"
#include "pos.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

namespace CH {

  typedef unsigned int player_id;

  class player : public game_object {
    const std::string name;
    const color col;
    const player_id id;
    pos position;
    direction dir;
    bool alive;
    unsigned int score;

  public:
    player(std::string name, color col, pos initial_pos, direction initial_dir);

    virtual color get_color() const;
    virtual pos get_position() const;
    virtual char get_graphic() const;

    player_id get_id() const;
    std::string get_name() const;
    direction get_direction() const;
    bool is_alive() const;
    unsigned int get_score() const;

    void update_position(pos p);
    void update_direction(direction d);
    void kill();
    void add_to_score(unsigned int points);
  };

}

#endif /* _PLAYER_H_ */
