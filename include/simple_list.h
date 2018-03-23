#pragma once

#include <iterator>

template <typename T>
struct Node
{

    Node(T _data):data(_data){}
    T        data;
    Node<T> *next;
};

template <typename T >
struct const_iterator : std::iterator<std::forward_iterator_tag, T const> {

    const_iterator(Node<T>*  _ptr = nullptr) : ptr(_ptr) {}
        
    const_iterator & operator++() {
        if (ptr != nullptr) {
            ptr = ptr->next;
        }
            return *this;
        }
 

        T const & operator*() const { return ptr->data; }
        
        
        bool operator==(const_iterator const & other) const {
            return ptr == other.ptr;
        }
        
        
        bool operator!=(const_iterator const & other) const {
            return !(*this == other);
        }
    private:
        Node<T> * ptr;

};


template <typename T, class Allocator = std::allocator<T> >
class simple_list {

private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    //size_t size   = 0;
    using alloc_t = typename Allocator::template rebind<Node<T>>::other;
    alloc_t alloc;

public:
    simple_list(){}

    void push_back( const T& value ){

        Node<T>* p = alloc.allocate(1u);  
        alloc.construct(p, value);

        if(this->tail == nullptr){
            this->head = p;
        }
        else{
           this->tail->next = p;
        }
        this->tail = p;
        tail->next = nullptr;
    }

    const_iterator<T> begin(){

        return const_iterator<T>(this->head);
    }

    const_iterator<T> end(){

        return nullptr;
    }

    ~simple_list(){
        auto h = this->head;
        while(h != nullptr){
            auto p = h;
            h = h->next;
            alloc.destroy(p);
            alloc.deallocate(p, 1u);
        }
    }
};