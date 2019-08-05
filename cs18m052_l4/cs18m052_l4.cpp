#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct stringTree{              //tree structure
    int value;
    stringTree *left;
    stringTree *right;
    int black;
};
int nn=0;                       //represent how many numbers present in the tree

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
        if (L[i] <= R[j])
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

//merge sort
void mergesort(int num[],int s,int e){
    if (s < e){
        int m = (s+e)/2;              //divide the array into two halves

        mergesort(num, s, m);
        mergesort(num, m+1, e);
        merge(num, s, m, e);
    }
}

//function for inserting number from the tree.
void insertnum(stringTree **s, int num){
    stringTree *tmp;
    int binarr[20],len=0;
    //start of 'convert number from integer to binary'
    while(num>0){
        if(num%2==0)
            binarr[len] = 0;
        else
            binarr[len] = 1;
        num /=2;
        len++;

    }//binarr contain binary value of the number
    for(int i=0,j=len-1;i<(len/2);i++,j--){
        int t;
        t = binarr[i];
        binarr[i] = binarr[j];
        binarr[j] = t;
    }
    //end of 'convert number from integer to binary'
    //if tree is empty then create first node
    if(*s==NULL){
        tmp = new stringTree;
        tmp->value = 1;
        tmp->left = NULL;
        tmp->right = NULL;
        if(len==1){
            tmp->black = 1;
            nn++;
        }else{
            tmp->black = 0;
        }
        *s = tmp;
    }

    int i=1;
    stringTree *node = *s;
    //for ith digit of binary, if node is not present then create the node
    while(i<len){
        if(binarr[i]==0 && node->left ==NULL){
            tmp = new stringTree;
            tmp->value = 0;
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->black = 0;
            node->left = tmp;
            node = node->left;
        }else if(binarr[i]==1 && node->right ==NULL){
            tmp = new stringTree;
            tmp->value = 1;
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->black = 0;
            node->right = tmp;
            node = node->right;
        }
        else if(binarr[i]==0){
            node = node->left;
        }else if(binarr[i]==1){
            node = node->right;
        }
        i++;
    }
    if(node->black==0){           //make last node of number black
        node->black = 1;
        nn++;
    }
}

//function for deleting number from the tree.
void deletenum(stringTree **s, int num){
    if(*s==NULL){                             //if tree is empty
        cout<<"String is not present"<<endl;
        return;
    }
    //start of 'convert number from integer to binary'
    int binarr[20],len=0;
    while(num>0){
        if(num%2==0)
            binarr[len] = 0;
        else
            binarr[len] = 1;
        num /=2;
        len++;

    }
    for(int i=0,j=len-1;i<(len/2);i++,j--){
        int t;
        t = binarr[i];
        binarr[i] = binarr[j];
        binarr[j] = t;
    }
    //end of 'convert number from integer to binary'
   stringTree *node = *s;
    stringTree *deletenode = NULL;      //pointer to delete unused nodes
    int lr=2;
    if(len==1){
        if(node->black==1){
            if(node->left==NULL && node->right==NULL){      //if by deleting number tree become empty
                *s = NULL;
            }else{
                node->black = 0;
            }
            nn--;
        }else{
            cout<<"Node is white"<<endl;
        }
        return;
    }
    int i=1;
    while(i<len){                       //for ith digit of binary number do
        if(binarr[i]==0){               //if ith digit is'0'
            if(node->left!=NULL){
                if(node->right!=NULL){
                    deletenode = node;
                    lr =0;
                }
                if(node->black==1){
                    deletenode = node;
                    lr =0;
                }
                node = node->left;
                if(i==len-1){
                    if(node->black==1){
                        node->black = 0;    //if black lsb node of number then remove color
                        nn--;               //decrease value of numbers present in the tree
                    }else{
                       cout<<"Node is white"<<endl;
                    }
                }
            }else{                          //if ith digit node is not present in the tree
                cout<<"String is not present"<<endl;
                break;
            }
        }
        else if(binarr[i]==1){              //if ith digit is'1'
            if(node->right!=NULL){
                if(node->left!=NULL){
                    deletenode = node;
                    lr = 1;
                }
                if(node->black==1){
                    deletenode = node;
                    lr =1;
                }
                node = node->right;
                if(i==len-1){
                    if(node->black==1){
                        node->black = 0;      //if black lsb node of number then remove color
                        nn--;                 //decrease value of numbers present in the tree
                    }else if(node->left==NULL && node->right==NULL){
                        cout<<"String is not present"<<endl;
                    }else{
                       cout<<"Node is white"<<endl;
                    }
                }
            }else{                            //if ith digit node is not present in the tree
                cout<<"String is not present"<<endl;
                break;
            }
        }
        i++;
    }
    if(lr==2 && node->left==NULL && node->right==NULL && nn==0){  //if after deleting number tree is empty
        *s = NULL;
    }
    else if(deletenode!=NULL){
        if(node->left==NULL && node->right==NULL){      //if there is no node after lsb node then remove unused nodes
            if(lr==0)
                deletenode->left = NULL;
            else if(lr==1)
                deletenode->right = NULL;
        }
    }
}

//recursive function for calculate integer values of node and add them to numarr if present in the tree.
void printnum(stringTree *s,int val,int *numarr,int *index){
    if(s==NULL){                      //if tree is empty.
        cout<<"Empty Tree"<<endl;
        return;
    }
    val = (val*2)+(s->value);         //calculate integer value of root to current node
    if(s->black==1){
        numarr[*index] = val;         //if node is black then add value into array
        (*index)++;
    }
    if(s->left!=NULL)
        printnum(s->left,val,numarr,index);
    if(s->right!=NULL)
        printnum(s->right,val,numarr,index);
}

int main() {
    int input,num;
    cin>>input;

    stringTree *s = NULL;

    while(input!=4){                 //take input untill 4 is encountered.
        if(input==1){
            cin>>num;
            insertnum(&s,num);       //insert num into tree
        }
        else if(input==2){
            cin>>num;
            deletenum(&s,num);      //delete num from tree
        }
        else if(input==3){
            int *numarr = new int[nn];
            int index =0;
            printnum(s,0,numarr,&index);       //get array of all the numbers present in the tree

            mergesort(numarr,0,nn-1);          //sort the array of numbers
            for(int i=0;i<nn;i++){
                cout<<numarr[i]<<" ";          //print numbers
            }
            if(nn!=0)
                cout<<endl;
        }
        cin>>input;
    }
    return 0;
}
