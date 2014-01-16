#include "direction.h"

namespace CH {

  direction direction_opposite(direction d) {
    switch (d) {
    case UP:
      return DOWN;
      break;
    case DOWN:
      return UP;
      break;
    case LEFT:
      return RIGHT;
      break;
    case RIGHT:
      return LEFT;
      break;
    }
  }

}
