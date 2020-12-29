#include "List.h"

int main() {
    
    
//    Node::Node<int> def_node;
//    Node::Node<int> node_test{5};
//    Node::Node<int> node_test2{15};
//    node_test.printNode();
//
//    node_test.previous = new Node::Node<int>{10};
//    node_test.next = std::unique_ptr<Node::Node<int>> (new Node::Node<int>{20});
//    node_test.printNode();
//
//
//    std::cout <<"Some test with iterators:" <<std::endl;
//
//    __iterator<int> iter{&node_test};
//    std::cout << *(--iter)<<std::endl;
//     std::cout << *(iter) <<std::endl;
//    node_test.printNode();
    

    
    List<int> l{};

    int i=8;
    l.push_front(i); //l-value
    l.push_back(4); //r-value
    l.push_back(i+2); //r-value
    l.push_back(7); //r-value
    l.push_front(9); //r-value
    l.push_back(5); //r-value
    std::cout << "My list so far: " << l<<std::endl;



    auto p{l.go_to(1)};
//    std::cout << *p <<std::endl;
    auto itp = l.insert(p,98);
    std::cout << "My list after insertion: \t" << l<<std::endl;
    auto pp{l.go_to(2)};
//    std::cout << *pp <<std::endl;
    auto itpp = l.insert(pp,15);
    std::cout << "My list after insertion is: \t" << l<<std::endl;
    auto ppp{l.go_to(4)};
    std::cout << *ppp <<std::endl;
    auto itppp = l.insert(ppp,96);
    std::cout << "My list after insertion is: \t" << l<<std::endl;
    
    
    

    std::cout << *ppp <<std::endl;
    auto iteras = l.go_to(6);
    l.erase(iteras);
    std::cout << "List after erasure: "<< l <<std::endl;
    
    auto addagain = l.go_to(6);
    auto itaddagain = l.insert(addagain, 19);
    std::cout << "My list after insertion is: \t" << l<<std::endl;
    

    l.pop_front();
    std::cout << "My list after pop_front() is: \t" << l<<std::endl;
    
    l.insert(++(++l.begin()), 99);
    std::cout << l <<std::endl;
    
    l.push_front(88);
    std::cout << l <<std::endl;
    
    auto prova = l.go_to(4);
    l.erase(prova);
    std::cout << l <<std::endl;
    
    l.pop_back();
    std::cout << "My list after pop_back() is: \t" << l<<std::endl;

    
    l.push_back(100);
    std::cout << l <<std::endl;
    
    std::cout << "Pop front and push_front: " <<std::endl;
    l.pop_front();
    std::cout << l << std::endl;
    l.push_front(99);
    std::cout << l << std::endl;
    
    l.pop_front();
    std::cout << l << std::endl;
    
    std::pair<bool, __iterator<int> > findpair = l.find(96);
    std::cout << findpair.first << " " ;// << findpair.second.current->data <<std::endl;
    
    
    List<double> ld;
    ld.push_front(1.2);
    ld.push_front(9.8);
    ld.push_back(10.5);
    std::cout << ld <<std::endl;
    std::pair<bool, __iterator<double> > findpairld = ld.find(12.0);
    std::cout << findpairld.first << " " ;// << findpair.second.current->data <<std::endl;

    l.clear();
    std::cout << l <<std::endl;
    
    return 0;
}
