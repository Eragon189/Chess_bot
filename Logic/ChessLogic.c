#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define FEN_LENGTH 256     // Maximum length of the FEN string

//Defining all peaces as array in form  ["file","rank","","pic path"] 
//set up white peaces
char WhiteKing[4] = ["0","0","WhiteKing","Recorces/White/LightKing.png"]
char WhiteBishop[4] = ["0","0","WhiteBishop","Recorces/White/LightBishop.png"]
char WhiteKnight[4] = ["0","0","WhiteKnight","Recorces/White/LightKnight.png"]
char WhitePawn[4] = ["0","0","WhitePawn","Recorces/White/LightPawn.png"]
char WhiteQueen[4] = ["0","0","WhiteQueen","Recorces/White/LightQueen.png"]
char WhiteRook[4] = ["0","0","WhiteRook","Recorces/White/LightRook.png"]
//set up black pecaes
char BlackKing[4] = ["0","0","BlackKing","Recorces/Black/DarkKing.png"]
char BlackBishop[4] = ["0","0","BlackKing","Recorces/Black/DarkBishop.png"]
char BlackKnight[4] = ["0","0","BlackKnight","Recorces/Black/DarkKnight.png"]
char BlackPawn[4] = ["0","0","BlackPawn","Recorces/Black/DarkPawn.png"]
char BlackQueen[4] = ["0","0","BlackQueen","Recorces/Black/DarkQueen.png"]
char BlackRook[4] = ["0","0","BlackRook","Recorces/Black/DarkRook.png"]
//set up a variable to keep track of whose turn it is
int whoseTurn = 0; // 0 for White, 1 for Black


void Import_File(){

//Code to import A file with FEN strings
//paces it in a 1D char array to store the values as strings
const char *filename = "example.fen";
    FILE *FEN = fopen(filename, "r");//open the file in read mode

    if (FEN == NULL) {//check if the file was opened successfully
        printf("Error opening file");
        return 1;
    }


}

void letter_separator(){

    char fen[FEN_LENGTH];       // Buffer to read the whole FEN string
    char fen_chars[FEN_LENGTH]; // 1D array to store individual characters
    int char_count = 0;         // Counter for characters

    if (fgets(fen, sizeof(fen), file) != NULL) {
        // Remove newline if present
        fen[strcspn(fen, "\n")] = '\0';

        // Copy each character into the 1D array
        for (int i = 0; fen[i] != '\0'; i++) {
            fen_chars[i] = fen[i];
            char_count++;
        }

        // Optionally null-terminate the character array (if you treat it as a string)
        fen_chars[char_count] = '\0';
    }
    fclose(FEN); // Close the file
    return 0;


}

void FEN_Translator(){
int file = 0;
int rank = 0;
char nextWord; // Buffer to hold the next word from the FEN string
for (int i = 0; i < FEN_LENGTH; i++) {
    nextWord = fen_chars[i]; // Sent nextWord to the next character in the array
//atoi() converts a string to an integer, so we can check if nextWord is a number
if(atoi(nextWord) >= 1 && atoi(nextWord) <= 8){//check if nextWord is a number to move sideways x spaces

    file=file+nextWord;

}else if(nextWord = "/"){//check for slach to move to next rank
    file = 0;
    rank++;

//check for each piece and assign it to the correct array

}else if(nextWord == "k"){

sprintf(BlackKing[0], "%d", file); // Set the file position
sprintf(BlackKing[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "K"){

sprintf(WhiteKing[0], "%d", file); // Set the file position 
sprintf(WhiteKing[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "b"){

sprintf(BlackBishop[0], "%d", file); // Set the file position
sprintf(BlackBishop[1], "%d", rank); // Set the rank position

    file++;

}else if(nextWord == "B"){

sprintf(WhiteBishop[0], "%d", file); // Set the file position
sprintf(WhiteBishop[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "q"){

    sprintf(BlackQueen[0], "%d", file); // Set the file position
    sprintf(BlackQueen[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "Q"){

sprintf(WhiteQueen[0], "%d", file); // Set the file position
sprintf(WhiteQueen[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "p"){

sprintf(BlackPawn[0], "%d", file); // Set the file position
sprintf(BlackPawn[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "P"){

sprintf(WhitePawn[0], "%d", file); // Set the file position
sprintf(WhitePawn[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "r"){

sprintf(BlackRook[0], "%d", file); // Set the file position
sprintf(BlackRook[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "R"){

sprintf(WhiteRook[0], "%d", file); // Set the file position
sprintf(WhiteRook[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "n"){

 sprintf(BlackKnight[0], "%d", file); // Set the file position
 sprintf(BlackKnight[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == "N"){

sprintf(WhiteKnight[0], "%d", file); // Set the file position
sprintf(WhiteKnight[1], "%d", rank); // Set the rank position
file++;

}else if(nextWord == " "){ // Check for space to determine when the turn identifier is
    if (nextWord == "b") {
        whoseTurn = 1; // set turn to Black
}if else(nextWord == "w") {
        whoseTurn = 0; //set turn to White
}
} else {
    printf("Invalid character in FEN string: %c\n", nextWord);
    exit(EXIT_FAILURE);//exit the program if an invalid character is found

}
}
}