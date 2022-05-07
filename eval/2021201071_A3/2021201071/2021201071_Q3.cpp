#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
using namespace std;
char array[500][500];
char *words[500];
char *sol[500];
int cnt=0;
string str="";
int directionx[4]={-1,0,1,0};
int directiony[4]={0,1,0,-1};
long long r,c,n;
class Trie
{
public:
        int mark;
        Trie* alphabet[26];
        Trie()
        {
            mark=0;
        for(int i=0;i<26;i++)
        {
            alphabet[i]=NULL;
        }
        }
};
void solve(int x, int y, Trie* root, string& str)
{
        if(!root->alphabet[array[x][y]-'a']) return;
        if(array[x][y]=='@') return;
        str.push_back(array[x][y]);
        
        char ch = array[x][y];
        array[x][y]='@';
        
        if(root->alphabet[ch-'a']->mark){
            sol[cnt] =  (char*) malloc(str.size()+1);
             strcpy(sol[cnt], str.c_str());
             cnt++;
           // sol.push_back(str);
            root->alphabet[ch-'a']->mark = 0;
        }
        
        for(int i=0;i<4;++i)
        {
            int x1 = directionx[i]+x;
            int y1 = directiony[i]+y;
            if(x1>=0 && x1<r && y1>=0 && y1<c && array[x1][y1]!='@') 
                solve(x1,y1,root->alphabet[ch-'a'],str);
        }
        str.pop_back();
        array[x][y]=ch;
        
        return;
    
}
int main()
{
    Trie* root=new Trie();

    cin>>r>>c;
    char ch;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>ch;
            array[i][j]=ch;
        }
    }
    int x;
    cin>>x;
    size_t malloc_size = 500;
    for(int w=0;w<x;w++)
    {
         string buffer;
         cin>>buffer;
       // if (fgets(buffer, 500, stdin) == NULL) {
    //     fprintf(stderr, "Error reading string into buffer.\n");}
    //     int slen = strlen(buffer);
    //     if (buffer[slen-1] == '\n') {
    //             buffer[slen-1] = '\0';}
     words[w] = (char*)malloc((buffer.size())+1);
      strcpy(words[w], buffer.c_str());
    }
    for(int i=0;i<x;i++)
    {
        Trie* curr=root;
        for(int j=0;j<strlen(words[i]);j++)
        {
            if(!(curr->alphabet[words[i][j]-'a'])) 
                curr->alphabet[words[i][j]-'a']=new Trie();
            curr=curr->alphabet[words[i][j]-'a'];
        }
        curr->mark=1;
    }
    
    

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            solve(i,j,root,str);
        }
    }
    char temp[500];
    for(int i=0;i<cnt-1;i++)
   {
     for(int j=i+1;j<cnt;j++)
     {
       if(strcmp(sol[i],sol[j])>0)
       {
         strcpy(temp,sol[i]); 
         strcpy(sol[i],sol[j]);
         strcpy(sol[j],temp);
       }
     }
   }

    for(int i=0;i<cnt;i++)
    {
        cout<<sol[i]<<" ";
    }
    return 0;

}