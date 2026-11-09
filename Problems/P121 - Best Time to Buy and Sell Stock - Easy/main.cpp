#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int smallest = prices[0];
        int bigProfit = 0;
        for(int i = 1;i<prices.size();i++){
            int curr = prices[i]-smallest;
            if(prices[i]<smallest) smallest=prices[i];
            bigProfit= max(bigProfit,curr);
        }
        return bigProfit;
    }
};

int main(){
    vector<int> val = {7,6,4,3,1};
    auto answer = Solution().maxProfit(val);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
