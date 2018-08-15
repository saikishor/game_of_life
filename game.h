struct CellMatrix
{
    int rows; // number of rows
    int cols; // number of columns
    int** data; // a pointer to an array of n_rows pointers to rows; a row is an array
};
typedef struct CellMatrix CellMatrix;
int initall(void);
int enditall(void);
CellMatrix Init_matrix(int, int);
void Initialize(struct CellMatrix **, int, int);
void increment_space(struct CellMatrix **);
void transfer_data(struct CellMatrix **,struct CellMatrix *);
void print_matrix(struct CellMatrix *);
int neighbours(int, int, struct CellMatrix *);
void life(struct CellMatrix **, struct CellMatrix *);
int increment_space_check(struct CellMatrix *);
void init_display(void);
void patterns_initialize(struct CellMatrix **, int);

