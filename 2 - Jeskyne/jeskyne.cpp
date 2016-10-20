#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Node
{
public:

    Node(){};
    int caveNum; // cislo jeskyne
    int parent; // index rodice
    int toPar; // cena k rodici
    int depth; // hloubka uzlu
    vector<int> priceTable;
    set<pair<int, int> > offspring; // potomci uzlu a cena cesty k nim
};

// Globalni vector -_-
vector<Node *> tree;

struct cmp
{
	bool operator()(const int i1, const int i2) const
	{
		int t1value = tree[i1]->depth;
		int t2value = tree[i2]->depth;
		return t1value < t2value;
	}
};


priority_queue<int, vector<int>, cmp> fronta;
queue<int> repair;
bool * vlozeno;




/*Rekurzivne prochazi stromovou strukturu, nastavi kazdemu uzlu index prislusneho rodice
  a vymaze rodice ze setu potomku
*/
void repairTree(int k)
{

    int i;
    int node;
    while(repair.size()>0)
    {
        node = repair.front();
        repair.pop();

        if(tree[node]->offspring.size()==1 && node!=0)
        {
            tree[node]->parent = tree[node]->offspring.begin()->first;
            tree[node]->toPar = tree[node]->offspring.begin()->second;
            tree[node]->offspring.clear();
            fronta.push(node);
            vlozeno[node] = true;
            for(i=0; i<k; i++)
            {
                tree[node]->priceTable.push_back(0);
            }

        }
        set<pair<int, int> >::iterator it;

        pair<int, int> toDel;
        toDel.first = tree[node]->parent;
        toDel.second = tree[node]->toPar;
        tree[node]->offspring.erase(toDel);

        for(it=tree[node]->offspring.begin(); it!=tree[node]->offspring.end(); ++it)
        {
            tree[it->first]->toPar = it->second;
            tree[it->first]->parent = node;
            tree[it->first]->depth = tree[node]->depth+1;
            repair.push(it->first);
        }
    }
    return;
}


int calculatePrice(int k)
{
    int par, pom, i;
    set<pair<int, int> >::iterator it;
    while(fronta.size()>0)
    {
        int node = fronta.top();
        fronta.pop();
        par = tree[node]->parent;

        if(node != 0 && !vlozeno[par])
        {
            fronta.push(par);
            vlozeno[par] = true;
        }

        if(tree[node]->offspring.size()==0) continue;

        pom = 0;
        for(it=tree[node]->offspring.begin(); it!=tree[node]->offspring.end(); ++it)
        {
            pom+=tree[it->first]->toPar;

            pom+=tree[it->first]->priceTable[k-1];
        }
        tree[node]->priceTable.push_back(pom);

        pom=0;
        for(i=1; i<k; i++)
        {
            pom=0;

            for(it=tree[node]->offspring.begin(); it!=tree[node]->offspring.end(); ++it)
            {
                int noCut = tree[it->first]->priceTable[i-1];
                int cut = it->second + tree[it->first]->priceTable[k-1];
                if ( noCut < cut )  pom += noCut;
                else pom += cut;
                //pom += tree[it->first]->priceTable[i-1];
            }
            if(pom<tree[node]->priceTable[i-1]) tree[node]->priceTable.push_back(pom);
            else tree[node]->priceTable.push_back(tree[node]->priceTable[i-1]);
        }

        if(node!=0) continue;//return calculatePrice(k);
        else
        {
            int finalPrice = tree[0]->priceTable[0];
            for(i=0; i<k; i++)
            {
                if(finalPrice > tree[0]->priceTable[i]) finalPrice = tree[0]->priceTable[i];
            }
            return finalPrice;
        }
    }
    return -1;
}


int main(void)
{
    int numOfCaves, numOfPumps, i;
    pair<int, int> tmp;
    pair<int, int> tmp2;


    scanf("%d %d", &numOfCaves, &numOfPumps);

    vlozeno = (bool*)malloc(numOfCaves*sizeof(bool));
    for(i=0; i<numOfCaves; i++)
    {
        vlozeno[i] = false;
    }

    /*Konstrukce prislusneho poctu uzlu*/
    for(i=0; i<numOfCaves; i++)
    {
        Node * temp = new Node;
        tree.push_back(temp);
        temp->caveNum = i;
    }

    /*Pridavani hran do setu potomku*/
    for(i = 0; i<numOfCaves; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        tmp.first = b;
        tmp.second = c;
        tmp2.first = a;
        tmp2.second = c;
        tree[a]->offspring.insert(tmp);
        tree[b]->offspring.insert(tmp2);
        tree[a]->toPar = c;
        tree[b]->toPar = c;
    }

    /*Inicializace korene stromove struktury*/
    tree[0]->parent = -1;
    tree[0]->toPar = 0;
    tree[0]->depth = 0;


    repair.push(0);
    repairTree(numOfPumps);


/*
    Vypis stromove struktury
*/
/*
for(int i=0; i<numOfCaves; i++)
{
    printf("Jeskyne cislo %d, pocet potomku: %d, hloubka %d\n",(int)tree[i]->caveNum, (int)tree[i]->offspring.size(), (int)tree[i]->depth);
    for(set<pair<int,int> >::iterator it = tree[i]->offspring.begin(); it!=tree[i]->offspring.end(); ++it)
        printf("  %d(cena %d) ", it->first, it->second);
    printf("\n");
}
*/

    int price = calculatePrice(numOfPumps);
    printf("%d\n", price);

    for (i = 0; i<numOfCaves; i++)
        delete tree[i];

    free(vlozeno);
    return 0;
}
