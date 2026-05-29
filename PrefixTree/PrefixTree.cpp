#include "PrefixTree.h"

// Конструктор: правильно инициализируем поля класса
PrefixTree::PrefixTree()
{
    root = new TrieNode();
    current = nullptr;
    std::cout << "PrefixTree created in constructor!\n";
}

// Вспомогательный метод для рекурсивного удаления узлов
void PrefixTree::clear(TrieNode* node)
{
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            clear(node->children[i]);
        }
    }
    delete node;
}

// Деструктор: надежно очищает всю память
PrefixTree::~PrefixTree()
{
    clear(root); 
    root = nullptr;
    current = nullptr;
    std::cout << "PrefixTree was destructed in destructor!\n";
}

// Возвращает новый узел (C++ стиль)
TrieNode* PrefixTree::getNewNode(void)
{
    return new TrieNode(); // Все поля уже инициализируются по умолчанию в структуре
}

void PrefixTree::insert(TrieNode* root, std::string key)
{
    if (!root || key.empty()) return;
    TrieNode* node = root;

    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        // Защита от некорректных символов (не от 'a' до 'z')
        if (index < 0 || index >= ALPHABET_SIZE) continue; 

        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool PrefixTree::search(TrieNode* root, std::string key)
{
    if (!root) return false;
    TrieNode* node = root;

    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || !node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

bool PrefixTree::isEmpty(TrieNode* root)
{
    if (!root) return true;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            // Ошибка исправлена: если нашли ребенка, дерево не пустое (false)
            return false; 
    return true;
}

TrieNode* PrefixTree::remove(TrieNode* root, std::string key, int depth)
{
    if (!root)
        return nullptr;

    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isEmpty(root)) {
            delete root;
            root = nullptr;
        }
        return root;
    }

    int index = key[depth] - 'a';
    if (index >= 0 && index < ALPHABET_SIZE)
    {
        root->children[index] = remove(root->children[index], key, depth + 1);
    }

    if (isEmpty(root) && !root->isEndOfWord) {
        delete root;
        root = nullptr;
    }

    return root;
}

bool PrefixTree::isLastNode(TrieNode* root)
{
    if (!root) return true;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
            return false;
    }
    return true;
}

void PrefixTree::recProposition(TrieNode* root, std::string currentPrefix, std::string* result, int& result_length)
{
    if (!root) return;

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
            currentPrefix.push_back('a' + i); // Вместо магического числа 97 используем 'a'
            recProposition(root->children[i], currentPrefix, result, result_length);
            currentPrefix.pop_back();
        }
    }
}

int PrefixTree::getProposition(std::string& query, std::string* result)
{
    if (!this->root) return 0;
    TrieNode* node = this->root;

    size_t n = query.length();
    for (size_t level = 0; level < n; level++)
    {
        int index = query[level] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || !node->children[index])
        {
            return 0; // Префикс не найден
        }
        node = node->children[index];
    }

    int result_length = 0;
    // Начинаем рекурсивный сбор подсказок из найденного узла
    recProposition(node, query, result, result_length);
    
    return result_length;
}

void PrefixTree::FillTreefromfile()
{
    std::ifstream file("text.txt");
    if (!file.is_open())
    {
        std::cerr << "ERROR: Can not open the file!\n";
        return; // Вместо жесткого exit(0) лучше просто выйти из метода
    }

    std::string word;
    while (file >> word) {
        insert(root, word);
    }
    file.close();
}

TrieNode* PrefixTree::get_root()
{
    return root;
}
