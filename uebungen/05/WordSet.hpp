#ifndef WORD_SET_H
#define WORD_SET_H

#include "Word.hpp"

class WordSet {
   public:
      WordSet();
      WordSet(const WordSet& other);
      ~WordSet();

      WordSet& operator=(const WordSet& other);

      // mutators
      void add(const Word& word);
	 /* add a word to the set, if it is not already present;
	    PRE: word is non-empty and has a letter, i.e. A-Z, a-z,
	    at the beginning and at the end */

      void remove(const Word& word);
	 /* remove a word from the set, if it is included
	    PRE: word is non-empty and has a letter, i.e. A-Z, a-z,
	    at the beginning and at the end */

      // accessors
      unsigned int size() const;
	 /* return number of words in the set */

      bool included(const Word& word) const;
	 /* returns true if word in the set
	    PRE: word is non-empty and has a letter, i.e. A-Z, a-z,
	    at the beginning and at the end */

      unsigned int words_beginning_with(unsigned int letter) const;
	 /* return number of words in the set beginning with the given letter
	    PRE: letter < LETTERS */

      const Word& select_word_beginning_with(unsigned int letter,
	    unsigned int index) const;
	 /* return index-th word beginning with the given letter
	    PRE: letter < LETTERS and
	    index < words_beginning_with(letter) */

      unsigned int words_ending_with(unsigned int letter) const;
	 /* return number of words in the set ending with the given letter
	    PRE: letter < LETTERS */

      const Word& select_word_ending_with(unsigned int letter,
	    unsigned int index) const;
	 /* return index-th word ending with the given letter
	    PRE: letter < LETTERS and
	    index < words_ending_with(letter) */

   private:
      struct Words* words; /* this is indeed private */
};

#endif
