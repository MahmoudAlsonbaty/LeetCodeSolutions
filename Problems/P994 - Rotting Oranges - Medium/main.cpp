#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <queue>
#include <ratio>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int minutes = 0;
        //The Visited Stores the minutes until this orange is rotten
        vector<vector<int>> visited(grid.size(),vector<int>(grid[0].size(),0));
        int OrangeGroups = 0;
        #define mp make_pair
        //q is rotten fruits location , and minutes till infection 
        queue<pair<pair<int,int>,int>> q;
        bool existSafeOranges = false;
        for(int i =0;i<grid.size();i++){
            for(int j = 0;j<grid[i].size();j++){
                if(grid[i][j] == 2) q.push(mp(mp(i, j),0));
            }
        }
        //Now we have all the Infections at 0
        while (!q.empty()) {
            pair<int,int> currentFruit = q.front().first;
            int y = currentFruit.first;
            int x = currentFruit.second;
            int currentMinutes = q.front().second;
            q.pop();
            //0 representing an empty cell,
            // 1 representing a fresh orange, or
            // 2 representing a rotten orange.
            
            //top
            if(y-1 >=0 && grid[y-1][x] != 0){
                //if rooten, Check the min time
                int newY = y-1;
                int newX = x;
                //rotten orange previously Discovered
                if(visited[newY][newX] != 0){
                   visited[newY][newX] = min(visited[newY][newX],currentMinutes+1);
                   minutes = max(minutes,visited[newY][newX]); 
                
                //rot the orange and add it's time
                }else{
                    if(grid[newY][newX] != 2){ //This is an already rot orrange from the start
                        visited[newY][newX] = currentMinutes+1;
                        q.push(mp(mp(newY,newX),currentMinutes+1));
                        minutes = max(minutes,visited[newY][newX]); 
                    }
                }
            }

            //bottom
            if(y+1 < grid.size() && grid[y+1][x] != 0){
                //if rooten, Check the min time
                int newY = y+1;
                int newX = x;
                //rotten orange previously Discovered
                if(visited[newY][newX] != 0){
                   visited[newY][newX] = min(visited[newY][newX],currentMinutes+1);
                   minutes = max(minutes,visited[newY][newX]); 
                
                //rot the orange and add it's time
                }else{
                    if(grid[newY][newX] != 2){ //This is an already rot orrange from the start
                        visited[newY][newX] = currentMinutes+1;
                        q.push(mp(mp(newY,newX),currentMinutes+1));
                        minutes = max(minutes,visited[newY][newX]); 
                    }
                }
            }

            //left
            if(x-1 >=0 && grid[y][x-1] != 0){
                //if rooten, Check the min time
                int newY = y;
                int newX = x-1;
                //rotten orange previously Discovered
                if(visited[newY][newX] != 0){
                   visited[newY][newX] = min(visited[newY][newX],currentMinutes+1);
                   minutes = max(minutes,visited[newY][newX]); 
                
                //rot the orange and add it's time
                }else{
                    if(grid[newY][newX] != 2){ //This is an already rot orrange from the start
                        visited[newY][newX] = currentMinutes+1;
                        q.push(mp(mp(newY,newX),currentMinutes+1));
                        minutes = max(minutes,visited[newY][newX]); 
                    }
                }
            }
            //right
            if(x+1 <grid[y].size() && grid[y][x+1] != 0){
                //if rooten, Check the min time
                int newY = y;
                int newX = x+1;
                //rotten orange previously Discovered
                if(visited[newY][newX] != 0){
                   visited[newY][newX] = min(visited[newY][newX],currentMinutes+1);
                   minutes = max(minutes,visited[newY][newX]); 
                
                //rot the orange and add it's time
                }else{
                    if(grid[newY][newX] != 2){ //This is an already rot orrange from the start
                        visited[newY][newX] = currentMinutes+1;
                        q.push(mp(mp(newY,newX),currentMinutes+1));
                        minutes = max(minutes,visited[newY][newX]); 
                    }
                }
            }
        }

        for(int i =0;i<grid.size();i++){
            for(int j = 0;j<grid[i].size();j++){
                if(grid[i][j] == 1 && visited[i][j] == 0) existSafeOranges = true; 
            }
        }

        if(existSafeOranges) return -1;
        return minutes;
    }
};



int main(){
    // vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    // vector<vector<int>> grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    // vector<vector<int>> grid = {{0, 2}};
    //0 empty , 1 fresh , 2 rotten
    vector<vector<int>> grid = {{1, 2}};
    auto answer = Solution().orangesRotting(grid);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    std::cout << answer <<endl;
    return 0;
}
