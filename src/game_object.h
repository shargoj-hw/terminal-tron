#include "color.h"
#include "pos.h"

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

namespace CH {

  class game_object {
  public:
    virtual char get_graphic() const = 0;
    virtual color get_color() const = 0;
    virtual pos get_position() const = 0;
  };

}

#endif /* _GAME_OBJECT_H_ */
