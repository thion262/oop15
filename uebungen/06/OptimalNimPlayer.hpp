#ifndef OPTIMAL_NIM_PLAYER
#define OPTIMAL_NIM_PLAYER

#include <string>
#include "NimPlayer.hpp"

class OptimalNimPlayer : public NimPlayer {
   public:
      OptimalNimPlayer();
      virtual const std::string& get_name() const;
      virtual NimMove get_move(const NimGame& game) const;
   private:
      std::string name;
};

#endif

