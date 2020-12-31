#include "Iterator.h"
#include "cmath"

/** @mainpage
 *
 *
 * @section sec_description Description
 * A C++ templated, double-linked list using smart pointers.
 *
 * @section sec_compile How to compile
 * Just run the usual `make` command. If you want to use *valgrind*:
 *
 *     valgrind -s ./exe.x
 *
 *
 *
 */


template <typename T>
class List {
private:
    /**
     * @brief Unique pointer to the head  of the @ref List
     */
    std::unique_ptr<Node::Node<T>> first;
    /**
     * @brief Raw pointer to the last element of the @ref List
     *
     */
    Node::Node<T>* last; //raw pointer to the last node
    /**
     * @brief The current size of the @ref List
     */
    int _size;
    
public:
    
    
    using iterator = __iterator<T>;
    
    /**
     *
     * @brief Return an @ref iterator to the first element of the @ref List
     */
    iterator begin(){return iterator{first.get()};}
    
    /**
     * @brief Return an @ref iterator to *one-past-the-last* element of the @ref List
     */
    iterator end(){return iterator{nullptr};} //one past the last
    
    /**
     * @brief Return an @ref iterator to the n-th element of the @ref List
     */
    iterator advance(const int n){

        if (n>=_size) {
            return end();
        }else{
            return std::next(begin(),n);
        }
    }
    
    /**
     * @brief Default constructor for @ref List
     */
    List() : first{nullptr}, last{nullptr},_size{0} {}
    
    /**
     * @brief Default-generated constructor
     */
    ~List() noexcept = default;
    
    /**
     * @brief Default-generated move constructor
     * @param List r-value reference
     */
    List(List &&) = default;
    
    /**
     * @brief Default-generated move assignment
     *
     * @param List r-value reference
     */
    List &operator=(List &&) = default;

    
    
    /**
     * @brief Push a @ref Node with value x to the front of the @ref List
     * @param x values to be inserted in @ref Node. Both an *r-value* and *l-value* reference can be given
     */
    template <typename O>
    void push_front(O&& x) {
        auto node = std::make_unique<Node::Node<T>>(std::forward<O>(x));
        std::swap(node, first);
        first->next = std::move(node);
        if (_size == 0) {
            assert(!last);
            assert(!first->next);
            last = first.get();
        }else{
            first->next->previous = first.get();
        }
        ++_size;
    }
    
    /**
     * @brief Push a @ref Node with value x in the back of the @ref List
     * @param x values to be inserted in @ref Node. Both an *r-value* and *l-value* reference can be given
     */
    template <typename O> //forward reference
    void push_back(O&& x){
        auto node = std::make_unique<Node::Node<T>>(std::forward<O>(x));
        if (_size==0) {
            assert(!last);
            assert(!first);
            first = std::move(node);
            last = node.get();
            _size = 1;
            return;
        }
        assert(!last->next);
        node->previous = last;
        last->next = std::move(node);
        last = last->next.get();
        ++_size;
    }
    
    
    iterator substitute(iterator p, const T& x){
        //_size must not be incremented!
        iterator tmp{p};
        if(tmp.current){
            *tmp = x;
            return tmp;
        }else{
            return iterator{nullptr};
        }

    }
    
    
    /**
     * @brief Inserts a new @ref Node in the current @ref List
     * @param position  iterator to the position where to insert the values
     * @param value values to be inserted in the @ref Node of the @ref List
     *
     */
    iterator insert(iterator position,const T& value) {
        auto newNode = std::make_unique<Node::Node<T>>(value);
        auto prev = position.current ? position.current->previous : last;
        auto ptr = prev? &prev->next:&first;
        position.current->previous = &(*newNode); //
        std::swap(*ptr,newNode);
        (*ptr)->next=std::move(newNode);
        (*ptr)->previous = prev;
        ++_size;
        if (!last) {
            last = first.get();
        }
        return iterator{ptr->get()};
    }
    
    /**
     * @brief Remove the element in the list corresponding to the entry position of the @ref List
     * @param position iterator to the position to be erased
     */
    void erase(iterator position){ //remove p from the list
        last->printNode();
        if (position.current==first.get()) {
            pop_front();
        }else if(position.current==last) {
            pop_back();
        }else{
            position.current->next->previous = position.current->previous;
            position.current->previous->next.reset(position.current->next.release());
            --_size;
        }
        
    }
    
    /**
     * @brief Remove the last element from the list
     */
    void pop_back(){
        last->previous->next.reset();
        std::cout << this <<std::endl;
        last=last->previous;
        --_size;
    }
    
    
    /**
     * @brief Remove the first element from the list
     */
    void pop_front(){
        //auto itBeg = begin();
        first->next->previous = nullptr;
        first.reset(first->next.release()); //the head is the next one
        --_size;
    }
    
    
    /**
     * @brief Find the value x in the @ref List
     * @param x values to be searched in the @ref List
     *
     * Returns a `std::pair` where the `first` element is `true` if x is found, `false` otherwise. The `second` element is an iterator to the position
     * of x (eventually `nullptr`)
     */
    std::pair<bool,iterator> find(const T& x){
        auto it = begin();
        auto itEnd = end();
        while (it!= itEnd) {
            if (compare(it,x)) {
                return std::pair<bool,iterator>(true,it);
            }
            ++it;
        }
        return std::pair<bool,iterator>(false,nullptr);
    }

    /**
     * @brief Friend function that overloads the `<<` operator and prints the @ref List
     *
     */
    friend std::ostream& operator<<(std::ostream& os, List& l){
        if (l._size==0) {
            os<<"List is empty";
            return os;
        }
        auto itStop = l.end();
        os << "The list has " << l._size << " elements"<<"\n";
        for (auto it = l.begin(); it!=itStop; ++it) {
            os<< *it << " ";
        }
        return os;
    }
    
    
    
    /**
     *
     * @brief Utility function used to compare data. A special case is considered if x is a double (`sizeof(x)==8`)
     * @param it iterator to the position to be compare
     * @param x value to be compared with `iterator.current`
     * @see find()
     */
    bool compare (iterator it,const T& x){
        bool ret = false;
        const double TOL = 1e-15;
        if (sizeof(x)==8) {
            if (std::fabs(it.current->data - x)<TOL) {
                ret = true;
            }
        }else{
            if (it.current->data==x) {
                ret = true;
            }        }
        return ret;
    }
    
    /**
     * @brief Clear the whole @ref List
     * Apply `reset` to the (unique) pointer to the first element and set @ref _size = 0
     */
    void clear(){
        first.reset();
        _size=0;
    }
    
};
