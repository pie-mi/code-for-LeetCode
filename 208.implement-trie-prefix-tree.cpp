/*
 * @lc app=leetcode id=208 lang=cpp
 *
 * [208] Implement Trie (Prefix Tree)
 */
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/*
Accepted
16 / 16 testcases passed
165ms Beats 5.01%
238.72MB Beats 5.06%
*/

// @lc code=start

// 因为是多叉树且不清楚多少叉，所以难以定义树节点类型，看到用数组或哈希来做的标题和标签
//  但树仍可递归看待，trie的哈希表仍指向trie类型的子树

class Node
{
private:
public:
    Node();
    ~Node();
    unordered_map<char, Node *> hashmap;
};

class Trie
{
public:
    Trie()
    {
        // node.push_back(' ');
        // hashmap[' '] = 0;
        hight = 0;
    }
    Trie(int L)
    {
        hight = L;
        size = 0;
    }

    void insert(string word)
    {
        if (word.length() > 1) // hight < word.size()
        {
            if (this->hashmap.find(word[0]) != this->hashmap.end())
            {
                auto word2 = word;
                word2.erase(word2.begin());
                // this->insert(word2);
                this->hashmap[word[0]]->insert(word2);
            }
            else
            {
                this->hashmap[word[0]] = new Trie; //(this->hight + 1);
                auto word2 = word;
                word2.erase(word2.begin());
                // this->insert(word2);
                this->hashmap[word[0]]->insert(word2);
            }
        }
        else if (word.length() == 1)
        {
            // 要指向/加入一个nullptr表示结束，例如app与apple都有，find(app)就要找到nullptr
            if (this->hashmap.find(word[0]) != this->hashmap.end())
            {
                this->hashmap[word[0]]->hashmap[' '] = nullptr;
            }
            else
            {
                this->hashmap[word[0]] = new Trie; //(this->hight + 1);
                this->hashmap[word[0]]->hashmap[' '] = nullptr;
                // 相当于多创了个app的p子树，因为p可能结尾，也可能有app"le"在后面要加入的
                // 因为只包含小写英文字母，所以用特殊字符与nullptr的键值对来表示结束
            }
        }
    }

    bool search(string word)
    {
        if (word.length() == 1)
        {
            // 搜到这里剩下最后一个字符，找到就true否则就没有
            // 例如已有apple，现在找app是要返回false
            if (this->hashmap.find(word[0]) != this->hashmap.end() && 
                this->hashmap[word[0]]->hashmap.find(' ') != this->hashmap[word[0]]->hashmap.end())//this->hashmap[word[0]] == nullptr
                return true;
            else
                return false;
        }

        if (word.size() > 1)
        {
            if (this->hashmap.find(word[0]) != this->hashmap.end())
            {
                auto word2 = word;
                word2.erase(word2.begin());
                // this->insert(word2);
                return this->hashmap[word[0]]->search(word2);
            }
            else
                return false;
        }
        //else
        //    return true;
    }

    bool startsWith(string prefix)
    {
        // return this->search(prefix);
        if (prefix.size() == 1)
        {
            if (this->hashmap.find(prefix[0]) != this->hashmap.end())
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            if (this->hashmap.find(prefix[0]) != this->hashmap.end())
            {
                auto prefix_popfront = prefix;
                prefix_popfront.erase(prefix_popfront.begin());
                return this->hashmap[prefix[0]]->startsWith(prefix_popfront);
            }
            else
                return false;
        }
    }

private:
    // vector<char> node; // AI说如果vector扩容重新分配了内存，指针仍指向原有的地址
    // unordered_map<char, int> hashmap;
    unordered_map<char, Trie *> hashmap;
    // Node root;
    int hight;
    int size;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end
