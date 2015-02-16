#include <cassert>
#include <vector>
#include "NimGame.hpp"

NimGame::NimGame(unsigned int _number_of_heaps, unsigned int _maxtake) :
      number_of_heaps(_number_of_heaps), maxtake(_maxtake),
      /* make heap_size a vector of number_of_heaps elements */
      heap_size(_number_of_heaps),
      resigned(false), next_player(PLAYER1) {
}

unsigned int NimGame::get_number_of_heaps() const {
   return number_of_heaps;
}

unsigned int NimGame::get_maximal_take() const {
   return maxtake;
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
   if (resigned) return true;
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
   // always accept a resignation
   if (move.has_resigned()) return true;
   // regular move
   return move.get_heap() < number_of_heaps &&
          move.get_count() <= heap_size[move.get_heap()] &&
	  (maxtake == 0 || move.get_count() <= maxtake);
}

void NimGame::execute_move(NimMove move) {
   assert(valid_move(move));
   if (move.has_resigned()) {
      // accept resignation
      resigned = true;
   } else {
      // regular move
      heap_size[move.get_heap()] -= move.get_count();
      switch (next_player) {
	 case PLAYER1: next_player = PLAYER2; break;
	 case PLAYER2: next_player = PLAYER1; break;
      }
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
