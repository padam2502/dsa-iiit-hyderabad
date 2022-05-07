#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
vector<string>ans;
vector<string>pr;
class Trie
{
public:
        int mark;
        Trie* array[26];
        Trie()
        {
            mark=0;
        for(int i=0;i<26;i++)
        {
            array[i]=NULL;
        }
        }
};
void autocomplete(Trie* node,string s)
{
	int ff=0;
	if(node->mark)
	{
		ans.push_back(s);
	}
	for(int i=0;i<26;i++)
	{

        if(node->array[i])
            {
            	ff=1;break;
            }
	}
	if(ff)
	{
		 for(int i=0;i<26;i++)
    	{
        	if(node->array[i])
        	{
            
           		s.push_back('a'+i);
            	autocomplete(node->array[i],s);
            	s.pop_back();
        	}
    	}
	}
	else
		{return;}
}
int editDistance(string s1, string s2) {
        int m=s1.size();
        int n=s2.size();
        int dp[m+1][n+1];
        for(int i=0;i<=m;i++) {
            for(int j=0;j<=n;j++)  {
                if(i==0) 
                    dp[i][j]=j;
                else if(j==0) 
                    dp[i][j]=i;
                else if(s1[i-1]==s2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else 
                    dp[i][j] = 1+min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]));
            }
        }
        return dp[m][n];
    }

 void printTrie(Trie *node,string& prefix,string tp)
 {
 	if(node->mark)
 	{
 		if(editDistance(tp,prefix)<=3)
 	   	pr.push_back(prefix);
 	}

  for (char index=0;index<26;++index)
  {
    Trie * Child=node->array[index];
    char next='a'+index;
    if(Child)
    {
      prefix.push_back(next);
      printTrie(Child, prefix,tp);
      prefix.pop_back();
    }
  }
}
 
int main()
{
	long long n,x;
	Trie* root=new Trie();
	vector<string>v;
	cin>>n;
	string str,temp;
	while(n--)
	{
		cin>>str;
		v.push_back(str);
	}
	 for(int i=0;i<v.size();i++)
    {
        Trie* curr=root;
        for(int j=0;j<(v[i].size());j++)
        {
            if(!(curr->array[v[i][j]-'a'])) 
                curr->array[v[i][j]-'a']=new Trie();
            curr=curr->array[v[i][j]-'a'];
        }
        curr->mark=1;
    }
	cin>>x>>temp;
	if(x==1)
	{
		int f=0;
		Trie* cur=root;
		for(int i=0;i<temp.size();i++)
		{
			if(cur->array[temp[i]-'a'])
				cur=cur->array[temp[i]-'a'];
			else
				{
					cout<<"0\n";
					f=1;
					break;
				}
		}
		if(!f)
		{
		    
		
		if( cur->mark)
		{
			cout<<"1\n";
		}
		else
		{
			cout<<"0\n";
		}
		}
	}
	else if(x==2)
	{
		int cnt=0;
		int g=0;
		int f=0;
		Trie* cur=root;
		for(int i=0;i<temp.size();i++)
		{
			if(cur->array[temp[i]-'a'])
				cur=cur->array[temp[i]-'a'];
			else
				{
					cout<<"0\n";
					g=1;
					break;
				}
		}
		if(!g)
		{

		for(int i=0;i<26;i++)
        if (cur->array[i])
            {
            	f=1;
            	break;
            }
    	if(f)
    	{
    		autocomplete(cur,temp);
    		cout<<ans.size()<<endl;
    		sort(ans.begin(),ans.end());
    		for(int i=0;i<ans.size();i++)
    		{
    			cout<<ans[i]<<endl;
    		}
    	}
    	else
    	{
    		cout<<1<<endl<<temp;
    	}
		}
	}
	else if(x==3)
	{
		string st="";
		Trie* cur=root;
		printTrie(cur,st,temp);
		cout<<pr.size()<<endl;
    		sort(pr.begin(),pr.end());
    		for(int i=0;i<pr.size();i++)
    		{
    			cout<<pr[i]<<endl;
    		}
	}

	return 0;

}