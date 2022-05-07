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
vector<long long>answ;
long long int ww=0;                       
long long int n;
long long int SA[TOTL];
long long int tempSA[TOTL];                        
long long int Rankarr[TOTL];
long long int tempRankarr[TOTL]; 
long long int c[TOTL];
char T[TOTL];

void cntsort(long long int k)
{
    memset(c, 0, sizeof c);                                                 
    
    long long int sum;

    for(long long int i=0;i<n;i++)
    {
        // if(i+k>n)
        // {
        //     c[0]++;
        // }
        // else
        // {
        //     c[Rankarr[i+k]]++;
            
        // }
        c[i + k < n ? Rankarr[i + k] : 0]++;
        
    }                  
    long long int maxi = max(300LL, n);

    for (long long int i=sum=0;i<maxi;i++)
    {
        long long int t;
        t= c[i];
        c[i] = sum;
        sum += t;
    }
    for (long long int i=0;i<n;i++)
    {
        // if(n>k+SA[i])
        // {
        //     tempSA[c[Rankarr[k+SA[i]]]++]=SA[i];
        // }
        // else
        // {
        //     tempSA[c[0]++]=SA[i];
        // }
        tempSA[c[SA[i]+k < n ? Rankarr[SA[i]+k] : 0]++] = SA[i];
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
      //k;
    for(long long int i=0;i<n;i++)
    {
        Rankarr[i]=T[i];
    }
    long long int r=0;
    for(long long int k=1;k<n;k <<= 1)
    {
                          
        cntsort(k); 
        //r=0;       
        cntsort(0); 
        long long init=SA[0] ;      
        tempRankarr[init]=r=0; 
        
        for(long long int i=1;i<n;i++)
        {
            // long long prev=SA[i-1];
            // long long cur=SA[i];
            // if(Rankarr[cur] == Rankarr[prev] && Rankarr[cur + k] == Rankarr[prev + k])
            // {
            //     tempRankarr[cur]=r;
            // }
            // else
            // {
            //     r+=1;
            //     tempRankarr[cur]=r;
            // }  
            tempRankarr[SA[i]] = // if same pair => same rank r; otherwise, increase r
(Rankarr[SA[i]] == Rankarr[SA[i-1]] && Rankarr[SA[i]+k] == Rankarr[SA[i-1]+k]) ? r : ++r;
        }
            
        for(long long int i = 0;i<n;i++)
        {
            Rankarr[i] = tempRankarr[i];
        }
            
        long long last=SA[n-1];

        if(Rankarr[SA[n-1]]==n-1)
            break; 
    }
}
vector<long long> computeLCP(string x)
{
    
    vector<long long> invSuff(n, 0);
    long long k=0;
    vector<long long> lcp(n, 0);
    
    for (long long i=0; i<n;i++)
    {
        invSuff[SA[i]] = i;
    }
        
    for(long long i=0;i<n;i++)
    {
        if(invSuff[i]==n-1)
        {
            k=0;
            continue;
        }
        // long long j = SA[invSuff[i]+ww-1];
        long long j = invSuff[i]+1;

        while(i+k<n && SA[j]+k<n && x[i+k]==x[SA[j]+k])
        {
             k++;
        }
           
        
        lcp[invSuff[i]] = k;

        if(k<=0)
        {
            
        }
        else
        {
            k--;
        }
            
        
    }
    return lcp;
}
long long fun(long long a,long long b)
{
    // cout<<"a"<<lcps[a-1]<<" ";
    long long tans=answ[a-1];
    for(long long i=a;i<b;i++)
    {
       // cout<<" "<<i<<lcps[i]<<" ";
            tans=min(answ[i],tans);
    }
    // if(tans!=1000005)
    return tans;
    // else return -1;
}
int main()
{
    cin>>ww;
    long long t;
    cin>>t;
    t=0;
    string s;
    cin >> s;
    long long ans = s.size();
    
    for (long long int i = 0; i < s.size(); i++)
    {
        T[i] = s[i];
        // if(i)
        // {
        //     if(T[i]==T[i-1])t++;
        // }
        
    }
    
    n = s.size();
    // if(ww==1)
    // {
    //     cout<<n;
    //     return 0;
    // }
    if(ww>n)
    {
        cout<<-1;
        return 0;
    }
    makeSA();
    
    string sol="";
    answ= computeLCP(s);
    for(long long i=0;i<n;i++)
    {
        cout<<SA[i]<<" ";
    }
    cout<<endl;
    for(auto u:answ)
    {
        cout<<u<<" ";
    }
    long long solu=-1;
    for(long long j=0;j<n-ww+1;j++)
    {
        solu=max(solu,fun(j+1,j+ww-1));
    }
    
    cout<<solu;


    return 0;
}