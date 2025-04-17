/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
typedef struct no {
    int v;
    struct no* prox;
} no;

typedef struct grafo {
    no **adj;
    int n;
} grafo;

grafo* cria_grafo (int n) {
    grafo *g = malloc(sizeof(grafo));
    g->n = n;
    g->adj = calloc(n, sizeof(no*));
    return g;
}

no* insere_lista(no *lista, int v) {
    no *novo = malloc(sizeof(no));
    novo->v = v;
    novo->prox = lista;
    lista = novo;
    return lista;
}

void insere_aresta(grafo *g, int u, int v) {
    g->adj[u] = insere_lista(g->adj[u], v);
}

bool ordenacao_topologica(grafo *g, int k, int *ordem) {
    int contador[k];
    no *candidato = NULL;
    for (int i=0;i<k;i++) contador[i] = 0;
	for (int i=0;i<k;i++) {
		no *aux = g->adj[i];
		while (aux != NULL) {
			contador[aux->v]++;
            aux = aux->prox;
		}
	}
    for (int i=0;i<k;i++)
        if (contador[i] == 0) candidato = insere_lista(candidato, i);

    for (int i=0;i<k;i++) {
        if (candidato == NULL) return false;
        ordem[i] = candidato->v;
        candidato = candidato->prox;
        no *aux = g->adj[ordem[i]];
        while (aux!=NULL) {
            contador[aux->v]--;
            if (contador[aux->v] == 0) candidato = insere_lista(candidato, aux->v);
            aux = aux->prox;
        }
    }
    return true;
}

int** buildMatrix(int k, int** rowConditions, int rowConditionsSize, int* rowConditionsColSize, int** colConditions, int colConditionsSize, int* colConditionsColSize, int* returnSize, int** returnColumnSizes) {
    grafo *lin = cria_grafo(k), *col = cria_grafo(k);
    int **matrix = malloc(k*sizeof(int*));
    int topologiaLin[k], topologiaCol[k];

    for (int i=0;i<k;i++) matrix[i] = malloc(k*sizeof(int));
    for (int i=0;i<rowConditionsSize;i++) insere_aresta(lin, rowConditions[i][0]-1, rowConditions[i][1]-1);
    for (int i=0;i<colConditionsSize;i++) insere_aresta(col, colConditions[i][0]-1, colConditions[i][1]-1);

    if (!ordenacao_topologica(lin, k, topologiaLin) || !ordenacao_topologica(col, k, topologiaCol)) {
        *returnSize = 0;
        return matrix;
    }

    for (int i=0;i<k;i++) {
        for (int ii=0; ii<k;ii++) {
            if (topologiaLin[i] == topologiaCol[ii]) matrix[i][ii] = topologiaCol[ii]+1;
            else matrix[i][ii] = 0;
        }
    }

    *returnSize = k;
    *returnColumnSizes = malloc(k*sizeof(int));
    for (int i=0;i<k;i++) (*returnColumnSizes)[i] = k;
    return matrix;
}
