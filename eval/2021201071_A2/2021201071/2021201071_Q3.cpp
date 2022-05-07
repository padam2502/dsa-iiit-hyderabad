#include <stdio.h>
#include <iostream>
#define max 100005
using namespace std;
template <class P>
class Deque{
	int beg;
	int rear;
	P* arr;
	int capacity;
	int filled;
	public :
	Deque()
    {
    	arr=new P[max];
        beg=-1;
        rear=-1;
        capacity=max;
        filled=0;
    }
    Deque(int n, P x)
    {
    	filled=n;
    	arr=new P[100005];
        beg=0;
        rear=0;
        capacity=n;
        for(int i=0;i<n;i++)
        	{arr[i]=x;++rear;}
    }
    void push_back(P x)
    {
    	
    /*if (beg==(rear+1)%capacity)
    {
    	capacity=min(2*capacity,100005);
    }*/
    ++filled;
    if(beg==-1)
    {
        beg=0;
        rear=0;
    }
    else
        rear=(rear+1)%max;
    arr[rear]=x ;

	}
 	void pop_back()
 	{
 	if(empty())
    {
        cout<<"Underflow\n"<<endl ;
        return ;
    }
    else{
    --filled;
    if(beg==rear)
    {
        beg=-1;
        rear=-1;
    }
    else if(rear==0)
        rear=max-1;
    else
        rear=rear-1;
 	}

 	}
 	void push_front(P x)
 	{

 		/*if(beg==((rear+1)%capacity))
        {
        	cout<<"Overflow\n"<<endl;
        	return;
    	}*/
    	++filled;
    if(beg==-1)
    {
        beg=0;
        rear=0;
    }
    else if(beg==0)
        beg=max-1 ;
    else 
        beg=beg-1;
    arr[beg] = x ;

 	}
 
 	void pop_front()
 	{
 		if(empty())
    	{
        cout<<"Underflow\n"<<endl;
        return ;
    	}
    	else{
    	--filled;
    	if(filled==1)
    	{
        	beg=-1;
        	rear=-1;
    	}
    	else if(beg==max-1)
            beg=0;
        else
            beg=beg+1;
 	}
	  
 }
 	P front()
 	{
 		return arr[beg];
 	}
 	P back()
 	{
 		return arr[rear];
 	}
 	bool empty()
 	{
 		return (filled==0);
 	}
 	void resize(int x,P d)
 	{
		 int tp=filled;
 		if(x>filled){
 			
 			for(int i=0;i<x-tp;i++)
  			{
   				push_back(d);
   			}
			
 		}
 		else
 		{
 			for(int i=0;i<tp-x;++i)
  			{
   				pop_back();
   			}
 		}
 		/*if(x>capacity)
 		{
 			int newcapacity=min(2*x,100005);
 			P* newarr = new P[newcapacity];
 			for(int i=0;i<capacity;++i)
  			{
   				newarr[i]=arr[i];
   			}
   			capacity=x;
   			for(;i<x;i++)
   			{
   				newarr[i]=d;
   			}
   			delete[] arr;
   			arr=newarr;
   		}
   		else if(x<capacity)
   		{
   			int w=filled;
   			if(filled>x)
   			{
   				while(w>x)
   				{
   					w--;
   					pop_back();
   				}
   				capacity=x;
   			}
   			else
   			{
   				for(int i=w+1;i<=x;i++)
   				{
   					push_back(d);
   				}
   				capacity=x;
   			}*/
	 //cout<<endl<<beg<<" "<<rear<<" "<<filled<<endl;
   		}
 	int size()
 	{
 		return filled;
 	}
 	void clear()
 	{
 		beg=-1;
 		rear=-1;
 		filled=0;
 	}
 	P operator[](int n)
 	{
 		//if(!n)return -1;
 		int z=(n+beg)%(max);
 		return arr[z];
 	}
    
};
int main()
{
	Deque<int>deq ;
	for(int i=0;i<1000;i++){
	deq.push_back(i);
	cout<<deq.back()<<" ";
	}
	cout<<endl;
	for(int i=0;i<100;i++){
	deq.push_front(i*2);
	cout<<deq.front()<<" ";
	}
	cout<<endl;
	cout<<deq.size()<<endl;
	for(int i=0;i<deq.size();i++){
	cout<<deq[i]<<" ";
	}
	deq.clear();
	cout<<endl;
	cout<<deq.size()<<endl;
	cout<<deq.empty()<<endl;;
	deq.resize(10,4);
	cout<<deq.size()<<endl;
	cout<<deq.empty()<<endl;
	cout<<deq.size()<<endl;
	for(int i=0;i<deq.size();i++){
	cout<<deq[i]<<" ";
	}
	/*char ch='y';
	int choice=-1;
	Deque<int>deq ;
	int w;
	while(ch=='y' || ch=='Y')
	{
	cout<<"\nEnter 1 for initialize a blank deque\nEnter 2 for initialize a deque of length n with all values as x.\nEnter 3 for push_back(x)\nEnter 4 for pop_back()\nEnter 5 for push_front(x)\nEnter 6 for pop_front()\nEnter 7 for front()\nEnter 8 for back()\nEnter 9 for empty()\nEnter 10 for size()\nEnter 11 for resize(x,d)\nEnter 12 for clear()\nEnter 13 for D[n]\n";
	cin>>w;
	if(w==1)
	{
		
	}
	else if(w==2)
	{
		int n,x;
		cout<<"Enter n\n";
		cin>>n;
		cout<<"Enter x\n";
		cin>>x;
		Deque<int>deq(n,x) ;
	}
	else if(w==3)
	{
		int x;
		cout<<"Enter x\n";
		cin>>x;
		deq.push_back(x);
	}
	else if(w==4)
	{
		deq.pop_back();
	}
	else if(w==5)
	{
		int x;
		cout<<"Enter x\n";
		cin>>x;
		deq.push_front(x);
	}
	else if(w==6)
	{
		
		deq.pop_front();
	}
	else if(w==7)
	{
		
		cout<<deq.front()<<endl;
	}
	else if(w==8)
	{
		
		cout<<deq.back()<<endl;
	}
	else if(w==9)
	{
		
		if(deq.empty())
		cout<<"True\n";
		else
		cout<<"False\n";
	}
	else if(w==10)
	{
		
		cout<<deq.size()<<endl;
	}
	else if(w==11)
	{
		int n,x;
		cout<<"Enter n\n";
		cin>>n;
		cout<<"Enter x\n";
		cin>>x;
		deq.resize(n,x);
	}
	else if(w==12)
	{
		
		deq.clear();
	}
	else if(w==13)
	{
		int n;
		cout<<"Enter key\n";
		cin>>n;
		cout<<deq[n]<<endl;
	}
	else
		cout<<"Error\n";
	cout<<"Want to continue (y/n)\n";
	cin>>ch;
	}
	*/

	return 0;
}