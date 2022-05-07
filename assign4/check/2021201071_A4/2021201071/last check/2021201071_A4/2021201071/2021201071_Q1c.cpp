#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdio>
#include <fstream>
#include <ctime>
using namespace std;
#define TOTL 10000010                  
                          
long long int n;
long long int SA[TOTL];
long long int tempSA[TOTL];
long long int prevsuff[TOTL];
long long int tempLCP[TOTL];
long long int LCP[TOTL];                         
long long int Rankarr[TOTL];
long long int tempRankarr[TOTL]; 
long long int c[TOTL];
char T[TOTL];

void cntsort(long long int k)
{
    memset(c, 0, sizeof c);                                                 
    
    long long int sum=0;

    for(long long int i=0;i<n;i++)
    {
        if(i+k>n)
        {
            c[0]++;
        }
        else
        {
            c[Rankarr[i+k]]++;
            
        }
        
    }                  
    long long int maxi = max(300LL, n);

    for (long long int i=0;i<maxi;i++)
    {
        long long int t;
        t= c[i];
        c[i] = sum;
        sum += t;
    }
    for (long long int i=0;i<n;i++)
    {
        if(n>k+SA[i])
        {
            tempSA[c[Rankarr[k+SA[i]]]++]=SA[i];
        }
        else
        {
            tempSA[c[0]++]=SA[i];
        }
        
    } 
        
    for (long long int i=0;i<n;i++)
    {
        SA[i]=tempSA[i];
    } 
        
}
void makeSA()
{ 
    
    for(long long int i=0;i<n;i++)
    {
        SA[i] = i;
    }
    long long int  k;
    for(long long int i=0;i<n;i++)
    {
        Rankarr[i]=T[i];
    }
    long long int r=0;
    for(k=1;k<n;k <<= 1)
    {
                           
        cntsort(k); 
        r=0;       
        cntsort(0); 
        long long init=SA[0] ;      
        tempRankarr[init]=0;
        for(long long int i=1;i<n;i++)
        {
            long long prev=SA[i-1];
            long long cur=SA[i];
            if(Rankarr[prev] == Rankarr[cur] && Rankarr[prev + k] == Rankarr[cur + k])
            {
                tempRankarr[cur]=r;
            }
            else
            {
                r+=1;
                tempRankarr[cur]=r;
            }  
        }
            
        for(long long int i = 0;i<n;i++)
        {
            Rankarr[i] = tempRankarr[i];
        }
            
        long long last=SA[n-1];

        if(Rankarr[last]==n-1)
            break; 
    }
}
void computeLCP()
{
    prevsuff[SA[0]]=-1; 
    long long int L=0;           
    for(long long int i=1;i<n;i++)
    {
        prevsuff[SA[i]] = SA[i-1];
    }    
    for(long long int i= 0;i<n;i++)
    { 
        if(prevsuff[i]==-1)
        {
            tempLCP[i] = 0;
            continue;
        }
        long long psuf=prevsuff[i];
        while(T[i+L]==T[psuf+L])
        {
            L++;
        }
        tempLCP[i]=L;
        L = max(L-1, 0LL); 
    }
    long long int i = 0;
    while(i<n)  
    {
        LCP[i] = tempLCP[SA[i]]; 
        i++;
    }
}
int main()
{
    string s;
    cin >> s;
    long long ans = s.size();
    string ww=s;
    reverse(s.begin(),s.end());
    s =ww + "$"+s;
    for (long long int i = 0; i < s.size(); i++)
    {
        T[i] = s[i];
    }
    n = s.size();
    makeSA();
    computeLCP();
    long long anslength=0;
    long long Position=0;
    for(long long i=1;i<n;++i)
    {
        if((LCP[i]>anslength))
        {
            if((SA[i-1]<ans && SA[i]>ans)||(SA[i]<ans && SA[i-1]>ans))
            {
                anslength=LCP[i];
                Position=SA[i];
            }
        }
    }
    cout << s.substr(Position, anslength);
    cout<<endl;
    return 0;
}