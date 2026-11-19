#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;


class Solution {
    vector<vector<int>> getSubarray(vector<int>& nums){
        vector<vector<int>> sol;
        for(int i = 0;i<nums.size();i++){
            vector<int> seq;
            for(int j = i;j<nums.size();j++){
                seq.push_back(nums[j]);
                sol.push_back(seq);
            }
            
        }
        return sol;
    }    public:
    int countConsistent(vector<int>& nums) {
        vector<vector<int>> sol = getSubarray(nums);
        int finalSol = 0;
        for(int i = 0;i<sol.size();i++){
            int mini = *min_element(sol[i].begin(),sol[i].end());
            long long holder =sol[i][0];
            for(int j = 0;j<sol[i].size();j++){
                holder = holder & sol[i][j];
            }
            if(holder == mini) finalSol++;
        }
        return finalSol;
    }
};

int main(){
    // auto answer = Solution().maxArea(height);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << answer <<endl;
    return 0;
}
