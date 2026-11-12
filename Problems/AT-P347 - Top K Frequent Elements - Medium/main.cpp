#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> freq(100000*2+1,-1);
        map<int,vector<int>,greater<int>> dis;
        for(auto num:nums){
            if(freq[num] == -1){
                //First time seeing it
                if(dis.count(1) == 0){
                    dis[1] = {num};
                }else{
                    dis[1].push_back(num);
                }
                freq[num] = 1;
            }else{
                //Number was there before
                //remove from old list
                auto loc = find(dis[freq[num]].begin(),dis[freq[num]].end(),num);
                dis[freq[num]].erase(loc);
                //insert to new list
                freq[num]++;
                if(dis.count(freq[num]) == 0){
                    dis[freq[num]] = {num};
                }else{
                    dis[freq[num]].push_back(num);
                }
            }
        }
        vector<int> sol;
        for(auto const &[key,value]:dis){
            for(auto t:value){
                if(k==0) return sol;
                sol.push_back(t);
                k--;
            }
        }
        return sol;
    }
};

int main(){
    vector<int> nums = {-1,-1};
    int k = 1;
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
