#include<stdio.h>
#include<string.h>

int is_accepted(char* input);

int main() {
    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);
    if (is_accepted(input)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
    return 0;
}

int is_accepted(char* input) {
    int n = strlen(input);
    int dp[n][n];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
        if (input[i] == '0') {
            dp[i][i] = 1;
        }
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (input[i] == '0' && input[j] == '0') {
                for (int k = i + 1; k < j; k++) {
                    if (dp[i][k - 1] && dp[k][j - 1]) {
                        dp[i][j] = 1;
                        break;
                    }
                }
            }
            if (input[i] == '1' && input[j] == '1') {
                for (int k = i + 1; k < j; k++) {
                    if (dp[i][k - 1] && dp[k][j - 1]) {
                        dp[i][j] = 1;
                        break;
                    }
                }
            }
        }
    }
    return dp[0][n - 1];
}
