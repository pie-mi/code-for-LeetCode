#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        bool flag = false; //是否找到一个满足的
        for(int i=0;i < nums.size();i++){
            for(int j=i+1; j< nums.size() ; j++){//从下一个开始，避免第一个元素自身相加就是target
                if(nums[i]+nums[j] == target){
                    result.insert(result.end(),i);
                    result.insert(result.end(),j);
                    flag = true;//找到   VS可以在for循环中返回，所以直接return result即可，不用设置flag
                }
            }
            if(flag) break;
        }
    return result;
    }
};

int main() {
    Solution a;
    vector<int> nums = {3,4,2};
    int target = 6; 
    vector<int> result = a.twoSum(nums,target);
    for (int i=0;i < result.size();i++)
        cout<<result.at(i)<<" ";
    return 0;
}