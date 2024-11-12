#pragma once
#include <iostream>
#include<vector>
#include "Node.h"

class Hashmap {
private:
	int size;
	std::vector<Item*> items;

public:
	Hashmap();
	~Hashmap();

	long hashFunc(std::string data);

	void insertItem(std::string key, std::string data, std::string key2);
	std::string getItem(std::string data);
	void displayHashmap();
	void deleteItem(std::string data);
	void menu();
	bool isValidData(const std::string& data);
	bool isValidKey(const std::string& key);
	bool isValidKey2(const std::string& key);

	std::vector<int> prefix_function(const std::string& pattern);
	std::vector<int> KMPSearch(const std::string& text, const std::string& pattern);
	std::vector<std::string> search(const std::string& fragment);


};
