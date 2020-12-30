#include "Iterator.h"
#include "cmath"

/** @mainpage
 *
 *
 * @section sec_description Description
 * A C++ templated, double-linked list using smart pointers.
 *
 * @section sec_description How to compile
 * Just run the usual `make` command. If you want to use *valgrind*:
 *
 *     valgrind -s ./exe.x
 *
 *
 *
 *
 */


template <typename T>
class List {
private:
    std::unique_ptr<Node::Node<T>> first;
    Node::Node<T>* last; //raw pointer to the last node
    int _size;
public:
    
    
    using iterator = __iterator<T>;
    
    iterator begin(){return iterator{first.get()};}
    iterator end(){return iterator{nullptr};} //one past the last
    
    iterator go_to(const int n){

        if (n>=_size) {
            return end();
        }else{
            return std::next(begin(),n);
        }
    }
    

    List() : first{nullptr}, last{nullptr},_size{0} {}
    ~List() noexcept = default;
    List(List &&) = default;
    List &operator=(List &&) = default;

    
    
    template <typename O>
    void push_front(O&& x) {
        auto node = std::make_unique<Node::Node<T>>(std::forward<O>(x));
        std::swap(node, first);  // assuming you implement swap or add a "using std::swap;" on the previous line
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
    
    /** Inserts a new @ref Node::Node in the current @ref List */
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
    
    /** Remove the element in the list corresponding to the entry position of the @ref List*/
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
    
    /**Remove the last element from the list*/
    void pop_back(){
        last->previous->next.reset();
        last=last->previous;
        --_size;
    }
    
    
    /**Remove the first element from the list*/
    void pop_front(){
        auto itBeg = begin();
        itBeg.current->next->previous = nullptr;
        first.reset(itBeg.current->next.release()); //the head is the next one
        --_size;
    }
    
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
    
    
    void clear(){
        first.reset();
        _size=0;
    }
    
};
