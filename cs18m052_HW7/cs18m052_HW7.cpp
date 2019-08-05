#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct list{          
    int node;
    list *next;
};
int *min_set;
//function for dfs from given node
void dfs(list *a[],int node,int *visited){
    list *tmp = a[node];
    visited[node] = 1;         //make current node as visited
    while(tmp!=NULL){          //for all non visited adjacent vertices call dfs
        if(visited[tmp->node]==0){
            dfs(a,tmp->node,visited);    
        }
        tmp = tmp->next;
    }
}
//function to find whether path exists between device x to y
int isPath(list *a[],int x,int y,int *pathV){
    list *tmp = a[x];
    if(x==y){         //if source and dest device are same then path exist
        return 1;
    }
    pathV[x] = 1;      //make current node visited
    while(tmp!=NULL){  //for all non visited adjacent vertices of current node find whether path exists or not
        if(pathV[tmp->node]==0){
            if(isPath(a,tmp->node,y,pathV)){   //if path exists return 1
                return 1;
            }    
        }
        tmp = tmp->next;
    }
    return 0;
}
//function to find minimal set of devices
void components(list *a[],int n){
    int visited[n] = {0};  
    int set[n] = {0};
    int cc=0;
    for(int i=0;i<n;i++){    //take next non visited vertex in graph
        if(visited[i]==0){   
            dfs(a,i,visited);  //find all reachable vertices from that vertex and make them visited
            //for all vertices already in minimal set if there is path exists from current vertex to that vertex remove that vertex from minimal set
            for(int j=0;j<cc;j++){    
                int pathV[n] = {0};
                if(set[j]!=-1 && isPath(a,i,set[j],pathV)){    
                    set[j] = -1;
                }
            }
            set[cc] = i;     //add current vertex to set of minimal devices
            cc++;
        } 
    }
    for(int i=0;i<cc;i++){   //copy minimal set to global array
        if(set[i]!=-1){
            min_set[set[i]] = 1;    
        }
    }
}
//function to find minimal latency
int latency(list *a[],int n){ 
    int hop = 1,flag=0;    //initialize hop to 1
    for(int i=0;i<n;i++){  //if all vertices in minimal set then hop equal to 1 and will not enter while loop
        if(min_set[i]==0){
            flag=1;
        }
    }
    //all vertices in minimal set have hop value equal to 1
    while(flag){       //until all vertices visited
        for(int i=0;i<n;i++){
            if(min_set[i]==hop){   //for all vertices of current level of hop value 
                list *tmp = a[i];
                while(tmp!=NULL){   //find  non visited adjacency vertices and assign them to next level of hop value
                    if(min_set[tmp->node]==0){
                        min_set[tmp->node] = hop+1;   
                    }
                    tmp = tmp->next;
                }
            }
        }   
        hop++;       //increment hop 
        flag = 0;  
        for(int i=0;i<n;i++){   //if non visited vertex exists then repeat while loop
            if(min_set[i]==0){
                flag = 1;
            }
        }
    }
    
    return hop;
}

int main() {
    int n,e,r,c;
    cin>>n>>e;
    list *a[n];                //adjacency list of graph
    min_set = new int[n];      //value 1 where device is in minimal set of devices otherwise 0 
    for(int i=0;i<n;i++){
        a[i] = NULL;
    }
    
    for(int i=0;i<e;i++){      
        cin>>r>>c;              //add edge r to c in list
        list *tmp1 = new list;
        tmp1->node = c;
        tmp1->next = NULL;
        if(a[r]==NULL){
            a[r] = tmp1; 
        }else{
            tmp1->next = a[r];
            a[r] = tmp1;
        }
    }
    
    components(a,n);        //find minimal set of devices
    for(int i=0;i<n;i++){   //print minimal set of devices
        if(min_set[i]){
            cout<<i<<" ";    
        }
    }
    cout<<endl;
    
    cout<<latency(a,n);    //find minimal latency
    
    return 0;
}