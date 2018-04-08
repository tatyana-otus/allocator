
#pragma once

#include <iostream>
#include <memory>
#include "debug_log.h"

template <typename T>
class blk_allocator_v1
{
    struct Deleter
    {
        void operator()(void* x)
        {
            D_PF_LOG(std::cout); 

            if(x != nullptr){
                reinterpret_cast<list_head*>(x)->prev.reset(nullptr);
                free(x);
            }    
        }
    };

    struct list_head
    {
        std::unique_ptr<char, Deleter> prev;
    };

private:
    uint32_t    cur_size = 0;
    uint32_t    max_size = 0;   

public:
    size_t num      = 0; 
    std::unique_ptr<char, Deleter> head;  
      
    using value_type = T;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;


    template <class U> struct rebind { using other =  blk_allocator_v1<U>; };

    blk_allocator_v1(size_t _num):num(_num ), head(nullptr) { D_PF_LOG(std::cout); }; 
    blk_allocator_v1( const blk_allocator_v1& other ):num(other.num), head(nullptr){ D_PF_LOG(std::cout); };


    template< class U >
    blk_allocator_v1( const blk_allocator_v1<U>& other ):num(other.num), head(nullptr){ D_PF_LOG(std::cout); };

    template< class U >
    blk_allocator_v1( blk_allocator_v1<U>&& other ):num(other.num), head(nullptr){ D_PF_LOG(std::cout); };


    T* allocate(std::size_t n)
    {
        D_PF_LOG(std::cout);

        int idx = 0;        
        if( (head != nullptr) && ((max_size - cur_size) >= n) ){
            idx = cur_size; 
        }

        if( idx == 0 ) {
            size_t block_size = (n > num) ? n : num;

            auto p = reinterpret_cast<char*>(malloc(sizeof(list_head) + block_size * sizeof(T)));
            if(!p) throw std::bad_alloc();

            auto new_head = reinterpret_cast<list_head*>(p);
            new(&(new_head->prev)) std::unique_ptr<char, Deleter>(std::move(head));

            head = std::unique_ptr<char, Deleter>{std::move(p)};

            max_size = block_size;
            cur_size = 0;
        }       
        cur_size += n;
        return (reinterpret_cast<T*>(head.get() + sizeof(list_head)) + idx);
    }


    void deallocate(T* p, std::size_t n)
    {     
       D_PF_LOG(std::cout);
    }


    template<typename U, typename ... Args>
    void construct( U* p, Args&&... args ) 
    {
        D_PF_LOG(std::cout);
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T * p) 
    {   
        D_PF_LOG(std::cout);     
        p->~T();
    }
};