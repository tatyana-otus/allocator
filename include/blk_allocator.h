
#pragma once

#include <iostream>


template <typename T, size_t num = 64>
struct blk_allocator
{
    static_assert(num > 0, "");

    using value_type = T;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;

    template <class U> struct rebind { using other =  blk_allocator<U, num>; };

    T* allocate(std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        void* p;

        if((cnt + n) > num)
            throw std::invalid_argument( "Invalid  number of elements for allocate()" );

        if(blk_ptr == nullptr) {
            p = malloc(num * sizeof(T));
            if(!p) throw std::bad_alloc();
            blk_ptr = reinterpret_cast<T*>(p); 
        }
        else {
            p = blk_ptr + cnt;
        }
        cnt += n;

        std::cout << "[allocate] p = " << (uint64_t)p ;
        std::cout << "  n = " << n << "  sizeof(T) = " << sizeof(T) << "  malloc( " <<  n * sizeof(T) << " )"<< std::endl << std::endl;

        return reinterpret_cast<T*>(p);;
    }

    void deallocate(T* p, std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl ;

        cnt -= n;
        if(cnt < 0)
            throw std::invalid_argument( "Invalid  number of elements for deallocate()" );
        if(cnt == 0) {
            std::free(blk_ptr);
            blk_ptr = nullptr;
        } 

        std::cout << "[deallocate] p = " << (uint64_t)p << std::endl << std::endl;
    }

    template<typename U, typename ... Args>
    void construct( U* p, Args&&... args ) 
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "[construct] p = " << (uint64_t)p << std::endl << std::endl;

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T * p) 
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "[destroy ]p = " << (uint64_t)p << std::endl << std::endl;
        
        p->~T();
    }

    int cnt = 0;
    T*  blk_ptr     = nullptr;
};