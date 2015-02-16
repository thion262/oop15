#include "NimMove.hpp"

NimMove::NimMove() : heap(0), count(0) {
}

NimMove::NimMove(unsigned int heap_, unsigned int count_) :
      // initialize members heap and count from the parameters
      heap(heap_), count(count_) {
   // nothing else to be done
}

unsigned int NimMove::get_heap() const {
   return heap;
}

unsigned int NimMove::get_count() const {
   return count;
}
