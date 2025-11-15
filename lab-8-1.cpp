#include <iostream>
#include "lab-8-1.h"

int main() {
    // Тестирование CopyString
    const char* original = "Hello, World!";
    char* copy = CopyString(original);
    std::cout << "Original: " << original << std::endl;
    std::cout << "Copy: " << copy << std::endl;

    // Тестирование ConcatinateStrings
    const char* str1 = "Hello, ";
    const char* str2 = "C++!";
    char* combined = ConcatinateStrings(str1, str2);
    std::cout << "String 1: " << str1 << std::endl;
    std::cout << "String 2: " << str2 << std::endl;
    std::cout << "Combined: " << combined << std::endl;

    // Тестирование с пустыми строками
    char* empty_test1 = ConcatinateStrings("", "World");
    char* empty_test2 = ConcatinateStrings("Hello", "");
    char* both_empty = ConcatinateStrings("", "");
    char* null_test = ConcatinateStrings(nullptr, "Test");

    std::cout << "Empty first: " << empty_test1 << std::endl;
    std::cout << "Empty second: " << empty_test2 << std::endl;
    std::cout << "Both empty: " << both_empty << std::endl;
    std::cout << "Null test: " << (null_test ? null_test : "nullptr") << std::endl;

    // Освобождаем память
    delete[] copy;
    delete[] combined;
    delete[] empty_test1;
    delete[] empty_test2;
    delete[] both_empty;
    delete[] null_test;

    return 0;
}