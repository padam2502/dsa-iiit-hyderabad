#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
template <class P, class Q>
class unorderMap{
public:
	class data{
	public:
	P key;
	Q value;
	data* next;
	data()
    {
        key=0;
        value=0;
        next=NULL;
    }

};
data* obj[100005];

unsigned long long Hash(P key)
{
	ostringstream os;
  	os << key;
  	string st=os.str();
  	unsigned long long ans=0;
  	for(long long i=0;i<st.size();i++)
  	{
  		ans=(st[i]+(ans << 6)+(ans << 16)-ans);
  	}
  	return (ans%100005);
}
data* createnode(P key,Q value)
{
	data *newnode=(data*)malloc(sizeof(data));
    	newnode->key=key;
    	newnode->value=value;
    	newnode->next=NULL;
    	return newnode;
}
void insert(P key, Q value)
{
	int index=Hash(key);
	if(obj[index]==NULL)
	{
		obj[index]=createnode(key,value);
	}
	else
	{
		data* temp=obj[index];
		while(temp->next!=NULL)
		{
			if(temp->key==key){temp->value=value;return;}
			temp=temp->next;
		}
		if(temp->key==key){temp->value=value;return;}
		temp->next=createnode(key,value);
	}
}
void erase(P key)
{

	int index=Hash(key);
	if(obj[index]==NULL)
	{
	   // cout<<"Not Found\n";
		return;
	}
	else
	{
		data* temp=obj[index];
		if(temp->key==key)
		{
    		obj[index]=obj[index]->next;
    		free(temp);
    		cout<<"deleted\n";
    		return;
		}
		else
		{
			while(temp->next!=NULL)
			{
				if((temp->next)->key==key){
					data *del=temp->next;
    				temp->next=del->next;
    				free(del);
    				break;
    				return;
    			}
				temp=temp->next;
			}
		}
	}
}
bool find(P key)
{
	int index=Hash(key);
	if(obj[index]==NULL)return false;
	data* temp=obj[index];
	while(temp!=NULL)
			{
				if(temp->key==key){
    				return true;
    			}
				temp=temp->next;
			}
	return false;
}
Q operator[](P key)
{
	int index=Hash(key);
    if(obj[index]==NULL)
    {		
    	//	cout<<"Not Present\n";
    		return 0;
    }
    else
    {
    	data *temp=obj[index];
    	while(temp!=NULL)
    	{
    		if(temp->key==key)
    		{
    			//	cout<<"FOUND\n";
    				return temp->value;
    		}
    			temp=temp->next;
    	}
   	}
   	return 0;
  }
};
int main()
{
	// unorderMap <int,int>map;
	int w=-1;
	// int n=0;
    // int res=0;
    // int k=0;
    // cout<<"Enter size of array\n";
    // cin>>n;
    // int arr[100005];
    // for(int i=0;i<n;i++)
    // {
    // 	cin>>arr[i];
    // }
    // cout<<"Enter value of k\n";
    // cin>>k;
    // for(int i=0;i<k;i++)
    // {
    //     if(!map.find(arr[i])) {
    //         res++;
    //     }
    //     map.insert(arr[i],map[arr[i]]+1);
    // }
    // cout<<res<<endl;
    // for(int i=k;i<n;i++)
    // {
    //     if(map[arr[i-k]]==1) {
    //         res--;
    //     }
    //     map.insert(arr[i-k],map[arr[i-k]]-1);
    //     if(map[arr[i]]==0) {
    //         res++;
    //     }
    //     map.insert(arr[i],map[arr[i]]+1);
    //     cout<<res<<endl;
    // }
	unorderMap <string,int>map;
	char ch='y';
	int choice=-1;
	//cout<<"\nEnter 1 for string\n2 for other\n";
	//cin>>choice;
	// if(choice==1)
	// {
	while(ch=='y' || ch=='Y')
	{
	cout<<"\nEnter 1 for insert\nEnter 2 for erase\nEnter 3 for find\nEnter 4 for map[key]\n";
	cin>>w;
	if(w==1)
	{
		string  x;
		int y;
		cout<<"Enter key and Value\n";
		cin>>x>>y;
		map.insert(x,y);
	}
	else if(w==2)
	{
		string x;
		cout<<"Enter key to be erase\n";
		cin>>x;
		map.erase(x);
	}
	else if(w==3)
	{
		string x;
		cout<<"Enter key to be find\n";
		cin>>x;
		if(map.find(x))cout<<"FOUND\n";
		else
			cout<<"Not Found\n";
	}
	else if(w==4)
	{
		string x;
		cout<<"Enter key for map[key]\n";
		cin>>x;
		cout<<map[x]<<endl;
	}
	else
		cout<<"Error\n";
	cout<<"Want to continue (y/n)\n";
	cin>>ch;
	    
	}
	/*unorderMap <int,int>map;
	char ch='y';
	int choice=-1;
	//cout<<"\nEnter 1 for string\n2 for other\n";
	//cin>>choice;
	//if(choice==1)
	//{
	while(ch=='y' || ch=='Y')
	{
	cout<<"\nEnter 1 for insert\nEnter 2 for erase\nEnter 3 for find\nEnter 4 for map[key]\n";
	cin>>w;
	if(w==1)
	{
		int  x;
		int y;
		cout<<"Enter key and Value\n";
		cin>>x>>y;
		map.insert(x,y);
	}
	else if(w==2)
	{
		int x;
		cout<<"Enter key to be erase\n";
		cin>>x;
		map.erase(x);
	}
	else if(w==3)
	{
		int x;
		cout<<"Enter key to be find\n";
		cin>>x;
		if(map.find(x))cout<<"FOUND\n";
		else
			cout<<"Not Found\n";
	}
	else if(w==4)
	{
		int x;
		cout<<"Enter key for map[key]\n";
		cin>>x;
		cout<<map[x]<<endl;
	}
	else
		cout<<"Error\n";
	cout<<"Want to continue (y/n)\n";
	cin>>ch;
	    
	}*/
	return 	0;

}