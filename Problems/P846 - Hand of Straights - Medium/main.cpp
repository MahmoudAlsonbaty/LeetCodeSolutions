#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <type_traits>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if(hand.size() % groupSize != 0) return false;
        if(groupSize == 1 && hand.size() >= 1) return true;
        sort(hand.begin(),hand.end());
        unordered_map<int,bool> used;

        int currentGpSize = 0;
        for(int i = 0;i<hand.size();i+=groupSize){
            sort(hand.begin()+i,hand.end());
            for(int j = i;j<i+groupSize;j++){
                if(j+1 == i+groupSize || hand[j+1]-hand[j] == 1 ){
                    continue;
                }else{
                    int nextElement = j+2;
                    bool found = false;
                    while(nextElement < hand.size()){
                        if(hand[nextElement] - hand[j] ==1){
                            swap(hand[nextElement],hand[j+1]);
                            found = true;
                            break;
                        }
                        nextElement++;
                    }
                    if(!found) return false;
                }
            }
        }
        return true;
}
};



int main(){
// vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
// int groupSize = 3;
// vector<int> hand = {1, 2, 3, 9, 10, 11, 15, 16, 17};
// int groupSize = 3;
// vector<int> hand = {1, 8, 3, 9, 10, 11, 15, 16, 17};
// int groupSize = 3;

// vector<int> hand = {1,2,3,8,5,6,7,8};
    // vector<int> hand = {1,2,3,5,6,7,8,8};
    // int groupSize = 4;
    vector<int> hand = {1, 1,2,2,3,3};
int groupSize = 3;
    auto answer = Solution().isNStraightHand(hand,groupSize);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
