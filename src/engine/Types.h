#pragma once

#include "oxygine-framework.h"
#include <stdint.h>

namespace lp {

  typedef int8_t int8;
  typedef uint8_t uint8;
  typedef int16_t int16;
  typedef uint16_t uint16;
  typedef int32_t int32;
  typedef uint32_t uint32;
  typedef int64_t int64;
  typedef uint64_t uint64;
  typedef float float32;
  typedef double float64;
  typedef intptr_t intptr;
  typedef uintptr_t uintptr;

  typedef unsigned char uchar;

  static const int32_t InvalidIndex = -1;
  static const int32_t EndOfString = -1;
  static const int32_t EndOfFile = -1;

  #define Ptr oxygine::intrusive_ptr

} // namespace lp
