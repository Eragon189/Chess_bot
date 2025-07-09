#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FEN_STRINGS 10 // Maximum number of FEN strings to store
#define FEN_LENGTH 256     // Maximum length of each FEN string
// ChessLogic.c
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


void Import_File(){

//import file code here
const char *filename = "example.fen";
    FILE *FEN = fopen(filename, "r");

    if (FEN == NULL) {
        perror("Error opening file");
        return 1;
    }

    char fen[MAX_FEN_STRINGS][FEN_LENGTH];
    int fen_count = 0; // Counter to track the number of FEN strings

    // Reading each FEN string one by one
    while (fgets(fen[fen_count], FEN_LENGTH, file) != NULL) {
        // Remove the newline character if it exists
        fen[fen_count][strcspn(fen[fen_count], "\n")] = '\0';

        // Store the FEN string character by character in an array
        char fen_chars[FEN_LENGTH];
        int char_index = 0;

        // Copy each character from the FEN string into the new array
        for (int i = 0; i < FEN_LENGTH && fen[fen_count][i] != '\0'; i++) {
            fen_chars[char_index] = fen[fen_count][i];
            char_index++;
        }

        // Null-terminate the character array
        fen_chars[char_index] = '\0';

        // Increment the FEN count
        fen_count++;

        // If the maximum number of FEN strings is reached, stop reading further
        if (fen_count >= MAX_FEN_STRINGS) {
            printf("Maximum number of FEN strings reached.\n");
            break;
        }
    }

    fclose(file); // Close the file after reading
    return 0;
}





void letter_separator(){

    //file braking code


}


void FEN_Translator(){
int file = 0;
int rank = 0;

if(nextWord > 0){//check if nextWord is a number to move sied spaces
    file=file+nextWord;
}else if(nextWord = "/"){//check for slach to move to next rank
    file = 0;
    rank++;
file = 0;
rank++;
}else if(nextWord == "k"){//check for each piece and assign it to the correct array

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

}
}