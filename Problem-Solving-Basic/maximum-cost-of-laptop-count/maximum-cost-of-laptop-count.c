#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'maxCost' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY cost
 *  2. STRING_ARRAY labels
 *  3. INTEGER dailyCount
 */

/*
 * Algorithm:
 * 1. Process laptops in order, tracking both cost and the count of legal laptops
 * 2. For each laptop:
 *    a. Add its cost to the current batch's cost accumulator
 *    b. If the laptop is 'legal', increment the legal count
 * 3. When we reach exactly 'dailyCount' legal laptops:
 *    a. Compare the current batch's total cost with the maximum seen so far
 *    b. Update the maximum cost if current batch is more expensive
 *    c. Reset the counters to start a new batch
 * 4. Return the maximum cost found
 *
 * Time Complexity: O(n) where n is the number of laptops
 * Space Complexity: O(1) additional space (not counting input/output)
 */

int maxCost(int *cost, char **labels, int dailyCount)
{
    int ans = 0;
    int cur_cnt = 0;
    int cur_cost = 0;
    int cost_count = sizeof(cost) / sizeof(cost[0]);

    for (int i = 0; i < cost_count; i++)
    {
        cur_cost += cost[i];

        // Skip illegal labels
        if (strcmp(labels[i], "illegal") == 0)
        {
            continue;
        }

        cur_cnt++;

        // Check if we've reached the daily count
        if (cur_cnt == dailyCount)
        {
            // Update answer if current cost is greater
            if (cur_cost > ans)
            {
                ans = cur_cost;
            }

            // Reset counters for the next batch
            cur_cnt = 0;
            cur_cost = 0;
        }
    }

    return ans;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int cost_count;
    scanf("%d", &cost_count);

    int *cost = malloc(cost_count * sizeof(int));
    for (int i = 0; i < cost_count; i++)
    {
        scanf("%d", &cost[i]);
    }

    int labels_count;
    scanf("%d", &labels_count);

    char **labels = malloc(labels_count * sizeof(char *));
    for (int i = 0; i < labels_count; i++)
    {
        labels[i] = malloc(8 * sizeof(char)); // "illegal" or "legal" + null terminator
        scanf("%s", labels[i]);
    }

    int dailyCount;
    scanf("%d", &dailyCount);

    int result = maxCost(cost_count, cost, labels, dailyCount);

    fprintf(fptr, "%d\n", result);

    for (int i = 0; i < labels_count; i++)
    {
        free(labels[i]);
    }
    free(labels);
    free(cost);

    fclose(fptr);

    return 0;
}