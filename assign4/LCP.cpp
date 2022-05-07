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
#include<climits>
#include<vector>
using namespace std;
long long ww;
long long lcps[1000005];
struct suffix
{
    int f, s, i;
    suffix() {}
    suffix(int f, int s, int i) : f(f), s(s), i(i) {}
    operator int()
    {
        return i;
    }
};

vector<int> suffix_array(string s)
{
    string t = s+"$";
    int n = t.size();
    vector<suffix> sa(n);
    vector<pair<int, int>> rs(n);
    for (int i = 0; i < n; i++)
        sa[i] = suffix(t[i] - 'a', t[i + 1] - 'a', i);
    for (int i = 1; i <= int(log2(n) + 1); i++)
    {
        sort(sa.begin(), sa.end(), [](auto a, auto b)
             { return a.f == b.f ? a.s < b.s : a.f < b.f; });
        for (int j = 0, rank = 0; j < n; j++)
        {
            if (j != 0)
                rank += (sa[j - 1].f != sa[j].f || sa[j - 1].s != sa[j].s);
            rs[sa[j].i] = make_pair(j, rank);
        }
        for (int j = 0, of = 1 << i; j < n; j++)
        {
            int k = sa[j].i;
            sa[j].f = rs[k].second;
            sa[j].s = k + of < n ? rs[k + of].second : rs[n - 1].second;
        }
    }
    vector<int> res(sa.begin() + 1, sa.end());
    return res;
}

vector<int> lcp_array(vector<int> &sa, string &s)
{
    int n = sa.size();
    vector<int> rs(n), lcp(n);
    for (int i = 0; i < n; i++)
        rs[sa[i]] = i;
    for (int i = 0, h = 0; i < n; i++)
    {
        if (rs[i] > 0)
        {
            int k = sa[rs[i] - 1];
            while (i + h < n && k + h < n && s[i + h] == s[k + h])
            {
                h++;
            }
            lcp[rs[i]] = h;
            if (h > 0)
                h -= 1;
        }
    }
    return lcp;
}
long long fun(long long a,long long b)
{
    //cout<<"a"<<lcps[a-1]<<" ";
    long long tans=1000005;
    for(long long i=a;i<b;i++)
    {
       // cout<<" "<<i<<lcps[i]<<" ";
            tans=min(lcps[i],tans);
    }
    return tans;
}
int main()
{
    cin>>ww;
    long long t;
    cin>>t;
    string s;
    cin >> s;
    long long ans = s.size();
    long long n=s.size();
    vector<int> sa = suffix_array(s);
    vector<int> lcp = lcp_array(sa, s);
    long long i=0;
    for(;i<n;i++)
    {
        //cout<<sa[i]<<endl;
        lcps[i]=lcp[i+1];

        //cout<<lcps[i]<<" ";
    }
    //lcps[i]=lcp[0];
    //cout<<lcps[i]<<endl;
    string sol="";
    long long solu=-1;
    for(long long j=0;j<n-ww+1;j++)
    {
        solu=max(solu,fun(j+1,j+ww-1));
    }
    
    cout<<solu;

    return 0;
}
/*
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
        long long init=SA[0] ;      
        tempRankarr[init]=0;                   
        cntsort(k); 
        r=0;       
        cntsort(0); 
        
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
        long long j = invSuff[i]+ww-1;

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
int main()
{
    
    string s;
    cin >> s;
    long long ans = s.size();
    
    for (long long int i = 0; i < s.size(); i++)
    {
        T[i] = s[i];
    }
    n = s.size();
    makeSA();
    cin>>ww;
    string sol="";
    vector<long long>answ= computeLCP(s);
    long long solu=0;
    for(auto u:answ)
    {
        solu=max(solu,u);
    }
    if(!solu)
    {
        cout<<-1<<endl;
    }
    else
    cout<<solu<<endl;

    return 0;
}
*/