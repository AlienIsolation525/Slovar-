#pragma once
#include <string>
using namespace std;

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

const string file2read = "text.txt";
const int ALPHABET_SIZE = 26;
const int MAX_VARIANTS = 9;

// Struct tree node
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord
    bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, string);
bool search(TrieNode*, string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
bool isLastNode(const TrieNode* root);
void recProposition(const TrieNode* root, string currentPrefix, string* result, int& result_length);
int getProposition(TrieNode* root, const string& query, string* result);
 //Fill the tree
void FillTreefromfile(string file2read, struct TrieNode* root);