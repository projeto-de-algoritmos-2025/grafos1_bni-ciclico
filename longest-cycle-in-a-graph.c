void dfs(int node, int* edges, int* visited, int* stack, int* distance, int* llength, int currentDistance) {
	if (node == -1) return;
	if (stack[node]) {
		*llength = (currentDistance - distance[node] > *llength) ? (currentDistance - distance[node]) : *llength;
		return;
	}
	if (visited[node]) return;
	visited[node] = 1;
	stack[node] = 1;
	distance[node] = currentDistance;
	dfs(edges[node], edges, visited, stack, distance, llength, currentDistance + 1);
	stack[node] = 0;
}

int longestCycle(int* edges, int edgesSize) {
	int* visited = (int*)calloc(edgesSize, sizeof(int));
	int* stack = (int*)calloc(edgesSize, sizeof(int));
	int* distance = (int*)calloc(edgesSize, sizeof(int));
	int llength = -1;
	for (int i = 0; i < edgesSize; i++)
		if (!visited[i])
			dfs(i, edges, visited, stack, distance, &llength, 0);
	free(visited);
	free(stack);
	free(distance);
	return llength;
}
