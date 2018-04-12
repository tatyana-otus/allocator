#pragma once

#include <vector>
#include <map>
#include <list>
#include "simple_list.h"
#include "blk_allocator_v1.h"
#include <algorithm>
#include <iterator>
#include <chrono>


 const int N_SZ = 10;


template<typename T>
static double gen_fact(T& m, size_t size = 64)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::generate_n(std::inserter(m, m.begin()), size, [i = 0, fact = 0]()mutable { fact =  (i == 1 || i == 0) ? 1 : fact * i;
                                                                       return std::make_pair(i++, fact); 
                                                                     });  
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    return diff.count();
}

template<typename T>
static double gen_iota(T& list, size_t size = 64)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::generate_n(std::back_inserter(list), size, [i = 0]()mutable { return i++; });  

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    
    return diff.count();
}


void std_map_def_alloc(size_t n = N_SZ)
{
    auto m = std::map<int, int, std::less<int> >{};
    gen_fact(m, n);
}

void std_map_custom_alloc(size_t n = N_SZ, size_t custom_alloc_size = N_SZ, std::ostream& os = std::cout)
{
    blk_allocator_v1<std::pair<const int, int>> alloc(custom_alloc_size);
    auto m = std::map<int, int, std::less<int>, blk_allocator_v1<std::pair<const int, int>> >(std::move(alloc));
    gen_fact(m, n);
    for (const auto& kv : m)
        os << kv.first << " " << kv.second << std::endl;
}


void simple_list_def_alloc(size_t n = N_SZ)
{   
    auto l = simple_list<int>{};
    gen_iota(l, n);
}


void simple_list_custom_alloc(size_t n = N_SZ, size_t custom_alloc_size = N_SZ, std::ostream& os = std::cout)
{   
    blk_allocator_v1<std::pair<const int, int>> alloc(custom_alloc_size);
    auto l = simple_list<int, blk_allocator_v1<int>>(std::move(alloc));

    gen_iota(l, n);
    for (const auto&  val: l)
        os << val << std::endl;
}


void test_vector(size_t n = N_SZ, size_t custom_alloc_size = N_SZ, std::ostream& os = std::cout)
{
    blk_allocator_v1<std::pair<const int, int>> alloc(custom_alloc_size);
    auto v = std::vector<int, blk_allocator_v1<int>>(n, std::move(alloc));
    std::iota(v.begin(), v.end(), 1);

    //gen_iota(v, n);
    for (const auto&  val: v)
        os << val << std::endl;
}


void test_map (int rep, size_t size, size_t custom_alloc_size) 
{
    double time_1 = 0;
    std::vector<std::map<int, int, std::less<int> >> map_1(rep);
    for(auto i = 0; i < rep; ++i){
        time_1 +=gen_fact(map_1[i], size);
    }    
    std::cout << "Time to generate std::map of size "  << size << " with default alloc" << " : " 
              << (time_1 / rep) << " s " << "(average time for " << rep << " iterations)\n";


    double time_2 = 0;
    blk_allocator_v1<std::pair<const int, int>> alloc(custom_alloc_size);
    std::vector<std::map<int, int, std::less<int>, blk_allocator_v1<std::pair<const int, int>>>> map_2;
    map_2.reserve(rep);
    for(auto i = 0; i < rep; ++i) {
        map_2.push_back( std::map<int, int, std::less<int>, blk_allocator_v1<std::pair<const int, int>> >(alloc));
    }

    for(auto i = 0; i < rep; ++i){
        time_2 += gen_fact(map_2[i], size);
    }  
    std::cout << "Time to generate std::map of size "  << size << " with custom  alloc (" << custom_alloc_size << ")" << " : " 
              << (time_2 / rep) << " s " << "(average time for " << rep << " iterations)\n";
}

void test_list (int rep, size_t size, size_t custom_alloc_size) 
{   
    double time = 0;
    std::vector<simple_list<int>> vec_1(rep);
    for(auto i = 0; i < rep; ++i){         
        time += gen_iota(vec_1[i], size);       
    } 
    std::cout << "Time to generate custom list of size "  << size << " with default alloc" << " : " 
              << (time / rep) << " s " << "(average time for " << rep << " iterations)\n"; 

    time = 0;
    blk_allocator_v1<int> alloc(custom_alloc_size);
    std::vector<simple_list<int, blk_allocator_v1<int>>> vec_2(rep, alloc);   
    for(auto i = 0; i < rep; ++i){
        time += gen_iota(vec_2[i], size);
    } 
    std::cout << "Time to generate custom list of size "  << size << " with custom  alloc (" << custom_alloc_size << ")" << " : " 
              << (time / rep ) << " s " << "(average time for " << rep << " iterations)\n";  
}
