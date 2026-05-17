#include <iostream>
#include <stdlib.h>
#include "PrefixTree.h"

int main(int argc, const char* argv[])
{
    struct TrieNode* root = getNewNode();
    FillTreefromfile(file2read, root);
    string input;

    while (true)
    {
        printf("\033[33m\nBegin to type a word (1st letter is enough)\033[32m then press Enter,\033[1;31m or type 'q' for exit:\033[m");
        std::cin >> input;
        if (input == "q")
        {
            break;
        }

        string props[MAX_VARIANTS];
        const int num_variants = getProposition(root, input, props);

        if (num_variants != 0)
        {
            for (size_t i = 0; i < num_variants; ++i)
                std::cout << props[i] << std::endl;
        }
    }

    return 0;
}