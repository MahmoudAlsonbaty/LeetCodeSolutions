#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int indexStartContainer = 0;
        long long biggest = 0;
        int right = height.size()-1;
        while (indexStartContainer < right) {
        
            long long localMax = min(height[indexStartContainer], height[right]) * (right-indexStartContainer);
            
            //Check if making the small pointer closer would increase the max;
            if(height[indexStartContainer] > height[right]){
                right--;
            }else{
                indexStartContainer++;
            }
            biggest = max(biggest,localMax);
        }
        return biggest;
    }
};

int main(){
vector<int> height = {1,2,3,1000,9};
    auto answer = Solution().maxArea(height);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
