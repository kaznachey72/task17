#include <string>
#include <array>

#include "stack.hpp"


int main() 
{
    constexpr size_t size = 6;
    std::array<std::string, size> str_values = {"aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee", "fffff"};


    const size_t capacity = 100;
    Stack<std::string> stack(capacity);
    std::cout << "stack create" << '\n' 
              << "capacity: " << capacity << '\n' 
              << "size: " << stack.size() << '\n'
              << std::endl;


    for (size_t i = 0; i < size; ++i) {
        stack.push(str_values[i]);
        std::cout << "push item: " << str_values[i] << '\t'
                  << "size after push: " << stack.size() << std::endl;
    }
    std::cout << std::endl;


    while (stack.size() > 0) {
        std::cout << "pop item:  " << stack.pop() << '\t'
                  << "size after pop:  " << stack.size() << std::endl;
    }
    std::cout << std::endl;


    stack.clear();
    std::cout << "size after clear: " << stack.size() << std::endl;
    std::cout << std::endl;

    return 0;
}
