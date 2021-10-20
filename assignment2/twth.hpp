//! Two Three controlling structures and classes
//! This file can be used as a header for the code files
//! or could be directly pasted.

//! Code Left to be Added ->
//!     split() and repair() from the two three tree

#include <iostream>
using namespace std;
#define int long long int

/// This represents node of the Two Three Tree
/// Type field is for determining the type of node ( NULL, SINGLE, LEAF, TWONODE, THREENODE )
struct twthnode
{
    int type;
    int d1,d2;
    struct twthnode* parent; // Parent pointer is yet to be adjusted.
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
    twth(int val);
    twth(twthnode* a);
    twthnode* get();
    twthnode* get(int val);
    void set(twthnode* node);
    void insert(int x);
    void insert(twthnode* node,twthnode* pos);
    void remove(int x);
    // ret_split* split(twthnode* node);
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

/// Structure returned by the delete_part() function
/// used as a sub function for deleting from
/// the two three tree.
struct ret_delete_part
{
    twthnode* n;
    int m;
};

/// Structure returned by the split() function
/// used as a function for splitting later on.
struct ret_split
{
    twthnode* n1;
    twthnode* n2;
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

/// This function returns a doublet (n,m) where
/// n is a node and m denotes the minimum value
/// present in a two three tree rooted at n.
/// If min(n)=min(tree with calling function) than m=-1.
ret_delete_part* delete_part(twthnode* node,int val)
{
    ret_delete_part* p=new ret_delete_part;

    if(node->type==3) {
        // cerr<<"twonode started"<<" ";
        int a=node->d1;
        twthnode* alpha = node->left;
        twthnode* beta  = node->middle;
        // cerr<<"twonode ok"<<" ";
        if(alpha->type==2 && beta->type==2) {
            // cerr<<"leaf"<<" ";
            if(val==alpha->d1) { 
                // cerr<<"val=1"<<" ";
                p->m=beta->d1; p->n=single(beta); 
                free(alpha);
            }
            else if(val==beta->d1) {
                // cerr<<"val=2"<<" ";
                p->m=alpha->d1; p->n=single(alpha);
                free(beta);
            }
            else { 
                // cerr<<"not found"<<" ";
                p->m=-1; p->n=node; 
            }
        }
        else {
            if(val<a) {
                // cerr<<"val<a"<<" ";
                ret_delete_part* ret=delete_part(alpha,val);
                if(ret->n->type!=1) { p->m=ret->m; p->n=twonode(a,ret->n,beta); }
                else {
                    if(beta->type==3) { 
                        p->m=ret->m; 
                        p->n=threenode(a,beta->d1,ret->n->left,beta->left,beta->middle); 
                    }
                    else { 
                        p->m=ret->m; 
                        twthnode* p1=twonode(a,ret->n->left,beta->left);
                        twthnode* p2=twonode(beta->d2,beta->middle,beta->right);
                        p->n=twonode(beta->d1,p1,p2);
                    }
                }
            }
            else {
                // cerr<<"val>=a"<<" ";
                ret_delete_part* ret=delete_part(beta,val);
                int m_prime= (ret->m==-1) ? a : ret->m ;
                if(ret->n->type!=1) { p->m=-1; p->n=twonode(a,alpha,ret->n); }
                else {
                    if(alpha->type==3) { 
                        p->m=-1; 
                        twthnode* t=threenode(alpha->d1,m_prime,alpha->left,alpha->middle,ret->n->left);
                        p->n=single(t);
                    }
                    else { 
                        p->m=-1; 
                        twthnode* p1=twonode(alpha->d1,alpha->left,alpha->middle);
                        twthnode* p2=twonode(m_prime,alpha->right,ret->n->left);
                        p->n=twonode(alpha->d2,p1,p2);
                    }
                }
            }
        }
        // cerr<<"twonode completed"<<" "<<p->m<<" ";
    }
    
    else {
        // cerr<<"threenode started"<<" ";
        int a=node->d1;
        int b=node->d2;
        twthnode* alpha = node->left;
        twthnode* beta  = node->middle;
        twthnode* gamma = node->right;
        // cerr<<"threenode ok"<<" ";
        if(alpha->type==2 && beta->type==2 && gamma->type==2) {
            // cerr<<"leaf"<<" ";
            if(val==alpha->d1) { 
                // cerr<<"val=1"<<" ";
                p->m=beta->d1; p->n=twonode(b,beta,gamma); 
                free(alpha);
            }
            else if(val==beta->d1) {
                // cerr<<"val=2"<<" ";
                p->m=-1; p->n=twonode(b,alpha,gamma);
                free(beta);
            }
            else if(val==gamma->d1) {
                // cerr<<"val=3"<<" ";
                p->n=twonode(a,alpha,beta); p->m=-1;
                free(gamma);
            }
            else { 
                // cerr<<"not found"<<" ";
                p->m=-1; p->n=node; 
            }
        }
        else {
            if(val<a) {
                // cerr<<"val<a"<<" ";
                ret_delete_part* ret=delete_part(alpha,val);
                if(ret->n->type!=1) { p->m=ret->m; p->n=threenode(a,b,ret->n,beta,gamma); }
                else {
                    if(beta->type==3) { 
                        p->m=ret->m; 
                        twthnode* t=threenode(a,beta->d1,ret->n->left,beta->left,beta->middle);
                        p->n=twonode(b,t,gamma);
                    }
                    else { 
                        p->m=ret->m; 
                        twthnode* p1=twonode(a,ret->n->left,beta->left);
                        twthnode* p2=twonode(beta->d2,beta->middle,beta->right);
                        p->n=threenode(beta->d1,b,p1,p2,gamma);
                    }
                }
            }
            else if(val<b) {
                // cerr<<"val<b"<<" ";
                ret_delete_part* ret=delete_part(beta,val);
                int m_prime= (ret->m==-1) ? a : ret->m ;
                if(ret->n->type!=1) { p->m=-1; p->n=threenode(m_prime,b,alpha,ret->n,gamma); }
                else {
                    if(alpha->type==3) { 
                        p->m=-1; 
                        twthnode* t=threenode(alpha->d1,m_prime,alpha->left,alpha->middle,ret->n->left);
                        p->n=twonode(b,t,gamma); 
                    }
                    else { 
                        p->m=-1; 
                        twthnode* p1=twonode(alpha->d1,alpha->left,alpha->middle);
                        twthnode* p2=twonode(m_prime,alpha->right,ret->n->left);
                        p->n=threenode(alpha->d2,b,p1,p2,gamma);
                    }
                }
            }
            else {
                // cerr<<"val>=b"<<" ";
                ret_delete_part* ret=delete_part(gamma,val);
                int m_prime= (ret->m==-1) ? b : ret->m ;
                if(ret->n->type!=1) { p->m=-1; p->n=threenode(a,m_prime,alpha,beta,ret->n); }
                else {
                    if(beta->type==3) { 
                        p->m=-1; 
                        twthnode* t=threenode(beta->d1,m_prime,beta->left,beta->middle,ret->n->left);
                        p->n=twonode(a,alpha,t); 
                    }
                    else { 
                        p->m=-1; 
                        twthnode* p1=twonode(beta->d1,beta->left,beta->middle);
                        twthnode* p2=twonode(m_prime,beta->right,ret->n->left);
                        p->n=threenode(a,beta->d2,alpha,p1,p2);
                    }
                }
            }
        }
        // cerr<<"threenode completed"<<" "<<p->m<<" ";
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

/// Makes a two three tree with one element.
/// O(1) time
twth::twth(int val)
{
    root=leaf(val);
    return;
}

/// Makes a two three tree with a particular node as root.
/// O(1) time
twth::twth(twthnode* a)
{
    root=a;
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

/// Insert a two three rooted at a given node.
/// Take care in this that duplicacy is not there as this function
/// does not check for that.
/// O(h(T)) time.
void twth::insert(twthnode* node,twthnode* pos)
{

}

/// Delete the required node from the two three tree.
/// If the node is not available than nothing is done.
/// O(h(T)) time.
void twth::remove(int val)
{
    // cerr<<"came"<<" ";
    int p=root->type;
    // cerr<<"done"<<" ";
    if(p==0) {}
    else if(p==2) {
        if(val==root->d1) {
            free(root);
            root=null();
        }
        else {}
    }
    else {
        ret_delete_part* ret=delete_part(root,val);
        // cerr<<"back to remove"<<" "<<ret->m<<" "<<ret->n->type<<" ";
        if(ret->n->type==1) root=ret->n->left;
        else root=ret->n;
        // cerr<<"removal completed"<<" "<<root->d1<<" "<<root->d2<<" ";
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
// ret_split* twth::split(twthnode* node)
// {

// }

void twth::repair(twthnode* node)
{

}

void twth::clear()
{
    free_space(root);
    return;
}
