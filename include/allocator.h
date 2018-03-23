#pragma once

#include <vector>
#include <map>
#include <list>
#include <blk_allocator.h>
#include <simple_list.h>
#include <def_allocator.h>


const int N_SZ = 10;


constexpr int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


void std_map_def_alloc(size_t n = N_SZ) {

    auto m = std::map<int, int, std::less<int> >{};
    for(size_t i = 0; i < n; i++) {      
        m[i] = factorial(i);
    }
}


void std_map_custom_alloc(size_t n = N_SZ, std::ostream& os = std::cout) {

    auto m = std::map<int, int, std::less<int>, blk_allocator<std::pair<const int, int>, N_SZ> >{};
    for(size_t i = 0; i < n; i++) {       
        m[i] = factorial(i);
    }

    for (auto& kv : m) {
        os << kv.first << " " << kv.second << std::endl;
    }
}


void simple_list_def_alloc(size_t n = N_SZ) {
    
    auto l = simple_list<int>{};
    for (size_t i = 0; i < n; ++i){
        l.push_back(i);
    }  
}


void simple_list_custom_alloc(size_t n = N_SZ, std::ostream& os = std::cout) {

    auto l = simple_list<int, blk_allocator<int, N_SZ>>{};
    for (size_t i = 0; i < n; ++i){
        l.push_back(i);
    }
    for (auto&  val: l) {
        os << val << std::endl;
    }
}