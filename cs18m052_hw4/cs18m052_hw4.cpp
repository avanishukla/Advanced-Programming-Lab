#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct location{                   //structure for x,y coordinates
    long long int x;
    long long int y;
    int rank;                      //stores domination score
    int index;                     //initial index/order
};

//function to merge the sorted arrays into loc[1...n] in ascending order
void merge(location loc[], int s, int m, int e,char t)
{
    int i, j, k, n1 = m-s+1, n2 = e-m,flag;
    location L[n1], R[n2];
    for (i = 0; i < n1; i++){    //copy first subarray into array L
        L[i].x = loc[s + i].x;
        L[i].y = loc[s + i].y;
        L[i].rank = loc[s + i].rank;
        L[i].index = loc[s + i].index;
    }
    for (j = 0; j < n2; j++){     //copy second subarray into array R
        R[j].x = loc[m + 1+ j].x;
        R[j].y = loc[m + 1+ j].y;
        R[j].rank = loc[m + 1+ j].rank;
        R[j].index = loc[m + 1+ j].index;
    }

    i = 0;
    j = 0;
    k = s;
    //merge the sorted arrays into loc[1...n] in ascending order
    while (i < n1 && j < n2)
    {
        flag = 0;
        switch(t){                     //condition check according to sorting by which element
            case 'X':                    //if sorting by 'X'
                if (L[i].x < R[j].x){
                    flag = 1;
                }
                else if(L[i].x == R[j].x){
                    if(L[i].y > R[j].y){
                        flag = 1;
                    }
                }
                break;
            case 'Y':
                if (L[i].y <= R[j].y)   //if sorting by 'Y'
                    flag = 1;
                break;
            case 'I':                   //if sorting by index initial order
                if (L[i].index <= R[j].index)
                    flag = 1;
                break;
        }
        if (flag==1)
        {
            loc[k].x = L[i].x;
            loc[k].y = L[i].y;
            loc[k].rank = L[i].rank;
            loc[k].index = L[i].index;
            i++;
            k++;
        }
        else
        {
            loc[k].x = R[j].x;
            loc[k].y = R[j].y;
            loc[k].rank = R[j].rank;
            loc[k].index = R[j].index;
            j++;
            k++;
        }
    }
    //when one array reaches at the end then for another array
     while (i < n1)     //if elements in L, copy them into loc[]
    {
        loc[k].x = L[i].x;
        loc[k].y = L[i].y;
        loc[k].rank = L[i].rank;
        loc[k].index = L[i].index;
        i++;
        k++;
    }
     while (j < n2)    //if elements in R, copy them into loc[]
    {
        loc[k].x = R[j].x;
        loc[k].y = R[j].y;
        loc[k].rank = R[j].rank;
        loc[k].index = R[j].index;
        j++;
        k++;
    }
}

//function to sort the array by t = ['X','Y','I'=index]
void sort(location loc[],int s,int e,char t){
    if (s < e){
        int m = (s+e)/2;           //recursively call the function for halves
        sort(loc, s, m, t);
        sort(loc, m+1, e, t);
        merge(loc, s, m, e, t);    //merge sorted two halves
    }
}

//function to find rank(domination score) of all x,y in the array
void findRank(location loc[],int s,int e){
    if(s==e){                 //if only one element in array then rank of that element is 0.
        loc[s].rank = 0;
        return;
    }
    int m = (s+e)/2;          //divide the array into halves

    findRank(loc,s,m);        //find the rank of each element in first half
    findRank(loc,m+1,e);      //find the rank of each element in second half

    sort(loc,s,m,'Y');        //sort the halves by 'Y'
    sort(loc,m+1,e,'Y');

    int count=0, ai=s, bi=m+1;
    //merge the halves by updating rank of elements in second half
    while(bi<=e && ai<=m){     //calculate rank for second half of the array
        while(ai<=m && loc[bi].y > loc[ai].y){
            count ++;            //count number of element in first half whose 'Y' value is less than its 'Y' value
            ai++;
        }
        loc[bi].rank += count;   //add that count into its rank
        bi++;
    }
    while(bi<=e){
        loc[bi].rank +=count;
        bi++;
    }
}

int main() {
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        location loc[n];
        for(int i=0;i<n;i++){           //take input for x,y
            cin>>loc[i].x>>loc[i].y;
            loc[i].rank = 0;
            loc[i].index = i;           //stores initial order
        }
        sort(loc,0,n-1,'X');            //first sort the array by 'X'
        findRank(loc,0,n-1);
        sort(loc,0,n-1,'I');            //sort the array by index to get the initial order
        for(int i=0;i<n;i++){
            cout<<loc[i].rank<<" ";     //print domination score for each x,y
        }
        cout<<endl;
    }
    return 0;
}
