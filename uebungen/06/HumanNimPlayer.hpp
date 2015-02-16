#ifndef HUMAN_NIM_PLAYER
#define HUMAN_NIM_PLAYER

#include <string>
#include "NimPlayer.hpp"

class HumanNimPlayer : public NimPlayer {
   public:
      HumanNimPlayer();
      virtual const std::string& get_name() const;
      virtual NimMove get_move(const NimGame& game) const;
   private:
      std::string name;
};

#endif
