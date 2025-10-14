/***************************************************************************
* Filename: main.c
* Author: Jeric Moon
* Date: 10/09/2025
* Desc: Provides the main user input parsing and vector handling
****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "calc.h"
#include "vect.h"
#include "parser.h"
#include "linkedlist.h"
    
//define program vector capacity
const int VECTOR_CAPACITY = 10;
//Main method, handles the bulk of the program.
int main(void)
{
    //Initialize vector array and fill it with value-less, empty name vectors
    myvect vectors[VECTOR_CAPACITY];
    int vector_array_size = 0;
    for(int i = 0; i < VECTOR_CAPACITY; i++)
    {
        strcpy(vectors[i].name, "");
    }
    //Define user_input and quit variable
    char user_input[100];
    bool quit = false;
    //Intro + prompt user for command
    printf("Welcome to VectLab! Please enter a command. Enter \"help\" for more info, or \"quit\" to quit.\n");
    while(!quit)
    {
        printf("Enter command: ");
        //Get user input via fgets
        fgets(user_input, sizeof(user_input), stdin);
        //Declare token array, 6 tokens max because commands should only have 5 tokens max. Set each token to null.
        char *tokens [6];
        for(int j = 0; j < 6; j++)
        {
            tokens[j] = NULL;
        }
        //set up while loop to iterate through the string and save each token, tokenizing at " " or '\n' chars.
        //position used to track number of elements and 
        int position = 0;
        tokens[position] = strtok(user_input, " \n");
        while(tokens[position] != NULL && position < 5)
        {
            position++;
            tokens[position] = strtok(NULL, " \n");
        }
        //Currently, position-1 = index of last element. 
        //Decriment position once to keep it inline with last index entry.
        position--; 
        //Immedieatly check to see if position/index of last element is > 4, indicates invalid command.
        //No command should have more than 5 tokens (pos > 4)
        if(position > 4)
        { 
            printf("Error! Unrecognized command. Please enter a new command.\n");
        }
        else 
        {          
            //If position == 0, only 1 token saved. Must be word command or trying to print a vector.
            if(position == 0)
            {
                if(!strcmp(tokens[0], "quit"))
                {
                    //If user input is "quit", set quit to true and skip to end of loop.
                    quit = true;
                }
                else if (!strcmp(tokens[0], "help"))
                {
                    //Displaying all list of recognized commands and other important info.
                    printf("List of commands:\n");
                    printf("%-15s - Displays this list.\n", "help"); //Done
                    printf("%-15s - Exits the program.\n", "quit"); //Done
                    printf("%-15s - Lists all vectors.\n", "list"); //Done
                    printf("%-15s - Clears all vectors.\n", "clear"); //Done
                    printf("%-15s - Displays the value of vector A.\n", "A"); //Done?
                    printf("%-15s - Adds vector A and vector B.\n", "A + B");
                    printf("%-15s - Subtracts vector B from vector A.\n", "A - B");
                    printf("%-15s - Creates new or replaces existing vector with given xy values. Z is optional.\n", "C = x y [z]");
                    printf("%-15s - Displays scalar mult k * vector B.\n", "k B or B k");
                    printf("%-15s - Vector 'C' value of opperation between A and B or A and scalar mult k.\n", "C = A [+, -] B");
                    printf("%-15s - Vector 'C' takes value of opperation between scalar and A.\n", "C = k A or A k");

                    printf("\nImportant info!\n)");
                    printf("Expressions must contain a single space around each piece.\n");
                    printf("Vectors cannot have their name start with numbers.\n");
                    printf("Decimals must contain leading 0! (0.1)\n");
                    printf("Commands are case sensitive! \"Help\" will not work, but \"help\" will.\n");
                    printf("The program has a maximum of ten vectors.\n\n");
                }
                else if (!strcmp(tokens[0], "list"))
                {
                    //Lists each vector, checking to see if the vector pointer is null.
                    printf("\nListing vectors..\n");
                    for(int i = 0; i < VECTOR_CAPACITY; i++)
                    {
                        char myvect_printout[50];
                        if (strcmp(vectors[i].name, "") != 0)
                        {
                            vect_values(vectors[i], myvect_printout);
                            printf("Value of vector %d: %s is %s\n", i+1, vectors[i].name, myvect_printout);
                        }
                    }
                    printf("All known vectors listed!\n\n");
                }
                else if(!strcmp(tokens[0], "clear"))
                {
                    //Clears all vectors, resets size to 0.
                    printf("Clearing vectors..\n");
                    for(int i = 0; i < VECTOR_CAPACITY; i++)
                    {
                        strcpy(vectors[i].name, "");
                        vectors[i].x = 0.0;
                        vectors[i].y = 0.0;
                        vectors[i].z = 0.0;
                    }
                    vector_array_size = 0;
                }
                else 
                {
                    int pos = vect_name_contains(tokens[0], vectors, VECTOR_CAPACITY);
                    if(pos != -1)
                    {
                        char myvect_printout[50];
                        vect_values(vectors[pos], myvect_printout);
                        printf("Value of vector: %s is %s\n", vectors[pos].name, myvect_printout);
                    }
                    else
                    {
                        printf("No known vector with that name!\n");
                    }
                }
            }
            else if(position == 1)
            {
                //Only valid expression with pos = 1 (num tokens = 2) are k A or A k (scalar mult).
                if(tokens[0][0] >= '0' && tokens[0][0] <= '9'){
                    //Due to stipulation that vector names can't start with numbers, check if first digit is a number character.
                    //If it is, convert to int, then check to see if next token is a vector.
                    //Then apply scalar mult or error code
                    int pos = vect_name_contains(tokens[1], vectors, VECTOR_CAPACITY);
                    if(pos != -1)
                    {
                        //Convert scalar_mult token to float.
                        float scalar_mult = atof(tokens[0]);
                        myvect scaled_vector = scalarmult(&vectors[pos], scalar_mult);
                        char myvect_printout[50];
                        vect_values(scaled_vector, myvect_printout);
                        printf("Value of expression: %s\n", myvect_printout);
                    } 
                    else
                    {
                        //If valid syntax, but vector doesn't exist, error.
                        printf("Error! Vector not found. Please enter a new command.\n");
                    }
                    
                }
                else if(tokens[1][0] >= '0' && tokens[1][0] <= '9')
                {
                    //If first token isn't a number, check if 2nd one is.
                    //Repeat steps
                    int pos = vect_name_contains(tokens[0], vectors, VECTOR_CAPACITY);
                    if(pos != -1)
                    {
                        float scalar_mult = atof(tokens[1]);
                        myvect scaled_vector = scalarmult(&vectors[pos], scalar_mult);
                        char myvect_printout[50];
                        vect_values(scaled_vector, myvect_printout);
                        printf("Value of expression: %s\n", myvect_printout);
                    } 
                    else
                    {  
                        //If valid syntax, but vector doesn't exist, error.
                        printf("Error! Vector not found. Please enter a new command.\n");
                    }

                }
                else
                {
                    //If neither entry in a 2 token command is a number, invalid command, print error.
                    printf("Error! Unrecognized command. Please enter a new command.\n");
                }
            }
            else if(position == 2)
            {
                //Only valid expressions with pos = 2 (num tokens = 3) are A [opperator] B.
                int pos1 = vect_name_contains(tokens[0], vectors, VECTOR_CAPACITY);
                int pos2 = vect_name_contains(tokens[2], vectors, VECTOR_CAPACITY);
                if(pos1 != -1 && pos2 != -1)
                {
                    //If the vectors exist, check to see if the middle token (opperator) is valid.
                    if(!strcmp(tokens[1], "+") || !strcmp(tokens[1], "-") || !strcmp(tokens[1], "="))
                    {
                        if(!strcmp(tokens[1], "="))
                        {
                            //If takes the form A = B, update A to copy of B
                            vectcopy(&vectors[pos1], &vectors[pos2]);
                        }
                        else if(!strcmp(tokens[1], "+"))
                        {
                            myvect result = vectadd(&vectors[pos1], &vectors[pos2]);
                            char myvect_printout[50];
                            vect_values(result, myvect_printout);
                            printf("Value of expression: %s\n", myvect_printout);
                        }
                        else if(!strcmp(tokens[1], "-"))
                        {
                            myvect result = vectsub(&vectors[pos1], &vectors[pos2]);
                            char myvect_printout[50];
                            vect_values(result, myvect_printout);
                            printf("Value of expression: %s\n", myvect_printout);
                        }
                    }
                    else
                    {
                        //If middle token (opperator) is invalid, error.
                        printf("Unrecognized command! Please enter a new command.\n");
                    }
                }
                //Error statements if vector 1 or 2 aren't found.
                //Not if-else because both can not exist.
                if(pos1 == -1)
                {
                    printf("First vector %s not recognized. Please enter a new command.\n", tokens[0]);
                }
                if(pos2 == -1)
                {
                    printf("Second vector %s not recognized. Please enter a new command.\n", tokens[2]);
                }

            }
            else if(position == 3)
            {
                //Only valid commands for pos = 3 (# tokens = 4) is A = x y or C = 10 A || C = A 10
                //Check if token 1 is =, otherwise invalid command
                if(!strcmp(tokens[1], "="))
                {
                    //Check if first char of token is a number.
                    if(tokens[0][0] <= '0' || tokens[0][0] >= '9')
                    {
                        //Check to see if first vector doesn't exist
                        int pos1 = vect_name_contains(tokens[0], vectors, VECTOR_CAPACITY);
                        bool too_many_vectors = false;
                        if(pos1 == -1)
                        {
                            //If vector doesn't already exist, make a new vector, try to add it.
                            if(vector_array_size < 10)
                            {
                                strcpy(vectors[vector_array_size].name, tokens[0]);
                                pos1 = vector_array_size;
                                vector_array_size++;
                                //Values will be added later. Update pos1 from -1.
                            }
                            else
                            {
                                too_many_vectors = true;
                            }
                        }
                        //Check if there are too many vectors before doing operations/assignments, 
                        //Value assignment code is reused between new vector assignment and vector replacement
                        //Check if token 2 doesnt start with a number
                        //Check if token 3 doesnt start with a number
                        //If both start with numbers, its form A = x y
                        //If one starts with number & other doesnt, it's form C = A 10 || C = 10 A
                        if(too_many_vectors)
                        {
                            printf("Error! Too many vectors! Please clear or redefine a vector to change entries.\n");
                        }
                        else if((tokens[2][0] >= '0' && tokens[2][0] <= '9') && (tokens[3][0] >= '0' && tokens[3][0] <= '9'))
                        {
                            //Form A = x y
                            vectors[pos1].x = atof(tokens[2]);
                            vectors[pos1].y = atof(tokens[3]);
                            vectors[pos1].z = 0.0;
                            //Print out new vector values
                            char myvect_printout[50];
                            vect_values(vectors[pos1], myvect_printout);
                            printf("Value of expression: %s\n", myvect_printout);
                        }
                        else if(tokens[2][0] >= '0' && tokens[2][0] <= '9')
                        {
                            //Form C = A 10
                            //Check if A exists
                            int pos2 = vect_name_contains(tokens[3], vectors, VECTOR_CAPACITY);
                            if(pos2 != -1)
                            {
                                //Convert scalar_mult token to float.
                                float scalar_mult = atof(tokens[2]);
                                myvect scaled_vector = scalarmult(&vectors[pos2], scalar_mult);
                                char name[50];
                                strcpy(name, vectors[pos1].name);
                                vectcopy(&vectors[pos1], &scaled_vector);
                                strcpy(vectors[pos1].name, name);
                                //Print out new vector values
                                char myvect_printout[50];
                                vect_values(vectors[pos1], myvect_printout);
                                printf("Value of expression: %s\n", myvect_printout);
                            }
                            else
                            {
                                printf("Error! Unable to find vector %s, enter a new command!\n", tokens[3]);
                            }
                        } 
                        else if(tokens[3][0] >= '0' && tokens[3][0] <= '9')
                        {
                            //Form C = 10 A
                            //Check if A exists
                            int pos2 = vect_name_contains(tokens[2], vectors, VECTOR_CAPACITY);
                            if(pos2 != -1){
                                //Convert scalar_mult token to float.
                                float scalar_mult = atof(tokens[3]);
                                myvect scaled_vector = scalarmult(&vectors[pos2], scalar_mult);
                                char name[50];
                                strcpy(name, vectors[pos1].name);
                                vectcopy(&vectors[pos1], &scaled_vector);
                                strcpy(vectors[pos1].name, name);
                                //Print out new vector values
                                char myvect_printout[50];
                                vect_values(vectors[pos1], myvect_printout);
                                printf("Value of expression: %s\n", myvect_printout);
                            }
                            else
                            {
                                printf("Error! Unable to find vector %s, enter a new command!\n", tokens[3]);
                            }
                        }
                        else
                        {
                            //End catch. If form C = A B, error.
                            printf("Error! Invalid command! Please enter a new one!\n");
                        }
                    }
                    else
                    {
                        //If C starts with a number
                        printf("Invalid command! Vector names cannot start with numbers!\n");
                    }
                }
                else
                {
                    //If tokens[1] / 2nd scaned token != "=", invalid command.
                    printf("Invalid command! Please enter a new command.\n");
                }
            }
            else if(position == 4)
            {
                //Pos = 4 (tokens = 5) takes form of C = A [opperator] B or A = x y z. Anything else invalid.
                if(!strcmp(tokens[1], "="))
                {
                    //Check if first char of token is a number.
                    if(tokens[0][0] <= '0' || tokens[0][0] >= '9')
                    {
                        //Check to see if first vector doesn't exist
                        int pos1 = vect_name_contains(tokens[0], vectors, VECTOR_CAPACITY);
                        bool too_many_vectors = false;
                        if(pos1 == -1)
                        {
                            //If vector doesn't already exist, make a new vector, try to add it.
                            if(vector_array_size < 10)
                            {
                                strcpy(vectors[vector_array_size].name, tokens[0]);
                                pos1 = vector_array_size;
                                vector_array_size++;
                                //Values will be added later. Update pos1 from -1

                            }
                            else
                            {
                                too_many_vectors = true;
                            }
                        }
                        //Check to see if there are too many vectors
                        //Code is reused between reassigning and defining new vector
                        //Check if tokens[2], [3], and [4] are all numbers. Form A = x y z.
                        //Else, check tokens[3] is equal to "+" or "-"
                        //If tokens[3] is an opperator, check if tokens[2] and [4] are valid vectors
                        //Finally, reassign and preform opperation
                        if(too_many_vectors){
                            printf("Error! Too many vectors! Please clear or redefine a vector to change entries.\n");
                        }
                        else if((tokens[2][0] >= '0' && tokens[2][0] <= '9') && ((tokens[3][0] >= '0' && tokens[3][0] <= '9')) && (tokens[4][0] >= '0' && tokens[4][0] <= '9'))
                        {
                            //Form A = x y z
                            vectors[pos1].x = atof(tokens[2]);
                            vectors[pos1].y = atof(tokens[3]);
                            vectors[pos1].z = atof(tokens[4]);
                            //Print out new vector values.
                            char myvect_printout[50];
                            vect_values(vectors[pos1], myvect_printout);
                            printf("Value of vector: %s\n", myvect_printout);
                        }
                        else if(!strcmp(tokens[3], "-") || !strcmp(tokens[3], "+"))
                        {
                            //Form C = A [+/-] B
                            int pos2 = vect_name_contains(tokens[2], vectors, VECTOR_CAPACITY);
                            int pos3 = vect_name_contains(tokens[4], vectors, VECTOR_CAPACITY);
                            if(pos2 != -1 && pos3 != -1)
                            {
                                //If vectors A & B are real, check to see if opperator is valid
                                //If opperator is valid, preform operation, update new vector
                                if(!strcmp(tokens[3], "+"))
                                {
                                    vectors[pos1] = vectadd(&vectors[pos2], &vectors[pos3]);
                                    //Reupdate name, direct vectadd does not preserve name
                                    strcpy(vectors[pos1].name, tokens[0]);
                                    char myvect_printout[50];
                                    vect_values(vectors[pos1], myvect_printout);
                                    printf("Value of expression: %s\n", myvect_printout);
                                }
                                else if(!strcmp(tokens[3], "-"))
                                {
                                    vectors[pos1] = vectsub(&vectors[pos2], &vectors[pos3]);
                                    //Reupdate name, direct vectadd does not preserve name
                                    strcpy(vectors[pos1].name, tokens[0]);
                                    char myvect_printout[50];
                                    vect_values(vectors[pos1], myvect_printout);
                                    printf("Value of expression: %s\n", myvect_printout);
                                }
                                else
                                {
                                    printf("Invalid opperator! Please enter a new command!\n");
                                }
                            }
                            //Error if vector A or B are not found
                            if(pos2 == -1)
                            {
                                printf("Error! Vector %s not found!\n", tokens[2]);
                            }
                            if(pos3 == -1)
                            {
                                printf("Error! Vector %s not found!\n", tokens[3]);
                            }

                        }
                        else 
                        {
                            //Unrecognized command of form C = A ?? B
                            printf("Error! Invalid command! Please enter a new command!\n");
                        }
                    }
                    else
                    {
                        //If C starts with a number
                        printf("Invalid command! Vector names cannot start with numbers!\n");
                    }
                }
                else
                {
                    //If tokens[1] / 2nd scaned token != "=", invalid command.
                    printf("Invalid command! Please enter a new command.\n");
                }
            }
        }
    }
    printf("Thank you for using my vector calculator!\n");
    return 0;
}

