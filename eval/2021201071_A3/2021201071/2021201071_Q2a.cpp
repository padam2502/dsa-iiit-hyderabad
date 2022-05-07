#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
vector<int>parent[100005];
    vector<pair<int,int> >v[100005];
   long long cn=0;
    vector<bool>processed;
    
class PriorityQueue
{
    public:
    vector<pair<int,int> > A;
    int ParentNode(int i)
    {
        return (i-1)/2;
    }
    int Leftchild(int i)
    {
        return (2*i+1);
    }
    int Rightchild(int i)
    {
        return (2*i+2);
    }
    void heapify_up(int i)
    {       
        if (i && A[ParentNode(i)].first>A[i].first)
        {        
            swap(A[i], A[ParentNode(i)]);
            heapify_up(ParentNode(i));
        }
    }
    void heapify_down(int i)
    {
        int left,right,smallest;
         left=Leftchild(i);
         right=Rightchild(i);
         smallest=i;
        if (left<Size() && A[left].first<A[i].first)
        {
            smallest=left;
        }
 
        if (right<Size() && A[right].first<A[smallest].first) {
            smallest=right;
        }
        if (smallest!=i)
        {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
    }
    unsigned int Size()
    {
        return A.size();
    }
    bool empty()
    {
        return Size() == 0;
    }
    void push(int key,int x)
    {
        A.push_back({key,x});
        int index = Size() - 1;
        heapify_up(index);
    }
    void pop()
    { 
            if(Size() != 0)
           {
            A[0]=A.back();
            A.pop_back();
            heapify_down(0);
        }  
    }
    pair<int,int> top()
    {  
            //if (Size() != 0)
           return A.at(0);     
     } 
};
// void printPath(int parent[], int j)
// {
       
//     // Base Case : If j is source
//     if (parent[j] == - 1)
//         return;
   
//     printPath(parent, parent[j]);
   
//     printf("%d ", j);
// }
// int printSolution(int dist[],int n,int parent[])
// {
//     int src = 0;
//     printf("Vertex\t Distance\tPath");
//     for (int i = 1; i < V; i++)
//     {
//         printf("\n%d -> %d \t\t %d\t\t%d ",
//                       src, i, dist[i], src);
//         printPath(parent, i);
//     }
// }
// void printing(int x,string &str)
// {
//     if(parent[x].size()==0)
//         {
//             // paths[str.back].push_back(str);
//             return;
//         }
//     for(auto w: parent[x])
//     {
//         str=str+" "+to_string(w);
//         paths[w].push_back(str);
//         cn++;
//         printing(w,str);
//         int l=str.size()-1;
//         for(;l>=0;--l)
//         {
//             if(str[l]==' '){str.pop_back();break;}
//             else
//                 str.pop_back();
//         }
        
//     }
// }
string reverse_string(string s)
{
    int j=0;
     reverse(s.begin(), s.end());
    s.insert(s.end(), ' ');
    for(int i=0;i<s.size();i++)
    {
         if(s[i]==' ')
         {
            reverse(s.begin()+j,s.begin()+i);
            j=i+1;
        }
 
    }
    s.pop_back();
    return s;
}
int main()
{
    PriorityQueue pq;
     vector<int>distance;
     
    long long n,m,a,b,c,dest;
    cin>>n>>m;
    vector<string>paths(n,"");
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        v[a].push_back({b,c});
        v[b].push_back({a,c});
    }
    
    cin>>dest;
    for(int i=0;i<n;i++)
        {
            distance.push_back(500000);
            processed.push_back(false);
            //parent[i]=-1;
        }
    distance[dest]=0;
    pq.push(0,dest);
    paths[dest]=to_string(dest);
//  pq.push(3);
//     pq.push(2);
//     pq.push(15);
 
   // cout << "Size is " << pq.Size() << endl;
    while (pq.Size() !=0) {
        pair<int,int>p;
        p=pq.top();
    int a = p.second;
     pq.pop();
    if(processed[a]) continue;
    processed[a] = true;
    for (auto u : v[a])
     {
    int b = u.first, w = u.second;
    if (distance[a]+w==distance[b])
     {
       //distance[b] = distance[a]+w;
       string temp=paths[a]+" "+to_string(b);
       if(paths[b]=="")
       {
           paths[b]=temp;
       }
       else
       {
           string s1,s2;
           s1=temp;
           s2=paths[b];
            s1=reverse_string(s1);
            s2=reverse_string(s2);
           if(s1<s2)
           {
               paths[b]=temp;
           }

       }
      // pq.push(distance[b],b);
    //    parent[a].clear();
    //    parent[a].push_back(b);
    // cout << "Size is " << pq.size() << endl;
    }
    else if (distance[a]+w<distance[b])
     {
         distance[b] = distance[a]+w;
       string temp=paths[a]+" "+to_string(b);
       paths[b].clear();
        paths[b]=temp;
       pq.push(distance[b],b);
      // parent[a].push_back(b);
    // cout << "Size is " << pq.size() << endl;
    }
    }
}
// string str;
// str=to_string(dest);
// printing(dest,str);
for(int i=0;i<n;i++)
{
    if(i!=dest){

    string temp=reverse_string(paths[i]);
    cout<<temp<<endl;}
}
return 0;
}