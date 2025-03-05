#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <map>
#include <string>
#include <unordered_set>
#include <array>

// Thread Pool
class ThreadPool
{
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template <class F, class... Args>
    auto execute(F &&f, Args &&...args) -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

ThreadPool::ThreadPool(size_t threads) : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back([this]
                             {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if (stop && tasks.empty())
                        return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            } });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

template <class F, class... Args>
auto ThreadPool::execute(F &&f, Args &&...args) -> std::future<typename std::invoke_result<F, Args...>::type>
{
    using return_type = typename std::invoke_result<F, Args...>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace([task]()
                      { (*task)(); });
    }
    condition.notify_one();
    return res;
}

// Levenshtein Distance (Fuzzy Search) with std::array
constexpr int Levenshtein(const std::string &s1, const std::string &s2)
{
    int m = s1.size();
    int n = s2.size();

    // Remplacer std::vector par std::array pour un tableau de taille fixe
    std::array<std::array<int, 100>, 100> dp{};

    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }
    return dp[m][n];
}

// Huffman Compression
std::map<char, std::string> huffmanTable;

void buildHuffman(const std::string &text)
{
    for (char c : text)
    {
        huffmanTable[c] = std::string(1, c);
    }
}

std::string compress(const std::string &text)
{
    std::string result;
    for (char c : text)
    {
        result += huffmanTable[c];
    }
    return result;
}

// Trie Structure for fast search
class TrieNode
{
public:
    bool isEndOfWord;
    std::unordered_map<char, TrieNode *> children;

    TrieNode() : isEndOfWord(false) {}
};

class Trie
{
public:
    Trie() : root(new TrieNode()) {}
    void insert(const std::string &word);
    bool search(const std::string &word);

private:
    TrieNode *root;
};

void Trie::insert(const std::string &word)
{
    TrieNode *node = root;
    for (char ch : word)
    {
        if (node->children.find(ch) == node->children.end())
        {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
    }
    node->isEndOfWord = true;
}

bool Trie::search(const std::string &word)
{
    TrieNode *node = root;
    for (char ch : word)
    {
        if (node->children.find(ch) == node->children.end())
        {
            return false;
        }
        node = node->children[ch];
    }
    return node->isEndOfWord;
}

// Bloom Filter for fast search
class BloomFilter
{
public:
    BloomFilter(size_t size);
    void insert(const std::string &item);
    bool contains(const std::string &item);

private:
    std::vector<bool> bitArray;
    size_t size;
    size_t hashFunction(const std::string &item) const;
};

BloomFilter::BloomFilter(size_t size) : size(size), bitArray(size, false) {}

size_t BloomFilter::hashFunction(const std::string &item) const
{
    size_t hash = 0;
    for (char ch : item)
    {
        hash = hash * 31 + ch;
    }
    return hash % size;
}

void BloomFilter::insert(const std::string &item)
{
    size_t hash = hashFunction(item);
    bitArray[hash] = true;
}

bool BloomFilter::contains(const std::string &item)
{
    size_t hash = hashFunction(item);
    return bitArray[hash];
}

// Fuzzy Search with Levenshtein
void fuzzySearch(const std::string &word, const std::string &search)
{
    int distance = Levenshtein(word, search);
    if (distance <= 2)
    {
        std::cout << "Found (Suggestion): " << word << " | Distance: " << distance << std::endl;
    }
}

// int main()
// {
//     ThreadPool pool(4);
//     Trie trie;
//     BloomFilter bloomFilter(1000);

//     // Insert words into Trie and Bloom Filter
//     std::vector<std::string> data = {"softadastra", "softdastr", "software", "solution", "astrada"};
//     for (const auto &word : data)
//     {
//         trie.insert(word);
//         bloomFilter.insert(word);
//     }

//     buildHuffman("softadastra");

//     std::string search = "softdstr";

//     std::vector<std::future<void>> results;

//     // Parallel Fuzzy Search using ThreadPool
//     for (const auto &word : data)
//     {
//         results.push_back(pool.execute(fuzzySearch, word, search));
//     }

//     // Wait for all search tasks to finish
//     for (auto &future : results)
//     {
//         future.get();
//     }

//     // Huffman Compression result
//     std::string compressed = compress("softadastra");
//     std::cout << "Compressed Text: " << compressed << std::endl;

//     // Example usage of Trie and Bloom Filter
//     std::cout << "Trie Search Result: " << (trie.search("software") ? "Found" : "Not Found") << std::endl;
//     std::cout << "Bloom Filter Search Result: " << (bloomFilter.contains("software") ? "Found" : "Not Found") << std::endl;

//     return 0;
// }
int main()
{
    ThreadPool pool(4);
    Trie trie;
    BloomFilter bloomFilter(1000);

    // Exemple de texte pour la compression Huffman
    std::string text = "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
    std::string compressedText;

    // Construire la table de Huffman
    buildHuffman(text);

    // Effectuer la compression
    compressedText = compress(text);

    // Afficher les résultats
    std::cout << "Texte original : " << text << std::endl;
    std::cout << "Texte compressé : " << compressedText << std::endl;

    // Optionnel : Afficher la table de Huffman
    std::cout << "\nTable de Huffman:\n";
    for (const auto &entry : huffmanTable)
    {
        std::cout << entry.first << " -> " << entry.second << std::endl;
    }

    // Recherche dans le Trie et le Bloom Filter
    std::vector<std::string> data = {"fox", "jumps", "quick", "dog", "lazy"};
    for (const auto &word : data)
    {
        trie.insert(word);
        bloomFilter.insert(word);
    }

    std::cout << "\nRecherche dans le Trie:\n";
    for (const auto &word : data)
    {
        std::cout << word << ": " << (trie.search(word) ? "Found" : "Not Found") << std::endl;
    }

    std::cout << "\nRecherche dans le Bloom Filter:\n";
    for (const auto &word : data)
    {
        std::cout << word << ": " << (bloomFilter.contains(word) ? "Found" : "Not Found") << std::endl;
    }

    return 0;
}
