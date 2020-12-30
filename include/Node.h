#ifndef Node_h
#define Node_h

#include <algorithm>
#include <iostream>
#include <memory>  // std::unique_ptr
#include <utility> // std::move
#include <algorithm>



namespace Node {


template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node* previous;

    /** Default constructor for struct Node*/
    Node() noexcept = default;
    
    /**
     * @brief Custom constructor with data
     * @param _data The values to be stored in the @ref Node.
     *
     * Create a @ref Node with given @ref data and with @ref next and @ref previous parents initialized to `nullptr`
     */
    explicit Node(const T& _data) : data{_data}, next{nullptr},previous{nullptr} {
        std::cout << "l-value Node"<<std::endl;
    }
    
    
    /**
     * @brief Copy constructor for @ref Node
     * @param _data The values to be stored in the @ref Node.
     * @param _next Raw pointer to the next @ref Node
     * @param _previous Raw pointer to the previous @ref Node
     *
     * Create a @ref Node with given @ref data , @ref next and @ref previous
     */
    Node(const T& _data, Node* _next, Node* _previous): data{_data}, next{_next}, previous{_previous} {}

    /**
     * @brief Move constructor for @ref Node
     * @param x The values to be stored in the current @ref Node
     *
     *
     */
    explicit Node(T&& x) : data{std::move(x)} {
      std::cout << "r-value" << std::endl;
    }
    
    Node(T&& x, Node* _next, Node* _previous) : data{std::move(x)}, next{_next}, previous{_previous} {
      std::cout << "r-value" << std::endl;
    }
    

    /**
     * @brief Default destructor.
     *
     *Release the memory owned by a @ref Node
     */
    ~Node()=default;
    
    //Move semantics, Copy semantics: TOBEDONE
    
    /**
     * @brief Utility function that prints a @ref Node
     *
     */
    void printNode(){
        std::cout << "Data is: " << data <<"\n";
        /*if(next.get()){
            std::cout << "Next is: " << next<<" with data: " << next->data <<"\n";
        }if (previous){
            std::cout << "Previous is: " <<previous<<" with data: " << previous->data <<"\n";
        }*/
    }
    
 };

} //end namespace

#endif /* Node_h */
