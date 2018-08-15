#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "game.h"
#include <unistd.h>

#define DELAY 100 //100 ms delay by default

int usleep(useconds_t usec);

// Define the Cell matrix struct
// struct CellMatrix
// {
//     int rows; // number of rows
//     int cols; // number of columns
//     int** data; // a pointer to an array of n_rows pointers to rows; a row is an array
// };

// typedef struct CellMatrix CellMatrix;


int main()
{
    int x = 0;
    int choice = 1;
    struct CellMatrix *current;
    struct CellMatrix *future;
    struct CellMatrix *temp;
    init_display();
    printf("Please select the pattern from above three patterns: ");
    scanf("%d", &choice);
    switch(choice){
      case 1:{
        Initialize(&current,5,5);
        Initialize(&future,5,5);
        Initialize(&temp,5,5);
        break;
      }
      case 2:{
        Initialize(&current,10,10);
        Initialize(&future,10,10);
        Initialize(&temp,10,10);
        break;
      }
      case 3:{
        Initialize(&current,9,9);
        Initialize(&future,9,9);
        Initialize(&temp,9,9);
        break;
      }
      default:
      {
        printf("Wrong entry of choice \n");
        printf("Please run the code again and select the appropriate option!!!! \n");
        exit(0);
      }
    }
    patterns_initialize(&current, choice);
    initall();
    noecho(); // Don't echo any keypresses
    curs_set(FALSE); // Don't display a cursor
    while(1)
    {
        clear();
        print_matrix(current);
        refresh();
        x = increment_space_check(current);
        if(x)
            increment_space(&current);
        x = increment_space_check(current);
        life(&current, &future);
        transfer_data(&current, future);
        usleep(DELAY*1000);
    }
    getch();
    enditall();
    return 0;
}
