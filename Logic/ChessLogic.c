#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define FEN_LENGTH 256     // Maximum length of the FEN string

//Defining all peaces as array in form  ["file","rank","","pic path"] 
char WhiteKing[4] = ["0","0","WhiteKing","Recorces/White/LightKing.png"]
char WhiteBishop[4] = ["0","0","WhiteBishop","Recorces/White/LightBishop.png"]
char WhiteKnight[4] = ["0","0","WhiteKnight","Recorces/White/LightKnight.png"]
char WhitePawn[4] = ["0","0","WhitePawn","Recorces/White/LightPawn.png"]
char WhiteQueen[4] = ["0","0","WhiteQueen","Recorces/White/LightQueen.png"]
char WhiteRook[4] = ["0","0","WhiteRook","Recorces/White/LightRook.png"]
char BlackKing[4] = ["0","0","BlackKing","Recorces/Black/DarkKing.png"]
char BlackBishop[4] = ["0","0","BlackKing","Recorces/Black/DarkBishop.png"]
char BlackKnight[4] = ["0","0","BlackKnight","Recorces/Black/DarkKnight.png"]
char BlackPawn[4] = ["0","0","BlackPawn","Recorces/Black/DarkPawn.png"]
char BlackQueen[4] = ["0","0","BlackQueen","Recorces/Black/DarkQueen.png"]
char BlackRook[4] = ["0","0","BlackRook","Recorces/Black/DarkRook.png"]

int whoseTurn = 0; // 0 for White, 1 for Black


void Import_File(){

//Code to import A file with FEN strings
//paces it in a 1D char array to store the values as strings
const char *filename = "example.fen";
    FILE *FEN = fopen(filename, "r");

    if (FEN == NULL) {
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

BlackKing[0]=sprintf(file)
BlackKing[1]=sprintf(rank)
file++;

}else if(nextWord == "K"){

WhiteKing[0]=sprintf(file)
WhiteKing[1]=sprintf(rank)
file++;

}else if(nextWord == "b"){

BlackBishop[0]=sprintf(file)
BlackBishop[1]=sprintf(rank)
file++;

}else if(nextWord == "B"){

WhiteBishop[0]=sprintf(file)
WhiteBishop[1]=sprintf(rank)
file++;

}else if(nextWord == "q"){

BlackQueen[0]=sprintf(file)
BlackQueen[1]=sprintf(rank)
file++;

}else if(nextWord == "Q"){

WhiteQueen[0]=sprintf(file)
WhiteQueen[1]=sprintf(rank)
file++;

}else if(nextWord == "p"){

BlackPawn[0]=sprintf(file)
BlackPawn[1]=sprintf(rank)
file++;

}else if(nextWord == "P"){

WhitePawn[0]=sprintf(file)
WhitePawn[1]=sprintf(rank)
file++;

}else if(nextWord == "r"){

BlackRook[0]=sprintf(file)
BlackRook[1]=sprintf(rank)
file++;

}else if(nextWord == "R"){

WhiteRook[0]=sprintf(file)
WhiteRook[1]=sprintf(rank)
file++;

}else if(nextWord == "n"){

BlackKnight[0]=sprintf(file)
BlackKnight[1]=sprintf(rank)
file++;

}else if(nextWord == "N"){

WhiteKnight[0]=sprintf(file)
WhiteKnight[1]=sprintf(rank)
file++;

}else if(nextWord == " "){ // Check for space to move to the next word
    if (nextWord == "b") {
        whoseTurn = 1; // Black
}if else(nextWord == "w") {
        whoseTurn = 0; // White
}
} else {
    printf("Invalid character in FEN string: %c\n", nextWord);
    exit(EXIT_FAILURE);

}
}
}