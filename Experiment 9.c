#include <stdio.h>
#include <string.h>

#define MAX_STATES 10

int transition[MAX_STATES][2][MAX_STATES];
int num_states, num_final_states, final_states[MAX_STATES];

void add_transition(int state, int symbol, int next_state) {
    transition[state][symbol][next_state] = 1;
}

void print_string_accepted(char *input_string) {
    int current_states[MAX_STATES] = {0};
    int next_states[MAX_STATES] = {0};
    int temp_states[MAX_STATES] = {0};
    int current_states_size = 0;
    int next_states_size = 0;
    int i, j, k;

    // Start in the initial state
    current_states[0] = 1;
    current_states_size++;

    // Iterate over the input string
    for (i = 0; i < strlen(input_string); i++) {
        // Compute the set of next states for the current states and input symbol
        next_states_size = 0;
        for (j = 0; j < current_states_size; j++) {
            for (k = 0; k < num_states; k++) {
                if (transition[j][input_string[i]-'0'][k]) {
                    next_states[next_states_size] = k;
                    next_states_size++;
                }
            }
        }

        // Swap current_states and next_states, and reset next_states
        memcpy(temp_states, current_states, sizeof(current_states));
        memcpy(current_states, next_states, sizeof(next_states));
        memcpy(next_states, temp_states, sizeof(temp_states));
        current_states_size = next_states_size;
        next_states_size = 0;
    }

    // Check if any of the current states are final states
    for (i = 0; i < current_states_size; i++) {
        for (j = 0; j < num_final_states; j++) {
            if (current_states[i] == final_states[j]) {
                printf("Input string '%s' is accepted.\n", input_string);
                return;
            }
        }
    }

    printf("Input string '%s' is rejected.\n", input_string);
}

int main() {
    int i;

    // Define the NFA
    num_states = 3;
    add_transition(0, 0, 1);
    add_transition(1, 0, 1);
    add_transition(1, 1, 2);

    // Define the final states
    num_final_states = 1;
    final_states[0] = 2;

    // Test some input strings
    print_string_accepted("o01");
    print_string_accepted("oo1");
    print_string_accepted("o0");
    print_string_accepted("o11");
    print_string_accepted("o111");

    return 0;
}
