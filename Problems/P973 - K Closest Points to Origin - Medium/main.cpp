#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        map<double,vector<vector<int>>> dis;
        for(auto t:points){
            double from0 = sqrt(pow((t[0]),2)+pow((t[1]),2));
            if(dis.count(from0) == 0){
                dis[from0] = {t};
            }else{
                dis[from0].push_back(t);
            }
        }
        vector<vector<int>> sol;
        for(auto const &[key,value]:dis){
            if(k==0) break;
            for(auto t:value){
                sol.push_back(t);
                k--;
            }
        }
        return sol;
    }
};

int main(){
    vector<vector<int>> points = {{1, 3}, {-2, 2}};
    int k = 1;
    auto answer = Solution().kClosest(points,k);
    
    for(int i = 0;i<answer.size();i++){
        cout << endl;
        for(int j = 0;j<answer[i].size();j++){
            cout<< answer[i][j] << " ";
        }
    }
    // std::cout << answer <<endl;
    return 0;
}
