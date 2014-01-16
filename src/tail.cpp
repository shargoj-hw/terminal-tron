#include "tail.h"

namespace CH {

  tail::tail(player p) : col(p.get_color()), position(p.get_position()), laid_by(p.get_id()) { }

  color tail::get_color() const { return col; }
  pos tail::get_position() const { return position; } 
  char tail::get_graphic() const { return WALL_CHARACTER; }    

}
