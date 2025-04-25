#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Complete the 'getMinCost' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY crew_id
 *  2. INTEGER_ARRAY job_id
 */

/*
 * Algorithm:
 * 1. Sort both crew_id and job_id arrays in ascending order
 * 2. Pair each crew with the job having the same relative position after sorting
 *    (i.e., the crew with the smallest ID with the job with the smallest ID, etc.)
 * 3. For each pair, calculate the absolute difference between crew_id and job_id
 * 4. Sum up all these absolute differences to get the total cost
 *
 * Intuition:
 * - Sorting both arrays minimizes the sum of absolute differences when pairing
 *   elements at matching positions
 * - This is optimal because any other pairing would lead to greater differences
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(1) additional space (not counting input/output)
 */

// Compare function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

long getMinCost(int crew_id_count, int *crew_id, int job_id_count, int *job_id)
{
    // Sort both arrays
    qsort(crew_id, crew_id_count, sizeof(int), compare);
    qsort(job_id, job_id_count, sizeof(int), compare);

    // Calculate sum of absolute differences
    long total_cost = 0;
    for (int i = 0; i < crew_id_count; i++)
    {
        total_cost += labs((long)crew_id[i] - (long)job_id[i]);
    }

    return total_cost;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int crew_id_count;
    scanf("%d", &crew_id_count);

    int *crew_id = malloc(crew_id_count * sizeof(int));

    for (int i = 0; i < crew_id_count; i++)
    {
        scanf("%d", &crew_id[i]);
    }

    int job_id_count;
    scanf("%d", &job_id_count);

    int *job_id = malloc(job_id_count * sizeof(int));

    for (int i = 0; i < job_id_count; i++)
    {
        scanf("%d", &job_id[i]);
    }

    long result = getMinCost(crew_id_count, crew_id, job_id_count, job_id);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);
    free(crew_id);
    free(job_id);

    return 0;
}