#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'possibleChanges' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY usernames as parameter.
 */

/*
 * Algorithm:
 * 1. For each username, check if we can create a lexicographically smaller name
 * 2. A username can be made lexicographically smaller if there exists two characters
 *    where a character at index i is greater than a character at index j, where i < j
 * 3. If such a pair exists, swap them to get a smaller username (though we don't actually do the swap)
 * 4. For each username, return "YES" if such a swap is possible, "NO" otherwise
 *
 * Time Complexity: O(n * m^2) where n is the number of usernames and m is the max length of a username
 * Space Complexity: O(n) for storing the results
 */

char **possibleChanges(int usernames_count, char **usernames)
{
    char **ans = (char **)malloc(usernames_count * sizeof(char *));

    for (int i = 0; i < usernames_count; i++)
    {
        ans[i] = (char *)malloc(4 * sizeof(char)); // "YES" or "NO" plus null terminator

        if (strlen(usernames[i]) <= 1)
        {
            strcpy(ans[i], "NO");
            continue;
        }

        int found = 0;
        for (int j = 0; j < strlen(usernames[i]) - 1; j++)
        {
            if (usernames[i][j] > usernames[i][j + 1])
            {
                strcpy(ans[i], "YES");
                found = 1;
                break;
            }
        }

        if (!found)
        {
            strcpy(ans[i], "NO");
        }
    }

    return ans;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int usernames_count;
    scanf("%d", &usernames_count);

    char **usernames = (char **)malloc(usernames_count * sizeof(char *));

    for (int i = 0; i < usernames_count; i++)
    {
        usernames[i] = (char *)malloc(1001 * sizeof(char));
        scanf("%s", usernames[i]);
    }

    char **result = possibleChanges(usernames_count, usernames);

    for (int i = 0; i < usernames_count; i++)
    {
        fprintf(fptr, "%s\n", result[i]);
        free(result[i]);
        free(usernames[i]);
    }

    free(result);
    free(usernames);

    fclose(fptr);

    return 0;
}