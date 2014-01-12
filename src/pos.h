#ifndef _POS_H_
#define _POS_H_

namespace CH {

  /* Represents a position in the GameWorld. Pos(0,0) is in the upper left corner. */
  struct pos {
    int x, y;

  pos() : x(0), y(0) { }
  pos(int _x, int _y) : x(_x), y(_y) { };
  };

}

#endif /* _POS_H_ */
