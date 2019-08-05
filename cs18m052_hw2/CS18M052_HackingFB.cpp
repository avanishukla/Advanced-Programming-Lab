#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//merge two subarrays into num array in descending order
void merge(int num[], int s, int m, int e)
{
    int i, j, k, n1 = m-s+1, n2 = e-m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)    //copy first subarray into array L
        L[i] = num[s + i];
    for (j = 0; j < n2; j++)     //copy second subarray into array R
        R[j] = num[m + 1+ j];

    i = 0;
    j = 0;
    k = s;
    //merge the arrays into num[1...n]
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            num[k] = L[i];
            i++;
            k++;
        }
        else
        {
            num[k] = R[j];
            j++;
            k++;
        }
    }
     while (i < n1)     //if elements in L, copy them into num[]
    {
        num[k] = L[i];
        i++;
        k++;
    }
     while (j < n2)    //if elements in R, copy them into num[]
    {
        num[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int num[],int s,int e){
    if (s < e){
        int m = (s+e)/2;

        mergesort(num, s, m);
        mergesort(num, m+1, e);
        merge(num, s, m, e);
    }
}

void countsort(int num[],int n,int e){
    int count[n], tmp[n];

    for(int i=0;i<n;i++){
        count[i] = 0;
    }
    for(int i=0;i<=e;i++){         //count occurence of each digit
        count[ num[i] ]++;
    }
    for(int i=1;i<n;i++){        //stores actual position of number
        count[i] += count[i-1];
    }
    for(int i=e;i>=0;i--){
        tmp[ count[num[i]]-1 ] = num[i];
        count[num[i]]--;
    }
    for(int i=e,j=0; i>=0,j<=e; i--,j++){
        num[j] = tmp[i];
    }
}

//main function
int main() {
    int p,n,sum=0;
    bool valid=1;

    cin>>p>>n;
    int num[n];

    for(int i=0;i<n;i++){
        cin>>num[i];
        sum += num[i];         //sum of all elements
        if(p==1 && num[i]>=n){     //for part-1 number can not be >= N
            valid = 0;
        }
    }

    if(sum%2==1)     //if sum is odd then Invalid
        valid = 0;

    if(valid==1){
        int e;
        if(p==1){     //for part-1
            e=n-1;
            while(e>0){
                countsort(num,n,e);     //sort remaining elements
                while(num[e]==0 && e>0){     //remove 0s from the array
                    e--;
                }
                int k = num[0];
                for(int i=1;i<=k && i<=e;i++){   //update the array
                    num[i]--;
                    num[0]--;
                }
                if(num[0]!=0)
                    break;
            }

            for(int i=0;i<n;i++){  //if all elements in array are zero then Valid
                if(num[i]!=0){
                    valid = 0;
                }
            }
        }
        else if(p==2){  //for part-2
            e = n-1;
            if(n==1){       //if one element then it must be zero
                if(num[0]!=0)
                    valid=0;
            }else if(n==2){   //if two elements then they must be same
                if(num[0]!=num[1])
                    valid=0;
            }else{
                while(e>=3){
                    mergesort(num,0,e);     //sort the remaining elements
                    num[0] -= num[e];
                    num[e] = 0;
                    e--;
                }
                if((num[0]+num[1]+num[2])%2==1)
                    valid=0;
                //for three elements, calculate number of hi5s between three persons
                int e1,e2,e3;
                e1 = (num[0]+num[1]-num[2])/2;
                e2 = (num[1]+num[2]-num[0])/2;
                e3 = (num[0]+num[2]-num[1])/2;
                if(e1<0 || e2<0 || e3<0)    //number of hi5s must be >=0
                    valid=0;
            }

        }
    }

    if(valid)
        cout<<"Valid";
    else
        cout<<"Invalid";

    return 0;
}
