#include <stdio.h>
#include <stdlib.h>

struct openDay
{
    int d_i; /* poradovy den */
    long long int c_i; /* cena */
    int t_i; /* trvanlivost */
};

void getInput(struct openDay ** days, int d)
{
    int i;
    for(i=0; i<d; i++)
    {
        int d_i, c_i, t_i;
        struct openDay * temp = (struct openDay*)malloc(sizeof(struct openDay));
        scanf("%d %d %d", &d_i, &c_i, &t_i);
        temp->d_i = d_i;
        temp->c_i = c_i;
        temp->t_i = t_i;
        days[i] = temp;
    }
}

void printArr(struct openDay ** days, int d)
{
    int i;
    for(i=0; i<d; i++)
    {
        printf("%d %lld %d\n", days[i]->d_i, days[i]->c_i, days[i]->t_i);
    }
}

void swap(int a, int b, struct openDay ** h)
{
    struct openDay * temp;
    temp = h[a];
    h[a] = h[b];
    h[b] = temp;
}

void heapify(int i, struct openDay ** A, int heapSize)
{
    int l = 2*i;
    int r = 2*i+1;
    int smallest;
    if(l<heapSize && A[l]->d_i <= A[i]->d_i)
    {
        smallest = l;
    } else
    {
        smallest = i;
    }

    if(r<heapSize && A[r]->d_i <= A[smallest]->d_i)
    {
        smallest = r;
    }

    if(smallest != i)
    {
        swap(i, smallest, A);
        heapify(smallest, A, heapSize);
    }
}

void heapify2(int i, struct openDay ** A, int heapSize)
{
    int l = 2*i;
    int r = 2*i+1;
    int smallest;
    if(l<heapSize && A[l]->c_i <= A[i]->c_i)
    {
        smallest = l;
    } else
    {
        smallest = i;
    }

    if(r<heapSize && A[r]->c_i <= A[smallest]->c_i)
    {
        smallest = r;
    }

    if(smallest != i)
    {
        swap(i, smallest, A);
        heapify2(smallest, A, heapSize);
    }
}

void insertHeap(struct openDay ** A, struct openDay * val, int i)
{

    while((i>=1) && (A[i/2]->c_i > val->c_i))
    {
        A[i] = A[i/2];
        i = i/2;
    }
    A[i] = val;
}

void buildHeap(struct openDay ** h1, int d)
{
    int i;
    for(i = d/2; i >= 0; i--)
        heapify(i, h1, d);
}

void extractMin(struct openDay ** A, int size)
{
    if(size<1) return;
    A[0] = A[size-1];
    size-=1;
    heapify(0, A, size);
}

void extractMin2(struct openDay ** A, int size)
{
    if(size<1) return;
    free(A[0]);
    A[0] = A[size-1];
    size-=1;
    heapify2(0, A, size);
}

int main(void)
{
    int n, d, i, h1Size, h2Size, flag;
    long long int totalPrice;
    struct openDay ** h1;
    struct openDay ** h2;
    d=0;
    flag=1;
    h2Size=0;
    totalPrice=0;
    scanf("%d %d", &n, &d);
    h1Size = d;
    h1 = (struct openDay**)malloc(d*sizeof(struct openDay*));
    getInput(h1,d);
    h2 = (struct openDay**)malloc(d*sizeof(struct openDay*));
    buildHeap(h1, d);


    for(i=1; i<=n; i++)
    {
        if(h1Size !=0 && i==h1[0]->d_i) /*Pokud v nektery den otevre lekarna, pridame ji do druhe heapy*/
        {
            h2Size++;
            insertHeap(h2, h1[0], h2Size-1);
            if(h1Size>1) {h1[1]->c_i += h1[0]->c_i;}

            extractMin(h1, h1Size);
            h1Size--;
        }

        while(h2Size>0 && ((h2[0]->t_i+h2[0]->d_i) < i))
        {
            extractMin2(h2,h2Size);
            h2Size--;
        }

        if(h2Size>0)
        {
            totalPrice+=h2[0]->c_i;
        }
        else
        {
            printf("You will die at day %d\n",i);
            flag=0;
            break;
        }
    }
    if(flag)printf("%lld\n",totalPrice);

    for(i=0; i<h2Size; i++)
    {
        free(h2[i]);
    }
    free(h1);
    free(h2);
    return 0;
}

