/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2026, Group 4
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL; // Null-terminate the tokens array
        
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // Sort the players by score in descending order
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Print the sorted results
    printf("Final Results:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s: %d points\n", i + 1, players[i].name, players[i].score);
    }
}


int main(void)
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Enter name for player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = '\0'; 
        players[i].score = 0; 
    }
    
    while (1) {
        // Display the remaining categories and question values
        display_categories();

        char current_player[MAX_LEN];
        printf("Enter the name of the current player: ");
        fgets(current_player, MAX_LEN, stdin);
        current_player[strcspn(current_player, "\n")] = '\0';

        if (!player_exists(players, NUM_PLAYERS, current_player)) {
            printf("Player not found. Please enter a valid player name.\n");
            continue;
        }

        char category[MAX_LEN];
        int value;
        printf("Enter Category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = '\0';
        printf("Enter Value: ");
        fgets(buffer, BUFFER_LEN, stdin);
        
        if (sscanf(buffer, "%d", &value) != 1) {
            printf("Invalid value. Please enter a numeric value.\n");
            continue;
        }

        if (already_answered(category, value)) {
            printf("Question already answered. Please select another question.\n");
            continue;
        }

        if (!display_question(category, value)) {
            printf("Invalid question entered. Please select another question.\n");
            continue;
        }

        char answerInput[BUFFER_LEN];
        printf("Enter your answer (must start with 'What is' or 'Who is'): ");
        fgets(answerInput, BUFFER_LEN, stdin);
        answerInput[strcspn(answerInput, "\n")] = '\0';

        char *tokens[BUFFER_LEN / 2];
        tokenize(answerInput, tokens);
        if (tokens[0] == NULL || (strcmp(tokens[0], "What") != 0 && strcmp(tokens[0], "Who") != 0) || tokens[1] == NULL || strcmp(tokens[1], "is") != 0) {
            printf("Invalid answer format. Please start your answer with 'What is' or 'Who is'.\n");
            continue;
        }

        char playerAnswer[MAX_LEN] = "";
        for (int i = 2; tokens[i] != NULL; i++) {
            strcat(playerAnswer, tokens[i]);
            if (tokens[i + 1] != NULL) {
                strcat(playerAnswer, " ");
            }
        }

        if (valid_answer(category, value, playerAnswer)) {
            printf("Correct!\n");
            update_score(players, NUM_PLAYERS, current_player, value);
        } else {
            const char *correctAnswer = get_correct_answer(category, value);
            printf("Incorrect. The correct answer was: %s\n", correctAnswer);
        }

        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                questions[i].answered = true;
                break;
            }
        }

        bool allAnswered = true;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (!questions[i].answered) {
                allAnswered = false;
                break;
            }
        }
        if (allAnswered) {
            printf("All questions have been answered. Ending game.\n");
            show_results(players, NUM_PLAYERS);
            break;
        }
    }
    return EXIT_SUCCESS;
}
