#ifndef MEM_OBJECT_H
#define MEM_OBJECT_H

#include <exception>
#include <sstream>
#include <sys/mman.h>
#include <unistd.h>

class MemObject {
   public:
      class Exception: public std::exception {};
      class InvalidMemObject: public Exception {
	 public:
	    virtual const char* what() const noexcept {
	       return "invalid MemObject";
	    }
      };
      class AccessViolation: public Exception {
	 public:
	    AccessViolation(off_t off, size_t size, size_t len) {
	       std::ostringstream os;
	       os << "access violation: [" <<
		  off << ", " << off+size <<
		  ") does not fit into [0, " <<
		  len << ")";
	       message = os.str();
	    }
	    virtual const char* what() const noexcept {
	       return message.c_str();
	    }
	 private:
	    std::string message;
      };

      MemObject() : fd{-1}, addr{MAP_FAILED}, len{0} {
      }

      MemObject(MemObject&& other) : MemObject() {
	 swap(*this, other);
      }

      MemObject(int fd_, off_t off, size_t len_, int prot, int flags) :
	 fd{fd_},
	 addr{mmap(nullptr, len_, prot, flags, fd_, off)},
	 len{len_} {
      }

      ~MemObject() noexcept {
	 if (addr != MAP_FAILED) {
	    munmap(addr, len);
	 }
	 if (fd >= 0) close(fd);
      }
      MemObject& operator=(const MemObject&) = delete;

      MemObject& operator=(MemObject&& other) {
	 swap(*this, other);
	 return *this;
      }

      friend void swap(MemObject& lhs, MemObject& rhs) {
	 using std::swap;
	 swap(lhs.fd, rhs.fd);
	 swap(lhs.addr, rhs.addr);
	 swap(lhs.len, rhs.len);
      }

      bool valid() const noexcept {
	 return addr != MAP_FAILED;
      }
      template<typename T>
      const T& access(size_t off) const
	    throw(AccessViolation, InvalidMemObject) {
	 if (!valid()) throw InvalidMemObject();
	 if (off < 0 || off >= len || off + sizeof(T) >= len) {
	    throw AccessViolation(off, sizeof(T), len);
	 }
	 return *(T*)((char*) addr + off);
      }
      template<typename T>
      T& access(size_t off)
	    throw(AccessViolation, InvalidMemObject) {
	 if (!valid()) throw InvalidMemObject();
	 if (off < 0 || off >= len || off + sizeof(T) >= len) {
	    throw AccessViolation(off, sizeof(T), len);
	 }
	 return *(T*)((char*) addr + off);
      }

   private:
      int fd;
      void* addr;
      size_t len;
};

#endif
