typedef ll T;
const int N = 5e5+50; // >= Node + Query
T ar[N]; // Initial Array
struct Node {
    Node *ch[2],*pre;
    T val, mx, sum, add;
    bool rev, flip;
    int size;
    Node() {size=0;val=mx=-1e9;add=0;}
    void addIt(T ad) {
        add+=ad; mx+=ad;
        sum+=size*ad; val+=ad; }
    void revIt() {rev^=1;}
    void upd() {
        size=ch[0]->size+ch[1]->size+1;
        mx=max(val,max(ch[0]->mx,ch[1]->mx));
        sum= ch[0]->sum + ch[1]->sum + val; }
    void pushdown();
} Tnull,*null=&Tnull;
void Node::pushdown(){
    if (add!=0){
        for (int i=0;i<2;++i)
            if (ch[i]!=null) ch[i]->addIt(add);
        add = 0; }
    if (rev){
        swap(ch[0],ch[1]);
        for (int i=0;i<2;i++)
            if (ch[i]!=null) ch[i]->revIt();
        flip ^= 1; rev = 0;} }
struct Splay{
    Node nodePool[N],*cur,*root;
    Splay() { cur=nodePool; root=null; }
    void clear() { cur=nodePool; root=null; }
    Node* newNode(T v,Node* f) {
        cur->ch[0]=cur->ch[1]=null;
        cur->size=1; cur->val=v;
        cur->mx=v; cur->sum = 0;
        cur->add=0; cur->pre=f;
        cur->rev = cur->flip=0;
        return cur++; }
    Node* build(int l,int r,Node* f) {
        if(l>r) return null;
        int m=(l+r)>>1;
        Node* t=newNode(ar[m],f);
        t->ch[0]=build(l,m-1,t);
        t->ch[1]=build(m+1,r,t);
        t->upd();
        return t; }
    void rotate(Node* x,int c) {
        Node* y=x->pre;
        y->pushdown(); x->pushdown();
        y->ch[!c]=x->ch[c];
        if (x->ch[c]!=null) x->ch[c]->pre=y;
        x->pre=y->pre;
        if (y->pre!=null) {
            if (y->pre->ch[0]==y) y->pre->ch[0]=x;
            else y->pre->ch[1]=x; }
        x->ch[c]=y; y->pre=x; y->upd();
        if (y==root) root=x; }
    void splay(Node* x,Node* f) {
        x->pushdown();
        while (x->pre!=f) {
            if (x->pre->pre==f) {
                if (x->pre->ch[0]==x) rotate(x,1);
                else rotate(x,0);
            } else {
                Node *y=x->pre,*z=y->pre;
                if (z->ch[0]==y) {
                    if (y->ch[0]==x) rotate(y,1),rotate(x,1);
                    else rotate(x,0),rotate(x,1);
                } else {
                    if (y->ch[1]==x) rotate(y,0),rotate(x,0);
                    else rotate(x,1),rotate(x,0); } } }
        x->upd(); }
    void select(int k,Node* f) {
        int tmp; Node* x=root;
        x->pushdown(); k++;
        for(;;){
            x->pushdown();
            tmp=x->ch[0]->size;
            if (k==tmp+1) break;
            if (k<=tmp) x=x->ch[0];
            else {
                k-=tmp+1;
                x=x->ch[1]; } }
        splay(x,f); }
    Node*&get(int l, int r) {
        select(l-1,null); select(r+1,root);
        return root->ch[1]->ch[0]; }
    void reverse(int l,int r) {
        Node* o=get(l,r);
        o->rev^=1;
        splay(o,null); }
    void del(int p) {
            select(p-1,null); select(p+1,root);
            root->ch[1]->ch[0] = null;
            splay(root->ch[1],null); }
    void split(int l,int r,Node*&s1) {
        Node* tmp=get(l,r);
        root->ch[1]->ch[0]=null;
        root->ch[1]->upd();
        root->upd();
        s1=tmp; }
    void cut(int l,int r) {
        Node* tmp;
        split(l,r,tmp);
        select(root->size-2,null);
        root->ch[1]->ch[0]=tmp;
        tmp->pre=root->ch[1];
        root->ch[1]->upd();
        root->upd(); }
    void init(int n) {
        clear();
        root=newNode(0,null);
        root->ch[1]=newNode(n+1,root);
        root->ch[1]->ch[0]=build(1,n,root->ch[1]);
        splay(root->ch[1]->ch[0],null); }
    void insertPos(int pos,T v) {
        select(pos,null); select(pos+1,root);
        root->ch[1]->ch[0] = newNode(v,root->ch[1]);
        splay(root->ch[1]->ch[0],null); }
    void insertRange(int pos,Node *s) {
        select(pos,null); select(pos+1,root);
        root->ch[1]->ch[0] = s;
        s->pre = root->ch[1];
        root->ch[1]->upd();
        root->upd(); }
    T query(int l,int r) {
        Node *o = get(l,r);
        return o->mx; }
    void addRange(int l,int r,T v) {
        Node *o = get(l,r);
        o->add+=v; o->val+=v;
        o->sum+=o->size * v;
        splay(o,null); }
    void output(int l,int r) {
        for (int i=l;i<=r;i++){
            select(i,null);
            cout << root->val << ' ';
        }; cout << endl; } } st;
// vim: cc=60 ts=2 sts=2 sw=2: