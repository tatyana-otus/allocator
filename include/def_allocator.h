
#pragma once

#include <iostream>

template <typename T>
struct def_allocator
{
    using value_type = T;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;

    template <class U> struct rebind { using other =  def_allocator<U>; };

    T* allocate(std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        auto p = malloc(n * sizeof(T));
    
        std::cout << "[allocate] p = " << (uint64_t)p ;
        std::cout << "  n = " << n << "  sizeof(T) = " << sizeof(T) << "  malloc( " <<  n * sizeof(T) << " )"<< std::endl << std::endl;
               
        return reinterpret_cast<T*>(p);        
    }

    void deallocate(T* p, std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl ;
        std::cout << "[deallocate] p = " << (uint64_t)p << std::endl << std::endl;
        std::free(p);
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

};