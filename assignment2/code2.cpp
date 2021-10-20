/// Algorithm
/// if(twonode) -> if(val>=x) -> go left
///             -> else       -> go middle
/// if(threenode) -> if(val1>=x)      -> go left
///               -> else if(val2>=x) -> go middle
///               -> else             -> go right
/// if(leaf) -> split , repair and return
/// if(null) -> return
/// Iterations = h(T)+h(T)+h(T)

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
    twthnode* get(int val);
    void set(twthnode* node);
    void insert(int x);
    ret_split* split(twthnode* node);
    void repair(twthnode* node);
    void display();
    void clear();
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

/// Structure returned by the split() function
/// used as a function for splitting later on.
struct ret_split
{
    twthnode* t1;
    twthnode* t2;
    twthnode* rep1;
    twthnode* rep2;
};

/// This is a function which can be called directly on the root
/// of two three tree and will free up all space occupied by that tree
/// O(N) time Where N is total number of nodes in the tree
void free_space(twthnode* node)
{
    if(node->left!=NULL) free_space(node->left);
    if(node->right!=NULL) free_space(node->right);
    if(node->middle!=NULL) free_space(node->middle);
    free(node);
    return;
}

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
ret_insert_part* insert_part(twthnode* node,int val)
{
    ret_insert_part* p=new ret_insert_part;
    
    if(node->type==2) {
        // cerr<<"leaf started"<<" ";
        int v=node->d1;
        // cerr<<"leaf not null"<<" ";
        if(val==v) {  
            // cerr<<"val==v"<<" ";
            p->n1=node;  p->n2=NULL;  p->m=-1; 
        }
        else if(val<v) { 
            // cerr<<"val<v"<<" ";
            p->m=v; p->n2=node; p->n1=leaf(val);
        }
        else {
            // cerr<<"val>v"<<" ";
            p->m=val; p->n1=node; p->n2=leaf(val);
        }
        // cerr<<"leaf completed"<<" "<<p->m<<" ";
    }
    
    else if(node->type==3) {
        // cerr<<"twonode started"<<" ";
        int a=node->d1;
        twthnode* alpha = node->left;
        twthnode* beta  = node->middle;
        // cerr<<"twonode ok"<<" ";
        if(val<a) {
            // cerr<<"val<a"<<" ";
            ret_insert_part* ret=insert_part(alpha,val);
            if(ret->n2==NULL) {  p->m=-1; p->n2=NULL; p->n1=twonode(a,ret->n1,beta);  }
            else {  p->m=-1; p->n2=NULL; p->n1=threenode(ret->m,a,ret->n1,ret->n2,beta);  }
        }
        else {
            // cerr<<"val>=a"<<" ";
            ret_insert_part* ret=insert_part(beta,val);
            if(ret->n2==NULL) { p->m=-1; p->n2=NULL; p->n1=twonode(a,alpha,ret->n1); }
            else { p->m=-1; p->n2=NULL; p->n1=threenode(a,ret->m,alpha,ret->n1,ret->n2); }
        }
        // cerr<<"twonode completed"<<" "<<p->m<<" ";
    }
    
    else {
        // cerr<<"threenode started"<<" ";
        int a=node->d1;
        int b=node->d2;
        twthnode* alpha  = node->left;
        twthnode* beta   = node->middle;
        twthnode* gamma  = node->right;
        // cerr<<"threenode ok"<<" ";
        if(val<a) {
            // cerr<<"val<a"<<" ";
            ret_insert_part* ret=insert_part(alpha,val);
            if(ret->n2==NULL) {  p->m=-1; p->n2=NULL; p->n1=threenode(a,b,ret->n1,beta,gamma);  }
            else {  p->m=a; p->n2=twonode(b,beta,gamma); p->n1=twonode(ret->m,ret->n1,ret->n2);  }    
        }
        else if(val>=a && val<b) {
            // cerr<<"val<b"<<" ";
            ret_insert_part* ret=insert_part(beta,val);
            if(ret->n2==NULL) { p->m=-1; p->n2=NULL; p->n1=threenode(a,b,alpha,ret->n1,gamma);  }
            else { p->m=ret->m; p->n2=twonode(b,ret->n2,gamma); p->n1=twonode(a,alpha,ret->n1); }
        }
        else {
            // cerr<<"val>=b"<<" ";
            ret_insert_part* ret=insert_part(gamma,val);
            if(ret->n2==NULL) { p->m=-1; p->n2=NULL; p->n1=threenode(a,b,alpha,beta,ret->n1);  }
            else { p->m=b; p->n2=twonode(ret->m,ret->n1,ret->n2); p->n1=twonode(a,alpha,beta);  }
        }
        // cerr<<"threenode completed"<<" "<<p->m<<" "<<(p->n1->d1)<<" "<<(p->n2->d1)<<" ";
    }
    
    return p;
}

/// This function will be used to display the elements in a
/// two three tree.
/// O(N) time where N is the total number of nodes.
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

/// Makes null two three tree.
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

/// Returns the last node which has a value
/// strictly smaller than the given value.
/// NULL if no such value exists.
/// O(h(T)) time
twthnode* twth::get(int val)
{
    twthnode* ans=root;    
    while(ans!=NULL || ans->type==0) {
        if(ans->type==2) {
            if(ans->d1<val) return ans;
            else return NULL;
        }
        else if(ans->type==3) {
            if(ans->d1>=val) ans=ans->left;
            else ans=ans->middle;
        }
        else {
            if(ans->d1>=val) ans=ans->left;
            else if(ans->d2>=val) ans=ans->middle;
            else ans=ans->right;
        }
    }
    if(ans==NULL || ans->type==0) return NULL;
    else return ans;
}

/// Sets the root node of the Two Three Tree.
/// O(1) time.
void twth::set(twthnode* node)
{
    root=node;
    return;
}

/// Insert a leaf node with given value in the tree.
/// Duplicacy is not allowed while inserting.
/// O(h(T)) time.
void twth::insert(int val)
{
    // cerr<<"came"<<" ";
    // cerr<<"root null"<<" "<<(root==NULL)<<" ";
    int p=root->type;
    // cerr<<"done"<<" ";
    if(p==0) {
        free(root);  // Clears un-necessary null() node
        root=leaf(val);
    }    
    else if(p==2) {
        if(val==root->d1) {}
        else if(val<root->d1) { root=twonode(root->d1,leaf(val),root); }
        else { root=twonode(val,root,leaf(val)); } 
    }
    else {
        ret_insert_part* ret=insert_part(root,val);
        // cerr<<"came back to insert"<<" "<<ret->m<<" ";
        if((ret->n2)==NULL) { 
            // cerr<<"in null"<<" "<<ret->n1->d1<<" "; 
            root=ret->n1;
        }
        else root=twonode(ret->m,ret->n1,ret->n2);
        // cerr<<"correct transfers"<<" "<<(root==NULL)<<" "<<root->d1<<" "<<root->d2<<" ";
    }
    return;
}

void twth::display()
{
    disp(root);
    cout<<"\n";
    return;
}

/// This function will be used to split the tree
/// at a particular node of the tree as provided.
/// O(h(T)) time.
ret_split* twth::split(twthnode* node)
{

}

void twth::repair(twthnode* node)
{

}

void twth::clear()
{
    free_space(root);
    return;
}


//////////////////////////////////////////// Specific functions for solving the problem ///////////////////////////////////////

void Split(twth* th,int x,twth* th1,twth* th2)
{
    twthnode* cut=th->get(x);
    ret_split* ans=th->split(cut);
    th1->set(ans->t1);
    th2->set(ans->t2);
    return;
}

int32_t main()
{
    twth th;
    int n;  cin>>n;
    int p,x;  cin>>p;
    for(int i=0;i<n;i++) { cin>>x; th.insert(x); }

    twth th1,th2;
    Split(&th,x,&th1,&th2);    
    th1.display();
    th2.display();

    th1.clear();
    th2.clear();
    th.clear();
    return 0;
}
