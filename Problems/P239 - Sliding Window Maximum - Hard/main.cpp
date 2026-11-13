#include <algorithm>
#include <functional>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int locationOfMaxElement = 0;
        vector<int> solutionMax;
        int windowBegin = 0;
        // locationOfMaxElement = (max_element(nums.begin(),nums.begin()+k)-nums.begin());
        map<int,int,greater<int>> maxMap; //number,index
        
        // solutionMax.push_back(nums[locationOfMaxElement]);
        for(int i = 0;i<nums.size();i++){
            if(i - windowBegin < k){
                maxMap[nums[i]] = i;
            }else{
                solutionMax.push_back(maxMap.begin()->first);
                maxMap[nums[i]] = i;
                int val = maxMap.begin()->first;
                int indx = maxMap.begin()->second;
                if(maxMap[nums[windowBegin]] == windowBegin){
                    maxMap.erase(nums[windowBegin]);
                }
                windowBegin++;
            }
            //     if(nums[i] >= nums[locationOfMaxElement]){
        //         locationOfMaxElement = i;
        //     }
        //     windowBegin++;
        //     if(locationOfMaxElement < windowBegin){
        //         locationOfMaxElement = (max_element(nums.begin()+windowBegin,nums.begin()+windowBegin+k)-nums.begin());
        //     }
        //     solutionMax.push_back(nums[locationOfMaxElement]);
        }
        solutionMax.push_back(maxMap.begin()->first);
        return solutionMax;
    }
};

int main(){
    // vector<int> nums = {1,-1};
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    auto answer = Solution().maxSlidingWindow(nums,k);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
        for(int i = 0;i<answer.size();i++){
        cout<< answer[i] << " ";
        }
    // std::cout << answer <<endl;
    return 0;
}
