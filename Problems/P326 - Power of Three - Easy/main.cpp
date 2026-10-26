#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n <= 0) return false;
        double a = double(log(double(n)));
        double b = double(log(3));
        double v = double(a)/b;
        double dif = abs(v - round(v));
        
        if(dif < 1e-14){
            return true;
        }
        return false;
    }
};

int main(){

    auto answer = Solution().isPowerOfThree(27);

    std::cout << answer <<endl;
    return 0;
}