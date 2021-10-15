//! Two Three controlling structures and classes
//! This file can be used as a header for the code files
//! or could be directly pasted.

#include <iostream>
using namespace std;
#define int long long int


/// This represents node of the Two Three Tree
/// Type field is for determining the type of node ( NULL, SINGLE, LEAF, TWONODE, THREENODE)
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
    int h;

    public:
    twth();
    twth(int val);
    twth(twthnode* a);
    twthnode* get();
    void insert(int x);
    void insert(twthnode* node);
    int remove();
    void display();
};

/// Structure returned by the insert_part() function
/// used as a sub function for inserting into
/// the two three tree.
struct ret_insert_part
{
    twth* n1;
    twth* n2;
    int m;
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
    // This is a error prone function so precaution is taken.
    cerr<<"Error occured"<<"\n";
    return;
}

/// Creates a Null type node for the Two Three Tree
/// O(1) time
twthnode* null()
{
    twthnode* temp=new twthnode;
    temp->type=0;
    temp->d1=-1;         temp->d2=-1;
    temp->parent=NULL;   temp->left=NULL;
    temp->right=NULL;    temp->middle=NULL;
    return temp;
}

/// Creates a Single type node for the Two Three Tree
/// O(1) time
twthnode* single(twth* t)
{
    twthnode* temp=new twthnode;
    temp->type=1;
    temp->d1=-1;         temp->d2=-1;
    temp->parent=NULL;   temp->left=t->get();
    temp->right=NULL;    temp->middle=NULL;
    return temp;
}

/// Creates a Leaf node for the Two Three Tree
/// O(1) time
twthnode* leaf(int val)
{
    twthnode* temp=new twthnode;
    temp->type=2;
    temp->d1=val;        temp->d2=-1;
    temp->parent=NULL;   temp->left=NULL;
    temp->right=NULL;    temp->middle=NULL;
    return temp;
}

/// Creates a node with two children for the Two Three Tree
/// O(1) time
twthnode* twonode(int val,twth* t1,twth* t2)
{
    twthnode* temp=new twthnode;
    temp->type=3;
    temp->d1=val;   temp->d2=-1;
    temp->parent=NULL;
    temp->left=t1->get();
    temp->middle=t2->get();
    temp->right=NULL;
    return temp;
}

/// Creates a node with three children for the Two Three Tree
/// O(1) time
twthnode* threenode(int val1,int val2,twth*t1,twth*t2,twth*t3)
{
    twthnode* temp=new twthnode;
    temp->type=4;
    temp->d1=val1;   temp->d2=val2;
    temp->parent=NULL;
    temp->left=(*t1).get();
    temp->middle=(*t2).get();
    temp->right=(*t3).get();
    return temp;
}

/// This function returns a triple (n1,n2,m) where
/// n1 and n2 are two three trees and m is the minimum in
/// two three tree n2.
/// O(h(T)) time.
ret_insert_part* insert_part(twth* t,int val)
{
    ret_insert_part* p;
    if((t->get())->type==2) {
        int v=(t->get())->d1;
        if(val==v) {  p->n1=t;  p->n2=NULL;  p->m=-1; }
        else if(val<v) { 
            twth th(val);
            p->m=v; p->n2=t; p->n1=&th;
        }
        else {
            twth th(val);
            p->m=val; p->n1=t; p->n2=&th;
        }
    }
    else if((t->get())->type==3) {
        int a=(t->get())->d1;
        twth alpha((t->get())->left);
        twth beta((t->get())->middle);
        if(val<a) {
            ret_insert_part* ret=insert_part(&alpha,val);
            if(ret->n2==NULL) { 
                twth l(twonode(a,ret->n1,&beta));
                p->m=-1; p->n2=NULL; p->n1=&l; 
            }
            else { 
                twth l(threenode(ret->m,a,ret->n1,ret->n2,&beta));
                p->m=-1; p->n2=NULL; p->n1=&l; 
            }
        }
        else {
            ret_insert_part* ret=insert_part(&beta,val);
            if(ret->n2==NULL) {
                twth l(twonode(a,&alpha,ret->n1));
                p->m=-1; p->n2=NULL; p->n1=&l;
            }
            else {
                twth l(threenode(a,ret->m,&alpha,ret->n1,ret->n2));
                p->m=-1; p->n2=NULL; p->n1=&l;
            }
        }
    }
    else {
        int a=(t->get())->d1;
        int b=(t->get())->d2;
        twth alpha((t->get())->left);
        twth beta((t->get())->middle);
        twth gamma((t->get())->right);
        if(val<a) {
            ret_insert_part* ret=insert_part(&alpha,val);
            if(ret->n2==NULL) { 
                twth l(threenode(a,b,ret->n1,&beta,&gamma));
                p->m=-1; p->n2=NULL; p->n1=&l; 
            }
            else { 
                twth l1(twonode(ret->m,ret->n1,ret->n2));
                twth l2(twonode(b,&beta,&gamma));
                p->m=-1; p->n2=&l2; p->n1=&l1; 
            }    
        }
        else if(val>=a && val<b) {
            ret_insert_part* ret=insert_part(&beta,val);
            if(ret->n2==NULL) { 
                twth l(threenode(a,b,&alpha,ret->n1,&gamma));
                p->m=-1; p->n2=NULL; p->n1=&l; 
            }
            else { 
                twth l1(twonode(a,&alpha,ret->n1));
                twth l2(twonode(b,ret->n2,&gamma));
                p->m=ret->m; p->n2=&l2; p->n1=&l1; 
            }
        }
        else {
            ret_insert_part* ret=insert_part(&gamma,val);
            if(ret->n2==NULL) { 
                twth l(threenode(a,b,&alpha,&beta,ret->n1));
                p->m=-1; p->n2=NULL; p->n1=&l; 
            }
            else { 
                twth l1(twonode(a,&alpha,&beta));
                twth l2(twonode(ret->m,ret->n1,ret->n2));
                p->m=b; p->n2=&l2; p->n1=&l1; 
            }
        }
    }
    return p;
}

void delete_part(twth* t,int val)
{

}

/// This function will be used to display the elements in a
/// two three tree.
/// O(N) time where N is the total number of nodes.
void disp(twthnode* root)
{
    int flag=1;
    if(root->left!=NULL) { flag=0; disp(root->left); }
    if(root->middle!=NULL) { flag=0; disp(root->middle); }
    if(root->right!=NULL) { flag=0; disp(root->right); }
    if(flag==1) cout<<root->d1<<" ";
    return;
}

twth::twth()
{
    root=null();
    return;
}

twth::twth(int val)
{
    root=leaf(val);
    return;
}

twth::twth(twthnode* a)
{
    root=a;
    return;
}

/// Returns the Root of the Two Three Tree
/// O(1) time
twthnode* twth::get()
{
    return root;
}

void twth::insert(int val)
{
    int p=root->type;
    twthnode* temp=root;
    if(p==0) root=leaf(val);
    else if(p==2) {
        if(val==root->d1) {}
        else if(val<root->d1) {
            twth t1(val);
            root=twonode(root->d1,&t1,this);
        }
        else {
            twth t1(val);
            root=twonode(val,this,&t1);
        } 
    }
    else {
        ret_insert_part* ret=insert_part(this,val);
        if((ret->n2)->get()==null()) root=(ret->n1)->get();
        else root=twonode(ret->m,ret->n1,ret->n2);
    }
    free_space(temp);
    return;
}

void twth::insert(twthnode* node)
{
    if(node->type==0) return;
    else if(node->type==1) insert(node->left);
    else if(node->type==2) insert(node->d1);
    else if(node->type==3) {}
    else {}
    return;
}

int twth::remove()
{

}

void twth::display()
{
    disp(root);
    cout<<"\n";
    return;
}
