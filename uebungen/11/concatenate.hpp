#ifndef CONCATENATE_H
#define CONCATENATE_H

#include <iostream> // salami
#include <utility>

template <typename IT1, typename IT2>
class ConcatenatedIterator {
   public:
      typedef typename IT1::value_type value_type;
      typedef typename IT1::reference reference;

      ConcatenatedIterator() : is_end(true) {
      }
      ConcatenatedIterator(IT1 begin1_, IT1 end1_, IT2 begin2_, IT2 end2_) :
	    is_end(false),
	    begin1(begin1_), end1(end1_), begin2(begin2_), end2(end2_) {
      }
      ConcatenatedIterator(const ConcatenatedIterator& other) :
	    is_end(other.is_end),
	    begin1(other.begin1), end1(other.end1),
	    begin2(other.begin2), end2(other.end2) {
      }
      friend void swap(ConcatenatedIterator& first,
	    ConcatenatedIterator& other) {
	 std::swap(first.is_end, other.is_end);
	 std::swap(first.begin1, other.begin1);
	 std::swap(first.end1, other.end1);
	 std::swap(first.begin2, other.begin2);
	 std::swap(first.end2, other.end2);
      }
      ConcatenatedIterator(ConcatenatedIterator&& other) :
	    ConcatenatedIterator() {
	 swap(*this, other);
      }
      ConcatenatedIterator& operator=(ConcatenatedIterator&& other) {
	 swap(*this, other);
	 return *this;
      }
      
      reference operator*() const {
	 if (begin1 != end1) {
	    return *begin1;
	 } else {
	    return *begin2;
	 }
      }
      ConcatenatedIterator& operator++() {
	 if (!is_end) {
	    if (begin1 != end1) {
	       ++begin1;
	    } else if (begin2 != end2) {
	       ++begin2;
	    }
	    if (begin2 == end2) is_end = true;
	 }
	 return *this;
      }
      bool operator==(const ConcatenatedIterator& other) const {
	 if (is_end && other.is_end) return true;
	 if (is_end != other.is_end) return false;
	 if (begin1 != end1 && other.begin1 != other.end1) {
	    return begin1 == other.begin1;
	 }
	 if (begin1 == end1 || other.begin1 == other.end1) return false;
	 if (begin2 != end2 && other.begin2 != other.end2) {
	    return begin2 == other.begin2;
	 }
	 return false;
      }
      bool operator!=(const ConcatenatedIterator& other) const {
	 return !(*this == other);
      }
   private:
      bool is_end;
      IT1 begin1; IT1 end1;
      IT2 begin2; IT2 end2;
};

template <typename C1, typename C2>
class ConcatenatedContainerView {
   public:
      typedef ConcatenatedIterator<typename C1::const_iterator,
	 typename C2::const_iterator> iterator;
      typedef iterator const_iterator;
      typedef typename C1::value_type value_type;
      ConcatenatedContainerView(const C1& c1, const C2& c2) :
	    it(c1.begin(), c1.end(), c2.begin(), c2.end()) {
      }
      iterator begin() const {
	 return it;
      }
      iterator end() const {
	 return iterator();
      }
   private:
      const iterator it;
};

template <typename C1, typename C2>
ConcatenatedContainerView<C1, C2> concatenate(const C1& c1, const C2& c2) {
   return ConcatenatedContainerView<C1, C2>(c1, c2);
}

template <typename C1, typename C2>
auto operator&(const C1& c1, const C2& c2)
      -> decltype(concatenate(c1, c2)) {
   return concatenate(c1, c2);
}

#endif
