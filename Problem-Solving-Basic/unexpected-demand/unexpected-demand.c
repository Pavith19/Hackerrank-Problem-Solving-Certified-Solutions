#include <stdio.h>
#include <stdlib.h>

/*
 * Complete the 'filledOrders' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY order
 *  2. INTEGER k
 */

/*
 * Algorithm:
 * 1. Sort the orders by size (smallest first)
 * 2. Process orders in ascending order:
 *    a. If we have enough capacity (k) to fulfill an order, fulfill it
 *    b. Decrement the remaining capacity by the order size
 *    c. If we don't have enough capacity, break
 * 3. Return the number of orders fulfilled
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(1) extra space (not counting input)
 */

// Comparison function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int filledOrders(int order_count, int *order, int k)
{
    // Sort the order array
    qsort(order, order_count, sizeof(int), compare);

    int ans = 0;
    for (int i = 0; i < order_count; i++)
    {
        if (order[i] <= k)
        {
            ans++;
            k -= order[i];
        }
        else
        {
            break;
        }
    }
    return ans;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int order_count;
    scanf("%d", &order_count);

    int *order = malloc(order_count * sizeof(int));

    for (int i = 0; i < order_count; i++)
    {
        scanf("%d", &order[i]);
    }

    int k;
    scanf("%d", &k);

    int result = filledOrders(order_count, order, k);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);
    free(order);

    return 0;
}