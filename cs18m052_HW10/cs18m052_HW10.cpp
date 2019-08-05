#include <iostream>
#include<math.h>
using namespace std;
//function to find house numbers for A
void housesForA(int arr[], int n, int sum) //arr[] stores wealthof each house,n= number of houses, sum=40% of totalsum
{  
    int **dp = new int*[n];   //array to store min(max_sum possible by i houses,j)
    for (int i=0; i<n; ++i) 
    { 
        dp[i] = new int[sum + 1];  
    } 
  
   for(int i=0;i<=sum;i++){
        if (arr[0] <=i)       
            dp[0][i] = arr[0];
   }
     
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < sum + 1; ++j) {
            if(arr[i] <= j){  //if current wealth is less than current sum 
                if(dp[i-1][j] !=j){   //if previous value is less than current sum then calculate value including current wealth and if it is greater than assign it else leave previous value as it is
                    if((arr[i] + dp[i-1][j-arr[i]]) > dp[i-1][j])
                        dp[i][j] = arr[i] + dp[i-1][j-arr[i]];
                    else
                        dp[i][j] = dp[i-1][j];
                }
                else if(dp[i-1][j]>0)     //if previous value is equal to current sum then assign it as it is
                    dp[i][j] = dp[i-1][j];
                else if(dp[i-1][j]==0){   //else calculate new value including current wealth
                    dp[i][j] = arr[i] + dp[i-1][j-arr[i]];
                }
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    int ans[n],count=0;
    int i=n-1,j=sum;    //start iteration from dp[n-1][sum]
    while(j>0 && i>0){    
        if(dp[i][j]==dp[i-1][j])  //if value is same then current wealth is not included
            i--;
        else{
            ans[count++] = i;
            j = j-arr[i];
            i--;
        }
    }
    ans[count++] = i;
    for (int i=0; i<count; ++i) //print index of houses for A in decreasing order
    { 
        cout<<ans[i]<<" "; 
    } 
} 

int main() {
    int n,sum = 0;
    cin>>n;
    int p[n];
    int k=n;
    for(int i=0;i<n;i++){
        cin>>p[i];
        sum += p[i];   //total sum of wealth
    }
    int s = floor(sum*0.4); //40% of total sum
    
    housesForA(p,n,s);
    return 0;
}