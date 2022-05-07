#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;
class node
{
public:
    int column;
    int row;
    int distance;
    node(int a,int b,int c)
    {
        row=a;
        column=b;
        distance=c;
    }
};

int main()
{
    node obj(1,0,0);
    queue<node>q;
    q.push(obj);
    long long n,m;
    int p,s;
    cin>>n>>m;
    char matrix[n][m];
    int sq[n][m];

    bool processed[n][m];
    vector<pair<int,int> >r;
    for(int i=0;i<n;i++) 
    {
        for(int j=0;j<m;j++)
        {
            char ch;
            cin>>ch;
            matrix[i][j]=ch;
            sq[i][j]=500000;
            if (matrix[i][j]!='#')
                processed[i][j]=false;
            else
                processed[i][j]=true;
            if(ch=='R')
                r.push_back({i,j});
             if(ch=='A')
             {
                p=i;s=j;
             }
        }
    }
    sq[1][0]=0;
    while(!q.empty())
    {
        node temp=q.front();
        q.pop();
        if( (!processed[temp.row-1][temp.column]) && temp.row>0)
        {
            processed[temp.row-1][temp.column]=true;
            sq[temp.row-1][temp.column]=temp.distance+1;
            q.push(node(temp.row-1,temp.column,temp.distance+1));
            
        }
        if((!processed[temp.row][temp.column-1]) && temp.column>0)
        {
            processed[temp.row][temp.column-1]=true;
            sq[temp.row][temp.column-1]=temp.distance+1;
            q.push(node(temp.row,temp.column-1,temp.distance+1));
            
        }
        if((!processed[temp.row+1][temp.column]) && temp.row<n-1)
        {
            processed[temp.row+1][temp.column]=true;
            sq[temp.row+1][temp.column]=temp.distance+1;
            q.push(node(temp.row+1,temp.column,temp.distance+1));
            
        }
        if((!processed[temp.row][temp.column+1]) && temp.column<n-1)
        {
            processed[temp.row][temp.column+1]=true;
            sq[temp.row][temp.column+1]=temp.distance+1;
            q.push(node(temp.row,temp.column+1,temp.distance+1));
            
        }
    }
    int f=0;
    for(int i=0;i<r.size();i++)
    {
        if(sq[r[i].first][r[i].second]<sq[p][s])
        {
            cout<<"NO\n";f=1;break;
        }
    }
    if(!f)
    {
        cout<<"YES\n";
        cout<<sq[p][s]<<endl;
    }
    return 0;
}
