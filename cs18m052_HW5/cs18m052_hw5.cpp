#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define dbg3(a,b,c) cout<<a<<" "<<b<<" "<<c<<endl;
int nn;
struct point{
    int x;
    int y;
    int d;
};
int *cost;
void swap(point *p,point *q){
    point temp = *p;
    *p = *q;
    *q = temp;
}

//function for hepify array when insert element into the array
void heapify(point *a,int i){
    while(i!=0 && a[(i-1)/2].d>a[i].d){
        swap(&a[(i-1)/2],&a[i]);
        i = (i-1)/2;
    }
}

//function for hepifying structure array from the root node
void heapifyRoot(point *arr,int i,int size){
    int l = 2*i+1 , r = 2*i+2;
    int min = i;
    if(l<size){
        if(arr[l].d<arr[min].d){
            min = l;
        }
    }
    if(r<size){
        if(arr[r].d<arr[min].d){
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

//function for delete min element from the structure
point deletemin(point *arr,int *size){
    point p = arr[0];
    swap(&arr[0],&arr[(*size)-1]);
    (*size)--;
    heapifyRoot(arr,0,*size);
    return p;
}

int connectPoints(point *p,int k, int *n, int *ispointIn){
    int c1 =0;
    for(int i=0;i<k;){
        
        point a = deletemin(p,n);
        if(ispointIn[a.x]==0 && ispointIn[a.y]==0){  //if points already not included then add them
            c1 += a.d;
            i++;
            ispointIn[a.x]=1;
            ispointIn[a.y]=1;
          
            if(a.x-1>0 && a.y+1<=nn){
                point p1;
                p1.x = a.x-1;       
                p1.y = a.y+1;
               
                p1.d = cost[a.x-2]+cost[a.y-1]-a.d;
               
                p[*n] = p1; 
                                
                heapify(p,*n);
                (*n)++;

            }
        }
        
    }
   return c1;
}

int main() {
    int n,k;
    cin>>n>>k;
    nn=n;
    cost = new int[n];
    point p[n-1];
    for(int i=0;i<n-1;i++){
        cin>>p[i].x>>p[i].y>>p[i].d;       //stores points and distance between then into structure array
        cost[i] = p[i].d;
        heapify(p,i);
    }
    
    int ispointIn[n+1] = {0};            //check whether point is used or not
    n--;
    int ans = connectPoints(p,k,&n,ispointIn);
    cout<<ans;
    
    return 0;
}
