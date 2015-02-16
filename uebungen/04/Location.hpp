#ifndef LOCATION_H
#define LOCATION_H

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

class Location {
   public:
      // initialization
      void set_name(const std::string& name_) {
	 name = name_;
      }
      void set_nof_neighbors(unsigned int nof_neighbors) {
	 neighbors.resize(nof_neighbors);
      }
      // accessors
      const std::string& get_name() const {
	 return name;
      }
      unsigned int get_nof_neighbors() const {
	 return neighbors.size();
      }
      const unsigned int& neighbor(unsigned int index) const {
	 assert(index < neighbors.size());
	 return neighbors[index];
      }
      // mutators
      unsigned int& neighbor(unsigned int index) {
	 assert(index < neighbors.size());
	 return neighbors[index];
      }
   private:
      std::string name;
      std::vector<unsigned int> neighbors;
};

std::istream& operator>>(std::istream& in, Location& loc) {
   std::string name; unsigned int nof_neighbors;
   if (in >> name >> nof_neighbors) {
      loc.set_name(name); loc.set_nof_neighbors(nof_neighbors);
      for (unsigned int i = 0; i < nof_neighbors; ++i) {
	 if (!(in >> loc.neighbor(i))) break;
      }
   }
   return in;
}

#endif
