#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <emscripten/emscripten.h>

#define GRID_SIZE 9
#define SUB_GRID 3
#define TOTAL_SQUARES 81
#define DIGITS "0123456789"


static int grid[GRID_SIZE][GRID_SIZE];
static int part_of_puzzle[GRID_SIZE][GRID_SIZE] = {0};


char *solution(char *problem);
static int min_col(int col);
static int min_row(int row);
static bool box_contains(int min_row, int min_col, int find);
static bool col_contains(int col, int find);
static bool row_contains(int row, int find);
static bool num_allowed(int row, int col, int num);
static bool fill_square(int row, int col);
static void load_puzzle(char *input_puzzle);
static void solve_puzzle();
static void *extract_solution(char *puzzle_solution);
static void clear_part_of_puzzle();


int main(void)
{
        printf("WASM Loaded\n");
        return EXIT_SUCCESS;
}


char EMSCRIPTEN_KEEPALIVE *solution(char *problem)
{
        load_puzzle(problem);
        solve_puzzle();
        clear_part_of_puzzle();
        return extract_solution(problem);
}


static void *extract_solution(char *puzzle_solution)
{
        for (int row = 0; row < GRID_SIZE; row++)
        {
            for (int col = 0; col < GRID_SIZE; col++)
            {
                puzzle_solution[row * GRID_SIZE + col] = DIGITS[grid[row][col]];
            }
        }
        puzzle_solution[TOTAL_SQUARES] = '\0';
        return puzzle_solution;
}


static void solve_puzzle()
{
        int row = 0;
        int col = 0;
        bool moving_forward = true;
        int current_square_num = row * GRID_SIZE + col;

        while (current_square_num < TOTAL_SQUARES)
        {
            if (part_of_puzzle[row][col])
            {
                if (moving_forward)
                {
                    col++;
                }
                else
                {
                    col--;
                }
            }
            else if (fill_square(row, col))
            {
                col++;
                moving_forward = true;
            }
            else
            {
                col--;
                moving_forward = false;
            }

            if (col >= GRID_SIZE)
            {
                row++;
                col = 0;
            }
            else if (col < 0)
            {
                if (row == 0)
                {
                    printf("Cannot solve puzzle!\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    row--;
                    col = GRID_SIZE - 1;
                }
            }
            current_square_num = row * GRID_SIZE + col;
        }
}


static void load_puzzle(char *input_puzzle)
{
        for (int row = 0; row < GRID_SIZE; row++)
        {
                for (int col = 0; col < GRID_SIZE; col++)
                {
                        int num = input_puzzle[row * GRID_SIZE + col] - '0';

                        if (num > 0)
                        {
                                part_of_puzzle[row][col] = 1;
                                
                        }
                        grid[row][col] = num;
                }
        }
}


static bool fill_square(int row, int col)
{
        int curr_num = grid[row][col];
        int first_try = curr_num;

        if (curr_num == 0)
        {
            first_try = 1;
        }

        for (int num = first_try; num <= GRID_SIZE; num++)
        {
            if (num_allowed(row, col, num))
            {
                grid[row][col] = num;
                return true;
            }
        }
        grid[row][col] = 0;
        return false;
}


static bool num_allowed(int row, int col, int num)
{
        int m_row = min_row(row);
        int m_col = min_col(col);

        if (!row_contains(row, num) &&
            !col_contains(col, num) &&
            !box_contains(m_row, m_col, num))
        {
            return true;
        }
        return false;
}


static bool row_contains(int row, int find)
{
        for (int col = 0; col < GRID_SIZE; col++)
        {
            if (grid[row][col] == find)
            {
                return true;
            }
        }
        return false;
}


static bool col_contains(int col, int find)
{
        for (int row = 0; row < GRID_SIZE; row++)
        {
            if (grid[row][col] == find)
            {
                return true;
            }
        }
        return false;
}


static bool box_contains(int min_row, int min_col, int find)
{
        int max_row = min_row + (GRID_SIZE / SUB_GRID);
        int max_col = min_col + (GRID_SIZE / SUB_GRID);

        for (int row = min_row; row < max_row; row++)
        {
            for (int col = min_col; col < max_col; col++)
            {
                if (grid[row][col] == find)
                {
                    return true;
                }
            }
        }
        return false;
}


static int min_col(int col)
{
        int min_col = 0;

        if (col >= 2 * SUB_GRID)
        {
            min_col = 2 * SUB_GRID;
        }
        else if (col >= SUB_GRID)
        {
            min_col = SUB_GRID;
        }
        return min_col;
}


static int min_row(int row)
{
        int min_row = 0;

        if (row >= 2 * SUB_GRID)
        {
            min_row = 2 * SUB_GRID;
        }
        else if (row >= SUB_GRID)
        {
            min_row = SUB_GRID;
        }
        return min_row;
}


static void clear_part_of_puzzle()
{
        for (int row = 0; row < GRID_SIZE; row++)
        {
                for (int col = 0; col < GRID_SIZE; col++)
                {
                        part_of_puzzle[row][col] = 0;
                }
        }
}
