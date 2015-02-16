#include <iostream>
#include "OptimalNimPlayer.hpp"

OptimalNimPlayer::OptimalNimPlayer() : name("Computer") {
}

const std::string& OptimalNimPlayer::get_name() const {
   return name;
}

NimMove OptimalNimPlayer::get_move(const NimGame& game) const {
   unsigned int number_of_heaps = game.get_number_of_heaps();
   if (game.nim_value() == 0) {
      // bad luck
      for (unsigned int i = 0; i < number_of_heaps; ++i) {
	 if (game.get_heap_size(i) > 0) {
	    return NimMove(i, 1);
	 }
      }
   } else {
      // find a winning move
      unsigned int maxtake = game.get_maximal_take();
      for (unsigned int i = 0; i < number_of_heaps; ++i) {
	 unsigned int max = game.get_heap_size(i);
	 if (maxtake && max > maxtake) max = maxtake;
	 for (unsigned int count = 1; count <= max; ++count) {
	    NimGame test = game;
	    NimMove move(i, count);
	    test.execute_move(move);
	    if (test.nim_value() == 0) {
	       return move;
	    }
	 }
      }
      // oops, our algorithm failed, we give up...
      return NimMove();
   }
}

// support dynamic loading
extern "C" NimPlayer* construct() {
   return new OptimalNimPlayer();
}
