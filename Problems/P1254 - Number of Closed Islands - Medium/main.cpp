#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    bool blockSafe(vector<vector<int>>& grid,int i,int j){
        // 0 Land , 1 Water
        bool top =false;
        bool bottom =false;
        bool left =false;
        bool right =false;
        //top
        if(i > 0 ){
            top = true;
        }
        //bottom
        if(i < grid.size()-1){
            bottom = true;
        }
        //left
        if(j >0){
            left = true;
        }
        //right
        if(j < grid[i].size()-1){
            right = true;
        }

        if(top && bottom && left && right) return true;
        return false;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int safeIslands = 0;
        int exploredIslands = 0;
        vector<vector<int>> visited(grid.size(),vector<int>(grid[0].size(),0));
        
        for(int i = 0;i<grid.size();i++){
            for(int j = 0;j<grid[i].size();j++){
                if(grid[i][j] == 1) continue;
                if(visited[i][j] != 0) continue; //Visited before
                exploredIslands++;
                bool IslandSafe = true;
                
                queue<pair<int,int>> q;
                q.push(make_pair(i, j));
                visited[i][j] = exploredIslands;
                while (!q.empty()) {
                    pair<int,int> curr = q.front();
                    q.pop();
                    int y = curr.first;
                    int x = curr.second;
                    if(!blockSafe(grid, y, x)) IslandSafe = false;

                    //0 Land 1 Water
                    //top
                    if(y-1 >=0 && grid[y-1][x] == 0 && visited[y-1][x] == 0){
                        visited[y-1][x] = exploredIslands;
                        q.push(make_pair(y-1,x));
                    }
                    //bottom
                    if(y+1 < grid.size() && grid[y+1][x] == 0 && visited[y+1][x] == 0){
                        visited[y+1][x] = exploredIslands;
                        q.push(make_pair(y+1,x));
                    }
                    //left
                    if(x-1 >= 0 && grid[y][x-1] == 0 && visited[y][x-1] == 0){
                        visited[y][x-1] = exploredIslands;
                        q.push(make_pair(y,x-1));
                    }
                    //right
                    if(x+1 < grid[y].size() && grid[y][x+1] == 0 && visited[y][x+1] == 0){
                        visited[y][x+1] = exploredIslands;
                        q.push(make_pair(y,x+1));
                    }
                }

                if(IslandSafe) safeIslands++;
            }
        }
        return safeIslands;
    }
};



int main(){
// vector<vector<int>> grid = {{1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1, 1, 0}, {1, 0, 1, 0, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 0}};
    // vector<vector<int>> grid = {{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}};
    vector<vector<int>> grid = {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 1, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 1, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1}};
auto answer = Solution().closedIsland(grid);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    std::cout << answer <<endl;
    return 0;
}
