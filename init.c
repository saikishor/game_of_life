#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

int initall(void)
{
	initscr();
	return 0;
}; 
int enditall(void)
{
	endwin();
	return 0;	
}

// Init a cell matrix with zeros 
CellMatrix* Init_matrix(int n_rows, int n_cols) {
    struct CellMatrix* matrix = malloc(sizeof(CellMatrix));
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    int x = 0;
    int** data = malloc(sizeof(int*) * n_rows); 
    for(x = 0; x < n_rows; x++){
        data[x] = calloc(n_cols, sizeof(int));
    }
    matrix->data = data;
    return matrix;
}

void Initialize(struct CellMatrix **matrix_local, int n_rows, int n_cols) {
    struct CellMatrix* matrix = malloc(sizeof(CellMatrix));
    matrix = malloc(sizeof(CellMatrix));
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    int x = 0;
    int** data = malloc(sizeof(int*) * n_rows); 
    for(x = 0; x < n_rows; x++){
        data[x] = calloc(n_cols, sizeof(int));
    }
    matrix->data = data;
    *matrix_local = matrix;
    
}

void increment_space(CellMatrix **matrix0) {
    int new_rows = (*matrix0)->rows + 2;
    int new_cols = (*matrix0)->cols + 2;
    int x = 0, y = 0;
    struct CellMatrix *matrix = Init_matrix(new_rows, new_cols);
    for(x = 1; x < new_rows-1; x++) {
        for(y = 1; y < new_cols-1; y++) {
            matrix->data[x][y] = (*matrix0)->data[x-1][y-1];
        }
    }
    free(*matrix0);
    *matrix0 = matrix;
}

void transfer_data(CellMatrix **matrix_to, CellMatrix *matrix_from) {
    int new_rows = (matrix_from)->rows;
    int new_cols = (matrix_from)->cols;
    int x = 0, y = 0;
    struct CellMatrix *matrix = Init_matrix(new_rows, new_cols);
    for(x = 0; x < new_rows; x++) {
        for(y = 0; y < new_cols; y++) {
            matrix->data[x][y] = (matrix_from)->data[x][y];
        }
    }
    *matrix_to = matrix;
}

void print_matrix(CellMatrix* m) {
    int x = 0, y = 0;
    int row, col;
    int r_mid = (int)((m->rows)/2.0) + 1;
    int c_mid = (int)((m->cols)/2.0) + 1;
    getmaxyx(stdscr, row, col);
    row = row/2; col = col/2;
    for(x = 0; x < m->rows; x++) {
        for(y = 0; y < m->cols; y++) {\
            if (m->data[x][y] == 1)
            {
                mvprintw(x+row-r_mid,y+col-c_mid,"X");
            } 
        }
    }
}

int neighbours(int x, int y, struct CellMatrix *space)
{
    int count = 0, life = 0;
    int i = 0, j = 0;
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
            if((space->data[x+i][y+j] == 1) && (i!=0 || j!=0))
                count++;
    if(space->data[x][y] == 1)
    {
        if (count<2)
            life = 0;
        else if (count == 2 || count == 3)
            life = 1;
        else
            life = 0;
    }
    else
    {
        if (count==3 && (space->data[x][y] == 0))
        {
            life = 1;
        }
    }
    return life;
}

void life(struct CellMatrix **current, struct CellMatrix **future)
{
  struct CellMatrix *temp = Init_matrix((*current)->rows, (*current)->cols);
  int r = (*current)->rows, c = (*current)->cols;
    int i = 0, j = 0;
    for (i = 1; i < r-1; i++)
    {
        for (j = 1; j < c-1; j++)
        {
            temp->data[i][j] = neighbours(i,j,(*current));
        }
    }
    *future = temp;
}

int increment_space_check(struct CellMatrix *current)
{
    int check = 0, count = 0;
    int r = current->rows, c = current->cols;
    int i = 0, j = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < c; j++)
        {
          count = count + current->data[i][j] + current->data[i + r-2][j];
          if(count>0)
          {
            check = 1;
            return check;
          }
        }
    }
    i = 0; j = 0;
    if(count==0)
        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < r; i++)
            {
              count = count + current->data[i][j] + current->data[i][j+c-2];
              if(count>0)
              {
                check = 1;
                return check;
              }
            }
        }
    if(count>0)
      check = 1;
  return check;
}

void init_display(void)
{
    printf("\nWelcome! to the Conway's Game of Life");
    printf("\nA program that plays Game of Life on terminal irrespective of its size and shape\n");
    printf("\nBelow are the available three patterns to start with");
    printf("\n\n");
    int data[5][26]={{0}};
    // pattern 1
    data[2][2] = 1; data[2][1] = 1;
    data[1][2] = 1; data[1][3] = 1;
    data[3][2] = 1;

    //pattern 2
    data[2][7] = 1; data[2][8] = 1;
    data[3][8] = 1; data[1][13] = 1;
    data[3][13] = 1; data[3][12] = 1;
    data[3][14] = 1;

    //pattern 3
    data[1][19] = 1; data[3][18] = 1;
    data[3][19] = 1; data[2][21] = 1;
    data[3][22] = 1; data[3][23] = 1;
    data[3][24] = 1;

    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    {
        printf("\n");
        for (j = 0; j < 24; j++)
        {
            if (data[i][j]==1)
            {
                printf("X  ");
            }
            else
            {
                if ((j==5)|(j==16))
                    printf("|  ");
                else
                    printf("   ");
            }
        }
    }   
    printf("\n   Pattern 1 \t\t   Pattern 2 \t\t\t Pattern 3");
    printf("\n \n \n");
}

void patterns_initialize(struct CellMatrix **matrix_local, int pattern){
  switch(pattern){
    case 1: {
      (*matrix_local)->data[2][2] = 1; (*matrix_local)->data[2][1] = 1;
      (*matrix_local)->data[1][2] = 1; (*matrix_local)->data[1][3] = 1;
      (*matrix_local)->data[3][2] = 1;
      break;
    }
    case 2:{
      (*matrix_local)->data[2][1] = 1; (*matrix_local)->data[2][2] = 1;
      (*matrix_local)->data[3][2] = 1; (*matrix_local)->data[1][7] = 1;
      (*matrix_local)->data[3][7] = 1; (*matrix_local)->data[3][6] = 1;
      (*matrix_local)->data[3][8] = 1;
      break;
    }
    case 3:{
      (*matrix_local)->data[1][2] = 1; (*matrix_local)->data[3][1] = 1;
      (*matrix_local)->data[3][2] = 1; (*matrix_local)->data[2][4] = 1;
      (*matrix_local)->data[3][5] = 1; (*matrix_local)->data[3][6] = 1;
      (*matrix_local)->data[3][7] = 1;
      break;
    }
  }
}
    