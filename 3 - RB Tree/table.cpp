#include<iostream>

using namespace std;

class CTable;

class NotFoundException {};

class CValue
{
    public:
        CValue() {};
        CValue(int a) {value = a;}
        CValue(const CValue &i) {*this = i;};
        CValue& operator = ( const CValue &i );
        int getV() const {return value;};
        bool operator == ( const CValue &i ) const;
        bool operator != ( const CValue &i ) const;
        bool operator < ( const CValue &i ) const;
        bool operator > ( const CValue &i ) const;
        bool operator >= ( const CValue &i ) const;
        bool operator <= ( const CValue &i ) const;

    private:
        int value;
};

CValue& CValue::operator = (const CValue &i)
{
    this->value = i.value;
    return *this;
}

bool CValue::operator == (const CValue &i) const
{
    if(this->value == i.value) return true;
    else return false;
}

bool CValue::operator != (const CValue &i) const
{
    if(this->value == i.value) return false;
    else return true;
}

bool CValue::operator < (const CValue &i) const
{
    if(this->value < i.value) return true;
    else return false;
}

bool CValue::operator <= (const CValue &i) const
{
    if(this->value <= i.value) return true;
    else return false;
}

bool CValue::operator > (const CValue &i) const
{
    if(this->value > i.value) return true;
    else return false;
}

bool CValue::operator >= (const CValue &i) const
{
    if(this->value >= i.value) return true;
    else return false;
}


class CKey
{
    public:
        CKey() {};
        CKey(int a) {key = a;}
        CKey(const CKey &i) {*this = i;};
        int getk() { return key;};
        ~CKey() {};
        CKey& operator = ( const CKey &i );
        bool operator == ( const CKey &i ) const;
        bool operator != ( const CKey &i ) const;
        bool operator < ( const CKey &i ) const;
        bool operator > ( const CKey &i ) const;
        bool operator >= ( const CKey &i ) const;
        bool operator <= ( const CKey &i ) const;

    private:
        int key;
};

CKey& CKey::operator = (const CKey &i)
{
    this->key = i.key;
    return *this;
}

bool CKey::operator == (const CKey &i) const
{
    if(this->key == i.key) return true;
    else return false;
}

bool CKey::operator != (const CKey &i) const
{
    if(this->key == i.key) return false;
    else return true;
}

bool CKey::operator < (const CKey &i) const
{
    if(this->key < i.key) return true;
    else return false;
}

bool CKey::operator <= (const CKey &i) const
{
    if(this->key <= i.key) return true;
    else return false;
}

bool CKey::operator > (const CKey &i) const
{
    if(this->key > i.key) return true;
    else return false;
}

bool CKey::operator >= (const CKey &i) const
{
    if(this->key >= i.key) return true;
    else return false;
}


// --------------------------------------------------------------------------------------------

class CNode
{
    public:
        CNode(const CKey & key, const CValue & val);
        ~CNode() {delete key; delete value;};
        char getColor() const {return color;};
        CNode* getParent() const {return parent;};
        CNode* getLeft() const {return left;};
        CNode* getRight() const {return right;};
        CKey& getKey() const {return *key;};
        CValue& getValue() const {return *value;};
        void setParent(CNode * par) {parent = par;};
        void setLeft(CNode * l) {left = l;};
        void setRight(CNode * r) {right = r;};
        void setColor(char c) {color=c;};
        void setValue(CValue * val) {value = val;};
        void setKey(CKey * k) {key = k;};
        void recolor();

        CNode * grandParent() const;
        CNode * uncle() const;
        CNode * sibling() const;

    private:
        char color;
        CNode * parent;
        CNode * left;
        CNode * right;
        CKey * key;
        CValue * value;
};

void CNode::recolor()
{
    if(color=='R') color = 'B';
    else color = 'R';
}

CNode::CNode(const CKey & key, const CValue & val)
{
    this->key = new CKey(key);
    this->value = new CValue(val);
    parent = NULL;
    left = NULL;
    right = NULL;
    color = 'U';
}

CNode * CNode::grandParent() const
{
    if(this!= NULL && this->parent!=NULL)
    {
        return this->parent->parent;
    }
    else return NULL;
}

CNode * CNode::uncle() const
{
    CNode * gp = this->grandParent();
    if(gp==NULL) return NULL;
    if(this->parent==gp->getLeft()) return gp->getRight();
    return gp->getLeft();
}

CNode * CNode::sibling() const
{
    if(this==NULL || this->getParent()==NULL) return NULL;
    if(this == this->getParent()->getLeft()) return this->getParent()->getRight();
    return this->getParent()->getLeft();
}

CNode * getMax(CNode * x)
{
    while(x->getRight()!=NULL)
    {
        x = x->getRight();
    }
    return x;
}

CNode * getPre(CNode * x)
{
    CNode * y;
    if(x->getLeft()!=NULL)
    {
        return getMax(x->getLeft());
    }

    y = x->getParent();
    while(y!=NULL && x==y->getLeft())
    {
        x = y;
        y = y->getParent();
    }

    return y;
}

void check1(CNode * x, CTable * table);
void check2(CNode * x, CTable * table);
void check3(CNode * x, CTable * table);
void check4(CNode * x, CTable * table);
void check5(CNode * x, CTable * table);



class CTable
{
    public:
        CTable();
        ~CTable() {freeMem(r);};
        void setR(CNode * root) {r = root;};
        bool insert(const CKey& key, const CValue& val);
        bool remove(const CKey& key);
        CNode * findNode(const CKey& key) const;
        CValue search(const CKey& key) const;
        bool isElem(const CKey& key) const;
        CNode *getRoot() const {return r;};
        void freeMem(CNode * p);

    private:
        CNode * r;
};

void CTable::freeMem(CNode * p)
{
    if (!p) return;
    freeMem(p->getLeft());
    freeMem(p->getRight());
    delete p;
}

CTable::CTable()
{
    r = NULL;
}

bool CTable::insert(const CKey & key, const CValue & val)
{
    CNode * node = new CNode(key, val);
    CNode * w = NULL;
    CNode * root = r;
    while(r!=NULL)
    {
        w = r;
        if(node->getKey() == r->getKey())
        {
            r->setValue(&node->getValue());
            //delete node;
            return false;
        }
        else if(node->getKey() < r->getKey())
        {
            r = r->getLeft();
        }
        else r = r->getRight();
    }

    node->setParent(w);
    if(w == NULL)
    {
        root = node;
    }
    else if (node->getKey() < w->getKey())
    {
        w->setLeft(node);
    }
    else
    {
        w->setRight(node);
    }

    if(root->getParent()==NULL) r = root;
    check1(node, this);


    return true;
}

void rotateLeft(CNode * x, CTable * table);
void rotateRight(CNode * x, CTable * table);

bool CTable::remove(const CKey& key)
{
    CNode * eb = NULL;
    CNode * z = findNode(key);
    if(z==NULL) return false;
    char remCol = z->getColor();
    CNode * x;
    CNode * y;
    x = NULL;
    y = NULL;

    if(z->getLeft()==NULL || z->getRight()==NULL)
    {
        y = z;
    }
    else
    {
        y = getPre(z);
    }

    if(y->getLeft()!=NULL)
    {
        x = y->getLeft();
    }
    else
    {
        x = y->getRight();
    }

    if(x!=NULL) x->setParent(y->getParent());
    if(y->getParent()==NULL)
    {
        r = x;
    }
    else if(y == y->getParent()->getLeft())
    {
        y->getParent()->setLeft(x);
    }
    else y->getParent()->setRight(x);
    if(y!=z)
    {
        z->setValue(&y->getValue());
        z->setKey(&y->getKey());
        z->setColor(y->getColor());

    }

//y - nahrazuje mazany uzel z

    if(remCol=='R') return true;
    y = z;
    eb = y;

    if(y->getParent()->getLeft() == y)
    {
cout << "weee";
        if(y->sibling()->getColor()=='R')
        {
            rotateLeft(y->getParent(),this);
            y->sibling()->recolor();
            y->getParent()->recolor();
        }

        if(y->sibling()->getColor()=='B' && (y->sibling()->getLeft()==NULL || y->sibling()->getLeft()->getColor()=='B') && (y->sibling()->getRight()==NULL || y->sibling()->getRight()->getColor()=='B'))
        {
            y->sibling()->recolor();
            if(y->getParent()->getColor()=='R')
            {
                y->getParent()->recolor();
                return true;
            }
            else eb = y->getParent();
        }
        if(y->sibling()->getColor()=='B' || y->sibling()==NULL)
        {
            if(y->sibling()->getRight()!=NULL && y->sibling()->getRight()->getColor()=='R')
            {
                rotateLeft(y->getParent(),this);
                y->sibling()->getRight()->recolor();
                char pom;
                if(y->sibling()!=NULL) pom = y->sibling()->getColor();
                else pom = 'B';
                char pom2;
                if(y->getParent()!=NULL) pom2 = y->getParent()->getColor();
                else pom2 = 'B';
                y->sibling()->setColor(pom2);
                y->getParent()->setColor(pom);
                return true;
            }
        }

        if((y->sibling()->getColor()=='B' || y->sibling()==NULL) && (y->sibling()->getRight()->getColor()=='B' || y->sibling()->getRight()==NULL) && y->sibling()->getLeft()!=NULL && y->sibling()->getLeft()->getColor()=='R')
        {
cout << "wee" ;
            rotateRight(y->sibling(), this);
            char pom;
            char pom2;
            if(y->sibling()!=NULL) pom = y->sibling()->getColor();
            else pom = 'B';
            if(y->sibling()->getLeft()!=NULL) pom2 = y->sibling()->getLeft()->getColor();
            else pom2 = 'B';

            y->sibling()->setColor(pom2);
            y->sibling()->getLeft()->setColor(pom);

            if(y->sibling()->getColor()=='B')
            {
                if(y->sibling()->getRight()->getColor()=='R')
                {
                    rotateLeft(y->getParent(),this);
                    y->sibling()->getRight()->recolor();
                    char pom = y->sibling()->getColor();
                    y->sibling()->setColor(y->getParent()->getColor());
                    y->getParent()->setColor(pom);
                    return true;
                }
            }


        }

    }


    else
    {
    // symetricky pripad...
    }

    return true;
}



CNode * CTable::findNode(const CKey& key) const
{
    CNode * p;
    p = r;
    while(p)
    {
        if(p->getKey() == key) return p;

        if (key < p->getKey()) p = p->getLeft();
        else if (key > p->getKey()) p = p->getRight();
    }
    return NULL;
}


bool CTable::isElem(const CKey& key) const
{
    if(findNode(key)!=NULL) return true;
    return false;
}

CValue CTable::search(const CKey& key) const
{
    CNode * p = findNode(key);
    if(p!=NULL) return p->getValue();

    if(p==NULL)
    {
        delete this;
        throw NotFoundException();
    }
    return p->getValue();
}

void rotateLeft(CNode * x, CTable * table)
{
    CNode * y = x->getRight();
    x->setRight(y->getLeft());
    if (x->getRight() != NULL) x->getRight()->setParent(x);

    y->setParent(x->getParent());

    if (x->getParent() == NULL) table->setR(y);

    else if (x == x->getParent()->getLeft()) x->getParent()->setLeft(y);
    else    x->getParent()->setRight(y);
    y->setLeft(x);
    x->setParent(y);
}

void rotateRight(CNode * y, CTable * table)
{
    CNode * x = y->getLeft();
    y->setLeft(x->getRight());
    if (x->getRight() != NULL) x->getRight()->setParent(y);
    x->setParent(y->getParent());
    if (x->getParent() == NULL) table->setR(x);

    else if (y == y->getParent()->getLeft()) y->getParent()->setLeft(x);
    else y->getParent()->setRight(x);
    x->setRight(y);
    y->setParent(x);
}





void check1(CNode * x, CTable * table)
{
    if(x->getParent() == NULL) x->setColor('B');
    else
    {
        x->setColor('R');
        check2(x, table);
    }
}

void check2(CNode * x, CTable * table)
{
    if(x->getParent()->getColor()!='B') check3(x, table);
}

void check3(CNode * x, CTable * table)
{
    CNode * y = x->uncle();
    if((y!=NULL) && (y->getColor()=='R'))
    {
        x->getParent()->setColor('B');
        y->setColor('B');
        CNode * gp = x->grandParent();
        gp->setColor('R');
        check1(gp, table);
    }
    else
    {
        check4(x, table);
    }
}

void check4(CNode * x, CTable * table)
{
    CNode * gp = x->grandParent();
    if((x == x->getParent()->getRight()) && (x->getParent() == gp->getLeft()))
    {
        rotateLeft(x->getParent(), table);
        x = x->getLeft();
    }
    else if ((x == x->getParent()->getLeft()) && (x->getParent()==gp->getRight()))
    {
        rotateRight(x->getParent(), table);
        x = x->getRight();
    }
    check5(x, table);
}

void check5(CNode * x, CTable * table)
{
    CNode * gp = x->grandParent();
    x->getParent()->setColor('B');
    gp->setColor('R');
    if((x == x->getParent()->getLeft()) && (x->getParent()==gp->getLeft()))
    {
        rotateRight(gp, table);
    }
    else if ((x == x->getParent()->getRight()) && (x->getParent()==gp->getRight()))
    {
        rotateLeft(gp, table);
    }
}





void preOrder(CNode * x)
{
	if (x != NULL)
	{
        cout << x->getKey().getk() << ", " << x->getColor() << endl;
        preOrder(x->getLeft());
        preOrder(x->getRight());
    }
}

int main(void)
{
    CTable * table = new CTable();


    CValue * val1 = new CValue(16);
    CValue * val2 = new CValue(16);
    CValue * val3 = new CValue(16);
    CValue * val4 = new CValue(16);
    CValue * val5 = new CValue(16);
    CValue * val6 = new CValue(16);
    CValue * val7 = new CValue(16);
    CValue * val8 = new CValue(16);
    CValue * val9 = new CValue(16);
    CValue * val10 = new CValue(16);
    CValue * val11 = new CValue(1);
    CValue * val12 = new CValue(16);
    CValue * val13 = new CValue(16);
    CValue * val14 = new CValue(16);
//10,85,15,70,20,60,30,50,65,80,90,40,5 and 55
    CKey * a = new CKey(10);
    CKey * b = new CKey(85);
    CKey * c = new CKey(15);
    CKey * d = new CKey(70);
    CKey * e = new CKey(20);
    CKey * f = new CKey(60);
    CKey * g = new CKey(30);
    CKey * h = new CKey(50);
    CKey * i = new CKey(65);
    CKey * j = new CKey(80);
    CKey * k = new CKey(90);
    CKey * l = new CKey(40);
    CKey * m = new CKey(5);
    CKey * n = new CKey(55);

    table->insert(*a, *val1);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*b, *val2);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*c, *val3);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*d, *val4);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*e, *val5);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*f, *val6);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*g, *val7);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*h, *val8);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*i, *val9);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*j, *val10);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*k, *val11);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*l, *val12);
        preOrder(table->getRoot());
        cout << endl << endl;
    table->insert(*m, *val13);
        preOrder(table->getRoot());
            cout << endl << endl;
    table->insert(*n, *val14);
        preOrder(table->getRoot());
            cout << endl << endl;


    //cout << table->getRoot();
  //  cout << table->getRoot()->getKey().getk() << ", " << table->getRoot()->getColor() << endl;

    table->remove(*c);

preOrder(table->getRoot());
            cout << endl << endl;

    delete table;

    return 0;
}
