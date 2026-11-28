#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size() - 1;
        // Turn trailing 9s into 0s (carry propagates left)
        while (i >= 0 && digits[i] == 9) {
            digits[i] = 0;
            i--;
        }
        if (i < 0) {
            // All digits were 9, e.g. 999 -> 1000
            digits.insert(digits.begin(), 1);
        } else {
            digits[i] += 1;
        }
        return digits;
    }
};



int main(){

    vector<int> digits = {9, 9, 9};
    auto answer = Solution().plusOne(digits);

    // cout2DVector(&answer);   // vector<vector<T>>
    coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
