#ifndef Iterator_h
#define Iterator_h

#include "Node.h"
#include <iterator>

template <typename T >
struct __iterator {;
    using NodeT = Node::Node<T>;
    NodeT* current;
    
//public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type *;
    
    explicit __iterator(NodeT* p) : current{p} {}
    __iterator() noexcept=default;
    ~__iterator()=default;
    
    reference operator*() const noexcept{
        return current->data;
    }
    
    pointer operator->() const noexcept{
        return &**this;
    }
    
    __iterator& operator++() {
      current = current->next.get();
      return *this;
    }
    
    __iterator& operator--(){
        current=current->previous;
        return *this;
    }
    
    
    
    friend bool operator==(__iterator &a, __iterator &b) {
      return a.current == b.current;
    }
    

    friend bool operator!=(__iterator &a, __iterator &b) { return !(a == b); }

};

#endif /* Iterator_h */
