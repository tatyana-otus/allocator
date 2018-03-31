#pragma once

#include <iostream>
#include "debug_log.h"

template <typename T, size_t num = 64>
class blk_allocator
{
    static_assert(num > 0, "");


    struct list_head{
        list_head* prev;
    };


private:
    list_head* head = nullptr;

    T*  blk_ptr = nullptr;
    int cnt     = 0;


public:     
    using value_type = T;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;


    template <class U> struct rebind { using other =  blk_allocator<U, num>; };


    blk_allocator() = default;
    template< class U >
    blk_allocator( const blk_allocator<U, num>& other ){}


    T* allocate(std::size_t n)
    {
        if(n != 1)
            throw std::invalid_argument( "Invalid  number of elements for allocate()" );

        int idx = cnt % num;

        if((idx == 0) || (head == nullptr)) {
            auto p = malloc(sizeof(list_head) + num * sizeof(T));
            if(!p) throw std::bad_alloc();

            auto new_head = reinterpret_cast<list_head*>(p);
            new_head->prev = head; 
            head = new_head;

            blk_ptr = reinterpret_cast<T*>(reinterpret_cast<list_head*>(p) + 1);
        }

        auto ret_ptr = blk_ptr + idx;       
        ++cnt;

        return ret_ptr;
    }


    void deallocate(T* p, std::size_t n)
    {
        cnt -= n;
        if(cnt < 0)
            throw std::invalid_argument( "Invalid  number of elements for deallocate()" );

        if(cnt == 0) {
            auto h = head;
            while(h != nullptr){
                auto p = h;
                h = h->prev;
                std::free(p);
            }
            head    = nullptr;
            blk_ptr = nullptr;
        }        
    }


    template<typename U, typename ... Args>
    void construct( U* p, Args&&... args ) 
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T * p) 
    {        
        p->~T();
    }
};