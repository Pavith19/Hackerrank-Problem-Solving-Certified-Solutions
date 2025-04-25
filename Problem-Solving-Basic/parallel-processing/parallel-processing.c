#include <stdio.h>
#include <stdlib.h>

/*
 * Complete the 'minTime' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY files
 *  2. INTEGER numCores
 *  3. INTEGER limit
 */

/*
 * Algorithm:
 * 1. Separate files into two groups:
 *    a. Files divisible by numCores (can benefit from parallel processing)
 *    b. Files not divisible by numCores (no benefit from parallel processing)
 * 2. Sort divisible files in descending order to prioritize larger files for optimization
 * 3. Apply parallel processing to at most 'limit' files from the divisible group
 *    (divide processing time by numCores for these files)
 * 4. Process the rest of the files with single-core processing
 * 5. Sum up all processing times
 *
 * Intuition:
 * - Parallel processing is most beneficial for larger files that are divisible by numCores
 * - Using parallel processing on non-divisible files gives no advantage
 * - Sort to ensure we use the limited parallel slots for the largest possible files
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the separated arrays
 */

// Comparison function for qsort (descending order)
int compare_desc(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

long minTime(int files_count, int *files, int numCores, int limit)
{
    int *divisible = (int *)malloc(files_count * sizeof(int));
    int *not_divisible = (int *)malloc(files_count * sizeof(int));
    int div_count = 0, not_div_count = 0;

    // Separate files into divisible and not divisible by numCores
    for (int i = 0; i < files_count; i++)
    {
        if (files[i] % numCores == 0)
        {
            divisible[div_count++] = files[i];
        }
        else
        {
            not_divisible[not_div_count++] = files[i];
        }
    }

    // Sort divisible files in descending order
    qsort(divisible, div_count, sizeof(int), compare_desc);

    // Calculate total time
    long total_time = 0;

    // Process limited number of files with parallel processing
    for (int i = 0; i < div_count; i++)
    {
        if (i < limit)
        {
            total_time += divisible[i] / numCores;
        }
        else
        {
            total_time += divisible[i];
        }
    }

    // Add time for non-divisible files (no benefit from parallel processing)
    for (int i = 0; i < not_div_count; i++)
    {
        total_time += not_divisible[i];
    }

    free(divisible);
    free(not_divisible);

    return total_time;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int files_count;
    scanf("%d", &files_count);

    int *files = (int *)malloc(files_count * sizeof(int));
    for (int i = 0; i < files_count; i++)
    {
        scanf("%d", &files[i]);
    }

    int numCores, limit;
    scanf("%d", &numCores);
    scanf("%d", &limit);

    long result = minTime(files_count, files, numCores, limit);

    fprintf(fptr, "%ld\n", result);

    free(files);
    fclose(fptr);

    return 0;
}