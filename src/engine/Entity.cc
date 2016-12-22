#include "Entity.h"

namespace lp {

  int64 Entity::nextId = 0;

  Entity::Entity(float x, float y): id(nextId++) {

  }

}
