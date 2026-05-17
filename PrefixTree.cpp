#include <iostream>
#include <fstream>
#include "PrefixTree.h"

using namespace std;

// Return new node
TrieNode* getNewNode(void)
{
    struct TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Remove node
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Base case
    if (!root)
        return nullptr;

    if (depth == key.size()) {

        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // Return new root
    return root;
}

bool isLastNode(const TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            return 0;
        }
    }
    return 1;
}

void recProposition(const TrieNode* root, string currentPrefix, string* result, int& result_length)
{
    if (root->isEndOfWord)
    {
        result[result_length++] = currentPrefix;
    }

    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            currentPrefix.push_back(97 + i);
            recProposition(root->children[i], currentPrefix, result, result_length);
            currentPrefix.pop_back();
        }
    }
}

int getProposition(TrieNode* root, const string& query, string* result)
{
    struct TrieNode* node = root;

    size_t level;
    size_t n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);
        if (!node->children[index])
        {
            return 0;
        }
        node = node->children[index];
    }

    bool isWord = (node->isEndOfWord == true);

    bool isLast = isLastNode(node);

    if (isWord && isLast)
    {
        return 0;
    }
    int result_length = 0;
    if (!isLast)
    {
        recProposition(node, query, result, result_length);
    }
    return result_length;
}

void FillTreefromfile(string file2read, struct TrieNode* root)
{
    string word;
    ifstream file;
    file.open(file2read);

     // Base case
    if (file.fail())
    {
        cout << "ERROR: Can not open the file!" << endl;
        exit(0);
    }

     // Reading file
    while (!file.eof()) {
        file >> word;
        insert(root, word);
    }
    file.close();
}