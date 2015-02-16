#include "MemObject.hpp"
#include <iostream>
#include <fcntl.h>

MemObject get_memobject() {
   std::string filename;
   std::cout << "Input file: "; getline(std::cin, filename);
   int fd = open(filename.c_str(), O_RDWR);
   if (fd < 0) exit(1);
   off_t off;
   std::cout << "Offset: "; std::cin >> off;
   size_t size;
   std::cout << "Size: "; std::cin >> size;
   MemObject words{fd, off, size, PROT_READ|PROT_WRITE, MAP_SHARED};
   return words;
}

char hallo[] = "Hallo";

int main() {
   try {
      MemObject words = get_memobject();
      std::cout << "Access position: "; size_t pos; std::cin >> pos;
      char*& cptr{words.access<char*>(pos)};
      if (cptr) {
	 std::cout << (long int) cptr << std::endl;
	 std::cout << cptr << std::endl;
      }
      cptr = hallo;
   } catch (const std::exception& exc) {
      std::cout << "got " << exc.what() << std::endl;
   }
}
