#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct node{                  //structure to store coordinates info of path
    int row;
    int col;
    int level;
    int mode;
    node *next;
};
node *front=NULL, *rear = NULL;   
int **visited;         //keeps record of visited node by mode
int **a;               //input array
int n,m;

//function for enqueue operation 
void enqueue(node *tmp){
    if(front==NULL & rear==NULL){
        front = tmp;
        rear = tmp;
    }
    else{
        rear->next = tmp;
        rear = tmp;
    }
}
//function for dequeue operation
node* dequeue(){
    node * tmp = front;
    if(front==rear){
        front = NULL;
        rear = NULL;
    }else{
        front = front->next;
    }
    return tmp;
}
//function to check whether black node is there while jumping from (x1,y1) to (x2,y2)
int isPath(int x1,int y1,int x2,int y2){
    if(x2>=0 && x2<n && y2>=0 && y2<m){
        int i,j;
        if(x1==x2){           //if jumping in same row
            i = x1;
            if(y1<y2){          //check for black node in columns
               j = y1+1;
                while(j<=y2){
                    if(a[i][j]==0){    //if node is black then return false
                        return 0;
                    }
                    j++;
                }
            }else{
                j = y1-1;
                while(j>=y2){
                    if(a[i][j]==0){     //if node is black then return false
                        return 0;
                    }
                    j--;
                }
            }
        }
        if(y1==y2){         //if jumping in same column
            j = y1;
            if(x1<x2){      //check for black node in rows
               i = x1+1;
                while(i<=x2){
                    if(a[i][j]==0){     //if node is black then return false
                        return 0;
                    }
                    i++;
                }
            }else{
                i = x1-1;
                while(i>=x2){
                    if(a[i][j]==0){     //if node is black then return false
                        return 0;
                    }
                    i--;
                }
            }
        }
        return 1;     //if no black node encounter in path then return true
    }
    return 0;
}

int minSteps(int x,int y){
    node *tmp = new node;    //insert (0,0) node into queue
    tmp->row = 0;
    tmp->col = 0;
    tmp->level = 0;    
    if(a[0][0]==2){          //if starting node is grey then start with drive othewise start with cycle
        tmp->mode = 3;
    }
    else{
        tmp->mode = 2;
    } 
    if(a[0][0]==0 || a[x][y]==0){   //if starting or destination node is black then can't find path
        return -1;
    }
    visited[0][0] = tmp->mode;
    enqueue(tmp);
    while(front!= NULL && rear!=NULL){     //loop untill queue is not empty
        node *q = dequeue();               //dequeue node
        if( isPath(q->row,q->col,(q->row)-(q->mode),q->col) ){    //move up if black node is not there
            if(x==(q->row)-(q->mode) && y==q->col){           //if node is destination node then return cost
                return (q->level)+1;
            }
            node *tmp1 = new node;
            tmp1->row = (q->row)-(q->mode);
            tmp1->col = q->col;
            tmp1->level = (q->level)+1;
            tmp1->next = NULL;
            if(a[tmp1->row][tmp1->col]==2){  //if node is grey then change mode
                if(q->mode==2){
                    tmp1->mode = 3;
                }
                else  if(q->mode==3){
                    tmp1->mode = 2;
                }
            }else{
                tmp1->mode = q->mode;
            }
            //if node is not visited by same mode then add node into queue, if visited value is 5 means node isvisited by both mode
            if(visited[(q->row)-(q->mode)][q->col] != tmp1->mode && visited[(q->row)-(q->mode)][q->col]!=5){
                visited[(q->row)-(q->mode)][q->col] += tmp1->mode;
                enqueue(tmp1);    
            }
        }
        if( isPath(q->row,q->col,(q->row)+(q->mode),q->col) ){  //move down if black node is not there
            if(x==(q->row)+(q->mode) && y==q->col){
                return (q->level)+1;
            }
            node *tmp2 = new node;
            tmp2->row = (q->row)+(q->mode);
            tmp2->col = q->col;
            tmp2->level = (q->level)+1;
            tmp2->next = NULL;
            if(a[tmp2->row][tmp2->col]==2){
                if(q->mode==2){
                    tmp2->mode = 3;
                }
                else  if(q->mode==3){
                    tmp2->mode = 2;
                }
            }else{
                tmp2->mode = q->mode;
            }
            if(visited[(q->row)+(q->mode)][q->col] != tmp2->mode && visited[(q->row)+(q->mode)][q->col] != 5){
                visited[(q->row)+(q->mode)][q->col] += tmp2->mode;
                enqueue(tmp2);   
            }
        }
        if( isPath(q->row,q->col,q->row,(q->col)-(q->mode)) ){  ////move left if black node is not there
            if(x==q->row && y==(q->col)-(q->mode)){
                return (q->level)+1;
            }
            node *tmp3 = new node;
            tmp3->row = q->row;
            tmp3->col = (q->col)-(q->mode);
            tmp3->level = (q->level)+1;
            tmp3->next = NULL;
            if(a[tmp3->row][tmp3->col]==2){
                if(q->mode==2){
                    tmp3->mode = 3;
                }
                else  if(q->mode==3){
                    tmp3->mode = 2;
                }
            }else{
                tmp3->mode = q->mode;
            }
            if(visited[q->row][(q->col)-(q->mode)] != tmp3->mode && visited[q->row][(q->col)-(q->mode)] != 5){
                visited[q->row][(q->col)-(q->mode)] += tmp3->mode;
                enqueue(tmp3);
            }
        }
        if( isPath(q->row,q->col,q->row,(q->col)+(q->mode)) ){   //move right if black node is not there
            if(x==q->row && y==(q->col)+(q->mode)){
                return (q->level)+1;
            }
            node *tmp4 = new node;
            tmp4->row = q->row;
            tmp4->col = (q->col)+(q->mode);
            tmp4->level = (q->level)+1;
            tmp4->next = NULL;
            if(a[tmp4->row][tmp4->col]==2){
                if(q->mode==2){
                    tmp4->mode = 3;
                }
                else  if(q->mode==3){
                    tmp4->mode = 2;
                }
            }else{
                tmp4->mode = q->mode;
            }
            if(visited[q->row][(q->col)+(q->mode)] != tmp4->mode && visited[q->row][(q->col)+(q->mode)] != 5){
                visited[q->row][(q->col)+(q->mode)] += tmp4->mode;
                enqueue(tmp4);   
            }
        }
    }
    return -1;
}

int main() {
    int t,x,y,steps;
    cin>>t;
    while(t--){
        front = NULL;
        rear = NULL;
        
        cin>>n>>m;
        a = new int*[n];              //allocate memory for input array
        for(int i = 0; i < n; i++)
            a[i] = new int[m];
        
        visited = new int*[n];        //allocate memory for  visited array
        for(int i = 0; i < n; i++)
            visited[i] = new int[m];
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>a[i][j];
                visited[i][j] = 0;
            }
        }
        cin>>x>>y;
        
        steps = minSteps(x,y);      //find min steps require to reach to destination
        cout<<steps<<endl;
        
        for(int i = 0; i < n; i++)  
            delete a[i];
        delete a;
        for(int i = 0; i < n; i++)
            delete visited[i];
        delete visited;
    }
    return 0;
}