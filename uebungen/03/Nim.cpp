#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "NimMove.hpp"
#include "NimGame.hpp"

using namespace std;

int main() {
   cout << "*** Game of Nim ***" << endl;

   // read parameters of the game
   unsigned int number_of_heaps;
   cout << "Number of heaps: ";
   if (!(cin >> number_of_heaps) || number_of_heaps == 0) {
      cout << "Bye!" << endl; return 1;
   }
   unsigned int maxtake;
   cout << "Maximal number of sticks that can be taken in one move: ";
   if (!(cin >> maxtake)) {
      cout << "Bye!" << endl; return 1;
   }

   // seed pseudo random generator
   srand(getpid() ^ time(0));
   // setup game
   NimGame game(number_of_heaps, maxtake);
   unsigned int minsize; unsigned int maxsize;
   if (maxtake) {
      minsize = maxtake * 2; maxsize = maxtake * 4;
   } else {
      minsize = 1; maxsize = 7;
   }
   unsigned int range = maxsize - minsize + 1;
   for (unsigned int i = 0; i < number_of_heaps; ++i) {
      game.set_heap_size(i, rand() % range + minsize);
   }

   while (!game.finished()) {
      // print current state
      cout << "Heaps:";
      for (unsigned int i = 0; i < number_of_heaps; ++i) {
	 cout << " " << game.get_heap_size(i);
      }
      cout << endl;
      NimMove move;
      if (game.get_next_player() == NimGame::PLAYER1) {
	 // human player
	 do {
	    unsigned int heap_index; unsigned int count;
	    cout << "Your move: ";
	    if (!(cin >> heap_index >> count)) {
	       cout << "Bye!" << endl; return 1;
	    }
	    move = NimMove(heap_index, count);
	 } while (!game.valid_move(move));
      } else {
	 // computer
	 if (game.nim_value() == 0) {
	    // bad luck
	    for (unsigned int i = 0; i < number_of_heaps; ++i) {
	       if (game.get_heap_size(i) > 0) {
		  move = NimMove(i, 1); break;
	       }
	    }
	 } else {
	    // find a winning move
	    bool found = false;
	    for (unsigned int i = 0; !found && i < number_of_heaps; ++i) {
	       unsigned int max = game.get_heap_size(i);
	       if (maxtake && max > maxtake) max = maxtake;
	       for (unsigned int count = 1;
		     !found && count <= max; ++count) {
		  NimGame test = game;
		  NimMove testmove(i, count);
		  test.execute_move(testmove);
		  if (test.nim_value() == 0) {
		     move = testmove; found = true;
		  }
	       }
	    }
	    assert(found);
	 }
	 cout << "Taking " << move.get_count() << " from heap "
	    << move.get_heap() << endl;
      }
      game.execute_move(move);
   }
   switch (game.winner()) {
      case NimGame::PLAYER1: cout << "Congratulations!" << endl; break;
      case NimGame::PLAYER2: cout << "You lose!" << endl; break;
   }
}
