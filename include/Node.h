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

    
    Node() noexcept = default;
    explicit Node(const T& _data) : data{_data}, next{nullptr},previous{nullptr} {
        std::cout << "l-value Node"<<std::endl;
    }
    Node(const T& _data, Node* _next, Node* _previous): data{_data}, next{_next}, previous{_previous} {}

    explicit Node(T&& x) : data{std::move(x)} {
      std::cout << "r-value" << std::endl;
    }
    
    Node(T&& x, Node* _next, Node* _previous) : data{std::move(x)}, next{_next}, previous{_previous} {
      std::cout << "r-value" << std::endl;
    }
    

    
    ~Node()=default;
    
    //Move semantics, Copy semantics
    
    void printNode(){
        std::cout << "Data is: " << data <<"\n";
        /*if(next){
            std::cout << "Next is: " << next<<" with data: " << next->data <<"\n";
        }if (previous){
            std::cout << "Previous is: " <<previous<<" with data: " << previous->data <<"\n";
        }*/
    }
    
 };

} //end namespace

#endif /* Node_h */
