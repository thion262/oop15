#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include "RandomNimPlayer.hpp"

static bool initialized = false;

RandomNimPlayer::RandomNimPlayer() : name("Randy") {
   if (!initialized) {
      srand(getpid() ^ time(0));
      initialized = true;
   }
}

const std::string& RandomNimPlayer::get_name() const {
   return name;
}

NimMove RandomNimPlayer::get_move(const NimGame& game) const {
   std::vector<NimMove> moves;
   unsigned int number_of_heaps = game.get_number_of_heaps();
   unsigned int maxtake = game.get_maximal_take();
   for (unsigned int i = 0; i < number_of_heaps; ++i) {
      unsigned int max = game.get_heap_size(i);
      if (maxtake && max > maxtake) max = maxtake;
      for (unsigned int count = 1; count <= max; ++count) {
	 moves.push_back(NimMove(i, count));
      }
   }
   if (moves.size() == 0) return NimMove();
   return moves[rand() % moves.size()];
}

// support dynamic loading
extern "C" NimPlayer* construct() {
   return new RandomNimPlayer();
}
