/*
 * @lc app=leetcode id=34 lang=cpp
 *
 * [34] Find First and Last Position of Element in Sorted Array
 */
#include <vector>
using namespace std;

/*
Accepted
88 / 88 testcases passed
15ms Beats0.42%
31.60MB Beats17.25%
*/

// @lc code=start
class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        // 看了二分查找进来的，要求O(log n)
        if (nums.size() == 0)
            return vector<int>{-1, -1};
        if (nums.size() == 1)
            if (nums[0] == target)
                return vector<int>{0, 0};
            else
                return vector<int>{-1, -1};
        vector<int> range{-1, -1};
        int middle;
        if (nums.size() % 2)
            middle = nums.size() / 2;
        else
            middle = (nums.size() + 1) / 2;
        auto left = 0;
        int right = nums.size() - 1; // auto就通过不了，不知道为什么unsigned long long也是取整的会错
        // auto currLeftBound = right; // 记录目前最小的target左边界
        // auto cuurRightBound = 0;
        //  有可能两边都是符合的，5 7 7 7 7 10，全部都记录最后排序似乎超出了O(log n)
        //  不太OK呀，每一个子树都要left与right，如果都是符合的那就要定义指数个left和right
        //  还是要递归，问了AI用vector作为返回值的也是可行的
        while (left <= right)
        {

            if (nums[middle] < target)
            {
                // vector<int> right(nums.begin() + middle, nums.end());
                // vector<int> a = searchRange(right, target);
                // range.insert(range.end(), a.begin(), a.end());
                left = middle + 1;
                if ((right - left + 1) % 2)
                    middle = left + (right - left + 1) / 2;
                else
                    middle = left + (right - left + 2) / 2;
            }
            else if (nums[middle] > target)
            {
                right = middle - 1;
                if ((right - left + 1) % 2)
                    middle = left + (right - left + 1) / 2;
                else
                    middle = left + (right - left + 2) / 2;
            }
            else
            {
                // 两边都要检查，可能两边都有
                // currLeftBound = middle;
                // cuurRightBound = middle;
                // auto leftLEFT = left;
                // auto rightLEFT = middle - 1;
                // auto leftRIGHT = middle + 1;
                // auto rightRIGHT = right;
                auto temp = searchChildRange(nums, left, right, target);
                range.clear();
                range.insert(range.end(), temp.begin(), temp.end());
                break;
            }
        }
        return range;
    }

private:
    vector<int> searchChildRange(vector<int> &nums, int left, int right, int target) // 之前为了节省空间，共用一个vector保存，实际确实会覆盖，省不了
    {
        int middle;
        if (left == right && nums[left] == target)
            return vector<int>{left, right};
        else if (left == right)
            return vector<int>{-1, -1};

        if ((right - left + 1) % 2)
            middle = left + (right - left + 1) / 2;
        else
            middle = left + (right - left + 1 + 1) / 2;
        vector<int> result{-1, -1}; //{1000000, -1};  题目nums.size 10^5
        if (nums[middle] == target)
            result[0] = result[1] = middle;

        // if (nums[middle] == target) 第一次肯定是等于才进来递归的

        vector<int> leftChild{-1, -1};
        vector<int> rightChild{-1, -1};
        if (nums[middle] >= target)
            leftChild = searchChildRange(nums, left, middle - 1, target);
        if (middle + 1 <= right)
            rightChild = searchChildRange(nums, middle + 1, right, target);
        // 左右子树结果只会是 {-1,-1}和真实有效两种情况
        if (leftChild[0] >= 0 && rightChild[0] >= 0)
        {
            result[0] = leftChild[0]; // min(leftChild[0], rightChild[0]);
            result[1] = rightChild[1];
        }
        else if (leftChild[0] >= 0)
        {
            if (nums[middle] == target) // 右子树无意义，根相等，左子树区间连上根
                result[0] = leftChild[0];
            else // 例如middle与旁边的都是target，但其余不是，则右子树的最左子树是旁边的，一层层传上去
                result = leftChild;
        }
        else if (rightChild[0] >= 0)
        {
            if (nums[middle] == target)
                result[1] = rightChild[1]; // case1的8左子树是{-1,-1} 右子树得到{4,4}，自己等于middle{3,3}
            else
                result = rightChild;
        }
        else
            ; // result要么是唯一target，如1 2 3的2，则已经在等于middle时设置好了；要么要为{-1,-1}，本来就初始化好了

        // if (!leftChild.empty() && leftChild[0] > -1 && leftChild[0] < result[0])
        //     result[0] = leftChild[0];
        // if (!rightChild.empty() && rightChild[1]!=-1 && rightChild[1] > result[1]) //空 {-1,-1} {1000000,-1}这几种情况都是没有实际意义
        //     result[1] = rightChild[1];

        return result;
    }
};
// @lc code=end
