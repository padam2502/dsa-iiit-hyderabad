#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;
template <class P>

    class node{
        public:
	P key;
	int count;
	node* left;
	node* right;
	int height;	
		node()
		{}
	node(P n ,int x,node* l =NULL,node* r=NULL,int h=1)
	{key=n;count=x;left=l ;right=r;height=1;}
};
template <class P>
class comparator_class {
public:

    int operator ()(P o1, P o2)
    {
        if(o1==o2)return 0;
        else if(o1>o2)
        {
        	return 1;
        }
        return -1;
    }
};

template <class P>
class AVL{
    public:
    
// struct node{
// 	P key;
// 	int count;
// 	node* left;
// 	node* right;
// 	int height;	
// 	node(P n ,int x,node* l =NULL,node* r=NULL,int h=1):key(n),count(x),left(l) , right(r),height(1) {}
// };

void print( node<P>* root)
{
    if (root!=NULL) {
        cout<<root->key<<"-"<<root->count<<" ";
        print(root->left);
        print(root->right);
    }
}
int height( node<P>* root)
{
    if(!root)
        return 0;
    return root->height;
}
 node<P>* LR( node<P>* x)
{
     node<P>* y=x->right;
     node<P>* ch=y->left;
    y->left=x;
    x->right=ch;
    x->height=((height(x->left))>(height(x->right)))?(height(x->left))+1:(height(x->right))+1;
    y->height=((height(y->left))>(height(y->right)))?(height(y->left))+1:(height(y->right))+1;
    return y;
}
 node<P>* RR(node<P>* y)
{
     node<P>* x=y->left;
     node<P>* ch=x->right;
    x->right=y;
    y->left=ch;
    y->height=((height(y->left))>(height(y->right)))?(height(y->left))+1:(height(y->right))+1;
    x->height=((height(x->left))>(height(x->right)))?(height(x->left))+1:(height(x->right))+1;
    return x;
}
 node<P>* insert(node<P>* root,P key,comparator_class<P> cmp)
{
	/*struct node* newnode=new node;
	newnode->key=data;
	newnode->height=1;
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->count=1;*/
	if(root==NULL)
	{
	      node<P>* newnode = new node<P>();//(struct node*)malloc(sizeof(struct node));
    newnode->key=key;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->height=1;
    newnode->count=1;
		return newnode;
	}
	if(cmp(root->key,key)==0)
	{
		root->count+=1;
		return root;
	}
	if(cmp(root->key,key)==1)
		{
			root->left=insert(root->left,key,cmp);
		}
	else
		{
			root->right=insert(root->right,key,cmp);
		}
	root->height=((height(root->left))>(height(root->right)))?(height(root->left))+1:(height(root->right))+1;
	int bf=0;
	if(root)
	 bf= (height(root->left))-(height(root->right));

	if(bf<-1)
	{
		if(cmp(key,(root->right->key))==-1)
			{
				root->right=RR(root->right);
        		return LR(root);
			}
			else
			{
				return LR(root);
			}
	}
	if(bf>1)
	{
		if(cmp(key,(root->right->key))==1)
			{
				root->left=LR(root->left);
        		return RR(root);
			}
			else
			{
				return RR(root);
			}
	}
	return root;
}
 node<P>* deletion( node<P>* root, P key,comparator_class<P> cmp)
{
    if (root==NULL)
        return root;
    if (cmp(key,(root->key))==-1)
        root->left=deletion(root->left,key,cmp);
    else if (cmp(key,(root->key))==1)
        root->right = deletion(root->right, key,cmp);
    else {
        if(root->count>1) {
            (root->count)-=1;
            return root;
        }
        if((root->left==NULL)||(root->right==NULL)) {
            
            if(!(root->left) && !(root->right))
            {
            	 node<P>* temp = NULL;
            	temp=root;
                root=NULL;
                
            	delete temp;
            }
            else
            {
            	 node<P>* temp = NULL;
            	if(root->left)
            	{
            	temp=root->left;
            	}
            	else
            	{temp=root->right;}

            	*root = *temp; 
            	delete temp;
        	}
        }
        	else 
        	{
        		 node<P>* temp=root->right;
    			while (temp->left!=NULL)
        		temp=temp->left;
            	root->key=temp->key;
            	root->count=temp->count;
            	temp->count=1;
            	root->right=deletion(root->right,temp->key,cmp);
        	}
    	}
    	if(root == NULL)
        return root;
    	root->height=((height(root->left))>(height(root->right)))?(height(root->left))+1:(height(root->right))+1;
    	int bf=0;
    	if(root)
    	 bf= (height(root->left))-(height(root->right));
    	
    	
		if(bf<-1)
		{
		    int res=0;
			if(root->right)
			{
				int x1=height((root->right)->left);
				int x2=height((root->right)->right);
				 res=x1-x2;
			}
		
			
			if(res>0)
			{
				root->right=RR(root->right);
        		return LR(root);
			}
			else
			{
				return LR(root);
			}
		}
		if(bf>1)
		{
		    int res=0;
			if(root->left)
			{
				int x1=height((root->left)->left);
				int x2=height((root->left)->right);
				 res=x1-x2;
			}
			
			if(res<0)
			{
				root->left=LR(root->left);
        		return RR(root);
			}
			else
			{
				return RR(root);
			}
		}
    	return root;
}
 node<P>* search( node<P>* root,P key,comparator_class<P> cmp) 
 {
     if(!root)return root;
    if(root!=NULL)
 	{  
 		if(cmp(key,(root->key))==0) 
       {
       //	cout<<"Element Found \n";
          return root;
       }
    	else if(cmp(root->key,key)==-1 )
       { 
          return search(root->right,key,cmp); 
       }
       else 
       return search(root->left,key,cmp);
	}
	return root;
} 
  node<P>* occurence( node<P>* root,P key,comparator_class<P> cmp)
 {
 	return (search(root,key,cmp));
 }
 node<P>* lowerbound( node<P>* root,P key,node<P>* p,comparator_class<P> cmp)
 {
//  	static double ans=INT_MAX;
 	if(!root)return p;
 	else if(cmp(root->key,key)>=0)
 	{
 	    p=root;
//  		ans=min(root->key,ans);
 		return lowerbound(root->left,key,p,cmp);
 	}
 	else
 	{
 		return lowerbound(root->right,key,p,cmp);
 	}
 }
  node<P>* upperbound( node<P>* root,P key,node<P>* p,comparator_class<P> cmp)
 {
//  	static double ans=INT_MAX;
 	if(!root)return p;
 	else if(cmp(root->key,key)>0)
 	{
 	    p=root;
//  		ans=min(root->key,ans);
 		return upperbound(root->left,key,p,cmp);
 	}
 	else
 	{
 		return upperbound(root->right,key,p,cmp);
 	}
 }
 
//    node<P>* getClosest( node<P>* root1, node<P>* root2,P key) {
//     if(abs(key-root1->key)<abs(key-root2->key)) {
//       return root1;
//     } 
//     else 
//       return root2;
//     }
//   node<P>* findClosest( node<P>* root, P key,comparator_class<P>cmp) {
//     if ((cmp(key,root->key)==-1) && root->left!=NULL) {
//        node<P>* closestL=findClosest(root->left,key,cmp);
//       return getClosest(root,closestL,key);
//     } 
//     else if((cmp(key,root->key)==1) && root->right!=NULL){
//        node<P>* closestR=findClosest(root->right,key,cmp);
//       return getClosest(root,closestR,key);
//     }
//     else {
//       return root;
//     }
//   }

 node<P>* kthLargest( node<P>* root,int &k)
{
    if (root==NULL)
        return root;
     node<P>*rc=kthLargest(root->right,k);
    if(rc)return rc;
    k=k-(root->count);
    if(k<=0)
    {
        return root;
    }
    
    return kthLargest(root->left,k);
}
int getrange(node<P> *root,P begin,P end,comparator_class<P> cmp)
{
    if(!root)
    	return 0;
    if((cmp(root->key,end)==0) && (cmp(root->key,begin)==0))
        return root->count;
    if((cmp(root->key,end)<=0) && (cmp(root->key,begin)>=0))
         return root->count + getrange(root->left,begin,end,cmp)+getrange(root->right,begin,end,cmp);
    else if((cmp(root->key,begin))==-1)
         return getrange(root->right,begin,end,cmp);
	else 
		return getrange(root->left,begin,end,cmp);
}
};
int main()
{
	// AVL<double> ob;
	AVL<string> ob;
	//temp<double> t;
	long long test;
	cin>>test;
	// comparator_class<double> cmp = comparator_class<double>();
	comparator_class<string> cmp = comparator_class<string>();
	int x=-1;
	//  node<double>* root = NULL;
	//  node<double>* temp = NULL;
	 node<string>* root = NULL;
	 node<string>* temp = NULL;

	char ch='y';
	while(test--)
	{
	    	//cout<<"\nEnter 1 for insertion\nEnter 2 for deletion\nEnter 3 for search\nEnter 4 for count of occurence\nEnter 5 for lower bound\nEnter 6 for upperbound\nEnter 7 for closest element\nEnter 8 for kth LargestElement\nEnter 9 for count number in range\n";
	cin>>x;
	if(x==1)
	{
		// double y;
		string y;
		//cout<<"Enter value\n";
		cin>>y;
		 root=ob.insert(root,y,cmp);
		 //cout<<endl;
		 //cout<<"Current AVL\n";
		 //ob.print(root);
	}
	else if(x==2)
	{
		// double y;
		string y;
		//cout<<"Enter value to be deleted\n";
		cin>>y;
		root=ob.deletion(root,y,cmp);
		//cout<<endl;
		 //cout<<"Current AVL\n";
		 //ob.print(root);
	}
	else if(x==3)
	{
		// double y;
		string y;
		//cout<<"Enter value to be search\n";
		cin>>y;
		if(ob.search(root,y,cmp))
		cout<<1<<endl;
		else
		cout<<0<<endl;
	}
	else if(x==4)
	{
		// double y;
		string y;
		//cout<<"Enter value to be count\n";
		cin>>y;
	//	t *temp=NULL;
		temp=ob.occurence(root,y,cmp);
		if(temp)
		cout<<temp->count<<"\n";
		else
		cout<<0<<"\n";
	}
	else if(x==5)
	{
		// double y;
		string y;
		//cout<<"Enter value for finding lower bound\n";
		cin>>y;
		temp=ob.lowerbound(root,y,NULL,cmp);
		if(!temp)cout<<"-1\n";
		else
		cout<<temp->key<<endl;
	}
	else if(x==6)
	{
		// double y;
		string y;
		//cout<<"Enter value for finding upper bound\n";
		cin>>y;
		
		temp=ob.upperbound(root,y,NULL,cmp);
		if(!temp)cout<<0<<"\n";
		else
		cout<<temp->key<<endl;
	}
	else if(x==7)
	{
		// double y;
		string y;
		//cout<<"Enter value for finding Closest element\n";
		cin>>y;
		// cout<<ob.findClosest(root,y,cmp)->key<<endl;
	}
	else if(x==8)
	{
		int y;
		//cout<<"Enter value of k\n";
		cin>>y;
		temp=ob.kthLargest(root,y);
		if(temp)
		{
		     cout<<temp->key<<endl;
		}
		else 
		cout<<0<<"\n";
	}
	else if(x==9)
	{
		// double y,z;
		string y,z;
		//cout<<"Enter the starting and ending of range\n";
		cin>>y>>z;
		cout<<ob.getrange(root,y,z,cmp);
	}
	else
		cout<<"Error\n";
// 	cout<<"Want to continue(y/n)\n";
// 	cin>>ch;
// 
}
return 0;
}
