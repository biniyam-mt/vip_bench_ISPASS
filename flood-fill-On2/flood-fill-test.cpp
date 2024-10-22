#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>

#include "utils.h"

#define M 10
#define N 10

using namespace std;

struct color
{
    int color_type;
    // write in percent [Eg: For half coverage, write 50 and not 0.5]
    int coverage;
};

/**
 * @brief Print an mXn matrix in a formatted way
 *
 * @param matrix
 * @param m
 * @param n
 */

void printMatrix(int **matrix, int m, int n)
{
    if (matrix)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                string color = "\033[1;3" + to_string(matrix[i][j]) + "m";
                cout << color << setw(3) << matrix[i][j] << "\033[0m";
            }
            cout << endl;
        }
    }
}

/**
 * @brief Sets all values of the mXn matrix to zero
 *
 * @param matrix
 * @param m
 * @param n
 */

void zeroMatrix(int **matrix, int m, int n)
{
    if (matrix)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Checks if the coverage set for each color is greater than 0 and adds up to 100%
 *
 * @param colors
 * @return true
 * @return false
 */
bool isCoverageCorrect(vector<color> colors)
{
    bool coverage = false;
    int total_coverage = 0;
    for (int i = 0; i < (int)colors.size(); i++)
    {
        total_coverage += colors[i].coverage;
    }

    if (total_coverage > 0 && total_coverage <= 100)
    {
        coverage = true;
    }

    return coverage;
}

/**
 * @brief Generate a vector of colors with random coverage
 *
 * @param num_color
 * @return vector<color>
 */
vector<color> getRandomColors(int num_color = 0)
{
    int color_count = num_color == 0 ? myrand() % 10 : num_color;
    vector<color> colors(color_count);

    int total_coverage = 0;

    for (int j = 0; j < (int)colors.size(); j++)
    {

        if (total_coverage >= 100)
            break;

        bool not_set = true;
        while (not_set)
        {
            int percent = myrand() % 50;
            if (percent > 0 && total_coverage + percent <= 100)
            {
                colors[j] = {j + 1, percent};
                total_coverage += percent;
                not_set = false;
            }
        }
    }

    return colors;
}

/**
 * @brief Generates an mXn matrix based on the given vector of colors in a random way
 *
 * @param matrix
 * @param colors
 * @param m
 * @param n
 */
void produceColorMatrix(int **matrix, vector<color> colors, int m, int n)
{
    if (!isCoverageCorrect(colors))
    {
        cerr << endl
             << "Error: Please check that the coverage of your color matrix is greater than 0 & less than or equal to 100." << endl
             << endl;
        return;
    }

    zeroMatrix(matrix, m, n);

    int max = m * n;

    for (int i = 0; i < (int)colors.size(); i++)
    {
        color current_color = colors[i];
        int paint_coverage = ceil((current_color.coverage * max / 100));
        int my_color = current_color.color_type;

        for (int j = 0; j < paint_coverage; j++)
        {

            bool not_found = true;

            while (not_found)
            {
                int index = myrand() % max;

                int row = index / m;
                int col = index % n;
                if ((matrix[row][col]) == 0)
                {
                    matrix[row][col] = my_color;
                    not_found = false;
                }
            }
        }
    }
}

/**
 * @brief Generates an mXn color matrix in a horizontal diagonal pattern
 *
 * @param matrix
 * @param colors
 * @param m
 * @param n
 */
void produceHorizontalDiagonalPattern(int **matrix, vector<color> colors, int m, int n)
{
    if (!isCoverageCorrect(colors))
    {
        cerr << endl
             << "Error: Please check that the coverage of your colors is greater than 0 & less than or equal to 100." << endl
             << endl;
        return;
    }

    zeroMatrix(matrix, m, n);

    int max = ceil((m * n) / 2);
    int row = 0, col = 0;

    for (int i = 0; i < (int)colors.size(); i++)
    {
        color current_color = colors[i];
        int paint_coverage = ceil((current_color.coverage * max / 100));
        int my_color = current_color.color_type;

        for (int j = 0; j < paint_coverage; j++)
        {

            if (col >= n)
            {
                row++;
                if (row >= m)
                {
                    break;
                }
                if (row % 2 == 0)
                {
                    col = 0;
                }
                else
                {
                    col = 1;
                }
            }

            matrix[row][col] = my_color;
            col += 2;
        }
    }
}

/**
 * @brief Generates an mXn color matrix in a vertical diagonal pattern
 *
 * @param matrix
 * @param colors
 * @param m
 * @param n
 */
void produceVerticalDiagonalPattern(int **matrix, vector<color> colors, int m, int n)
{
    if (!isCoverageCorrect(colors))
    {
        cerr << endl
             << "Error: Please check that the coverage of your colors is greater than 0 & less than or equal to 100." << endl
             << endl;
        return;
    }

    zeroMatrix(matrix, m, n);

    int max = ceil((m * n) / 2);
    int row = 0, col = 0;

    for (int i = 0; i < (int)colors.size(); i++)
    {
        color current_color = colors[i];
        int paint_coverage = ceil((current_color.coverage * max / 100));
        int my_color = current_color.color_type;

        for (int j = 0; j < paint_coverage; j++)
        {

            if (row >= m)
            {
                col++;
                if (col >= n)
                {
                    break;
                }
                if (col % 2 == 0)
                {
                    row = 0;
                }
                else
                {
                    row = 1;
                }
            }

            matrix[row][col] = my_color;
            row += 2;
        }
    }
}

/**
 * @brief Generates an mXn color matrix with mixed colors in a horizontal diagonal pattern
 *
 * @param matrix
 * @param colors
 * @param m
 * @param n
 */
void produceRandomHorizontalDiagonalPattern(int **matrix, vector<color> colors, int m, int n)
{
    if (!isCoverageCorrect(colors))
    {
        cerr << endl
             << "Error: Please check that the coverage of your colors is greater than 0 & less than or equal to 100." << endl
             << endl;
        return;
    }

    zeroMatrix(matrix, m, n);

    int max = ceil((m * n) / 2);
    int row = myrand() % (m), col;

    if (row % 2 == 0)
    {
        col = 0;
    }
    else
    {
        col = 1;
    }

    for (int i = 0; i < (int)colors.size(); i++)
    {
        color current_color = colors[i];
        int paint_coverage = ceil((current_color.coverage * max / 100));
        int my_color = current_color.color_type;

        for (int j = 0; j < paint_coverage; j++)
        {
            if (col >= n)
            {
                bool not_set = true;

                while (not_set)
                {
                    row = myrand() % (m);

                    if (row % 2 == 0)
                    {
                        if (matrix[row][0] == 0)
                        {
                            not_set = false;
                            col = 0;
                        }
                    }
                    else
                    {
                        if (matrix[row][1] == 0)
                        {
                            not_set = false;
                            col = 1;
                        }
                    }
                }
            }

            matrix[row][col] = my_color;
            col += 2;
        }
    }
}
/**
 * @brief Generates an mXn color matrix with mixed colors in a vertical diagonal pattern
 *
 * @param matrix
 * @param colors
 * @param m
 * @param n
 */
void produceRandomVerticalDiagonalPattern(int **matrix, vector<color> colors, int m, int n)
{
    if (!isCoverageCorrect(colors))
    {
        cerr << endl
             << "Error: Please check that the coverage of your colors is greater than 0 & less than or equal to 100." << endl
             << endl;
        return;
    }

    zeroMatrix(matrix, m, n);

    int max = ceil((m * n) / 2);
    int row, col = myrand() % (n);

    if (col % 2 == 0)
    {
        row = 0;
    }
    else
    {
        row = 1;
    }

    for (int i = 0; i < (int)colors.size(); i++)
    {
        color current_color = colors[i];
        int paint_coverage = ceil((current_color.coverage * max / 100));
        int my_color = current_color.color_type;

        for (int j = 0; j < paint_coverage; j++)
        {
            if (row >= m)
            {

                bool not_set = true;
                while (not_set)
                {
                    col = myrand() % (n);

                    if (col % 2 == 0)
                    {
                        if (matrix[0][col] == 0)
                        {
                            not_set = false;
                            row = 0;
                        }
                    }
                    else
                    {
                        if (matrix[1][col] == 0)
                        {
                            not_set = false;
                            row = 1;
                        }
                    }
                }
            }

            matrix[row][col] = my_color;
            row += 2;
        }
    }
}

int main()
{
    mysrand(time(NULL));

    vector<color> rand_colors = getRandomColors(3);
    vector<color> color_test_set_1 = {{1, 20}, {2, 40}};
    vector<color> color_test_set_2 = {{1, 20}, {2, 40}, {3, 40}};
    vector<color> color_test_set_3 = {{1, 20}, {2, 20}, {3, 20}, {4, 40}};
    vector<color> wrong_color_test_set = {{1, 90}, {2, 40}};
    vector<color> color_test_full = {{1, 100}};

    int **color_matrix_1;

    color_matrix_1 = new int *[M];

    for (int i = 0; i < M; i++)
    {

        color_matrix_1[i] = new int[N];
    }

    produceColorMatrix(color_matrix_1, rand_colors, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    zeroMatrix(color_matrix_1, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceColorMatrix(color_matrix_1, color_test_set_1, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceColorMatrix(color_matrix_1, wrong_color_test_set, M, N);
    std::cout << endl;

    produceHorizontalDiagonalPattern(color_matrix_1, color_test_set_2, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceVerticalDiagonalPattern(color_matrix_1, color_test_set_2, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceHorizontalDiagonalPattern(color_matrix_1, color_test_full, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceVerticalDiagonalPattern(color_matrix_1, color_test_full, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceRandomHorizontalDiagonalPattern(color_matrix_1, color_test_set_3, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    produceRandomVerticalDiagonalPattern(color_matrix_1, color_test_set_3, M, N);
    printMatrix(color_matrix_1, M, N);
    std::cout << endl;

    return 0;
}