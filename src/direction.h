#ifndef _DIRECTION_H_
#define _DIRECTION_H_

namespace CH {

  enum direction {
    UP, DOWN, LEFT, RIGHT
  };

  direction direction_opposite(direction d);
  
}

#endif /* _DIRECTION_H_ */
