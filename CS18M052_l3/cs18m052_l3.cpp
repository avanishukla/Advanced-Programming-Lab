#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void polyMulti(long long int c[], long long int a[], long long int b[], int s){

    if(s==0){        //if zero element in the array then return
        return;
    }

    if(s==1){         //if single elements in both the array then simply multiply them and return
        c[0] = a[0] * b[0];
        return;
    }

    int m = s/2;      //find the middle point of the array
    int t = ceil((double)s/2);    //this is the size of resultant array: sum of lower and higher part of the array

    long long int tmp1[t] = {0};    //two temporary array to store resultant array of array A and B
    long long int tmp2[t] = {0};
    int i;

    for(i=0;i<m;i++){                //caclulation of resultant array
        tmp1[i] = a[i] + a[i+m];
        tmp2[i] = b[i] + b[i+m];
    }
    if(i+m<s){                      //if size is odd then higher part have one more element, add last element as it is
       tmp1[i] = a[i+m];
    }
    if(i+m<s){
        tmp2[i] = b[i+m];
    }

    int ul0 = 2*m-1, ul1 = 2*t-1, ul2 = (2*s)-(2*m)-1;
    long long int u0[ul0], u1[ul1], u2[ul2];

    polyMulti(u0,a,b,m);       //u0 stores the result of a0*b0
    polyMulti(u2,a+m,b+m,s-m); //u2 stores the result of a1*b1
    polyMulti(u1,tmp1,tmp2,t); //u1 stores the result of (a0+a1) * (b0+b1)

    for(i=0;i<min(ul0,ul2);i++){           //calcute u1 - u0 - u2 and store result into u1
        u1[i] = u1[i] - u0[i] - u2[i];
    }
    if(ul0<ul2){
        while(i<ul2){
            u1[i] = u1[i] - u2[i];
            i++;
        }
    }else if(ul0>ul2){
        while(i<ul0){
             u1[i] = u1[i] - u0[i];
            i++;
        }
    }

    for(int i=0;i<2*s-1;i++){          //calculate u2 * x^(2*m) + u1 * x^m + u0 and store into array C
        if(i<m){
            c[i] = u0[i];
        }else if(2*m-i>0 && i<ul0){
            c[i] = u0[i] + u1[i-m];
        }else if(2*m-i>0){
            c[i] = u1[i-m];
        }else if(i<ul0){
            c[i] = u0[i] + u1[i-m] + u2[i-(2*m)];
        }else if(i<ul1+m){
            c[i] = u1[i-m] + u2[i-(2*m)];
        }else{
            c[i] = u2[i-(2*m)];
        }
    }
}

int main() {
    int n,m,s;
    cin>>n>>m;

    if(n<m){   //get the highest power from both the polynomial
        s=m;
    }else{
        s=n;
    }
    long long int a[s],b[s];
    long long int c[2*s-1];
    for(int i=0;i<n;i++){         //take input
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        cin>>b[i];
    }
    if(n>m){                   //append zero and make polynomial of the same degree(highest degree)
        for(int i=m;i<s;i++){
            b[i] = 0;
        }
    }else{
        for(int i=n;i<s;i++){
            a[i] = 0;
        }
    }

    polyMulti(c,a,b,s);        //multiply both polynomial and assign result to array C

    for(int i=0;i<m+n-1;i++){
        cout<<c[i]<<" ";
    }

    return 0;
}
