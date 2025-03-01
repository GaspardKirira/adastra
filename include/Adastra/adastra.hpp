#ifndef ADASTRA_ADASTRA_HPP
#define ADASTRA_ADASTRA_HPP

#include <optional>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <map>
#include <queue>

namespace Adastra
{

    class Adastra
    {
    public:
        Adastra() {}
        ~Adastra() {}

        template <typename ForwardIt>
        static void sortColl(ForwardIt first, ForwardIt last, auto cmp)
        {
            std::sort(first, last, cmp);
        }

        template <typename ForwardIt, typename Compare>
        void sortWithLogging(ForwardIt first, ForwardIt last, Compare comp)
        {
            std::cout << "Debut du tri\n";
            for (auto it = first; it != last; ++it)
            {
                std::cout << "Element en cours: " << *it << "\n";
            }
            std::sort(first, last, comp);
            std::cout << "Fin du tri\n";
        }

        bool areAllElementsValid(const std::vector<int> &data)
        {
            for (int num : data)
            {
                if (num < 0)
                    return false;
            }
            return true;
        }

        void sortWithValidation(const std::vector<int> &data)
        {
            if (!areAllElementsValid(data))
            {
                throw std::invalid_argument("Tous les elements doivent etre non negatifs");
            }
            std::sort(data.begin(), data.end());
        }

        template <typename T>
        static std::optional<T> linearSearch(auto &first, auto &last, const T &target)
        {
            auto it = std::find(first, last, target);
            if (it != last)
                return *it;
            else
                return std::nullopt;
        }

        template <typename T>
        static bool binarySearch(auto &first, auto &last, const T &target)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a > b;
                     });

            return std::binary_search(first, last, target);
        }

        template <typename ForwardIt, typename T>
        bool safeBinarySearch(ForwardIt first, ForwardIt last, const T &target)
        {
            if (first == last)
            {
                throw std::invalid_argument("Plage vide pour la recherche binaire");
            }
            return binarySearch(first, last, target);
        }

        // TODDO: Trouve le premier element >= target
        template <typename ForwardIt, typename T>
        static std::optional<T> lowerBoundBinarySearch(ForwardIt first, ForwardIt last, const T &target)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a < b;
                     });
            auto it = std::lower_bound(first, last, target);
            if (it != last && *it == target)
                return *it;
            else
                return std::nullopt;
        }

        // TODO: trouve le premier element > a target
        template <typename ForwardIt, typename T>
        static std::optional<T> upperBoundBinarySearch(ForwardIt first, ForwardIt last, const T &target)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a < b;
                     });
            auto it = std::upper_bound(first, last, target);
            if (it != last)
                return *it;
            else
                return std::nullopt
        }

        template <typename ForwardIt, typename T>
        static std::pair<ForwardIt, ForwardIt> equalRangeBinarySearch(ForwardIt first, ForwardIt last, const T &target)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a < b;
                     });
            auto range = std::equal_range(first, last, target);
            return range;
        }

        template <typename ForwardIt1, typename ForwardIt2>
        static std::optional<ForwardIt1> searchSubSequence(ForwardIt1 first, ForwardIt1 last,
                                                           ForwardIt2 _first, ForwardIt2 _last)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a < b;
                     });
            auto it = std::search(first, last, _first, _last);
            if (it != last)
                return it;
            else
                return std::nullopt;
        }

        template <typename ForwardIt, typename T>
        static std::optional<ForwardIt> searchRepetition(ForwardIt first, ForwardIt last, size_t repetition, const T &target)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a < b;
                     });
            auto it = std::search_n(first, last, repetition, target);
            if (it != last)
                return it;
            else
                return std::nullopt;
        }

        template <typename ForwardIt>
        static std::optional<ForwardIt> findForAdjacentDuplicates(ForwardIt first, ForwardIt last)
        {
            sortColl(first, last,
                     [](int a, int b)
                     {
                         return a < b;
                     });
            auto it = std::adjacent_find(first, last);
            if (it != last)
                return it;
            else
                return std::nullopt;
        }

        template <typename ForwardIt, typename T, typename Compare>
        std::optional<ForwardIt> findEndWithCompare(ForwardIt first, ForwardIt last, const T &target, Compare comp)
        {
            auto it = std::find_end(first, last, target.begin(), target.end(), comp);
            if (it != last)
                return it;
            else
                return std::nullopt;
        }

        template <typename ForwardIt, typename T, typename Compare = std::equal_to<>>
        std::optional<ForwardIt> findFirstOfWithCompare(ForwardIt first, ForwardIt last, const T &target, Compare comp = Compare())
        {
            auto it = std::find_first_of(first, last, target.begin(), target.end(), comp);
            if (it != last)
                return it;
            else
                return std::nullopt;
        }
    };

    class TrieNode
    {
    public:
        std::unordered_map<char, TrieNode *> children;
        bool isEndOfWord;
        int frequency;

        TrieNode() : isEndOfWord(false), frequency(0) {}

        ~TrieNode()
        {
            for (auto &child : children)
            {
                delete child.second;
            }
        }
    };

    class Trie
    {
    private:
        TrieNode *root;
        std::map<std::string, std::vector<std::string>> semanticMap;

        void collectSuggestions(TrieNode *node, const std::string &prefix, std::vector<std::string> &suggestions)
        {
            if (node->isEndOfWord)
            {
                suggestions.push_back(prefix);
            }

            for (auto &child : node->children)
            {
                collectSuggestions(child.second, prefix + child.first, suggestions);
            }
        }

        int levenshteinDistance(const std::string &s1, const std::string &s2)
        {
            int m = s1.size(), n = s2.size();
            std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

            for (int i = 0; i <= m; i++)
                dp[i][0] = i;
            for (int j = 0; j <= n; j++)
                dp[0][j] = j;

            for (int i = 1; i <= m; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                    {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    else
                    {
                        dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                    }
                }
            }
            return dp[m][n];
        }

        void collectWords(TrieNode *node, const std::string &prefix, std::vector<std::pair<std::string, double>> &results, const std::string &query)
        {
            if (node->isEndOfWord)
            {
                int distance = levenshteinDistance(query, prefix);
                double score = (1.0 / (1 + distance)) + (prefix.size() * 0.1) + (node->frequency * 0.2);
                if (semanticMap.find(query) != semanticMap.end())
                {
                    auto synonyms = semanticMap[query];
                    if (std::find(synonyms.begin(), synonyms.end(), prefix) != synonyms.end())
                    {
                        score += 0.5; // Boost score if synonym is found
                    }
                }
                results.emplace_back(prefix, score);
            }
            for (auto &child : node->children)
            {
                collectWords(child.second, prefix + child.first, results, query);
            }
        }

    public:
        Trie()
        {
            root = new TrieNode();
            semanticMap["solaire"] = {"énergie", "lumière", "soleil"};
            semanticMap["solution"] = {"réponse", "résultat", "remède"};
        }

        ~Trie() { delete root; }

        void insert(const std::string &word)
        {
            TrieNode *node = root;
            for (char c : word)
            {
                if (node->children.find(c) == node->children.end())
                {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->isEndOfWord = true;
            node->frequency++;
        }

        std::vector<std::string> searchWithRanking(const std::string &query)
        {
            std::vector<std::pair<std::string, double>> results;
            collectWords(root, "", results, query);
            std::sort(results.begin(), results.end(), [](const auto &a, const auto &b)
                      { return a.second > b.second; });

            std::vector<std::string> finalResults;
            for (const auto &result : results)
            {
                finalResults.push_back(result.first);
            }
            return finalResults;
        }

        std::vector<std::string> suggestions(const std::string &prefix)
        {
            TrieNode *node = root;
            std::vector<std::string> results;

            for (char c : prefix)
            {
                if (node->children.find(c) == node->children.end())
                {
                    return results;
                }
                node = node->children[c];
            }
            collectSuggestions(node, prefix, results);
            return results;
        }

        bool search(const std::string &word)
        {
            TrieNode *node = root;
            for (char c : word)
            {
                if (node->children.find(c) == node->children.end())
                {
                    return false;
                }
                node = node->children[c];
            }
            return node->isEndOfWord;
        }
    };

} // namespace adastra

#endif // ADASTRA_ADASTRA_HPP
