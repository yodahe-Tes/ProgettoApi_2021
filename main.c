#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define strToINt(dig,buffer,resultFin)      while ((buffer)[(dig)] > '/'){  (resultFin) = ((resultFin) <<3) + ((resultFin)<<1 ) +(buffer)[(dig)] -'0';   (dig)++;}
#define MAX_BUF 2400
#define RED 0
#define BLACK 1
#define LUNG_MAX_STRING 2400
#define INFINITY 9999999

typedef struct nodo{
    int SomDistMin;
    int indiceGraf;
    struct nodo *left;
    struct nodo *right;
    struct nodo *parent;
    int color;
} nodo;

typedef struct Tree{
    nodo *root;
    nodo *nil;
} Tree;

typedef struct strPesi{
    int indice;
    int peso;
}strPesi
;

int dijkstra(int numVert,int G[numVert][numVert],int sorgente);

void rb_insert(Tree* T,int somDistMin,int indiceGraf );

void rb_insert_fixup(Tree* T, nodo * z);

void left_rotate( Tree* T,nodo* x );

void right_rotate(Tree* T,nodo *x);

void stampa(struct nodo* da_stampare);

void stampaCort(struct nodo* da_stampare,int maxDaStampare, int*stampati);

void buildMinHeap(strPesi stPesi[], int length);

void minHeapify(strPesi stPesi[], int i, int length);

void enqueue(strPesi stPesi[], int peso,int indice, int *dimPQ);

void swap(strPesi *str1, strPesi *str2);

void deQueue(strPesi stPesi[],int *dimPQ);

void sort(strPesi stPesi[], int dimQ);

int main() {

    //FILE *fp;
    //fp = fopen("input_1", "r");
    //if (fp == NULL) {
      //  perror("Unable to open file!");
       // exit(1);
    //}

    char *noNod, *lungcl;
    char buf[MAX_BUF];
    int numNodi,lungClassific;
    int grafIndex=0;

    nodo nil = { 0,  0,  NULL, NULL, NULL, BLACK};
    Tree* TdiGrad;
    Tree Tgrad;
    TdiGrad=& Tgrad;
    Tgrad.nil = &nil;
    Tgrad.root = &nil;

    char* buffer = (char *)malloc(sizeof(buf)+1);
    char *fgetsReturn1 = fgets(buffer, LUNG_MAX_STRING, stdin);
    if(fgetsReturn1!=NULL){};
    if (strncmp(buffer, "Topk\n", 1) == 0) {
        printf("\n");
        char *fgetsReturn2 = fgets(buffer, LUNG_MAX_STRING, stdin);
        if(fgetsReturn2!=NULL){};
    }
    noNod = strtok(buffer, " ");
    numNodi = atoi(noNod);
    lungcl = strtok(NULL, " ");
    lungClassific= atoi(lungcl);
    int  grafo[numNodi][numNodi];

    while (fgets(buffer, 100, stdin) != NULL  ) {

        if (strncmp(buffer, "TopK", 1) == 0) {
            if(grafIndex==0){
                printf("\n");
            }
            else{
                if (lungClassific < grafIndex){
                    int stampati=0;
                    stampaCort(TdiGrad->root,lungClassific,&stampati);
                }
                else{
                    stampa(TdiGrad->root);
                }
                printf("\n");
            }
        }
        else if (strncmp(buffer, "AggiungiGrafo\n", 1) == 0) {

            for (int i = 0; i < numNodi ; i++){
                int k=0;
                char *fgetsReturn3 = fgets(buffer, LUNG_MAX_STRING, stdin);
                if(fgetsReturn3){};
                int dig=0;
                int resultFin=0;
                strToINt(dig,buffer,resultFin)
                grafo[i][k]= resultFin;
                dig++;
                while(k < numNodi ){
                    k++;
                    resultFin=0;
                    strToINt(dig,buffer,resultFin)
                    grafo[i][k]= resultFin;
                    dig++;
                }
            }
            int sumOFDist = dijkstra(numNodi, grafo, 0);
            rb_insert(TdiGrad,sumOFDist,grafIndex);
            grafIndex++;
        }
    }
    free(buffer);
    //fclose(fp);

    return 0;
}


int dijkstra (int numVert, int G[numVert][numVert], int sorgente ){
    int dimQ=0;
    int u, uDist;
    strPesi Qpesi[numVert];
    for(int v=0; v < numVert; v++){
        for(int ed=0; ed < numVert; ed++){
            if(G[v][ed]==0)
                G[v][ed]=INFINITY;
        }
        enqueue(Qpesi, G[sorgente][v], v, &dimQ);
    }
    Qpesi[sorgente].peso=0;
    deQueue(Qpesi, &dimQ);

    while(dimQ > 0){
        int i=1;
        if(numVert>4)
            buildMinHeap(Qpesi,dimQ);
        else sort(Qpesi, dimQ);

        u=Qpesi[0].indice;
        uDist=Qpesi[0].peso;
        if(uDist <INFINITY){
            while(i < dimQ){
                int secRoute= uDist + G[u][Qpesi[i].indice];
                if(secRoute <= Qpesi[i].peso){
                    Qpesi[i].peso= secRoute;
                }
                i++;
            }
        }
        deQueue(Qpesi, &dimQ);
    }
    int sumOfDist =0;
    for(int v=0; v < numVert-1; v++)
        if(Qpesi[v].indice != sorgente )
        {
            if(Qpesi[v].peso >= INFINITY)
                Qpesi[v].peso=0;
            sumOfDist+=Qpesi[v].peso;
        }
    return sumOfDist;
}

void left_rotate( Tree* T,nodo* x ){
    struct nodo *y = x->right;
    x->right = y->left;

    if (y->left != T->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->nil) {
        T->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(Tree* T,struct nodo *x){
    nodo *y = x->left;
    x->left = y->right;
    if (y->right != T->nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == T->nil) {
        T->root = y;
    }
    else if (x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void rb_insert_fixup(Tree* T, nodo * z){

    struct nodo *y;
    if (z == T->root)
    {
        T->root->color= BLACK;
    }
    else
    {
        nodo* x = z->parent;
        if (x->color == RED)
        {
            if (x == x->parent->left)
            {

                y = x->parent->right;
                if (y->color == RED)
                {
                    x->color = BLACK;
                    y->color = BLACK;
                    x->parent->color = RED;
                    rb_insert_fixup(T,x->parent);
                }
                else
                {
                    if (z == x->right)
                    {
                        z = x;
                        left_rotate(T,z);
                        x = z->parent;
                    }
                    x->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(T,x->parent);
                }
            }
            else
            {
                y = x->parent->left;
                if (y->color == RED)
                {
                    x->color = BLACK;
                    y->color = BLACK;
                    x->parent->color = RED;
                    rb_insert_fixup(T,x->parent);
                }
                else
                {
                    if (z == x->left)
                    {
                        z = x;
                        right_rotate(T,z);
                        x = z->parent;
                    }
                    x->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(T,x->parent);
                }
            }
        }

    }
}

void rb_insert(Tree* T,int somDistMin,int indiceGraf ){

    struct nodo* z = (struct nodo*)malloc(sizeof(struct nodo));
    z->SomDistMin = somDistMin;
    z->indiceGraf = indiceGraf;
    z->left= NULL ;
    z->right= NULL;
    z->parent= NULL;
    z->color=RED;

    struct nodo *y = T->nil;
    struct nodo *x = T->root;

    while (x != T->nil)
    {
        y = x;
        if (z->SomDistMin < x->SomDistMin)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->SomDistMin<y->SomDistMin)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    rb_insert_fixup(T,z);
}


void stampa(nodo* da_stampare){
    if(da_stampare->right != NULL){
        stampa(da_stampare->left);
        printf(" %d",da_stampare->indiceGraf);
        stampa(da_stampare->right);
    }
}

void stampaCort(nodo* da_stampare, int maxDaStampare, int*stampati){

    if(da_stampare->right == NULL || *stampati >= maxDaStampare){
        return;
    }
    if(da_stampare->left != NULL){
        stampaCort(da_stampare->left,maxDaStampare,stampati);
    }
    if(*stampati < maxDaStampare){
        printf(" %d",da_stampare->indiceGraf);
        (*stampati)++;
    }
    stampaCort( da_stampare->right,maxDaStampare,stampati);
}

void enqueue(strPesi stPesi[], int peso,int indice,int* puntDimPQ)
{
    if (*puntDimPQ==0)
    {
        stPesi[0].indice= indice;
        stPesi[0].peso = peso;
        *puntDimPQ= *puntDimPQ+1;
    }
    else
    {
        stPesi[*puntDimPQ].peso = peso;
        stPesi[*puntDimPQ].indice= indice;
        *puntDimPQ= *puntDimPQ+1;
    }
}

void swap(strPesi *str1, strPesi *str2)
{
    strPesi temp = *str2;
    *str2 = *str1;
    *str1 = temp;
}

void deQueue(strPesi stPesi[],int* dimPQ)
{
    swap(&stPesi[0], &stPesi[*dimPQ - 1]);
    *dimPQ = *dimPQ-1;
}

void minHeapify(strPesi stPesi[], int i, int length){
    int lft= 2*i;
    int rgt= 2*i+1;
    int min;

    if (lft < length && stPesi[lft].peso < stPesi[i].peso)
        min = lft;
    else
        min=i;

    if (rgt< length && stPesi[rgt].peso< stPesi[min].peso)
        min=rgt;

    if (min!= i) {
        swap(&stPesi[i],&stPesi[min]);
        minHeapify(stPesi, min, length);
    }
}

void buildMinHeap(strPesi stPesi[], int length){

    for (int i= length/2; i>=0; i--) {
        minHeapify(stPesi, i, length);
    }
}

void sort(strPesi stPesi[], int dimQ){

    if (dimQ>1){
        if(stPesi[0].peso>stPesi[1].peso || (stPesi[0].peso==stPesi[1].peso&&stPesi[0].indice > stPesi[1].indice))
        swap(&stPesi[0],&stPesi[1]);
        if(dimQ>2){
            if(stPesi[1].peso>stPesi[2].peso || (stPesi[1].peso==stPesi[2].peso&&stPesi[1].indice > stPesi[2].indice))
                swap(&stPesi[1],&stPesi[2]);
        }
    }
}