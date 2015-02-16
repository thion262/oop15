#include <iostream>
#include "HumanNimPlayer.hpp"

using namespace std;

HumanNimPlayer::HumanNimPlayer() {
   do {
      cout << "Your name: ";
      if (!(cin >> name)) {
	 name = "Anonymous";
      }
   } while (name == "");
   cout << "Welcome, " << name << endl;
}

const std::string& HumanNimPlayer::get_name() const {
   return name;
}

NimMove HumanNimPlayer::get_move(const NimGame& game) const {
   NimMove move;
   do {
      unsigned int heap_index; unsigned int count;
      cout << name << ", your move: ";
      if (!(cin >> heap_index >> count)) {
	 return NimMove();
      }
      move = NimMove(heap_index, count);
   } while (!game.valid_move(move));
   return move;
}

// support dynamic loading
extern "C" NimPlayer* construct() {
   return new HumanNimPlayer();
}
