#ifndef NIM_GAME_H
#define NIM_GAME_H

#include <vector>
#include "NimMove.hpp"

class NimGame {
   public:
      /* initialize a game of Nim with the given number of
	 heaps where in one move up to maxtake sticks can be taken from
	 exactly one heap; if maxtake is 0, any number of sticks can
	 be taken; the player who does not find any sticks for
	 removal loses */
      NimGame(unsigned int number_of_heaps_, unsigned int maxtake_);

      /* return the number of heaps */
      unsigned int get_number_of_heaps() const;

      /* initialize the given heap (index starting from 0) to
	 the given size */
      void set_heap_size(unsigned int index, unsigned int size);

      /* retrieve the size of the given heap (index starting from 0) */
      unsigned int get_heap_size(unsigned int index) const;

      /* PLAYER1 is the player who plays/played the first move */
      typedef enum {PLAYER1, PLAYER2} Player;

      /* is the game finished? */
      bool finished() const;

      /* if yes, who has won?
	 PRE: finished() returns true */
      Player winner() const;

      /* otherwise, whose turn is next?
         PRE: finished() returns false */
      Player get_next_player() const;

      /* is the given move valid?
	 PRE: finished() returns false */
      bool valid_move(NimMove move) const;

      /* execute the given move
	 PRE: finished() returns false and valid_move(move) true */
      void execute_move(NimMove move);

      /* compute the nim value for the current state of the game */
      unsigned int nim_value() const;

   private:
      const unsigned int number_of_heaps;
      const unsigned int maxtake;
      std::vector<unsigned int> heap_size; // size of each of the heaps
      Player next_player;
};

#endif
