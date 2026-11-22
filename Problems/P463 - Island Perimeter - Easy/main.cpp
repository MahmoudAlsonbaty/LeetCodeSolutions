#include <cstddef>
#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int getPerimeterBlock(vector<vector<int>>& grid, int i,int j){
        int answer = 0;
        //top
        if((i-1 >= 0 && grid[i-1][j] == 0) || i-1 ==-1 /*Outside grid counts*/){
            answer++;
        }
        //bottom
        if((i+1 < grid.size() && grid[i+1][j] == 0) || i+1 ==grid.size() /*Outside grid counts*/){
            answer++;
        }
        //left
        if((j-1 >= 0 && grid[i][j-1] == 0) || j-1 ==-1 /*Outside grid counts*/){
            answer++;
        }
        //right
        if((j+1 < grid[i].size() && grid[i][j+1] == 0) || j+1 ==grid[i].size() /*Outside grid counts*/){
            answer++;
        }
        return answer;
    }
    
    int islandPerimeter(vector<vector<int>>& grid) {
        int sol= 0;
        // 1 -> Land , 0 -> Water
        bool foundIsland = false;
        for(int i = 0;i<grid.size();i++){
            if(foundIsland) break;
            for(int j = 0;j<grid[i].size();j++){
                if(grid[i][j] == 0) continue;
                foundIsland = true;
                
                vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
                //          y   x
                queue<pair<int,int>> q;
                q.push(make_pair(i, j));
                visited[i][j] = true;

                while (!q.empty()) {
                    pair<int,int> curr = q.front();
                    q.pop();
                    int y = curr.first;
                    int x = curr.second;
                    cout << " Y :" << y << " X : " <<x <<endl;
                    sol+= getPerimeterBlock(grid, y, x);
                    //top
                    if(y-1 >= 0 && grid[y-1][x] == 1 && visited[y-1][x] == false){
                        visited[y-1][x] = true;
                        q.push(make_pair(y-1, x));

                    }
                    //bottom
                    if(y+1 < grid.size() && grid[y+1][x] == 1 && visited[y+1][x] == false){
                        visited[y+1][x] = true;
                        q.push(make_pair(y+1, x));
                    }
                    //left
                    if(x-1 >= 0 && grid[y][x-1] == 1 && visited[y][x-1] == false){
                        visited[y][x-1] = true;
                        q.push(make_pair(y, x-1));
                    }
                    //right
                    if(x+1 < grid[y].size() && grid[y][x+1] == 1 && visited[y][x+1] == false){
                        visited[y][x+1] = true;
                        q.push(make_pair(y, x+1));
                    }

                }
                //it's 1 Island only
                break;
            }
        }
        return sol;
    }
};



int main(){
    // vector<vector<int>> grid = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
    // vector<vector<int>> grid = {{1}};
    // vector<vector<int>> grid = {{1, 0}};
    vector<vector<int>> grid = {{1, 1},{1,1}};
    auto answer = Solution().islandPerimeter(grid);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    std::cout << answer <<endl;
    return 0;
}
