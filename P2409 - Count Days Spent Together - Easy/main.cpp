#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int daysInAMonth[] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int arriveAliceMonth = stoi(arriveAlice.substr(0,2));
        int arriveAliceDay = stoi(arriveAlice.substr(3,2));
        int leaveAliceMonth =stoi(leaveAlice.substr(0,2));
        int leaveAliceDay =stoi(leaveAlice.substr(3,2));

        int arriveBobMonth = stoi(arriveBob.substr(0,2));
        int arriveBobDay = stoi(arriveBob.substr(3,2));
        int leaveBobMonth =stoi(leaveBob.substr(0,2));
        int leaveBobDay =stoi(leaveBob.substr(3,2));
        
        int daysSpent = 0;
        bool aliceArrived = false;
        bool BobArrived = false;
        for(int i = min(arriveAliceMonth,arriveBobMonth); i<=12;i++){
            for(int j = 1;j<=daysInAMonth[i];j++){
                    if(arriveAliceMonth == i){
                        if(arriveAliceDay <= j){
                            aliceArrived = true;
                        }
                    }else if (arriveAliceMonth < i){
                        aliceArrived = true;
                    }
                    if(leaveAliceMonth == i){
                        if(leaveAliceDay < j){
                            aliceArrived = false;
                        }
                    }else if (leaveAliceMonth < i){
                        aliceArrived = false;
                    }

                    if(arriveBobMonth == i){
                        if(arriveBobDay <= j){
                            BobArrived = true;
                        }
                    }else if (arriveBobMonth < i){
                        BobArrived = true;
                    }
                    if(leaveBobMonth == i){
                        if(leaveBobDay < j){
                            BobArrived = false;
                        }
                    }else if (leaveBobMonth < i){
                        BobArrived = false;
                    }

                    if(aliceArrived && BobArrived){
                        cout << "[" << i<<"-"<<j<<"] Together (" <<daysSpent<<")"<<endl;
                        daysSpent++;
                    }
            }
            
        }
        return daysSpent;
    }
};

int main(){
    auto answer = Solution().countDaysTogether("02-14","12-06","09-25","10-31");

    std::cout << answer <<endl;
    return 0;
}
