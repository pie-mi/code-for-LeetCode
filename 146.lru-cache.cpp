/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 */
#include <list>
#include <unordered_map>
#include <utility>

/*
Accepted
23/23 cases passed (82 ms)
Your runtime beats 59.74 % of cpp submissions
Your memory usage beats 46.84 % of cpp submissions (178.8 MB)
*/

// @lc code=start
class LRUCache
{
private:
    int capa;
    // map之类的插入删除时间复杂度不满足O(1)，知道用链表，就key哈希之后到list的iterator，再指向list，内部才是真的value，豆包AI直接说常见于实现LRU
    // list用pair是AI看来的，写到后面理解了：为了弹走链表开头最旧的，哈希表也要知道对应key弹走，所以list不能只单保存value
    std::list<std::pair<int, int>> LRUlist; // 被标签里的链表剧透，本来质疑的，AI直接来了个更加剧透
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> LRUhash;
    bool checkCpacity() //(std::unordered_map<int,std::list<std::pair<int, int>>::iterator> map, size_t capa)
    {
        return LRUhash.size() > capa ? false : true;
    }

public:
    LRUCache(int capacity)
    {

        capa = capacity;
        LRUhash.reserve(capacity);
    }

    int get(int key)
    {
        auto it = LRUhash.find(key);
        if (it != LRUhash.end())
        {
            // 忘了get之后也要调整最近使用顺序
            LRUlist.splice(LRUlist.end(), LRUlist, it->second);
            /*在使用splice()方法后，源迭代器iter将失效，
            因为它指向的元素已经被移动。
            因此，在调用splice()之后，不应再使用该迭代器。
            更新哈希表对应的迭代器
            */
            auto tail = --LRUlist.end();
            LRUhash[key] = tail;
            return it->second->second; // from AI
        }
        else
            return -1;
    }

    void put(int key, int value)
    {

        auto pair = std::make_pair(key, value);
        auto it = LRUhash.find(key);
        if (it != LRUhash.end())
        {
            // 已经存在，一定非空,也不会超出容量，但是也要更新为新的value
            LRUlist.push_back(pair);
            LRUlist.erase(it->second);
            // 获取list最后一个元素的iterator不能end()-1，应该用--end()或者prev(list.end())
            auto tail = --LRUlist.end();
            LRUhash[key] = tail;
        }
        else
        {
            LRUlist.push_back(pair); // 直接压进去，下面再判断有没有超capacity，弹走也是其他旧的
            auto tail = --LRUlist.end();
            LRUhash[key] = tail;
            if (!checkCpacity()) // oversize
            {
                auto oldKey = LRUlist.begin()->first; // list存pair的用处
                LRUhash.erase(oldKey);
                LRUlist.pop_front();
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
