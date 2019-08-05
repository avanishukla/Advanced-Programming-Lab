#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int t,m,cost;
    cin>>t;
    while(t--){
        cin>>m;
        cost = 0;
        int i;          
        for(i =m;i>2;){    //starting from M neighbourhood if neighbourhood number is even then divide number by 2 otherwise decrease number by one and add respective cost
            if(i%2==1){
                cost +=2;
                i--;
            }
            else{
                cost +=4;
                i = i/2;
            }
        }
        cost = cost + 2*i;   //At the end if reaches at 1 then add 2(0->1) into cost else if reaches at 2 then add 4(0->1->2) into cost
        cout<<cost<<endl;
    }
    return 0;
}