/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

// @lc code=start
//#include <vector>
//using namespace std;
class MinStack {

private:
    int min; //要处理：只push一次后立刻getmin，第一个push来的就是最小值
    std::vector<int> base;
    void updateMin(){
        if(!base.empty()){
           min = *base.begin(); //应该等同于base[0]
           std::vector<int>::iterator kuci; //迭代器
           for (kuci = base.begin(); kuci != base.end(); kuci++)
            {
                if(*kuci < min){
                 min = *kuci;
                }
            }
          
        }
    }

public:
    MinStack() {
        //min = 0; //构造函数初始化min不行，因为第一个push是3，那min会是0
    }
    
    void push(int val) {
        base.push_back(val);
        if(base.size()==1) //第一个进来就是最小值，后面min记录的值就是正常的
            min = base[0];
        min = val < min ? val : min; //更新最小值
    }
    
    void pop() {
        base.pop_back(); //数组的话，要记录长度，尾指针前移一个
        //更新min
        //min = *base.begin(); //min设为第一个值，若pop完已经为空，题目说不会再getmin
        /*if(!base.empty()){
           min = *base.begin(); //应该等同于base[0]
            std::vector<int>::iterator kuci; //迭代器
            for (kuci = base.begin(); kuci != base.end(); kuci++)
            {
                if(*kuci < min){
                 min = *kuci;
                }
            }
          
        }*/
        updateMin();
    }
    
    int top() {
        int n = base.size() - 1;
        return base[n];
    }
    
    int getMin() {
        /*if(base.size()==1)
            return base[0];*/
        return min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

