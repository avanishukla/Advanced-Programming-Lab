#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void swap(int *p,int *q){
    int temp = *p;
    *p = *q;
    *q = temp;
}

//function for hepify when insert elememt into array
void heapify(int *a,int i){
    while(i!=0 && a[(i-1)/2]>a[i]){
        swap(&a[(i-1)/2],&a[i]);
        i = (i-1)/2;
    }
}

//function for heapify subtree
void heapifyRoot(int *arr,int i,int size){
    int l = 2*i+1 , r = 2*i+2;
    int min = i;
    if(l<size){
        if(arr[l]<arr[min]){
            min = l;
        }
    }
    if(r<size){
        if(arr[r]<arr[min]){
            min = r;
        }
    }

    if(min==l){
        swap(&arr[l],&arr[i]);
        heapifyRoot(arr,l,size);
    }
    else if(min==r){
        swap(&arr[r],&arr[i]);
        heapifyRoot(arr,r,size);
    }
}

//function to get min element from the haep
int deletemin(int *arr,int *size){
    int k = arr[0];
    swap(&arr[0],&arr[(*size)-1]);
    (*size)--;
    heapifyRoot(arr,0,*size);
    return k;
}

void kSum(int *a,int *b,int m,int n,int k){
    int ak[k],bk[k],c[k*k];
    for(int j=0;j<k;j++){
        ak[j] = deletemin(a,&m);      //extract min k elements from array 'a' and store into array 'ak'
        bk[j] = deletemin(b,&n);      //extract min k elements from array 'b' and store into array 'bk'
    }

    int p=0;
    for(int i=0;i<k;i++){      //calculate sum of each elements form array 'ak' and 'ab' and store sum into min-heap 'c'
        for(int j=0;j<k;j++){
            c[p] = ak[i] + bk[j];
            heapify(c,p);     //heapify 'c'
            p++;
        }
    }
    int csize = k*k;         //extract min k sum from 'c'
    for(int i=0;i<k;i++){
        cout<<deletemin(c,&csize)<<" ";
    }
}

int main() {
    int n,m,k;
    cin>>m>>n>>k;
    int a[m],b[n];
    for(int i=0;i<m;i++){
        cin>>a[i];          //store elements of array a in min-heap
        heapify(a,i);
    }
    for(int i=0;i<n;i++){
        cin>>b[i];        //store elements of array b in min-heap
        heapify(b,i);
    }
    //a and b are min-heap

    kSum(a,b,m,n,k);       //find smallest k sum

    return 0;
}
