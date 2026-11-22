#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for(int i = 0;i<nums.size();i++){
            if(nums[i] != i) return i;
        }
        return 0;
    }
};



int main(){

    // auto answer = Solution().missingNumber();
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
