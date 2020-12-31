#ifndef Iterator_h
#define Iterator_h

#include "Node.h"
#include <iterator>

template <typename T >
struct __iterator {;
    using NodeT = Node::Node<T>;
    /**
     * @brief Raw pointer to the current @ref Node
     *
     */
    NodeT* current;
    
//public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type *;
    
    /**
     * @brief Custom constructor for @ref __iterator
     * @param p Raw pointer to a @ref Node
     *
     * Construct a new @ref __iterator that refers to @ref Node p
     */
    explicit __iterator(NodeT* p) : current{p} {}
    
    /**
     * @brief Default-generated constructor
     *
     */
    __iterator() noexcept=default;
    
    /**
     * @brief Default-generated destructor
     *
     */
    ~__iterator()=default;
    
    
    /**
     * @brief Dereference operator
     *
     * Dereferences an @ref __iterator by returning the data stored by the @ref Node it refers to
     */
    reference operator*() const noexcept{
        return current->data;
    }
    
    
    /**
     * @brief Arrow operator
     *
     * Access operator: it return a pointer to the data stored in the @ref Node the @ref __iterator refers to
     */
    pointer operator->() const noexcept{
        return &**this;
    }
    
    
    /**
     * @brief Post- increment operator
     *
     */
    __iterator& operator++() {
      current = current->next.get();
      return *this;
    }
    
    /**
     * @brief Post- decrement operator
     *
     */
    __iterator& operator--(){
        current=current->previous;
        return *this;
    }
    
    /**
     * @brief Equality operator
     *
     * @param a Reference to first iterator.
     * @param b Reference to the second iterator
     * Two iterators are equal iff they point to the same @ref Node
     *
     */
    friend bool operator==(__iterator &a, __iterator &b) {
      return a.current == b.current;
    }
    
    /**
     *@brief Inequality operator
     *@param a Reference to the first iterator
     *@param b Reference to the second iterator
     *
     * It's the logical negation of the `==` operator
     */
    friend bool operator!=(__iterator &a, __iterator &b) { return !(a == b); }

};

#endif /* Iterator_h */
