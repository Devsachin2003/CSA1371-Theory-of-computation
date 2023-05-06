#include <stdio.h>
#include <stdbool.h>
#define MAX_STATES 10

int n, m; // n -> number of states, m -> number of input symbols
int transitions[MAX_STATES][MAX_STATES][MAX_STATES]; // transitions[i][j][k] -> transition from state i to state j on input symbol k
bool visited[MAX_STATES];

void epsilon_closure(int state, int closure[]) {
    int i;
    closure[state] = 1; // mark the state as visited
    for (i = 0; i < n; i++) {
        if (transitions[state][i][0] == 1 && closure[i] == 0) {
            epsilon_closure(i, closure); // recursive call to find the ε-closure of the state
        }
    }
}

int main() {
    int i, j, k, closure[MAX_STATES];
    printf("Enter the number of states: ");
    scanf("%d", &n);
    printf("Enter the number of input symbols: ");
    scanf("%d", &m);
    printf("Enter the transitions:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k <= m; k++) {
                transitions[i][j][k] = 0;
            }
        }
    }
    while (true) {
        int from, to, symbol;
        printf("Enter the transition (from, to, symbol): ");
        scanf("%d%d%d", &from, &to, &symbol);
        if (from == -1 || to == -1 || symbol == -1) {
            break;
        }
        transitions[from][to][symbol] = 1; // mark the transition from state 'from' to state 'to' on input symbol 'symbol'
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            closure[j] = 0;
        }
        epsilon_closure(i, closure); // find the ε-closure of the state 'i'
        printf("ε-closure(%d) = { ", i);
        for (j = 0; j < n; j++) {
            if (closure[j] == 1) {
                printf("%d ", j);
            }
        }
        printf("}\n");
    }
    return 0;
}
