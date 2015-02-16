#ifndef TERRITORY_H
#define TERRITORY_H

#include <cassert>
#include <iostream>
#include <vector>
#include "Location.hpp"

class Territory {
   public:
      // construction
      void set_nof_locations(unsigned int nof_locations) {
	 locations.resize(nof_locations);
      }
      // accessors
      const Location& location(unsigned int index) const {
	 assert(index < locations.size());
	 return locations[index];
      }
      // mutators
      Location& location(unsigned int index) {
	 assert(index < locations.size());
	 return locations[index];
      }
   private:
      std::vector<Location> locations;
};

std::istream& operator>>(std::istream& in, Territory& t) {
   unsigned int nof_locations;
   if (in >> nof_locations) {
      t.set_nof_locations(nof_locations);
      for (unsigned int i = 0; i < nof_locations; ++i) {
	 if (!(in >> t.location(i))) break;
      }
   }
   return in;
}

#endif
