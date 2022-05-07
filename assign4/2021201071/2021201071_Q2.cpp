#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
class PriorityQueue
{
    public:
    vector<pair<long long int,long long int> > A;
    long long  ParentNode(long long int i)
    {
        return (i-1)/2;
    }
    long long Leftchild(long long int i)
    {
        return (2*i+1);
    }
    long long Rightchild(long long int i)
    {
        return (2*i+2);
    }
    void heapify_up(long long int i)
    {       
        if (i && A[ParentNode(i)].first>A[i].first)
        {        
            swap(A[i], A[ParentNode(i)]);
            heapify_up(ParentNode(i));
        }
    }
    void heapify_down(long long int i)
    {
        long long int left=Leftchild(i);
        long long int right=Rightchild(i);
        long long int smallest=i;
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
    long long int Size()
    {
        return A.size();
    }
    bool empty()
    {
        return Size() == 0;
    }
    void push(long long int key,long long int x)
    {
        A.push_back({key,x});
        long long int index = Size() - 1;
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
    pair<long long int,long long int> top()
    {  
            if (Size() != 0)
           return A.at(0);     
     } 
};
int main(int argc, char *argv[])
{
    //long long int arr[100005];
    long long int total=0;
    vector<long long int>v;
    long long int j,k=0,n,cnt=0;
    // FILE* fin = fopen(argv[1], "r");
    string filename;
    string line;
    fstream file;
    file.open(argv[1]);
    
    while(getline(file,line,',') )
    {
        long long int x=stoll(line);
        v.push_back(x);
        k++;
        total++;
    //   cout << line << '\n';
        if(k==100005)
        {
            k=0;
            
            sort(v.begin(),v.end());
            fstream outs;
            outs.open("./data/temp"+to_string(cnt)+".txt",ios::out);
            for(auto w:v)
            {
                outs << w <<",";
            }
            ++cnt;
            outs.close();
            v.clear();
        }
    }
    if(k!=0)
    {
        k=0;
        sort(v.begin(),v.end());
            fstream outs;
            outs.open("./data/temp"+to_string(cnt)+".txt",ios::out);
            for(auto w:v)
            {
                outs << w <<",";
            }
            ++cnt;
            outs.close();
            v.clear();
    }
    file.close();
    fstream sorts[cnt];
    fstream outputfile;
     PriorityQueue pq;
    for(long long i=0;i<cnt;i++)
    {
        sorts[i].open("./data/temp"+to_string(i)+".txt",ios::in);
        getline(sorts[i],line,',');
        long long x=stoll(line);
        pq.push(x,i);
    }
    outputfile.open(argv[2],ios::out);
    for(long long ww=0;ww<total;ww++)
    {
        pair<long long int,long long int>p;
        p=pq.top();
        if(ww!=total-1)
        outputfile<<p.first<<",";
        else
        outputfile<<p.first;
        long long int a=p.second;
        pq.pop();
        if(getline(sorts[a],line,','))
        {
        long long int x=stoll(line);
        pq.push(x,a);
        }
    }
    outputfile.close();
    for(long long int j=0;j<cnt;j++)
    {
        sorts[j].close();
        remove(("./data/temp"+to_string(j)+".txt").c_str());
    }
   // outs.open("temp"+to_string(cnt),ios::out);
    return 0;
}