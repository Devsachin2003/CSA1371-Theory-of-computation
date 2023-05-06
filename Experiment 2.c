#include<stdio.h>

int main() {
    // Define the DFA
    int transitions[][2] = {{1, -1}, {-1, 2}, {1, 2}}; // Transition table
    int initial_state = 0;
    int accepting_state = 2;

    // Get input string from user
    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);

    // Initialize the current state to the initial state
    int current_state = initial_state;

    // Traverse the DFA
    for (int i = 0; input[i] != '\0'; i++) {
        int input_symbol = input[i] - '0'; // Convert character to integer
        current_state = transitions[current_state][input_symbol];
        if (current_state == -1) {
            printf("Rejected\n");
            return 0;
        }
    }

    // Check if the final state is an accepting state
    if (current_state == accepting_state) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
