#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "unistd.h"
#include <ncurses.h>


void display_grid(int** grid, int rows, int cols) {

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			if (grid[row][col] == 1) {
			  attron(COLOR_PAIR(1));
			  mvaddch(row, col, ' ');
			  attroff(COLOR_PAIR(1));
			} else {
			  attron(COLOR_PAIR(2));
			  mvaddch(row, col, ' ');
			  attroff(COLOR_PAIR(2));
			}		
		}
	}
}

int count_nbs(int** grid, int row, int col, int rows, int cols) {
    int count = 0;
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if (r == row && c == col) continue; 
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                count += grid[r][c]; 
            }
        }
    }
    return count;
}


int** init_grid(int rows, int cols) {
	int** arrays = malloc(rows*sizeof(int*));
	for (int i = 0; i < rows; ++i) {
		arrays[i] = calloc(cols, sizeof(int));
	}
	return arrays;
}

void random_grid(int** arrays, int rows, int cols) {
	srand(time(NULL));
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			int random = rand();
			arrays[row][col] = random % 2;
		}
	}
}

int** update_grid(int** arrays, int rows, int cols) {
	int** new = init_grid(rows, cols);
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			int nbs = count_nbs(arrays, row, col, rows, cols);
			if (arrays[row][col] == 1) {
				new[row][col] = (nbs == 2 || nbs == 3 ) ? 1 : 0;
			} else {
				new[row][col] =  (nbs == 3) ? 1 : 0;
			}
		}
	}
	for (int i = 0; i < rows; ++i) {
		free(arrays[i]);
	}
	free(arrays);
	return new;
}

int main() {
	int rows = 128, cols = 236;
	int** grid = init_grid(rows, cols);
	random_grid(grid, rows, cols);

	initscr();
	noecho();
	curs_set(FALSE);
	timeout(1000);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	while(1) {

	  display_grid(grid, rows, cols);
	  refresh();
	  
	  grid = update_grid(grid, rows, cols);

	  refresh();
	  usleep(72500);
	}

	endwin();
	return 0;
}
