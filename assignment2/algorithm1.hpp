/// Algorithm
/// While(not null) node->left and height++
/// h1 = height of tree 1
/// h2 = height of tree 2
/// Can save the height of trees in the ADT.
/// if(h1>=h2) insert(tree 2 into tree 1 at height h2)
/// else insert(tree 1 into tree 2 at height h1)
/// Iterations <= O(h(T1)+h(T2)+max(h(T1),h(T2))+|h(T1)-h(T2)|)


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
