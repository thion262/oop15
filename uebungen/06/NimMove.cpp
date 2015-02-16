#include "NimMove.hpp"

NimMove::NimMove() : heap(0), count(0), resigned(true) {
}

NimMove::NimMove(unsigned int _heap, unsigned int _count) :
      // initialize members heap and count from the parameters
      heap(_heap), count(_count), resigned(false) {
   // nothing else to be done
}

bool NimMove::has_resigned() const {
   return resigned;
}

unsigned int NimMove::get_heap() const {
   return heap;
}

unsigned int NimMove::get_count() const {
   return count;
}
