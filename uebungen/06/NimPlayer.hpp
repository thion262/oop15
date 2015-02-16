#ifndef NIM_PLAYER_H
#define NIM_PLAYER_H

#include "NimGame.hpp"

class NimPlayer {
   public:
      virtual const std::string& get_name() const = 0;
      virtual NimMove get_move(const NimGame& game) const = 0;
};

#endif
