#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int q,n;
    cin>>q;

    while(q--){
        cin>>n;

        long long int cn[n];
        for(int i=1;i<=n;i++){   //intialize count[1..n] with zero
            cn[i]=0;
        }

        for (int i=1; i<=n; i++){       //count different ways possible for all values up to 'n' and store the result
            for (int j=1; j<=3; j++){
                if(j<i){
                    cn[i] += cn[i-j];   //if took jth step then add ways possible for i-j
                }
                else if(j==i){
                    cn[i]++;            //if j step remaining then only one way possible
                }
            }
        }
        cout<<cn[n]<<endl;
    }
    return 0;
}
