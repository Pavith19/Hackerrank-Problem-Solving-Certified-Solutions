#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
 * Complete the 'mostBalancedPartition' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY parent
 *  2. INTEGER_ARRAY files_size
 */

/*
 * Algorithm:
 * 1. Calculate the total size of each subtree in the file system tree:
 *    a. Use a recursive approach to sum up file sizes
 *    b. For each node, its total size = its own size + sizes of all child subtrees
 * 2. Find the optimal partition point by:
 *    a. The system is divided into two parts by removing one edge from the tree
 *    b. When edge to node i is cut, we get subtree i and the rest of the tree
 *    c. Size of subtree i is size_sums[i]
 *    d. Size of the rest of the tree is total_size - size_sums[i]
 * 3. Calculate the absolute difference between these two parts for each possible cut
 * 4. Return the minimum difference found
 *
 * Time Complexity: O(n) where n is the number of nodes in the tree
 * Space Complexity: O(n) for storing the size sums
 */

// Recursive function to calculate size sums
long size_sums_rec(int node, int *parent, int *files_size, long *size_sums, int parent_count)
{
    // Calculate children first
    for (int i = 0; i < parent_count; i++)
    {
        if (parent[i] == node)
        {
            size_sums[i] = size_sums_rec(i, parent, files_size, size_sums, parent_count);
        }
    }

    // Sum up this node's size plus all its children's sizes
    long sum = files_size[node];
    for (int i = 0; i < parent_count; i++)
    {
        if (parent[i] == node)
        {
            sum += size_sums[i];
        }
    }

    size_sums[node] = sum;
    return sum;
}

int mostBalancedPartition(int parent_count, int *parent, int files_size_count, int *files_size)
{
    // Allocate and initialize size_sums array
    long *size_sums = (long *)malloc(parent_count * sizeof(long));
    for (int i = 0; i < parent_count; i++)
    {
        size_sums[i] = -1; // Initialize with -1 to indicate not calculated yet
    }

    // Calculate size sums using recursion
    size_sums_rec(0, parent, files_size, size_sums, parent_count);

    // Find the minimum absolute difference
    long total_size = size_sums[0];
    long min_diff = LONG_MAX;

    for (int i = 1; i < parent_count; i++)
    {
        long diff = labs(total_size - 2 * size_sums[i]);
        if (diff < min_diff)
        {
            min_diff = diff;
        }
    }

    free(size_sums);
    return (int)min_diff;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int parent_count;
    scanf("%d", &parent_count);

    int *parent = malloc(parent_count * sizeof(int));
    for (int i = 0; i < parent_count; i++)
    {
        scanf("%d", &parent[i]);
    }

    int files_size_count;
    scanf("%d", &files_size_count);

    int *files_size = malloc(files_size_count * sizeof(int));
    for (int i = 0; i < files_size_count; i++)
    {
        scanf("%d", &files_size[i]);
    }

    int result = mostBalancedPartition(parent_count, parent, files_size_count, files_size);

    fprintf(fptr, "%d\n", result);

    free(parent);
    free(files_size);
    fclose(fptr);

    return 0;
}