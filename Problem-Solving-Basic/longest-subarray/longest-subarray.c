#include <stdio.h>
#include <stdlib.h>

/*
 * Complete the 'longestSubarray' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

/*
 * Algorithm:
 * 1. For each possible starting position:
 *    a. Try to form a subarray with at most 2 distinct values
 *    b. Additionally, the two values must differ by at most 1
 * 2. Use a window expansion approach:
 *    a. Track distinct values seen so far (at most 2)
 *    b. When a new value is encountered, check if it can be added:
 *       i. If we have 0 values so far, add it
 *       ii. If we have 1 value so far, add it if |new_val - existing_val| ≤ 1
 *       iii. If we have 2 values already, check if the new value matches either
 *    c. If a value can't be added, the window can't be expanded further
 * 3. Track the maximum valid window length
 *
 * Time Complexity: O(n²) where n is the array length
 * Space Complexity: O(1) additional space
 */

int longestSubarray(int arr_count, int *arr)
{
    int ans = 0;

    // O(n^2) is okay because of constraints.
    for (int i = 0; i < arr_count; i++)
    {
        int w[2] = {-1, -1}; // Stores the two distinct values (-1 means empty)
        int w_count = 0;     // Number of distinct values stored
        int cnt = 0;         // Length of current subarray

        for (int j = i; j < arr_count; j++)
        {
            // Check if current element matches either of the two values
            if (w_count > 0 && arr[j] == w[0])
            {
                cnt++;
                continue;
            }

            if (w_count > 1 && arr[j] == w[1])
            {
                cnt++;
                continue;
            }

            // If we don't have any value yet, add this as first
            if (w_count == 0)
            {
                w[0] = arr[j];
                w_count = 1;
                cnt++;
            }
            // If we have only one value, check if new value can be added
            else if (w_count == 1)
            {
                if (abs(w[0] - arr[j]) <= 1)
                {
                    w[1] = arr[j];
                    w_count = 2;
                    cnt++;
                }
                else
                {
                    // If difference > 1, we can't add this element
                    break;
                }
            }
            // If we already have two values, and this is a third distinct value, break
            else
            {
                break;
            }
        }

        // Update answer with max subarray length found
        if (cnt > ans)
        {
            ans = cnt;
        }
    }

    return ans;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int arr_count;
    scanf("%d", &arr_count);

    int *arr = malloc(arr_count * sizeof(int));
    for (int i = 0; i < arr_count; i++)
    {
        scanf("%d", &arr[i]);
    }

    int result = longestSubarray(arr_count, arr);

    fprintf(fptr, "%d\n", result);

    free(arr);
    fclose(fptr);

    return 0;
}