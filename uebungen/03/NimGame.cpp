#include <cassert>
#include <vector>
#include "NimGame.hpp"

NimGame::NimGame(unsigned int number_of_heaps_, unsigned int maxtake_) :
      number_of_heaps(number_of_heaps_), maxtake(maxtake_),
      /* make heap_size a vector of number_of_heaps elements */
      heap_size(number_of_heaps_),
      next_player(PLAYER1) {
}

unsigned int NimGame::get_number_of_heaps() const {
   return number_of_heaps;
}

void NimGame::set_heap_size(unsigned int index, unsigned int size) {
   assert(index < number_of_heaps);
   heap_size[index] = size;
}

unsigned int NimGame::get_heap_size(unsigned int index) const {
   assert(index < number_of_heaps);
   return heap_size[index];
}

bool NimGame::finished() const {
   for (unsigned int i = 0; i < number_of_heaps; ++i) {
      if (heap_size[i] > 0) return false;
   }
   return true;
}

NimGame::Player NimGame::winner() const {
   assert(finished());
   if (next_player == PLAYER1) {
      return PLAYER2;
   } else {
      return PLAYER1;
   }
}

NimGame::Player NimGame::get_next_player() const {
   assert(!finished());
   return next_player;
}

bool NimGame::valid_move(NimMove move) const {
   assert(!finished());
   return move.get_heap() < number_of_heaps &&
          move.get_count() <= heap_size[move.get_heap()] &&
	  (maxtake == 0 || move.get_count() <= maxtake);
}

void NimGame::execute_move(NimMove move) {
   assert(valid_move(move));
   heap_size[move.get_heap()] -= move.get_count();
   switch (next_player) {
      case PLAYER1: next_player = PLAYER2; break;
      case PLAYER2: next_player = PLAYER1; break;
   }
}

unsigned int NimGame::nim_value() const {
   unsigned int val = 0;
   for (unsigned int i = 0; i < number_of_heaps; ++i) {
      unsigned int nimval = heap_size[i];
      if (maxtake) nimval %= (maxtake + 1);
      val ^= nimval;
   }
   return val;
}
