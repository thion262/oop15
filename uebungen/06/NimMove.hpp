#ifndef NIM_MOVE_H
#define NIM_MOVE_H

class NimMove {
   public:
      NimMove();
      NimMove(unsigned int _heap, unsigned int _count);
      bool has_resigned() const;
      unsigned int get_heap() const;
      unsigned int get_count() const;

   private:
      unsigned int heap;
      unsigned int count;
      bool resigned;
};

#endif
