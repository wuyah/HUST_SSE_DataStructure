#include"EditDistance.h"

#define TEST1


#if defined(TEST)
int main()
{
    system("clear");
    char string_1[1024];
    char string_2[1024];

    printf("enter first string\n");
    scanf("%s", &string_1);
    printf("enter second string\n");
    scanf("%s", &string_2);

    printf("\nthe Edit Distance is %d", EditDistance(string_1, string_2));
    return 0;
}
#endif

void EditDistanceShow() {
    char string_1[1024];
    char string_2[1024];

    printf("enter first string\n");
    scanf("%s", &string_1);
    printf("enter second string\n");
    scanf("%s", &string_2);

    printf("\nthe Edit Distance is %d", EditDistance(string_1, string_2));
}

int mindp(int a, int b, int c) {
    if ((a <= b) && (a <= c)) {
        return a;
    } else if ((b <= a) && (b <= c)) {
        return b;
    } else {
        return c;
    }
}

int EditDistance(char *string_1, char *string_2) {
    int len_1 = strlen(string_1);
    int len_2 = strlen(string_2);
    int dp[1025][1025];
    // init the first col and row;
    for (int i = 0; i <= len_1; i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i <= len_2; i++) {
        dp[0][i] = i;
    }
    // use dp to calculate final distance
    for (int i = 1; i <= len_1; i++) {
        for (int j = 1; j <= len_2; j++) {
            int flag = 1;
            if (string_1[i] == string_2[j])
                flag = 0;

            int a = (dp[i - 1][j] + 1);
            int b = (dp[i][j - 1] + 1);
            int c = (dp[i - 1][j - 1] + flag);
            dp[i][j] = mindp(a, b, c);
        }
    }

    return dp[len_1][len_2];
}