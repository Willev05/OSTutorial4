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
#include "questions.h"

question questions[NUM_QUESTIONS];

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    strcpy(questions[0].category, "programming");
    questions[0].value = 100;
    strcpy(questions[0].question, "what is true in binary?");
    strcpy(questions[0].answer, "1");

    strcpy(questions[1].category, "programming");
    questions[1].value = 200;
    strcpy(questions[1].question, "this data structure follows the first in, first out principle.");
    strcpy(questions[1].answer, "queue");

    strcpy(questions[2].category, "programming");
    questions[2].value = 300;
    strcpy(questions[2].question, "this design pattern ensures only one instance of a class can exist.");
    strcpy(questions[2].answer, "singleton");

    strcpy(questions[3].category, "programming");
    questions[3].value = 400;
    strcpy(questions[3].question, "this conccurency issue occurs when two threads access shared data simultaneously and at least one modifies it.");
    strcpy(questions[3].answer, "race");

    strcpy(questions[4].category, "algorithms");
    questions[4].value = 100;
    strcpy(questions[4].question, "this notation measures how an algorith's runtime grows as input size increases.");
    strcpy(questions[4].answer, "complexity");

    strcpy(questions[5].category, "algorithms");
    questions[5].value = 200;
    strcpy(questions[5].question, "this data structure is commonly used in depth first search.");
    strcpy(questions[5].answer, "stack");

    strcpy(questions[6].category, "algorithms");
    questions[6].value = 300;
    strcpy(questions[6].question, "this traversal method visits the left subree, then root, then the right subtree in a binary tree.");
    strcpy(questions[6].answer, "inorder");

    strcpy(questions[7].category, "algorithms");
    questions[7].value = 400;
    strcpy(questions[7].question, "this algorithm finds a minimum spanning tree by repeatedly selecting the smallest edge that doesn't form a cycle.");
    strcpy(questions[7].answer, "kruskal");

    strcpy(questions[8].category, "databases");
    questions[8].value = 100;
    strcpy(questions[8].question, "this command retrieves data from a database table.");
    strcpy(questions[8].answer, "select");

    strcpy(questions[9].category, "databases");
    questions[9].value = 200;
    strcpy(questions[9].question, "this property of a transaction guarantees that all operations succeed or none do.");
    strcpy(questions[9].answer, "atomicity");

    strcpy(questions[10].category, "databases");
    questions[10].value = 300;
    strcpy(questions[10].question, "this normal form removes partial dependencies on a composite key.");
    strcpy(questions[10].answer, "second");

    strcpy(questions[11].category, "databases");
    questions[11].value = 400;
    strcpy(questions[11].question, "this type of dependency exists when a non-key attribute depends on another non-key attribute.");
    strcpy(questions[11].answer, "transistive");
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("///\n");
    for (int i = 0; i < NUM_QUESTIONS; i++){
        if (questions[i].answered) continue;
        printf("%s\n", questions[i].category);
        printf("%d\n///\n", questions[i].value);
    }
}

// Displays the question for the category and dollar value
bool display_question(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            printf("%s\nValue: %d\n", questions[i].question, value);
            return true;
        }
    }
    return false;
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            questions[i].answered = true;
            if(strcmp(questions[i].answer, answer) == 0) {
                return true;
            } else return false;
                
        }
    }
    
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            if(questions[i].answered) {
                return true;
            } 
            else return false;
        }
    }
    return false;
}


char* get_correct_answer(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answer;
        }
    }
    return NULL;
}
