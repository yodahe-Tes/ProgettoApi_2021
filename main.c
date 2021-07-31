#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_MAX_LINEE 1000

typedef struct Nodo{
    int a;
    char *info2;

} nodo;

typedef struct Arco{
    char info1;
    char info2;
} arco;

typedef struct Grafo{
    int indice;
    int nodo;
    int arco;
    int **peso;
} grafo;

typedef struct DistanzaNin{
    int numGrafo;
    int distMin;
} distanzaMIn;

void createGraph(char **lineaLetta);

int main() {



    FILE *fp;
    fp = fopen("input_1.txt", "r");/*apro file*/
    if (fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }
    char ** lines = NULL;
    char ** primaLinea;
    int num_linee = 0;
    int lungStrin =70 ;
    char buf[70];
    int numNodi;
    int lungClassif;

    //   if (fgets(buf, lungStrin, fp)!null){
    //       sscanf( %d %d,&a[0],&a[1])
    //  };

    primaLinea = (char **) malloc(N_MAX_LINEE * sizeof(char *));
     fgets(buf, lungStrin, fp);                                                          // while (fgets(buf, lungStrin, stdin)!=null;    per dopo quando usero input da stdinput
        primaLinea[0] = (char *)malloc(sizeof(buf)+1);
        strncpy(primaLinea[0], buf,70);


    char *noNod, *lungcl;

    noNod = strtok(primaLinea[0], " ");     //mi ritorna puntatore alla stringa
    printf(" numnodi is %s", noNod);
    numNodi = atoi(noNod);                      // converto stringa in int
    printf(" numnodi is now %d", numNodi);

    lungcl = strtok(NULL, " ");          // adesso in puntatore punta al prossimo token
    printf(" lungClassif is %s", lungcl);
    int lungClassific= atoi(lungcl);
    printf(" lungClassif is now %d", lungClassific);

    int distMin[lungClassific] ;


    lines = (char **) malloc(N_MAX_LINEE * sizeof(char *));
    while (fgets(buf, lungStrin, fp) != NULL) {      // while (fgets(buf, lungStrin, stdin)!=null;    per dopo quando usero input da stdinput
        if (strcmp(buf, "q\n") == 0) {

            break;
        }
        lines[num_linee] = (char *)malloc(sizeof(buf)+1);
        strncpy(lines[num_linee], buf,70);
        printf(" \nlines[%d] is %s", num_linee,lines[num_linee]);
        num_linee++;

    }

    printf(" \nlines[11] is %s", lines[10]);

    int numGrafi = (num_linee/(numNodi+1));
    printf(" \nnumGrafi is %d \n\n", numGrafi);

    char * richiesta;
    int pesi[numGrafi];
    for (int j = 0; j < num_linee; j++)  {
        sscanf(lines[j], "%s", richiesta);
        if (strncmp(richiesta, "AggiungiGrafo", 10) == 0) {
            for (int i = 0; j < numNodi ; j++)
            {scanf("%d,",&pesi[i]);
            }
    //        createGraph(lines[j],lines[j+1],lines[j+2],lines[j+3]);
        } else if (strncmp(richiesta, "TopK", 10) == 0) {
     //       printDistMIn();
        }
    }



    for(int i=0 ;i<numGrafi;i++){
        createGraph(lines);
    }



  //  graph gr[]




    for (int i = 0; i < num_linee; i++) {     //Forse deve essere   for int i=1 ... perche ho reso la prima linea null quando ho modificato con strtok
        free(lines[i]);
    }
    free(lines);

    fclose(fp);

    return 0;
}


void createGraph(char **lineaLetta){
    char *pesiDiNodi,*pesiDiNodi2,*pesiDiNodi3,*pesiDiNodi1;
    pesiDiNodi = strtok(lineaLetta[0], ",");     //mi ritorna puntatore alla stringa
    printf(" pesiDiNodi is %s", pesiDiNodi);
    int pesoDiNod1 = atoi(pesiDiNodi);

    pesiDiNodi1 = strtok(NULL, ",");          // adesso in puntatore punta al prossimo token
    printf(" pesiDiNod1 is %s", pesiDiNodi1);
    int pesiDiNod2= atoi(pesiDiNodi);

    pesiDiNodi2 = strtok(NULL, ",");          // adesso in puntatore punta al prossimo token
    printf(" pesiDiNod3 is %s", pesiDiNod2);
    int pesiDiNod3= atoi(pesiDiNodi);

    pesiDiNodi3 = strtok(NULL, ",");          // adesso in puntatore punta al prossimo token
    printf(" pesiDiNod4 is %s", pesiDiNod3);

};