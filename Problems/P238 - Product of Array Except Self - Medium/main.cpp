#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<long long> prefix;
        vector<long long> suffix;
        for(int i = 0;i<nums.size();i++){
            if(i == 0){
                suffix.push_back(1);//do something
                suffix.push_back(nums[nums.size()-1]);//do something
                prefix.push_back(1);
                prefix.push_back(nums[i]);
            }else{
                prefix.push_back(prefix[i]*nums[i]);
                suffix.push_back(suffix[i]*nums[nums.size()-i-1]);
            }
        }

        vector<int> sol;
        for(int i = 0;i<nums.size();i++){
            long long pre = prefix[i];
            long long post = suffix[nums.size()-i-1];
           
                sol.push_back(post * pre);
            
        }
        return sol;
    }
};

int main(){
    vector<int> nums = {1, 2, 3, 4};
    auto answer = Solution().productExceptSelf(nums);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
        for(int i = 0;i<answer.size();i++){
            cout << endl;
            cout<< answer[i];
    }
    // std::cout << answer <<endl;
    return 0;
}
