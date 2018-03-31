#pragma once

#include <iostream>

void debug_info(std::ostream& d_out) { d_out << std::endl; }

template<typename Arg,  typename... Args>
void debug_info(std::ostream& d_out, const Arg& arg, const Args&... args)
{
    d_out << arg;
    debug_info(d_out, args...);
}

#ifdef DEBUG_INFO_ALL
    #define DEBUG_INFO_1
	#define DEBUG_INFO_2
#endif

#ifdef DEBUG_INFO_1
    #define D_1_LOG debug_info
#else
    #define D_1_LOG(...)  
#endif

#ifdef DEBUG_INFO_2
    #define D_2_LOG debug_info
#else
    #define D_2_LOG(...)  
#endif