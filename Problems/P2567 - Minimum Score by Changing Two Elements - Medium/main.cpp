#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        if(nums.size() <= 3) return 0;
        sort(nums.begin(),nums.end());

        int first = abs(*(nums.end()-3) - nums[0]);
        int scond = abs(*(nums.end()-1) - nums[2]);
        int third = abs(*(nums.end()-2) - nums[1]);
        return min(first,min(scond,third));
    }
};



int main(){

    // auto answer = Solution().minimizeSum();
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // std::cout << answer <<endl;
    return 0;
}
