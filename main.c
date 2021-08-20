#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_MAX_LINEE 150000
#define MAX_BUF 2500
#define MAXGRAF 1500
#define LUNG_MAX_STRING 2500
#define INFINITY 9999999

typedef struct DistanzaMin{
    int indiceGraf;
    int SomDistMin;
    int graduatoria;
} strDistMin;

int left(int i){
    return 2*i;
}

int right(int i){
    return 2*i+1;
}


void maxHeapify(strDistMin arrStrDist[], int i, int length){
    int l= left(i);
    int r= right(i);
    int tmp,tmp2;
    int max;
    if ((l <= length) && (arrStrDist[l].SomDistMin > arrStrDist[i].SomDistMin))
        max = l;
    else
        max=i;

    if ((r<= length) && (arrStrDist[r].SomDistMin > arrStrDist[max].SomDistMin))
        max=r;

    if (max!= i) {
        tmp=arrStrDist[i].SomDistMin;
        tmp2=arrStrDist[i].indiceGraf;
        arrStrDist[i].SomDistMin=arrStrDist[max].SomDistMin;
        arrStrDist[i].indiceGraf=arrStrDist[max].indiceGraf;

        arrStrDist[max].SomDistMin=tmp;
        arrStrDist[max].indiceGraf=tmp2;

        maxHeapify(arrStrDist, max, length);
    }
}

void buildMaxHeap(strDistMin arrStrDist[], int length){

    for (int i= length/2; i>=0; i--) {
        maxHeapify(arrStrDist, i, length);
    }
}

void heapsort(strDistMin arrStrDist[], int length){
    buildMaxHeap(arrStrDist, length);
    for (int i= length; i>0; i--) {
        int tmp=arrStrDist[i].SomDistMin;
        int tmp2=arrStrDist[i].indiceGraf;
        arrStrDist[i].SomDistMin=arrStrDist[0].SomDistMin;
        arrStrDist[i].indiceGraf=arrStrDist[0].indiceGraf;
        arrStrDist[0].SomDistMin=tmp;
        arrStrDist[0].indiceGraf=tmp2;
        length--;
        maxHeapify(arrStrDist, 0, length);
    }
}

int dijkstra (int numVert, int G[numVert][numVert], int sorgente ){
    int dist[numVert];
    int visited[numVert],adj=0;

    for(int vr=0; vr < numVert; vr++){
        for(int ed=0; ed < numVert; ed++){
            if(G[vr][ed]==0)
                G[vr][ed]=INFINITY;
        }
        dist[vr]=G[sorgente][vr];
        visited[vr]=0;
    }
    dist[sorgente]=0;
    visited[sorgente]=1;

    int shortestpath;
    for(int passo=1; passo < numVert - 1; passo++)
    {
        shortestpath=INFINITY;
        for(int v=0; v < numVert; v++)
            if(shortestpath >= dist[v] && visited[v] == 0)
            {
                shortestpath=dist[v];
                adj=v;
            }
        visited[adj]=1;
            for(int v=0; v < numVert; v++)
                if(visited[v]==0 && dist[v] > shortestpath + G[adj][v])
                    dist[v]= shortestpath + G[adj][v];
    }
    int sumOfDist =0;
    for(int v=0; v < numVert; v++)
        if(v!=sorgente)
        {
            if(dist[v]==INFINITY)
                dist[v]=0;
            sumOfDist+=dist[v];
        }
    return sumOfDist;
}


int main() {

    //FILE *fp;
    //fp = fopen("input_3", "r");
    //if (fp == NULL) {
    //    perror("Unable to open file!");
    //    exit(1);
    //}

    char ** lines ;
    char *primaLinea;
    int num_linee = 0;
    int lungStrin =LUNG_MAX_STRING ;
    char buf[MAX_BUF];
    int numNodi;
    int lungClassific;


                                                             // while (fgets(buf, lungStrin, stdin)!=null;    per dopo quando usero input da stdinput
    primaLinea = (char *)malloc(sizeof(buf)+1);
    char *fgetsReturn1 = fgets(primaLinea, lungStrin, stdin);
            if(fgetsReturn1!=NULL){};                                                 // scanf("%s",&primaLinea);
                                                                   //strncpy(primaLinea, buf,MAX_BUF+1);
    if (strncmp(primaLinea, "Topk\n", LUNG_MAX_STRING) == 0) {
        printf("\n");
        char *fgetsReturn2 = fgets(primaLinea, lungStrin, stdin);                                                          // while (fgets(buf, lungStrin, stdin)!=null;    per dopo quando usero input da stdinput
        if(fgetsReturn2!=NULL){};                                           // scanf("%s",&primaLinea);
                                                             //strncpy(primaLinea, buf,MAX_BUF);
    }
    char *noNod, *lungcl;
    noNod = strtok(primaLinea, " ");
    numNodi = atoi(noNod);
    lungcl = strtok(NULL, " ");
    lungClassific= atoi(lungcl);
    lines = (char **) malloc(N_MAX_LINEE * sizeof(char *));


    while (fgets(buf, lungStrin, stdin) != NULL) {                   // while (fgets(buf, lungStrin, stdin)!=null;    per dopo quando usero input da stdinput
        lines[num_linee] = (char *)malloc(sizeof(buf)+1);
        strncpy(lines[num_linee], buf,MAX_BUF);
        num_linee++;
    }

    int  grafo[numNodi][numNodi];
    char *richiesta;
    int numIndDaStampare;
    int grafIndex=0;
    strDistMin ArrStrdistMIn[MAXGRAF];
    ArrStrdistMIn->indiceGraf=0;
    ArrStrdistMIn->SomDistMin=0;
    int j=0;
    while(j<num_linee){
        richiesta = lines[j];
        if (strncmp(richiesta, "TopK", LUNG_MAX_STRING) == 0||strncmp(richiesta, "TopK\n", LUNG_MAX_STRING) == 0) {
            if(grafIndex==0){
                printf("\n");
            }
            else{
                heapsort(ArrStrdistMIn, grafIndex - 1);
                if (lungClassific > grafIndex)
                    numIndDaStampare=grafIndex;
                else
                    numIndDaStampare=lungClassific;

                for (int i = 0; i < numIndDaStampare; i++){
                    printf(" %d",ArrStrdistMIn[i].indiceGraf);
                }
                printf("\n");
            }
            j++;
        }
        else if (strncmp(richiesta, "AggiungiGrafo\n", LUNG_MAX_STRING) == 0) {

            for (int i = 0; i < numNodi ; i++){
                j++;
                int k=0;
                char *stringPesi = strtok(lines[j], ",");
                int peso= atoi(stringPesi);
                grafo[i][k]=peso;
                while(stringPesi != NULL && k < numNodi ){
                    k++;
                    stringPesi = strtok(NULL, ",");
                    if(stringPesi != NULL){
                        peso= atoi(stringPesi);
                        grafo[i][k]=peso;
                    }
                }
            }
            int sumOFDist = dijkstra(numNodi, grafo, 0);
            //printf("\n%d",sumOFDist);
            ArrStrdistMIn[grafIndex].indiceGraf=grafIndex;
            ArrStrdistMIn[grafIndex].SomDistMin=sumOFDist;
            ArrStrdistMIn[grafIndex].graduatoria=grafIndex;

            grafIndex++;
            j++;
        }

    }
    for (int i = 0; i < num_linee; i++) {
        free(lines[i]);
    }
    free(primaLinea);
    free(lines);
    //fclose(fp);
    //printf("\nho finito\n\n");
    return 0;
}



