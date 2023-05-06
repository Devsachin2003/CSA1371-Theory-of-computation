#include<stdio.h>
#include<string.h>

#define MAX_STATES 100

int transition[MAX_STATES][2][MAX_STATES];
int n_states;
int final_states[MAX_STATES];
int n_final_states;

void add_transition(int from_state, char input_symbol, int to_state);
void add_final_state(int state);
int is_accepted(char* input);

int main() {
    // Define the NFA
    n_states = 3;
    add_transition(0, 'b', 1);
    add_transition(1, 'a', 2);
    add_transition(2, 'b', 2);
    add_transition(2, 'a', 2);
    add_final_state(2);

    // Read input from user and check if it is accepted by the NFA
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

void add_transition(int from_state, char input_symbol, int to_state) {
    if (input_symbol == 'a') {
        transition[from_state][0][to_state] = 1;
    } else if (input_symbol == 'b') {
        transition[from_state][1][to_state] = 1;
    }
}

void add_final_state(int state) {
    final_states[n_final_states++] = state;
}

int is_accepted(char* input) {
    int current_states[MAX_STATES];
    memset(current_states, 0, sizeof(current_states));
    current_states[0] = 1;
    for (int i = 0; i < strlen(input); i++) {
        int next_states[MAX_STATES];
        memset(next_states, 0, sizeof(next_states));
        for (int j = 0; j < n_states; j++) {
            if (current_states[j]) {
                for (int k = 0; k < n_states; k++) {
                    if (transition[j][input[i]-'a'][k]) {
                        next_states[k] = 1;
                    }
                }
            }
        }
        memcpy(current_states, next_states, sizeof(next_states));
    }
    for (int i = 0; i < n_states; i++) {
        if (current_states[i]) {
            for (int j = 0; j < n_final_states; j++) {
                if (i == final_states[j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
