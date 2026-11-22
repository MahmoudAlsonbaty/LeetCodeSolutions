#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <utility>

using namespace std;

class Solution {
public:
    struct mycompare{
        bool operator()(const pair<int,int>& f1,const pair<int,int>& f2){
            return f1.second < f2.second;
        }
    };
    
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        vector<int> sol;
        for(auto num:nums){
            freq[num]++;
        }

        priority_queue<pair<int,int>,vector<pair<int,int>>,mycompare> q;
        for(auto [num,fre]:freq){
            q.push(make_pair(num, fre));
        }
        for(int i =0;i<k;i++){
            sol.push_back(q.top().first);
            q.pop();
        }

        return sol;
    }
};

int main(){
    // vector<int> nums = {1, 1, 1, 2, 2, 3};
    // int k = 2;
    // vector<int> nums = {-1,-1};
    // int k = 1;
    vector<int> nums = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
    int k = 2;
    // vector<int> nums = {3,0,1,0};
    // int k = 1;
    auto answer = Solution().topKFrequent(nums,k);
    
    for(int i = 0;i<answer.size();i++){
        cout << endl;
        // for(int j = 0;j<answer[i].size();j++){
            cout<< answer[i];
        // }
    }
    // std::cout << answer <<endl;
    return 0;
}
