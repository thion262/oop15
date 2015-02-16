#ifndef WORD_H
#define WORD_H

#include <string>

constexpr unsigned int LETTERS = 'Z' - 'A' + 1;

/* class representing words that begin and end with
   a letter, i.e. A-Z, a-z
*/

class Word {
   public:
      Word(); /* unusable object, can be assigned to */
      Word(const std::string& word_);
	 /* PRE: the word begins and ends with a letter */
      Word(const Word& other);

      static bool valid(const std::string& word);
	 /* check if this word can be passed to the constructor */

      const std::string& get_word() const;
	 /* PRE: word has been properly initialized */
      unsigned int get_first_index() const;
	 /* PRE: word has been properly initialized */
      unsigned int get_last_index() const;
	 /* PRE: word has been properly initialized */

   private:
      std::string word; /* not read-only to permit assignment */
      unsigned char first; /* mapped to 0..LETTERS-1 */
      unsigned char last; /* mapped to 0..LETTERS-1 */
};

#endif
