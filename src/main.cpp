#include <allocator.h>


int main(int, char**)
{

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


    return 0;
}