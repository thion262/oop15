#ifndef RANDOM_NIM_PLAYER
#define RANDOM_NIM_PLAYER

#include <string>
#include "NimPlayer.hpp"

class RandomNimPlayer : public NimPlayer {
   public:
      RandomNimPlayer();
      virtual const std::string& get_name() const;
      virtual NimMove get_move(const NimGame& game) const;
   private:
      std::string name;
};

#endif

