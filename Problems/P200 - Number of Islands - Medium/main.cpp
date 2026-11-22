#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<int>> partOf(grid.size(),vector<int>(grid[0].size(),0));

        int NumberOfIslands = 0; 
        for(int i = 0;i<grid.size();i++){
            for(int j = 0;j<grid[i].size();j++){
                if(grid[i][j] =='0') continue;
                if(partOf[i][j] != 0) continue; //Already part of Island
                NumberOfIslands++;
                //1 = Land, 0 = Water
                queue<pair<int,int>> q;
                q.push(make_pair(i, j));
                partOf[i][j] = NumberOfIslands;
                while (!q.empty()) {
                    pair<int,int> curr= q.front();
                    q.pop();
                    int y = curr.first;
                    int x = curr.second;

                    //top
                    if(y-1 >= 0 && grid[y-1][x] == '1' && partOf[y-1][x] == 0){
                        partOf[y-1][x] = NumberOfIslands;
                        q.push(make_pair(y-1, x));

                    }
                    //bottom
                    if(y+1 < grid.size() && grid[y+1][x] == '1' && partOf[y+1][x] == 0){
                        partOf[y+1][x] = NumberOfIslands;
                        q.push(make_pair(y+1, x));
                    }
                    //left
                    if(x-1 >= 0 && grid[y][x-1] == '1' && partOf[y][x-1] == 0){
                        partOf[y][x-1] = NumberOfIslands;
                        q.push(make_pair(y, x-1));
                    }
                    //right
                    if(x+1 < grid[y].size() && grid[y][x+1] == '1' && partOf[y][x+1] == 0){
                        partOf[y][x+1] = NumberOfIslands;
                        q.push(make_pair(y, x+1));
                    }
                }
            }
        }
        return NumberOfIslands;
    }
};



int main(){
    // vector<vector<char>> grid = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};
    vector<vector<char>> grid = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
    auto answer = Solution().numIslands(grid);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    std::cout << answer <<endl;
    return 0;
}
