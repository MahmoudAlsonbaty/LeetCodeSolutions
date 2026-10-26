#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int res = 0;
        vector<int> missing;
        for(int i = 0;i<rocks.size();i++){
            //find the number of rocks missing to get full
            missing.push_back(capacity[i] - rocks[i]);
        }

        sort(missing.begin(),missing.end());

        for(int i = 0; i<rocks.size();i++){
            if(additionalRocks <= 0) break;
            if(missing[i] <= additionalRocks){
                res++;
                additionalRocks -= missing[i];
            } 
        }

        return res;
    }
};
int main(){
    vector<int> capacity = {2,3,4,5};
    vector<int> rocks = {1,2,4,4};
    int additionalRocks = 2;
    auto answer = Solution().maximumBags(capacity,rocks,additionalRocks);

    std::cout << answer <<endl;
    return 0;
}
