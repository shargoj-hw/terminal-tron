#include "color.h"
#include "game_object.h"
#include "player.h"
#include "pos.h"

#ifndef _TAIL_H_
#define _TAIL_H_

namespace CH {

#define WALL_CHARACTER ('#')
  
  class tail : public game_object { 
    const color col;
    const pos position;

  public:
    const player_id laid_by;
    tail(player p);

    virtual color get_color() const;
    virtual pos get_position() const;
    virtual char get_graphic() const;
  };

}

#endif /* _TAIL_H_ */
