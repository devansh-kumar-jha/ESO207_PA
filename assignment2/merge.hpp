/// The required function Merge(T1,T2) which was to be made as a
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
