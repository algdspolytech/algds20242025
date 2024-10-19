typedef struct {
  int size; // число вершин
  int **adj_list; // число связей, затем номера вершин, с которыми вершина связана
} graph_list;

typedef struct {
  int size;
  int *adj_matrix;
} graph_matrix;

int compare_lm(const graph_list *l, const graph_matrix *m);
graph_list parse_list(const char *file_name);
graph_matrix parse_matrix(const char *file_name);
void add_elemet_l(graph_list *l, int *el);
void add_element_m(graph_matrix *m, int *el);
void del_l(graph_list *l);
void del_m(graph_matrix *m);
