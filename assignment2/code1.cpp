#include<bits/stdc++.h>
using namespace std;
#define int long long int

///////////////////////////////// Structures and Functions for controlling the 2-3 Tree ///////////////////////////////////////////

/// This represents node of the Two Three Tree
/// Type field is for determining the type of node ( NULL, SINGLE, LEAF, TWONODE, THREENODE )
struct twthnode
{
    int type;
    int d1,d2;
    struct twthnode* parent;
    struct twthnode* left;
    struct twthnode* middle;
    struct twthnode* right;
};

/// Class controlling a Two Three tree with all member functions
/// bound together with the elements of the tree.
class twth
{
    private:
    twthnode* root;

    public:
    twth();
    twthnode* get();
    void set(twthnode* node);
    int min();
    void insert(twthnode* node,twthnode* pos,int m,int type);
    void display();
};

/// Structure returned by the insert_part() function
/// used as a sub function for inserting into
/// the two three tree.
struct ret_insert_part
{
    twthnode* n1;
    twthnode* n2;
    int m;
};

/// Creates a Null type node for the Two Three Tree
/// O(1) time
twthnode* null()
{
    twthnode* temp=new twthnode;
    if(temp==NULL) cerr<<"Memory full";
    temp->type=0;
    temp->d1=-1;         temp->d2=-1;
    temp->parent=NULL;   temp->left=NULL;
    temp->right=NULL;    temp->middle=NULL;
    return temp;
}

/// Creates a Single type node for the Two Three Tree
/// O(1) time
twthnode* single(twthnode* node)
{
    twthnode* temp=new twthnode;
    if(temp==NULL) cerr<<"Memory full";
    temp->type=1;
    temp->d1=-1;         temp->d2=-1;
    temp->parent=NULL;   
    temp->left=node;     node->parent=temp;
    temp->right=NULL;    temp->middle=NULL;
    return temp;
}

/// Creates a Leaf node for the Two Three Tree
/// O(1) time
twthnode* leaf(int val)
{
    twthnode* temp=new twthnode;
    if(temp==NULL) cerr<<"Memory full";
    temp->type=2;
    temp->d1=val;        temp->d2=-1;
    temp->parent=NULL;   temp->left=NULL;
    temp->right=NULL;    temp->middle=NULL;
    return temp;
}

/// Creates a node with two children for the Two Three Tree
/// O(1) time
twthnode* twonode(int val,twthnode* n1,twthnode* n2)
{
    twthnode* temp=new twthnode;
    if(temp==NULL) cerr<<"Memory full";
    temp->type=3;
    temp->d1=val;   temp->d2=-1;
    temp->parent=NULL;
    temp->left=n1;      n1->parent=temp;
    temp->middle=n2;    n2->parent=temp;
    temp->right=NULL;
    return temp;
}

/// Creates a node with three children for the Two Three Tree
/// O(1) time
twthnode* threenode(int val1,int val2,twthnode* n1,twthnode* n2,twthnode* n3)
{
    twthnode* temp=new twthnode;
    if(temp==NULL) cerr<<"Memory full";
    temp->type=4;
    temp->d1=val1;   temp->d2=val2;
    temp->parent=NULL;
    temp->left=n1;     n1->parent=temp;
    temp->middle=n2;   n2->parent=temp;
    temp->right=n3;    n3->parent=temp;
    return temp;
}

/// This function returns a triple (n1,n2,m) where
/// n1 and n2 are two nodes and m is the minimum in
/// two three tree rooted at n2.
ret_insert_part* insert_part(twthnode* node,twthnode* pos,int m,int type)
{
    ret_insert_part* p=new ret_insert_part;
    if(pos->type==3) {
        pos->type=4;
        if(type==1) {
            pos->right=pos->middle;
            pos->middle=pos->left;
            pos->left=node;
            pos->d2=pos->d1;    pos->d1=m;
        }
        else {  pos->d2=m;   pos->right=node;  }
        node->parent=pos;
        p->n1=NULL; p->n2=NULL; p->m=-1;
    }
    else {
        pos->type=3;
        if(type==1) {
            twthnode* k=twonode(m,node,pos->left);
            pos->left=pos->middle;
            pos->middle=pos->right;
            if(pos->parent==NULL) { p->m=pos->d1; p->n1=k; p->n2=pos; }
            else p=insert_part(k,pos->parent,pos->d2,type);
            pos->d1=pos->d2;
        }
        else {
            twthnode* k=twonode(m,pos->right,node);
            if(pos->parent==NULL) { p->m=pos->d2; p->n1=pos; p->n2=k; }
            else p=insert_part(k,pos->parent,pos->d2,type);
        }
        pos->right=NULL;   pos->d2=-1;
    }
    return p;
}

/// This function will be used to display the elements in a
/// two three tree.
void disp(twthnode* root)
{
    if(root->type==0) return;
    int flag=1;
    if(root->left!=NULL) { flag=0; disp(root->left); }
    if(root->middle!=NULL) { flag=0; disp(root->middle); }
    if(root->right!=NULL) { flag=0; disp(root->right); }
    if(flag==1) cout<<root->d1<<" ";
    return;
}

/// Constructor for a null two three tree.
/// O(1) time
twth::twth()
{
    root=null();
    return;
}

/// Returns the root node of the Two Three Tree.
/// O(1) time
twthnode* twth::get()
{
    return root;
}

/// Sets the root node of the Two Three Tree.
/// O(1) time.
void twth::set(twthnode* node)
{
    root=node;
    return;
}

/// Returns the minimum value in the tree.
/// -1 is returned if tree is null().
/// O(h(T)) time.
int twth::min()
{
    if(root->type==0) return -1;
    twthnode* x=root;
    while(x->left!=NULL) x=x->left;
    return x->d1;
}

/// Insert a two three rooted at a given node.
/// The height of the given node `pos` should be equal to height of `node`.
/// Also the values in the tree rooted at `node` should be either all strictly greater or smaller.
/// O(h(T)-h(pos)) time.
void twth::insert(twthnode* node,twthnode* pos,int m,int type)
{
    if(pos->type==0) { 
        free(pos); 
        pos=node; 
    }
    else if(pos->type==2) {}
    else {
        if(node->type==0) {}
        else {
            ret_insert_part* ret=insert_part(node,pos,m,type);
            if(ret->n1==NULL) {}
            else root=twonode(ret->m,ret->n1,ret->n2);
        }    
    }
    return;
}

/// Displays all the nodes of the tree.
/// O(N) time where N is the total number of nodes.
void twth::display()
{
    disp(root);
    cout<<"\n";
    return;
}

///////////////////////////////// Specifics functions related to the question  ///////////////////////////////////////////

/// The required function Merge(S1,S2,S) which was to be made as a
/// solution to the given problem.
/// O(h(T1)+h(T2)) time.
twth Merge(twth th1,twth th2)
{
    twth th;

    if(th1.get()->type==0) { th.set(th2.get()); return th; }
    if(th2.get()->type==0) { th.set(th1.get()); return th; }

    int h1=1,h2=1;
    twthnode* temp1=th1.get();
    twthnode* temp2=th2.get();
    while(temp1->type>2) {
        h1++;
        if(temp1->right==NULL) temp1=temp1->middle;
        else temp1=temp1->right;
    }
    while(temp2->type>2) {
        h2++;
        temp2=temp2->left;
    }

    if(h1==h2) th.set(twonode(temp2->d1,th1.get(),th2.get()));
    else if(h1>h2) {
        for(int i=0;i<h2;i++) temp1=temp1->parent;
        th1.insert(th2.get(),temp1,temp2->d1,2);
        th.set(th1.get());
    }
    else {
        for(int i=0;i<h1;i++) temp2=temp2->parent;
        th2.insert(th1.get(),temp2,th2.min(),1);
        th.set(th2.get());
    }
    return th;
}

/// This function prints all the element of the
/// two-three tree in ascending order.
/// O(N) time where N is total number nodes in tree.
void Extract(twth th)
{
    th.display();
    return;
}

/// Makes a tree for singleton set.
/// O(1) time.
twth MakeSingleton(int x)
{
    twth th;
    th.set(leaf(x));
    return th;
}

/// Testing function.
void test()
{
    twth T=MakeSingleton(1);
    for(int i=2;i<=500;i++) T=Merge(T,MakeSingleton(i));

    twth U=MakeSingleton(777);
    for(int i=778;i<=1000;i++) U=Merge(U,MakeSingleton(i));

    twth V=Merge(T,U);
    Extract(V);
    return;
}

int32_t main()
{
    test();
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms/n";
    return 0;
}
