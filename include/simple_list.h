#pragma once

#include <iterator>

template <typename T>
struct Node
{
    Node(T _data):data(_data){}
    T        data;
    Node<T> *next;
};


template <typename T, class Allocator = std::allocator<T> >
class simple_list {
public:

    using value_type = T;

struct iterator : std::iterator<std::forward_iterator_tag, T > {

    iterator(Node<T>*  _ptr = nullptr) : ptr(_ptr) {}
        
    iterator & operator++()
    {
    if (ptr != nullptr) 
        ptr = ptr->next;
        return *this;
    }


    T  & operator*()  { return ptr->data; }
        
        
    bool operator==(iterator  & other)  
    {
        return ptr == other.ptr;
    }
        
        
    bool operator!=(iterator  & other)  
    {
        return !(*this == other);
    }    
    private:
        Node<T> * ptr;
};

private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;

    using alloc_t = typename Allocator::template rebind<Node<T>>::other;
    alloc_t alloc;


public:
    simple_list() {};
    simple_list(const Allocator& _alloc) : alloc(_alloc) {};


    void push_back( const T& value )
    {
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

    iterator begin()
    {
        return iterator(this->head);
    }


    iterator end()
    {
        return nullptr;
    }

    iterator insert( iterator pos, const T& value )
    {

    }

    ~simple_list()
    {
        auto h = this->head;
        while(h != nullptr){
            auto p = h;
            h = h->next;
            alloc.destroy(p);
            alloc.deallocate(p, 1u);
        }
        this->head = nullptr;
    }
};