#include <stdio.h>
#include <stdlib.h>

/*
 * Complete the 'findSum' function below.
 *
 * The function is expected to return a LONG_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY numbers
 *  2. 2D_INTEGER_ARRAY queries
 */

/*
 * Algorithm:
 * 1. Use prefix sum technique to efficiently calculate subarray sums
 * 2. Create two prefix arrays:
 *    a. prefix_sum: For computing regular subarray sums
 *    b. zero_count: For tracking the number of zeros in a prefix
 * 3. For each query (l, r, x):
 *    a. Calculate regular sum using prefix_sum: prefix_sum[r] - prefix_sum[l-1]
 *    b. Find zeros in range using zero_count: zero_count[r] - zero_count[l-1]
 *    c. Add x * (zeros in range) to the sum
 * 4. Return results for all queries
 *
 * Time Complexity: O(n + q) where n is the array length and q is number of queries
 * Space Complexity: O(n) for prefix sum arrays
 */

long *findSum(int numbers_count, int *numbers, int queries_rows, int **queries)
{
    long *prefix_sum = (long *)malloc((numbers_count + 1) * sizeof(long));
    int *zero_count = (int *)malloc((numbers_count + 1) * sizeof(int));
    long *result = (long *)malloc(queries_rows * sizeof(long));

    prefix_sum[0] = 0;
    zero_count[0] = 0;

    // Precompute prefix sum and zero count
    for (int i = 0; i < numbers_count; i++)
    {
        prefix_sum[i + 1] = prefix_sum[i] + numbers[i];
        zero_count[i + 1] = zero_count[i] + (numbers[i] == 0);
    }

    // Process each query
    for (int i = 0; i < queries_rows; i++)
    {
        int l = queries[i][0];
        int r = queries[i][1];
        int x = queries[i][2];

        // Calculate sum and add x * count of zeros
        result[i] = (prefix_sum[r] - prefix_sum[l - 1]) + (x * (zero_count[r] - zero_count[l - 1]));
    }

    free(prefix_sum);
    free(zero_count);

    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int numbers_count;
    scanf("%d", &numbers_count);

    int *numbers = (int *)malloc(numbers_count * sizeof(int));
    for (int i = 0; i < numbers_count; i++)
    {
        scanf("%d", &numbers[i]);
    }

    int queries_rows;
    int queries_columns;
    scanf("%d %d", &queries_rows, &queries_columns);

    int **queries = (int **)malloc(queries_rows * sizeof(int *));
    for (int i = 0; i < queries_rows; i++)
    {
        queries[i] = (int *)malloc(queries_columns * sizeof(int));
        for (int j = 0; j < queries_columns; j++)
        {
            scanf("%d", &queries[i][j]);
        }
    }

    long *result = findSum(numbers_count, numbers, queries_rows, queries);

    for (int i = 0; i < queries_rows; i++)
    {
        fprintf(fptr, "%ld\n", result[i]);
        free(queries[i]);
    }
    fprintf(fptr, "\n");

    free(numbers);
    free(queries);
    free(result);

    fclose(fptr);

    return 0;
}