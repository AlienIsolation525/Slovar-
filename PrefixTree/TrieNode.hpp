#pragma once
#include <string>
#include <iostream>
#include <fstream>
    
const int ALPHABET_SIZE = 26;


struct TrieNode
{
    TrieNode* children[ALPHABET_SIZE];
    std::string data;
    bool isEndOfWord;
};