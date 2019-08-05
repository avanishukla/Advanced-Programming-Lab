#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h> 
using namespace std;

//function to check whether subsequence Tn present in string S or not
int isStringPresent(string s,string t,int n){
    string tmp;
    int k=0,count=0;
    for(int i=0;i<t.length();i++){ //for every character in string t check whether it's present n times in the string s 
        for(int j=0;j<n;j++){
            while(k<s.length() && s[k]!=t[i]){
                k++;
            }
            if(k<s.length()){
                k++;
                count++;   //count number of charcters matched in string s
            }else{        //if pointer reached at end of string s then break the loop
                break;
            }
        }
    }
    if(count<t.length()*n) 
        return 0;
    else
        return 1;
}

//function to find maximum value of i by binary search method
int findMaxI(string s,string t){
    int n = s.length(),m = t.length();
    //array A has count of each char present in string s and array charInT shows which char present in string t (1=present,0=not present)
    int A[4] ={0},charInT[4] = {0};    
    for(int i=0;i<n;i++){   //calculate count of each char present in string s
        A[s[i]-97]++;
    }
    if (t.find('a') != std::string::npos)
        charInT[0] =1;
    if (t.find('b') != std::string::npos)
        charInT[1] =1;
    if (t.find('c') != std::string::npos)
        charInT[2] =1;
    if (t.find('d') != std::string::npos)
        charInT[3] =1;
    int min=INT_MAX;
    //value of min times char present in string s can be highest value of imax
    for(int i=0;i<4;i++){      
        if(charInT[i]==1 && A[i]<min)
            min = A[i];
    }
    int ilower = 1,ihigher = min,imiddle ; 
    int valLower, valHigher, valmiddle ; 
    //val* represents if for value of i* string present in s  
    valLower = isStringPresent(s,t,ilower);
    valHigher = isStringPresent(s,t,ihigher);
    if(valLower==0){  //if string t1 is not present in string s then return i=0
        return 0;; 
    }
    if(valHigher==1){  //if string tmin(possible highest value of imax) is not present in string s then return i=min
        return ihigher; 
    }
    //perform binary search like 
    while(ilower<=ihigher){    
                
        imiddle = (ilower+ihigher)/2; 
        if(imiddle==ilower || imiddle==ihigher){ 
            return imiddle;
        }
        valmiddle = isStringPresent(s,t,imiddle);
        
        if(valmiddle==1){  //if t(imiddle) is present in string s then go for higher value of i
            ilower = imiddle;
        }else if(valmiddle==0){  //if t(imiddle) is not present in string s then go for lower value of i
            ihigher = imiddle;
        }
    }   
    
    return 0;
}

int main() {
    string s,t;
    cin>>s>>t;
    
    cout<<findMaxI(s,t);   //find imax such that Timax is subsequence of S.
    return 0;
}