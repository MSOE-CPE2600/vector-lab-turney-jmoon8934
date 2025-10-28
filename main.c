/***************************************************************************
* Filename: main.c
* Author: Jeric Moon
* Date: 10/24/2025
* Desc: Provides the main user input parsing and vector handling
****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include "calc.h"
#include "vect.h"
#include "parser.h"
#include "linkedlist.h"
    

//Main method, handles the bulk of the program.
int main(void)
{
    //Define variables used throughout the program
    linked_list vectors = llInit();
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
        while(position < 6 && tokens[position] != NULL)
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
                    printf("%-15s - Displays this dialogue.\n", "help"); //Done
                    printf("%-15s - Exits the program.\n", "quit"); //Done
                    printf("%-15s - Lists all vectors.\n", "list, or ls"); //Done
                    printf("%-15s - Clears all vectors.\n", "clear"); //Done
                    printf("%-15s - Saves loaded vectors into provided filename.\n", "save");
                    printf("%-15s - Loads vectors from provided filename, if file exists.\n" , "load");
                    printf("%-15s     - Loading will clear all vectors currently stored.\n", "");
                    printf("%-15s     - Saving to an existing file will overwrite the file.\n", "");
                    printf("%-15s     - File paths must not contain spaces.\n", "");
                    printf("%-15s     - Relative or absolute paths work.\n", "");
                    printf("%-15s - Displays the value of vector A.\n", "A"); //Done?
                    printf("%-15s - Adds vector A and vector B.\n", "A + B"); //Done
                    printf("%-15s - Subtracts vector B from vector A.\n", "A - B"); //Done
                    printf("%-15s - Creates new or replaces existing vector with given xy values. Z is optional.\n", "C = x y [z]"); //Done
                    printf("%-15s - Displays scalar mult k * vector B.\n", "k B or B k"); //Done
                    printf("%-15s - Vector 'C' value of opperation between A and B.\n", "C = A [+, -] B"); //Done
                    printf("%-15s - Vector 'C' takes value of opperation between scalar and A.\n", "C = k A or A k"); //Done

                    printf("\nImportant info!\n)");
                    printf("Expressions must contain a single space around each piece.\n");
                    printf("Vectors cannot have their name start with numbers.\n");
                    printf("Decimals must contain leading 0! (0.1)\n");
                    printf("Commands are case sensitive! \"Help\" will not work, but \"help\" will.\n");
                }
                else if (!strcmp(tokens[0], "list") || !strcmp(tokens[0], "ls"))
                {
                    //Lists each vector, checking to see if the vector pointer is null.
                    printf("\nListing vectors..\n");
                    listVectors(&vectors);
                    printf("All known vectors listed!\n\n");
                }
                else if(!strcmp(tokens[0], "clear"))
                {
                    printf("Clearing vectors..\n");
                    llClear(&vectors);
                }
                else 
                {
                    myvect *vect = vect_name_contains(tokens[0], &vectors);
                    if(vect)
                    {
                       printVector(vect);
                    }
                    else
                    {
                        printf("No known vector with that name!\n");
                    }
                }
            }
            else if(position == 1)
            {
                //Only valid expressions with pos = 1 (num tokens = 2) are scalar mult and FILE-IO.
                if(!strcmp(tokens[0], "save") || !strcmp(tokens[0], "load"))
                {
                    FILE *fp; 
                    char file_location[100];
                    strcpy(file_location, tokens[1]);
                    //Check if the file_location is long enough to end in .csv
                    //If file location is not long enough, append .csv regardless b/c it can't contain it.
                    if(strlen(file_location)>= 5)
                    {
                        //Check to see if the file_location does end in .csv
                        if(strcmp(file_location + strlen(file_location) - 4, ".csv") != 0)
                        {
                        //append .csv to file_location
                        strcat(file_location, ".csv");
                        }
                    } 
                    else
                    {
                        strcat(file_location, ".csv");
                    }

                    //if command is save, store value into bool 
                    //if save, write to fp location
                    //else, read file
                    bool save = !strcmp(tokens[0], "save");
                    if(save)
                    {
                        fp = fopen(file_location, "w");
                    } 
                    else
                    {
                        fp = fopen(file_location, "r");
                    }
                    //Check to see if fp is null before using it.
                    if(fp){
                        if(save)
                        {
                            node *curr = vectors.head;
                            while(curr)
                            {
                                fprintf(fp, "%s,%f,%f,%f,\n", curr->vect->name, curr->vect->x, curr->vect->y, curr->vect->z);
                                curr = curr->next;
                            }
                            printf("Finished saving to file!\n");
                        }
                        else
                        {
                            //If !save (loading), clear all vectors
                            llClear(&vectors);
                            char line[100];
                            //Initialize array of strs to hold csv values
                            char *parsing [7] = {NULL};
                            while(fgets(line, 100, fp))
                            {
                                //reset parsing position to 0
                                int parsing_pos = 0;
                                //do the first strok for the name (must be present)
                                parsing[parsing_pos] = strtok(line, ",");                               
                                while(parsing_pos < 6 && parsing[parsing_pos] != NULL)
                                {
                                    parsing_pos++;
                                    parsing[parsing_pos] = strtok(NULL, ",\n");
                                }
                                if(parsing_pos != 4)
                                {
                                    printf("Invalid line detected while parsing. Skipping line.\n");
                                }
                                else
                                {
                                    //If the line syntax is correct, start parsing values
                                    myvect vect = {0};
                                    strcpy(vect.name, parsing[0]);
                                    //utilize errno for edge case parsing[] = 0.00)
                                    errno = 0;
                                    double values[3] = {strtod(parsing[1], NULL), strtod(parsing[2], NULL), strtod(parsing[3], NULL)};
                                    if(errno == 0)
                                    {
                                        vect.x = values[0];
                                        vect.y = values[1];
                                        vect.z = values[2];
                                        llPushBack(&vectors, &vect);
                                    }
                                    else
                                    {
                                        printf("Invalid data detected, skipping line.\n");
                                    }
                                }
                            }
                            printf("Finished loading vectors!\n");
                        }
                        //close file pointer & flush it
                        fflush(fp);
                        fclose(fp);
                    }
                    else
                    {
                        printf("Error finding file! Please try a different file.\n");
                    }
                }
                else if(tokens[0][0] >= '0' && tokens[0][0] <= '9'){
                    //Due to stipulation that vector names can't start with numbers, check if first digit is a number character.
                    //If it is, convert to int, then check to see if next token is a vector.
                    //Then apply scalar mult or error code
                    myvect *vect = vect_name_contains(tokens[1], &vectors);
                    if(vect)
                    {
                        //Temporary scaled_vector just to print value.
                        myvect scaled_vector;
                        //Convert mult token to float
                        float scalar_mult = atof(tokens[1]);
                        scalarmult(&scaled_vector, vect, scalar_mult);
                        printVector(&scaled_vector);
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
                    myvect *vect = vect_name_contains(tokens[1], &vectors);
                    if(vect)
                    {
                        //Temporary scaled_vector just to print value.
                        myvect scaled_vector;
                        //Convert mult token to float
                        float scalar_mult = atof(tokens[1]);
                        scalarmult(&scaled_vector, vect, scalar_mult);
                        printVector(&scaled_vector);
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
                myvect *vect1 = vect_name_contains(tokens[0], &vectors);
                myvect *vect2 = vect_name_contains(tokens[2], &vectors);
                if(vect1 && vect2)
                {
                    //If the vectors exist, check to see if the middle token (opperator) is valid.
                    if(!strcmp(tokens[1], "+") || !strcmp(tokens[1], "-") || !strcmp(tokens[1], "="))
                    {
                        char result_string[100];
                        sprintf(result_string, "%s %s %s", tokens[0], tokens[1], tokens[2]);
                        if(!strcmp(tokens[1], "="))
                        {
                            //If takes the form A = B, update A to copy of B
                            char vect1_name[30];
                            strcpy(vect1_name, vect1->name);
                            vectcopy(vect1, vect2);
                            strcpy(vect1->name, vect1_name);
                            printVector(vect1);
                        }
                        else if(!strcmp(tokens[1], "+"))
                        {
                            //Temporary vector just to print out operation
                            myvect result;
                            vectadd(&result, vect1, vect2);
                            strcpy(result.name, result_string);
                            printVector(&result);
                        }
                        else if(!strcmp(tokens[1], "-"))
                        {
                            //Temporary vector just to print out operation
                            myvect result;
                            vectsub(&result, vect1, vect2);
                            strcpy(result.name, result_string);
                            printVector(&result);
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
                if(!vect1)
                {
                    printf("First vector %s not recognized. Please enter a new command.\n", tokens[0]);
                }
                if(!vect2)
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
                        myvect *vect1 = vect_name_contains(tokens[0], &vectors);
                        if(!vect1)
                        {
                            myvect vect = {0};
                            vect.x = 0;
                            vect.y = 0;
                            vect.z = 0;
                            strcpy(vect.name, tokens[0]);
                            llPushBack(&vectors, &vect);
                            vect1 = vect_name_contains(tokens[0], &vectors);
                        } 
                        //Value assignment code is reused between new vector assignment and vector replacement
                        //Check if token 2 doesnt start with a number
                        //Check if token 3 doesnt start with a number
                        //If both start with numbers, its form A = x y
                        //If one starts with number & other doesnt, it's form C = A 10 || C = 10 A
                        if((tokens[2][0] >= '0' && tokens[2][0] <= '9') && (tokens[3][0] >= '0' && tokens[3][0] <= '9'))
                        {
                            //Form A = x y
                            vect1->x = atof(tokens[2]);
                            vect1->y = atof(tokens[3]);
                            vect1->z = 0.0;
                            //Print out new vector values
                            printVector(vect1);
                        }
                        else if(tokens[2][0] >= '0' && tokens[2][0] <= '9')
                        {
                            //Form C = A 10
                            //Check if A exists
                            myvect *vect2 = vect_name_contains(tokens[3], &vectors);
                            if(vect2)
                            {
                                //Convert scalar_mult token to float.
                                float scalar_mult = atof(tokens[2]);
                                scalarmult(vect1, vect2, scalar_mult);
                                //Print out new vector values
                                printVector(vect1);
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
                            myvect *vect2 = vect_name_contains(tokens[2], &vectors);
                            if(vect2){
                                //Convert scalar_mult token to float.
                                float scalar_mult = atof(tokens[3]);
                                scalarmult(vect1, vect2, scalar_mult);
                                //Print out new vector values
                                printVector(vect1);
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
                        myvect *vect1 = vect_name_contains(tokens[0], &vectors);
                        if(!vect1)
                        {
                            myvect vect = {0};
                            vect.x = 0;
                            vect.y = 0;
                            vect.z = 0;
                            strcpy(vect.name, tokens[0]);
                            llPushBack(&vectors, &vect);
                            vect1 = vect_name_contains(tokens[0], &vectors);
                        } 
                        //Check to see if there are too many vectors
                        //Code is reused between reassigning and defining new vector
                        //Check if tokens[2], [3], and [4] are all numbers. Form A = x y z.
                        //Else, check tokens[3] is equal to "+" or "-"
                        //If tokens[3] is an opperator, check if tokens[2] and [4] are valid vectors
                        //Finally, reassign and preform opperation
                        if((tokens[2][0] >= '0' && tokens[2][0] <= '9') && ((tokens[3][0] >= '0' && tokens[3][0] <= '9')) && (tokens[4][0] >= '0' && tokens[4][0] <= '9'))
                        {
                            //Form A = x y z
                            vect1->x = atof(tokens[2]);
                            vect1->y = atof(tokens[3]);
                            vect1->z = atof(tokens[4]);
                            //Print out new vector values.
                            printVector(vect1);
                        }
                        else if(!strcmp(tokens[3], "-") || !strcmp(tokens[3], "+"))
                        {
                            //Form C = A [+/-] B
                            myvect *vect2 = vect_name_contains(tokens[2], &vectors);
                            myvect *vect3 = vect_name_contains(tokens[4], &vectors);
                            if(vect2 && vect3)
                            {
                                //If vectors A & B are real, check to see if opperator is valid
                                //If opperator is valid, preform operation, update new vector
                                if(!strcmp(tokens[3], "+"))
                                {
                                    vectadd(vect1, vect2, vect3);
                                    //Reupdate name, direct vectadd does not preserve name
                                    printVector(vect1);
                                }
                                else if(!strcmp(tokens[3], "-"))
                                {
                                    vectsub(vect1, vect2, vect3);
                                    //Reupdate name, direct vectadd does not preserve name
                                    printVector(vect1);
                                }
                                else
                                {
                                    printf("Invalid opperator! Please enter a new command!\n");
                                }
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
    llClear(&vectors);
    return 0;
}

