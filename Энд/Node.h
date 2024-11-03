#pragma once
#include <iostream>

class Item {
public:
    std::string data;
    std::string key;
    std::string key2;
    Item* next;

    Item(std::string key, std::string data, std::string key2) {
        this->key = key;
        this->key2 = key2;
        this->data = data;
        this->next = nullptr;
    }
};


