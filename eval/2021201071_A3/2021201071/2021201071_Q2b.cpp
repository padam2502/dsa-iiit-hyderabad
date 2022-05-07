#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
vector<bool>visited;
vector<pair<int,int> >v[100005];
string paths;
vector<pair<int,string>>ans;
vector<string>combo;
    long long n,m,a,b,c,dest;
bool sortbysec(const pair<int,string> &a, const pair<int,string> &b) {
if(a.first==b.first)
return a.second<b.second;
return a.first < b.first;
}
void DFS(int s,int d)
{
    paths.push_back('0'+s);
    visited[s]=true;

    if(s==d)
    {
        string temp="";
      for(int i=0;i<paths.size();i++)
       { temp.push_back(paths[i]);temp+=" ";}
       temp.pop_back();
    combo.push_back(temp);
    temp="";

    }
    else
    {
         for(auto u:v[s])
        {
            if(visited[u.first]==false)
                DFS(u.first,d);
        }
    }
    paths.pop_back();
    visited[s]=false;
}
int main()
{
    vector<int>distance;
    cin>>n>>m;
    int adjmatrix[n][m]={0};
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        v[a].push_back({b,c});
        v[b].push_back({a,c});
        adjmatrix[a][b]=c;
        adjmatrix[b][a]=c;
    }
    
    int w;
    cin>>w;
    for(int i=0;i<n-1;i++)
    {

        for(int j=i+1;j<n;j++)
        {
            int s=i;
            int d=j;
            visited.clear();
            for(int l=0;l<n;l++)
            {
                visited.push_back(false);
            }
            DFS(s,d);
        }
    }
    for(int i=0;i<combo.size();i++)
    {
        int sum=0;
        //string xy=combo[i];
        for(int j=0;j<combo[i].size()-2;j+=2)
        {
            sum+=adjmatrix[combo[i][j]-'0'][combo[i][j+2]-'0'];
        }
        ans.push_back({sum,combo[i]});
       // combo[i]=to_string(sum)+" "+combo[i];
    }
    sort(ans.begin(),ans.end(),sortbysec);
    w=min(w,(int)ans.size());
    for(int i=0;i<w;i++)
    {
        // for(int j=0;j<combo[i].size();j++)
        {
            cout<<ans[i].second<<endl;
            //cout<<combo[i].substr(2,combo[i].size()-2)<<endl;
        }
    }
    return 0;
}
