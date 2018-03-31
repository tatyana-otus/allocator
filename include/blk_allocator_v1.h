
#pragma once

#include <iostream>
#include "debug_log.h"

template <typename T>
class blk_allocator_v1
{
    
    struct list_head{
        list_head* prev;
        list_head* next;
        uint32_t   cur_size;
        uint32_t   max_size;
    };

private:
    list_head* head = nullptr;
    

public:  
    size_t num      = 0;   
    using value_type = T;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;


    template <class U> struct rebind { using other =  blk_allocator_v1<U>; };



    blk_allocator_v1(size_t _num):num(_num ) {}; 

    template< class U >
    blk_allocator_v1( const blk_allocator_v1<U>& other ):num(other.num) {}

    //void reserve(size_t _num) { num = _num; }


    T* allocate(std::size_t n)
    {
        D_2_LOG(std::cout,__PRETTY_FUNCTION__);

        int idx = 0;
        size_t block_size = (n > num) ? n : num;
        if(head != nullptr){
            auto empy_size = head->max_size - head->cur_size;
            if(empy_size >= n){
                idx = head->cur_size; 
            }
        }

        D_2_LOG(std::cout, "idx = ", idx);
        if( idx == 0 ) {
            D_2_LOG(std::cout, "malloc = ", sizeof(list_head) + block_size * sizeof(T));

            auto p = malloc(sizeof(list_head) + block_size * sizeof(T));
            if(!p) throw std::bad_alloc();
            D_1_LOG(std::cout, "MALLOC !!!! p = ", (uint64_t)p, "\n");

            auto new_head = reinterpret_cast<list_head*>(p);
            new_head->prev = head; 
            new_head->next = nullptr;
            if(head != nullptr) head->next   = new_head;
            head = new_head;
            head->max_size = block_size;
            head->cur_size = 0; 
        }
        head->cur_size += n;
        return (reinterpret_cast<T*>(head + 1) + idx);
    }


    void deallocate(T* p, std::size_t n)
    {     
        D_2_LOG(std::cout,__PRETTY_FUNCTION__);

        auto h = head;
        while(h != nullptr){
            auto t = reinterpret_cast<T*>(h + 1);
            auto idx = p - t;

            if ( (idx >= 0) && (idx <  h->max_size) ) {
                h->cur_size -=n;
                if(h->cur_size == 0){
                    if(h->prev != nullptr) h->prev->next = h->next;
                    if(h->next != nullptr) h->next->prev = h->prev;
                    D_1_LOG(std::cout, "FREE !!!! h = ", (uint64_t)h, "\n");
                    if(h == head) head = h->prev;
                    std::free(h); 
                    h = nullptr ;                
                }
                return;               
            }
            h = h->prev;
        }     
    }


    template<typename U, typename ... Args>
    void construct( U* p, Args&&... args ) 
    {
        D_2_LOG(std::cout,__PRETTY_FUNCTION__);

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T * p) 
    {   
     D_2_LOG(std::cout,__PRETTY_FUNCTION__);     
        p->~T();
    }
};