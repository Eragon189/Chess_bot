#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define FEN_LENGTH 256     // Maximum length of the FEN string

//Defining all peaces as array in form  ["file","rank","","pic path"] 
//set up white peaces
char *WhiteKing[4] = {"0","0","WhiteKing","Recorces/White/LightKing.png"};
char *WhiteBishop[4] = {"0","0","WhiteBishop","Recorces/White/LightBishop.png"};
char *WhiteKnight[4] = {"0","0","WhiteKnight","Recorces/White/LightKnight.png"};
char *WhitePawn[4] = {"0","0","WhitePawn","Recorces/White/LightPawn.png"};
char *WhiteQueen[4] = {"0","0","WhiteQueen","Recorces/White/LightQueen.png"};
char *WhiteRook[4] = {"0","0","WhiteRook","Recorces/White/LightRook.png"};
//set up black pieces
char *BlackKing[4] = {"0","0","BlackKing","Recorces/Black/DarkKing.png"};
char *BlackBishop[4] = {"0","0","BlackBishop","Recorces/Black/DarkBishop.png"};
char *BlackKnight[4] = {"0","0","BlackKnight","Recorces/Black/DarkKnight.png"};
char *BlackPawn[4] = {"0","0","BlackPawn","Recorces/Black/DarkPawn.png"};
char *BlackQueen[4] = {"0","0","BlackQueen","Recorces/Black/DarkQueen.png"};
char *BlackRook[4] = {"0","0","BlackRook","Recorces/Black/DarkRook.png"};
//set up a variable to keep track of whose turn it is
int whoseTurn = 0; // 0 for White, 1 for Black


int Import_File() {
    // Code to import a file with FEN strings
    // Places it in a 1D char array to store the values as strings
    const char *filename = "example.fen";
    FILE *FEN = fopen(filename, "r"); // open the file in read mode

    if (FEN == NULL) { // check if the file was opened successfully
        printf("Error opening file\n");
        return 1;
    }

    char fen[FEN_LENGTH];       // Buffer to read the whole FEN string
    char fen_chars[FEN_LENGTH]; // 1D array to store individual characters
    int char_count = 0;         // Counter for characters

    if (fgets(fen, sizeof(fen), FEN) != NULL) {
        // Remove newline if present
        fen[strcspn(fen, "\n")] = '\0';

        // Copy each character into the 1D array
        for (int i = 0; fen[i] != '\0'; i++) {
            fen_chars[i] = fen[i];
            char_count++;
        }
        fen_chars[char_count] = '\0'; // Null-terminate the character array
    }   
    fclose(FEN); // Close the file

    FEN_Translator(fen_chars);
    return 0;
}

void FEN_Translator(char *fen_chars) {
    // Function to translate FEN string into piece positions

    int file = 0;
    int rank = 0;
    char nextChar;

    for (int i = 0; i < FEN_LENGTH && fen_chars[i] != '\0'; i++) {
        nextChar = fen_chars[i];

        // Check if nextChar is a number to move sideways x spaces
        if (nextChar >= '1' && nextChar <= '8') {
            file += (nextChar - '0');
        }
        // Check for slash to move to next rank
        else if (nextChar == '/') {
            file = 0;
            rank++;
        }
        // Check for each piece and assign it to the correct array
        else if (nextChar == 'k') {
            sprintf(BlackKing[0], "%d", file);
            sprintf(BlackKing[1], "%d", rank);
            file++;
        } else if (nextChar == 'K') {
            sprintf(WhiteKing[0], "%d", file);
            sprintf(WhiteKing[1], "%d", rank);
            file++;
        } else if (nextChar == 'b') {
            sprintf(BlackBishop[0], "%d", file);
            sprintf(BlackBishop[1], "%d", rank);
            file++;
        } else if (nextChar == 'B') {
            sprintf(WhiteBishop[0], "%d", file);
            sprintf(WhiteBishop[1], "%d", rank);
            file++;
        } else if (nextChar == 'q') {
            sprintf(BlackQueen[0], "%d", file);
            sprintf(BlackQueen[1], "%d", rank);
            file++;
        } else if (nextChar == 'Q') {
            sprintf(WhiteQueen[0], "%d", file);
            sprintf(WhiteQueen[1], "%d", rank);
            file++;
        } else if (nextChar == 'p') {
            sprintf(BlackPawn[0], "%d", file);
            sprintf(BlackPawn[1], "%d", rank);
            file++;
        } else if (nextChar == 'P') {
            sprintf(WhitePawn[0], "%d", file);
            sprintf(WhitePawn[1], "%d", rank);
            file++;
        } else if (nextChar == 'r') {
            sprintf(BlackRook[0], "%d", file);
            sprintf(BlackRook[1], "%d", rank);
            file++;
        } else if (nextChar == 'R') {
            sprintf(WhiteRook[0], "%d", file);
            sprintf(WhiteRook[1], "%d", rank);
            file++;
        } else if (nextChar == 'n') {
            sprintf(BlackKnight[0], "%d", file);
            sprintf(BlackKnight[1], "%d", rank);
            file++;
        } else if (nextChar == 'N') {
            sprintf(WhiteKnight[0], "%d", file);
            sprintf(WhiteKnight[1], "%d", rank);
            file++;
        }
        // Check for space to determine when the turn identifier is
        else if (nextChar == ' ') {
            // Next character should be 'w' or 'b'
            if (fen_chars[i + 1] == 'b') {
                whoseTurn = 1; // set turn to Black
            } else if (fen_chars[i + 1] == 'w') {
                whoseTurn = 0; // set turn to White
            }
            break; // End parsing after turn info
        }
        else {
            printf("Invalid character in FEN string: %c\n", nextChar);
            exit(EXIT_FAILURE); // exit the program if an invalid character is found
        }
    }
}