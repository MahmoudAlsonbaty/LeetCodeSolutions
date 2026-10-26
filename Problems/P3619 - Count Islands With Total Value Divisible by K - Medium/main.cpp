#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        //find starting node
        queue<pair<int,int>> q;
        map<pair<int,int>,bool> visited;
        int count = 0;
        for(int i =0;i<grid.size();i++){
            for(int j = 0; j< grid[i].size();j++){
                if(visited.count(make_pair(i,j)) != 0 || grid[i][j] == 0) continue;
                long long sum = 0;
                q.push(make_pair(i,j));
                sum += grid[i][j];

                visited[make_pair(i,j)] = true;
                while(!q.empty()){
                    pair<int,int> current = q.front();
                    q.pop();

                    //top
                    pair<int,int> locT(current.first -1,current.second);
                    if(locT.first < 0 ){
                        
                    }else{
                        if(grid[locT.first][locT.second] != 0&& visited.count(locT) == 0){
                            q.push(locT);
                            sum += grid[locT.first][locT.second];
                            visited[locT] = true;
                        }
                    }
                    
                    //right
                    pair<int,int> locR(current.first,current.second+1);
                    if(locR.second >= grid[locR.first].size()){

                    }else{
                        if(grid[locR.first][locR.second] != 0&& visited.count(locR) == 0){
                            q.push(locR);
                            sum += grid[locR.first][locR.second];

                            visited[locR] = true;
                        }
                    }
                    
                    //bottom
                    pair<int,int> locB(current.first +1,current.second);
                    if(locB.first >= grid.size()){

                    }else{
                        if(grid[locB.first][locB.second] != 0&& visited.count(locB) == 0){
                            q.push(locB);
                            sum += grid[locB.first][locB.second];
                            visited[locB] = true;
                        }
                    }
                    
                    //left
                    pair<int,int> locL(current.first,current.second-1);
                    if(locL.second < 0){

                    }else{
                        if(grid[locL.first][locL.second] != 0&& visited.count(locL) == 0){
                            q.push(locL);
                            sum += grid[locL.first][locL.second];
                            visited[locL] = true;
                        }
                    }
                }
                if(sum != 0 && sum%k ==0){
                    count++;
                }
            }
        }
        return count;
    }
};


int main(){
    vector<vector<int>> grid = {{0,2,1,0,0},{0,5,0,0,5},{0,0,1,0,0},{0,1,4,7,0},{0,2,0,0,8}};
    auto answer = Solution().countIslands(grid,5);

    std::cout << answer <<endl;
    return 0;
}