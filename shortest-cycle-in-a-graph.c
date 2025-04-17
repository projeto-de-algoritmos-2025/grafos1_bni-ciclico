typedef struct no {
    int v;
    struct no* prox;
} no;

typedef struct fila {
    no *head, *tail;
} fila;

fila* cria_fila(void) {
	fila *nova_fila = malloc(sizeof(fila));
	if (nova_fila == NULL) return NULL;
	nova_fila->head = NULL;
	nova_fila->tail = NULL;
	return nova_fila;
}

int enfila(fila *h, int e) {
	no *novo = malloc(sizeof(no));
	if (novo == NULL) return 0;
	novo->v = e;
	if (h->tail == NULL) h->head = novo;
	else h->tail->prox = novo;
	novo->prox = NULL;
	h->tail = novo;
	return 1;
}

no* desenfila(fila *h) {
	if (h->head == NULL) return 0;
	no *aux = h->head;
	h->head = h->head->prox;
	if (h->head == NULL) h->tail = NULL;
	return aux;
}

int fila_vazia(fila *h) {
	return h->head == NULL;
}

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
    g->adj[v] = insere_lista(g->adj[v], u);
}

int bfs(grafo *g, int src, int n) {
    fila *f = cria_fila();
    int visitado[n], distancia[n], pai[n], menor_dist = 2000;
    for (int i=0;i<n;i++) visitado[i] = 0;
    for (int i=0;i<n;i++) pai[i] = -1;
    distancia[src] = 0;
    enfila(f, src);
    visitado[src] = 1;
    while (!fila_vazia(f)) {
        no *u = desenfila(f);
        no *aux = g->adj[u->v];
        while (aux != NULL) {
            if (visitado[aux->v] == 0) {
                visitado[aux->v] = 1;
                distancia[aux->v] = distancia[u->v]+1;
                pai[aux->v] = u->v;
                enfila(f,aux->v);
            } else if (pai[aux->v] != u->v && pai[u->v] != aux->v){
                int dist_temp = distancia[aux->v] + distancia[u->v] + 1;
                if (dist_temp < menor_dist) menor_dist = dist_temp;
            }
            aux = aux->prox;
        }
    }
    return menor_dist;
}

int findShortestCycle(int n, int** edges, int edgesSize, int* edgesColSize) {
    grafo *g = cria_grafo(n);
    int min_cycle = 2000;
    for (int i=0;i<edgesSize;i++) insere_aresta(g, edges[i][0], edges[i][1]);
    for (int i=0;i<n;i++) {
        int menor = bfs(g, i, n);
        if (menor < min_cycle) min_cycle = menor;
    }

    if (min_cycle == 2000) return -1;
    return min_cycle;
}
