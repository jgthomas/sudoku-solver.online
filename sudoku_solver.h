#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

void solve_puzzle(Grid *puzzle);
void delete_puzzle(Grid *puzzle);
bool fill_square(Grid *puzzle, int row, int col);
int min_row(Grid *puzzle, int row);
int min_col(Grid *puzzle, int col);
bool box_contains(Grid *puzzle, int min_row, int min_col, int find);
bool col_contains(Grid *puzzle, int col, int find);
bool row_contains(Grid *puzzle, int row, int find);
bool num_allowed(Grid *puzzle, int row, int col, int num);
Square *make_square(int num, bool part_of_puzzle);

#endif
