//#define DEBUG_INFO_ALL
//#define DEBUG_TEST

#include "allocator.h"


int main(int, char**)
{

try 
{
#ifdef DEBUG_TEST

    auto size = 1024;
    auto rep = 1;

    for(auto i = 128; i < size; i += 128){
        test_list(rep, size, i);
        std::cout << "\n";
        test_map (rep, size, i);
        std::cout << "-----------\n";
    } 
       
    test_vector(106, 10, std::cout);
#else
    /*
• создание экземпляра std::map
• заполнение 10 элементами, где ключ это число от 0 до 9, а значение - факториал ключа
*/  
    std_map_def_alloc();

/*
• создание экземпляра std::map с новым аллокатором ограниченным 10 елементами
• заполнение 10 элементами, где ключ это число от 0 до 9, а значение - факториал ключа
• вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
*/    
    std_map_custom_alloc();

/*
• создание экземпляра своего контейнера для хранения int
• заполнение 10 элементами от 0 до 9
*/ 
    simple_list_def_alloc();    

/*
• создание экземпляра своего контейнера для хранения int с новым аллокатором ограниченным 10 елементами
• заполнение 10 элементами от 0 до 9
• вывод на экран всех значений хранящихся в контейнере
*/    
    simple_list_custom_alloc();

#endif
}

catch (std::exception const& e) {
    std::cerr << e.what() << '\n';
}
  
    return 0;
}