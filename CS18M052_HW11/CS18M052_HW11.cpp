#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        string s,s1;
        cin>>s1>>s;
        
        int lettersLength = 0;
        for(int i=0;i<s1.length();i++){  //count number of letters[A-Z] in string s1
            if(s1[i]!='?')
                lettersLength++;
        }
        char letters[lettersLength];
        lettersLength =0;
        for(int i=0;i<s1.length();i++){  //store only letters[A-Z] of string s1 into char array letters
            if(s1[i]!='?')
                letters[lettersLength++] = s1[i];
        }
        
        int symbolLength = lettersLength+1,k=0;
        int symbol[symbolLength];    //sympol array keeps track of whether the given letter has question mark before it, if letter[i] has question mark before it in string s1 then symbol[i]=1 otherwise symbol[i]=0        
        for(int i=0;i<s1.length();i++){
            if(s1[i]!='?'){
                if(i>0 && s1[i-1]=='?')
                    symbol[k++] = 1;
                else
                    symbol[k++] = 0;
            }   
        }
        int j,flag;
        for(int i=0;i<s.length();){  //for each index i in string s calculate value of pi
            j=i,k=0,flag=i;
            while(1){
                if(lettersLength==0){  //if there is no letters in string s1 then pi value will be its index 
                    cout<<i+1<<" ";
                    i++;
                    break;
                }
                if(lettersLength-k >= s.length()-j && s[j]!=letters[k]){//if s and s1 both have same number of letters and first letter doesn't match then s doesn't contain s1, print -1
                    for(int z=i;z<s.length();z++)
                        cout<<-1<<" ";
                    i = s.length();
                    break;
                }
                if( j>=s.length() && k<lettersLength){//if we reach at the end of string s and s1 still have lettres remaing to match then s doesn't contain s1, print -1
                    for(int z=i;z<s.length();z++)
                        cout<<-1<<" ";
                    i = s.length();
                    break;
                }
                if(k>=lettersLength){ //if s1 found in s then print end of index(pi) 
                    for(int z=i;z<=flag;z++)
                        cout<<j<<" ";
                    i = flag+1;
                    break;
                }
                if(s[j]==letters[k]){//if letter match then increment index in both s and s1
                    if(k==0)
                        flag = j;
                    k++;
                    j++;
                }
                else if(s[j]!=letters[k]){ //if letter doesn't match
                    if(symbol[k]==1)  //and s1 have '?' before current letter then increment index in s1
                        j++;
                    else{         //othewise restart finding string s1 
                        if(k!=0)
                            k=0;
                        else
                            j++;    
                    }
                }
            } 
        }
        cout<<endl;
    }
    return 0;
}     