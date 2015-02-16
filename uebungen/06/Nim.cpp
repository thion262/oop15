#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include <link.h>
#include "NimMove.hpp"
#include "NimGame.hpp"
#include "NimPlayer.hpp"

using namespace std;

typedef NimPlayer* NimPlayerConstructor();

NimPlayer* load_player(char* name) {
   std::string path("./"); // look in current directory
   path += name;
   path += ".so"; // add suffix
   void* handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
   if (!handle) return 0;
   NimPlayerConstructor* constructor =
      (NimPlayerConstructor*) dlsym(handle, "construct");
   if (!constructor) {
      dlclose(handle); return 0;
   }
   return constructor();
}

int main(int argc, char** argv) {
   if (argc != 3) {
      cout << "Names of players expected. Bye." << endl; return 1;
   }
   NimPlayer* player[2] = {load_player(argv[1]), load_player(argv[2])};
   if (!player[0] || !player[1]) {
      cout << "Dynamic loading of players failed. Bye." << endl; return 1;
   }

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
      NimPlayer* next_player = player[game.get_next_player()];
      move = next_player->get_move(game);
      cout << next_player->get_name();
      if (move.has_resigned()) {
	 cout << " resigns." << endl;
      } else {
	 cout << " takes " << move.get_count() << " from heap "
	 << move.get_heap() << endl;
      }
      game.execute_move(move);
   }
   NimPlayer* winner = player[game.winner()];
   cout << winner->get_name() << " has won!" << endl;
}
