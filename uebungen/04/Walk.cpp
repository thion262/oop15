#include <iostream>
#include <fstream>
#include <string>
#include "Location.hpp"
#include "Territory.hpp"

using namespace std;

int main() {
   std::fstream in{"states.txt"};
   if (!in) {
      std::cout << "Sorry, cannot open states" << std::endl;
      return 1;
   }
   Territory t;
   if (!(in >> t)) {
      cout << "Sorry, unable to parse states" << std::endl;
      return 1;
   }

   unsigned int index = 32; /* let us start in NY */
   for(;;) {
      const Location& loc{t.location(index)};
      cout << "You are currently in " << loc.get_name() << endl;
      if (loc.get_nof_neighbors() == 0) break;
      cout << "You can continue your journey to";
      for (unsigned int i = 0; i < loc.get_nof_neighbors(); ++i) {
	 const Location& neighbor{t.location(loc.neighbor(i))};
	 cout << " " << neighbor.get_name();
      }
      cout << endl;

      cout << "Next: ";
      std::string next;
      if (!(cin >> next)) break;
      bool found = false;
      for (unsigned int i = 0; i < loc.get_nof_neighbors(); ++i) {
	 const Location& neighbor{t.location(loc.neighbor(i))};
	 if (next == neighbor.get_name()) {
	    index = loc.neighbor(i); found = true; break;
	 }
      }
      if (!found) {
	 cout << "No such neighbor: " << next << endl;
      }
   }
}
