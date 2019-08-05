#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct node{
    int r,g,b,index;
};
struct edge{
    int x1,y1,x2,y2,src,dest;
    double w;
};
struct subset
{
    int parent;
    int rank;
};
struct node1D{
    int x,y,r,g,b;
};
struct contours{
    node1D *cc;
    int count;
};
node **gp;
node1D *gp1D;
edge *e;
edge *mstEdges;
int **adjacencyM;

void allEdges(int k){
    int p =0;
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            if(i+1<k){
                e[p].x1 = i;
                e[p].y1 = j;
                e[p].x2 = i+1;
                e[p].y2 = j;
                e[p].src = gp[i][j].index;
                e[p].dest = gp[i+1][j].index;
                e[p].w = sqrt(pow(gp[i][j].r-gp[i+1][j].r,2.0)+pow(gp[i][j].g-gp[i+1][j].g,2.0)+pow(gp[i][j].b-gp[i+1][j].b,2.0));
                p++;
            }
            if(j+1<k){
                e[p].x1 = i;
                e[p].y1 = j;
                e[p].x2 = i;
                e[p].y2 = j+1;
                e[p].src = gp[i][j].index;
                e[p].dest = gp[i][j+1].index;
                e[p].w = sqrt(pow(gp[i][j].r-gp[i][j+1].r,2.0)+pow(gp[i][j].g-gp[i][j+1].g,2.0)+pow(gp[i][j].b-gp[i][j+1].b,2.0));
                p++;
            }
            if(i+1<k && j+1<k){
                e[p].x1 = i;
                e[p].y1 = j;
                e[p].x2 = i+1;
                e[p].y2 = j+1;
                e[p].src = gp[i][j].index;
                e[p].dest = gp[i+1][j+1].index;
                e[p].w = sqrt(pow(gp[i][j].r-gp[i+1][j+1].r,2.0)+pow(gp[i][j].g-gp[i+1][j+1].g,2.0)+pow(gp[i][j].b-gp[i+1][j+1].b,2.0));
                p++;
            }
            if(i-1>=0 && j-1>=0){
                e[p].x1 = i;
                e[p].y1 = j;
                e[p].x2 = i-1;
                e[p].y2 = j-1;
                e[p].src = gp[i][j].index;
                e[p].dest = gp[i-1][j-1].index;
                e[p].w = sqrt(pow(gp[i][j].r-gp[i-1][j-1].r,2.0)+pow(gp[i][j].g-gp[i-1][j-1].g,2.0)+pow(gp[i][j].b-gp[i-1][j-1].b,2.0));
                p++;
            }
        }
    }
}

//merge two subarrays into num array in descending order
void merge(int s, int m, int l)
{
    int i, j, k, n1 = m-s+1, n2 = l-m;
    edge L[n1], R[n2];

    for (i = 0; i < n1; i++){    //copy first subarray into array L
        L[i] = e[s + i];
    }
    for (j = 0; j < n2; j++){     //copy second subarray into array R
        R[j] = e[m + 1+ j];
    }

    i = 0;
    j = 0;
    k = s;
    //merge the arrays into num[1...n]
    while (i < n1 && j < n2)
    {
        if (L[i].w <= R[j].w)
        {
            e[k] = L[i];
            i++;
            k++;
        }
        else
        {
            e[k] = R[j];
            j++;
            k++;
        }
    }
     while (i < n1)     //if elements in L, copy them into num[]
    {
        e[k] = L[i];
        i++;
        k++;
    }
     while (j < n2)    //if elements in R, copy them into num[]
    {
        e[k] = R[j];
        j++;
        k++;
    }
}

void sortEdges(int s,int l){
    if (s < l){
        int m = (s+l)/2;

        sortEdges(s, m);
        sortEdges(m+1, l);
        merge(s, m, l);
    }
}

int find(subset *ss,int i){
    if (ss[i].parent != i)
        ss[i].parent = find(ss, ss[i].parent);

    return ss[i].parent;
}

void unions(subset *ss,int x,int y){
    int xp = find(ss, x);
    int yp = find(ss, y);

    if (ss[xp].rank < ss[yp].rank){
        ss[xp].parent = yp;
    }
    else if (ss[xp].rank > ss[yp].rank){
        ss[yp].parent = xp;
    }
    else
    {
        ss[yp].parent = xp;
        ss[xp].rank++;
    }
}

void MST(int nv,int ne,int c){
    sortEdges(0,ne);
    subset *ss = new subset[nv];
    for (int i = 0; i < nv; ++i)
    {
        ss[i].parent = i;
        ss[i].rank = 0;
    }

    int mstNE = 0,i=0;
    mstEdges = new edge[nv-1-c];
    while(mstNE < nv-1-c){
        int x = find(ss, e[i].src);
        int y = find(ss, e[i].dest);

        if (x != y)
        {
            mstEdges[mstNE++] = e[i];
            unions(ss, x, y);
        }
        i++;
    }
}

void constructAM(int nv,int ne){
    adjacencyM = new int *[nv];
    int count[nv] = {0};
    for(int i=0;i<nv;i++)
        adjacencyM[i]=new int[8];

    for(int i=0;i<ne;i++)
    {
        for(int j=0;j<8;j++){
            adjacencyM[i][j] = -1;
        }
    }
    for(int i=0;i<ne;i++)
    {
        adjacencyM[mstEdges[i].src][count[mstEdges[i].src]++] = mstEdges[i].dest;
        adjacencyM[mstEdges[i].dest][count[mstEdges[i].dest]++] = mstEdges[i].src;
    }
}

void DFS(int i,int *visited,node1D *com,int *count){
    visited[i] = true;
    com[*count] = gp1D[i];
    (*count)++;
    for(int j=0;j<8;j++){
        if(adjacencyM[i][j]!=-1){
            if(visited[adjacencyM[i][j]]==0){
                DFS(adjacencyM[i][j], visited,com,count);
            }
        }
    }
}

void sortByCount(contours *ct,int l){
    for(int i=1;i<l;i++){
        contours tmp = ct[i];
        int j = i-1;
        while(j>=0 && ct[j].count>tmp.count){
            ct[j+1] = ct[j];
            j--;
        }
        ct[j+1] = tmp;
    }
}

void boundary(node1D *cc){

}

void components(int nv,int c){
    int visited[nv] = {0};
    contours ct[c+1];
    for(int i=0;i<c+1;i++){
        ct[i].cc = new node1D[nv];
        ct[i].count = 0;
    }

    int comCount = 0;

    for (int i=0; i<nv; i++)
    {
        if (visited[i] == 0)
        {
            DFS(i, visited,ct[comCount].cc,&ct[comCount].count);
            comCount++;
        }
    }
    sortByCount(ct,c+1);

    for(int i=0;i<comCount;i++){
        cout<<ct[i].count<<" ";
        boundary(ct[i].cc);
        for(int j=0;j<ct[i].count;j++){
            cout<<"["<<ct[i].cc[j].x<<","<<ct[i].cc[j].y<<"] ";
        }
        cout<<endl;
    }
}

int main() {
    int n,c,x,y;
    cin>>n>>c;
    int k =sqrt(n);
    gp = new node *[k];
    for(int i=0;i<k;i++){
        gp[i] = new node[k];
    }

    e = new edge[2*(k-1)*(2*k-1)];

    for(int i=0;i<n;i++){
        cin>>x>>y;
        cin>>gp[x][y].r>>gp[x][y].g>>gp[x][y].b;
        gp[x][y].index = i;
    }

    allEdges(k);
    MST(n,2*(k-1)*(2*k-1),c);
    constructAM(n,n-1-c);

    gp1D= new node1D[n];
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            gp1D[gp[i][j].index].x = i;
            gp1D[gp[i][j].index].y = j;
            gp1D[gp[i][j].index].r = gp[i][j].r;
            gp1D[gp[i][j].index].g = gp[i][j].g;
            gp1D[gp[i][j].index].b = gp[i][j].b;
        }
    }

    components(n,c);

    return 0;
}
