#include <stdio.h>
#include <stdlib.h>

#include "Grafo.h"
#include "../Cap3/Utils.h"

int comparaVertice(void *info1, void *info2){

    pVertice v1 = (pVertice) info1;
    pVertice v2 = (pVertice) info2;

    int *id1 = (int *) v1->info;
    int *id2 = (int *) v2->info;

    return *id2 - *id1;
}

/* ----------------------------- */
void imprimeAdjacencia(void *info1){
    pVertice v = (pVertice) info1;
    printf("%d - " , *((int *)(v->info)));
}

/* ----------------------------- */
void imprimeVertice(void *info1){
    pVertice v = (pVertice) info1;
    printf("\nVertice %d - Adjacencias [", *((int *)v->info));

    imprimirLista(v->listaAdjacencias, imprimeAdjacencia);
    printf("]\n");
}

/* ----------------------------- */
void imprimeVerticeSemAdjacencias(void *info1){
    pVertice v = (pVertice) info1;
    printf("\nVertice %d - ", *((int *)v->info));
}

/* ---------------------------------------- */
void* alocaInfoVertice(void *info){
   pVertice pv = (pVertice) malloc(sizeof(Vertice));
   pv->info = alocaInfoInt(((pVertice)info)->info);
   return pv;
}
void imprimeVerticeLargura(void *info1) {
    pVertice v = (pVertice)info1;
    printf("%d ", *((int *)v->info));
}
/* ----------------------------- */
void main(){

    int vertices[] = {1,2,3,4,5};

    int opcao, vOrigem, vDestino;
    int *pv;

    pDGrafo grafo = criarGrafo();

    do{
        printf("\n 0  - Criar grafo \n");
        printf("  1  - Incluir Vertice \n");
        printf("  2  - Incluir Aresta \n");
        printf("  3  - Excluir Vertice  \n");
        printf("  4  - Excluir Aresta   \n");
        printf("  5  - Mostrar grafo \n");
        printf("  6  - Busca em profundidade \n");
        printf("  7  - Busca em amplitude \n");
        printf("  8  - Existe caminho?  (entre dois vertices) \n");
        printf("  9  - Encontra caminho (entre dois vertices) \n");
        printf("10 - Sair \n");

        scanf ("%d", &opcao);

        switch (opcao){

         case 0 :
            incluirVertice(grafo, &vertices[0], comparaVertice);
            incluirVertice(grafo, &vertices[1], comparaVertice);
            incluirVertice(grafo, &vertices[2], comparaVertice);
            incluirVertice(grafo, &vertices[3], comparaVertice);
            incluirVertice(grafo, &vertices[4], comparaVertice);

            incluirAresta(grafo, &vertices[0], &vertices[1], comparaVertice);
            incluirAresta(grafo, &vertices[1], &vertices[3], comparaVertice);
            incluirAresta(grafo, &vertices[2], &vertices[3], comparaVertice);
            incluirAresta(grafo, &vertices[2], &vertices[4], comparaVertice);
            incluirAresta(grafo, &vertices[3], &vertices[4], comparaVertice);
            incluirAresta(grafo, &vertices[4], &vertices[1], comparaVertice);

            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 1 :

            pv = (int *)malloc(sizeof(int));
            printf ("ID do v�rtice : ");
            scanf("%d", pv);
            incluirVertice(grafo, pv, comparaVertice);

            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 2 :

            printf ("\nID do v�rtice origem : ");
            scanf("%d", &vOrigem);
            printf ("\nID do v�rtice destino : ");
            scanf("%d", &vDestino);
            incluirAresta(grafo, &vOrigem, &vDestino, comparaVertice);

            mostrarGrafo(grafo,imprimeVertice);
            getch();
            break;

        case 3:
            printf("ID do v�rtice a ser exclu�do: ");
            scanf("%d", &vOrigem);

            excluirVertice(grafo, &vOrigem, comparaVertice);

            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 4:
            printf("\nID do v�rtice origem : ");
            scanf("%d", &vOrigem);
            printf("\nID do v�rtice destino : ");
            scanf("%d", &vDestino);
            excluirAresta(grafo, &vOrigem, &vDestino, comparaVertice);

            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 5 :
            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 6 :
            buscaEmProfundidade(grafo, comparaVertice, imprimeVerticeSemAdjacencias);
            getch();
            break;

        case 7:
                // Come�a a busca em amplitude a partir do primeiro v�rtice
                if (grafo->listaVertices->primeiro != NULL) {
                    buscaAmplitude(grafo, comparaVertice, imprimeVerticeLargura);
                } else {
                    printf("O grafo est� vazio!\n");
                }
                getch();
                break;
        case 8 :
            printf ("\nID do v�rtice origem : ");
            scanf("%d", &vOrigem);
            printf ("\nID do v�rtice destino : ");
            scanf("%d", &vDestino);

            int result = existeCaminho(grafo, &vOrigem, &vDestino, comparaVertice);
            // existe um caminho
            if (result != 0)
                printf("Existe caminho!");
            else
                printf("N�o existe caminho!");

            getch();
            break;
        case 9 :
            printf ("\nID do v�rtice origem : ");
            scanf("%d", &vOrigem);
            printf ("\nID do v�rtice destino : ");
            scanf("%d", &vDestino);

            pDLista caminho = getCaminho(grafo, &vOrigem, &vDestino, comparaVertice, alocaInfoVertice);
            if (caminho->quantidade > 0){
                printf("\n Existe um caminho: ");
                imprimirLista(caminho, imprimeVerticeSemAdjacencias);
            }
            else
                printf("\n *** N�O existe um caminho. *** ");

            getch();
            break;
        }

    }while (opcao != 10);

}
