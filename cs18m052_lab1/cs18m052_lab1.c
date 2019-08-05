#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//recursive function to print all the arrangements for part1
void allpermutationpart1(char *tmp, int r, int b, int *count,int i){
    //when remaining number of red and blue marbles are zero print that arrangement and increment count by one
    if(r==0 && b==0){
        tmp[i] = '\0';
        printf("%s\n",tmp);
        (*count)++;
        return;
    }
    //when remaing number of red is zero continue for blue
    else if(r==0){
        tmp[i]='B';
        allpermutationpart1(tmp,r,b-1,count,i+1);
        return;
    }
    //when remaing number of blue is zero continue for red
    else if(b==0){
        if(tmp[i-1]!='R'){
            tmp[i]='R';
            allpermutationpart1(tmp,r-1,b,count,i+1);
        }
        return;
    }

    if(i==0){   //for first element starts with B then R
        tmp[i]='B';
        allpermutationpart1(tmp,r,b-1,count,i+1);
        tmp[i]='R';
        allpermutationpart1(tmp,r-1,b,count,i+1);
    }
    else{
        if(tmp[i-1]=='B'){  //if previous element is B
            tmp[i]='B';
            allpermutationpart1(tmp,r,b-1,count,i+1);
            tmp[i]='R';
            allpermutationpart1(tmp,r-1,b,count,i+1);
        }
        else if(tmp[i-1]=='R'){
            tmp[i]='B';
            allpermutationpart1(tmp,r,b-1,count,i+1);
        }
    }
}

//recursive function to print all the arrangements for part1
void allpermutationpart2(char *tmp, int r, int b, int *count,int i){
    //when remaining number of red and blue marbles are zero print that arrangement and increment count by one
    if(r==0 && b==0){
        printf("%s\n",tmp);
        (*count)++;
        return;
    }
    //when remaing number of red is zero continue for blue
    else if(r==0){
        tmp[i]='B';
        allpermutationpart2(tmp,r,b-1,count,i+1);
        return;
    }
    //when remaing number of blue is zero continue for red
    else if(b==0){
        if(tmp[i-1]!='R'){   //if previous element is B
            tmp[i]='R';
            allpermutationpart2(tmp,r-1,b,count,i+1);
        }
        else{
            if(tmp[i-2]=='B'){ //if previous elements is BR
                tmp[i]='R';
                allpermutationpart2(tmp,r-1,b,count,i+1);
            }
        }
        return;
    }

    if(i==0){   //for first element starts with B then R
        tmp[i]='B';
        allpermutationpart2(tmp,r,b-1,count,i+1);
        tmp[i]='R';
        allpermutationpart2(tmp,r-1,b,count,i+1);
    }
    else{   //for all elements except first element
        if(tmp[i-1]=='B'){   //if previous element is B
            tmp[i]='B';
            allpermutationpart2(tmp,r,b-1,count,i+1);
            tmp[i]='R';
            allpermutationpart2(tmp,r-1,b,count,i+1);
        }
        else if(tmp[i-1]=='R'){
            tmp[i]='B';
            allpermutationpart2(tmp,r,b-1,count,i+1);
            if(tmp[i-2]=='B' || i==1){
                tmp[i]='R';
                allpermutationpart2(tmp,r-1,b,count,i+1);
            }
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t,r,b,count,i;
    char tmp[20];
    scanf("%d",&t);
    while(t--){
        count = 0;
        scanf("%d %d",&r,&b);
        if(r>0 && b>0 && r<10 && b<10){
            if(r<=b+1){
                allpermutationpart1(tmp,r,b,&count,0);  //print all arragements for part1
            }
            printf("%d\n",count);
            count = 0;
            allpermutationpart2(tmp,r,b,&count,0);      //print all arragements for part1
            printf("%d\n",count);
            for(i=0;i<20;i++){                           //clears tmp variable
                tmp[i] = '\0';
            }
        }

    }
    return 0;
}
