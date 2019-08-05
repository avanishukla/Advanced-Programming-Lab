#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//function takes steps 's' as argument and count different ways to reach that many steps
void nextstep(int s,long long int *cn){
    int i;
    if(s==0){
        (*cn)++;   //when reach at top increment count by one
    }
    for(i=1;i<=3;i++){
        if(s>=i){        //do when remaining steps is greater than i (1,2,3)
            nextstep(s-i,cn);    //find ways after took i steps
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    long long int cn=0;      //stores the number of ways

    scanf("%d",&n);

    nextstep(n,&cn);
    printf("%lld",cn);

    return 0;
}
