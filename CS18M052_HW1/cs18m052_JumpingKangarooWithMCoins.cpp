#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//function to count possible ways for given 'n' and 'm'
long long int possibleways(int n,int m){
    long long int cn[n+1];
    for(int i=0;i<=n;i++){          //for m=1 stores the possible ways for [1...n] into cn
        cn[i]=0;
    }
    cn[1]=1;
    cn[2]=1;
    cn[3]=1;

    if(m==1){
        return cn[n];
    }
    for(int i=2;i<m;i++){          //calculate possible ways for n=[1...n] for each 2 to m-1 coins
        for(int j=n;j>=i;j--){
            if(j==i){
                cn[j] = 1;
            }else{
                cn[j] = cn[j-1] + cn[j-2] +cn[j-3];//if take k steps then calculate possible ways for (j-k,m-1) where k=(1,2,3)
            }
        }
        for(int j=i-1;j>=0;j--){
            cn[j]=0;
        }
    }
    cn[n] = cn[n-1] + cn[n-2] +cn[n-3];        //calculate possible ways for m coins and n steps
    return cn[n];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int q,n,m;
    long long int a;
    cin>>q;

    while(q--){
        a=0;
        cin>>n>>m;
        if(m==n){         //if coins is equal to the number of steps then there is only one way (1,1,..1) m times
            a=1;
        }
        else if(m<n){     //if coins is greater than total steps then there is no way possible
            a = possibleways(n,m);
        }
        cout<<a<<endl;
    }
    return 0;
}
