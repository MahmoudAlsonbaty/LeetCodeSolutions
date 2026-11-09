#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;
class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        vector<int> prefix = {};
        if(nums.size() ==1)return 0;

        long long sum =0;
        for(int i = 0;i<nums.size();i++){
            sum += nums[i];
            prefix.push_back(sum);
        }
        prefix.push_back(0);
        for(int i = 0;i<prefix.size();i++){
            int a = prefix[i];
            int b = prefix[prefix.size()-i-1];
            if(a == b){
                return i;
            }
        }
        return -1;
    }
};

int main(){
    vector<int> val = {1,-1,4};
    auto answer = Solution().findMiddleIndex(val);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
