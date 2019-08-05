#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define MAXSIZE 10
using namespace std;

struct bignum_t
{
    int digit[MAXSIZE];
    int sign;
};

//function will sort number according to d's place using counting sort 
void sortfun(bignum_t num[],int n,int d){
    int index[n];             //store new index 
    int count[10] = {0};
    
    if(d==-1){                //this is for sorting number considering their sign
        int k=0;
        for(int i=n-1;i>=0;i--){   //traverse 'sorted array ignoring sign' from last index for sorting negative numbers
            if(num[i].sign==255){
                index[i] = k;
                k++;
            }
        }
        for(int i=0;i<n;i++){   //traverse 'sorted array ignoring sign' from first index for sorting positive numbers
            if(num[i].sign==0){
                index[i] = k;
                k++;
            }
        }
    }
    else{
        for(int i=0;i<n;i++){         //count occurence of each digit
            count[ num[i].digit[d] ]++;
        }
        for(int i=1;i<10;i++){        //stores actual position of number
            count[i] += count[i-1];
        }
        for(int i=n-1;i>=0;i--){      //assign new index into index array
            index[i] = count[num[i].digit[d]] - 1;
            count[num[i].digit[d]]--;
        }    
    }
     
    int oldi;
    bignum_t oldnum;
    for(int i=0;i<n;i++){       //rotate num array according to new indexes
        while(index[i]!=i){     //while numbers are not at its correct position
            oldi = index[index[i]];     //store index value before placing at correct position
            oldnum = num[index[i]];     //store num before placing at correct position
            
            index[index[i]] = index[i];
            num[index[i]] = num[i];       //place num at its correct position
            
            index[i] = oldi;
            num[i] = oldnum;      
        }
    }
}

int main() {
    int n,ms=0;
    long int tmp;
    cin>>n;
    bignum_t num[n];
    
    for(int i=0;i<n;i++){
        cin>>tmp;
        int j=0,s=0;
        while(tmp>0){                  //stores number in digit array
            num[i].digit[j++] = tmp%10;     
            tmp /=10;
            s++;
        }
        if(s > ms){
            ms = s;              //maximum number of digit in given numbers
        }
        while(j<=10){               //assign zero to rest of indexes of digit array
            num[i].digit[j++] = 0;
        }
    }
    for(int i=0;i<n;i++){
        cin>>num[i].sign;         //stores sign
    }
    
    for(int i=0;i<ms;i++){
        sortfun(num,n,i);        // call sort function for ith place
    }
    //after above function calls, numbers are sorted ignoring sign 
    
    sortfun(num,n,-1);            //call sort function for sign
    
    for(int i=0;i<n;i++){           //print numbers from digit array
        if(num[i].sign==255){
            cout<<'-';
        }
        int j=9;
        while(num[i].digit[j]==0){
            j--;
        }
        while(j>=0){
            cout<<num[i].digit[j];
            j--;
        }
        cout<<' ';
    }
    
    return 0;
}