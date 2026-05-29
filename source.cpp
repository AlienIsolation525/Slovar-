#include "PrefixTree\PrefixTree.h"

#include <stdlib.h>

using namespace std;
const int MAX_VARIANTS = 9;

int main()
{

    string input;
    PrefixTree prefix_tree;
    TrieNode* root = prefix_tree.get_root();
    prefix_tree.FillTreefromfile();
    
        while (true)
    {
        printf("\033[33m\nBegin to type a word (1st letter is enough)\033[32m then press Enter,\033[1;31m or type 'q' for exit:\033[m");
        std::cin >> input;
        if (input == "q")
        {
            break;
        }

        string props[MAX_VARIANTS];
        const int num_variants = prefix_tree.getProposition(input, props);

        if (num_variants != 0)
        {
            for (size_t i = 0; i < num_variants; ++i)
                std::cout << props[i] << std::endl;
        }
    }
    
    cin.get();
        cin.get();
            cin.get();

    return 0;
}