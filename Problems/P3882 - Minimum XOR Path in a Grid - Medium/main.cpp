#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        vector<vector<vector<int>>> Paths;
        for(int i = 0;i<grid.size();i++){
            Paths.push_back(vector<vector<int>>());
            for(int j = 0;j<grid[i].size();j++){
                if(i ==0 && j ==0){
                    Paths[i].push_back(vector<int>());
                    Paths[i][j].push_back(grid[i][j]);
                    continue;
                } 
                Paths[i].push_back(vector<int>());

                if(i>0){
                    for(auto t:Paths[i-1][j]){
                        Paths[i][j].push_back(grid[i][j] ^ t);
                    }
                }
                if(j>0){
                    for(auto t:Paths[i][j-1]){
                        Paths[i][j].push_back(grid[i][j] ^ t);
                    }
                }
                
            }
        }
        int m = grid.size()-1;
        int n = grid[grid.size()-1].size()-1;
        int res = *min_element(Paths[m][n].begin(),Paths[m][n].end());
        return res;
    }
};
int main(){
    vector<vector<int>> T1 = {{1,2},{3,4}};
    vector<vector<int>> T2 = {{6,7},{5,8}};
    vector<vector<int>> T3 = {{2,7,5}};
    vector<vector<int>> T4 = {{26,24,3},{2,22,17}};
    /*
    26 24 3
    2 22 17
    */
    auto sol1 = Solution().minCost(T1);
    auto sol2 = Solution().minCost(T2);
    auto sol3 = Solution().minCost(T3);
    auto sol4 = Solution().minCost(T4);
    cout << sol1 << endl;
    cout << sol2 << endl;
    cout << sol3 << endl;
    cout << sol4 << endl;
    cout<< " "<<endl;
    cout << (26 ^ 24 ^ 3 ^ 17) <<endl;
    cout << (26 ^ 2 ^ 22 ^ 17) <<endl;
    cout << (26 ^ 24 ^ 22 ^ 17) <<endl;
    return 0;
}