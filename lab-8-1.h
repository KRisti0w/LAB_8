#ifndef UNTITLED_LAB_8_1_H
#define UNTITLED_LAB_8_1_H

#pragma once
#include <cstring> // для memcpy

// Создает копию строки |str|
char* CopyString(const char* str) {
    if (str == nullptr) return nullptr;

    // Считаем длину строки
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // Выделяем память
    char* copy = new char[length + 1];

    // Копируем данные с помощью memcpy
    memcpy(copy, str, length + 1);

    return copy;
}

// Соединяет две строки в одну новую
char* ConcatinateStrings(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) return nullptr;
    if (a == nullptr) return CopyString(b);
    if (b == nullptr) return CopyString(a);

    // Считаем длины строк
    int len_a = 0, len_b = 0;
    while (a[len_a] != '\0') len_a++;
    while (b[len_b] != '\0') len_b++;

    // Выделяем память для результата
    char* result = new char[len_a + len_b + 1];

    // Копируем первую строку
    memcpy(result, a, len_a);

    // Копируем вторую строку
    memcpy(result + len_a, b, len_b + 1); // +1 чтобы скопировать нуль-терминатор

    return result;
}
#endif //UNTITLED_LAB_8_1_H
