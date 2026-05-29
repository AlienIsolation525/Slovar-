#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "TrieNode.hpp"

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define file2read  "text.txt";


    


class PrefixTree
{



public:
    PrefixTree();
    ~PrefixTree();

    void clear(TrieNode* node);
    
    void insert(TrieNode* node, std::string str);
    
    bool search(TrieNode* node, std::string str);
    
    bool isEmpty(TrieNode* node);
    
    TrieNode* remove(TrieNode* node, std::string str, int depth = 0);
    
    bool isLastNode(TrieNode* root);
    
    void recProposition(TrieNode* root, std::string currentPrefix, std::string* result, int& result_length);
    
    int getProposition(std::string& query, std::string* result);
    
    TrieNode* getNewNode();
    
    TrieNode* get_root();

    void FillTreefromfile();



    private:

    TrieNode* root;
    TrieNode* current;
};


