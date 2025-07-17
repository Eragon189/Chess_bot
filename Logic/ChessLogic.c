#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define FEN_LENGTH 256     // Maximum length of the FEN string
int debug = 0; // Debugging variable, set to 1 to enable debugging output
char *fileName = "start.fen"; // FEN file name
//Defining all peaces as array in form  {"file","rank","index","id","pic path"}
//set up white peaces
int WhiteSquares[8][8] = {//white = 0,black = 1
    //format [rank],[file]
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0}
};
char WhiteKing[1][4][32] = {
    {"0","0","WhiteKing","Recorces/White/LightKing.png"}
};
char WhiteBishops[2][4][32] = {
    { "0", "0", "White_BlackSquare_Bishop", "Recorces/White/LightBishop.png" },
    { "0", "0", "White_WhiteSquare_Bishop", "Recorces/White/LightBishop.png" }
};
char WhiteKnights[2][4][32] = {
    // {"file","rank","index","id","pic path"}
    {"0","0","0","WhiteKnight1","Recorces/White/LightKnight.png"},
    {"0","0","1","WhiteKnight2","Recorces/White/LightKnight.png"}
};
char WhitePawns[8][4][32] = {
    // {"file","rank","index","id","pic path"}
    {"0","0","0","WhitePawn1","Recorces/White/LightPawn.png"},
    {"0","0","1","WhitePawn2","Recorces/White/LightPawn.png"},
    {"0","0","2","WhitePawn4","Recorces/White/LightPawn.png"},
    {"0","0","3","WhitePawn3","Recorces/White/LightPawn.png"},
    {"0","0","4","WhitePawn5","Recorces/White/LightPawn.png"},
    {"0","0","5","WhitePawn6","Recorces/White/LightPawn.png"},
    {"0","0","6","WhitePawn7","Recorces/White/LightPawn.png"},
    {"0","0","7","WhitePawn8","Recorces/White/LightPawn.png"}
};
char WhiteQueen[1][4][32] = {
    {"0","0","WhiteQueen","Recorces/White/LightQueen.png"}
};
char WhiteRooks[2][4][32] = {
    // {"file","rank","index","id","pic path"}
    {"0","0","0","WhiteRook1","Recorces/White/LightRook.png"},
    {"0","0","1","WhiteRook2","Recorces/White/LightRook.png"}
};

//set up black pieces
char BlackKing[1][4][32] = {
    {"0","0","BlackKing","Recorces/Black/DarkKing.png"}
};
char BlackBishops[2][4][32] = {
    {"0","0","Black_BlackSquare_Bishop","Recorces/Black/DarkBishop.png"},
    {"0","0","Black_WhiteSquare_Bishop","Recorces/Black/DarkBishop.png"}
};
char BlackKnights[2][4][32] = {
    // {"file","rank","index","id","pic path"}
    {"0","0","0","BlackKnight1","Recorces/Black/DarkKnight.png"},
    {"0","0","1","BlackKnight2","Recorces/Black/DarkKnight.png"}
};
char BlackPawns[8][4][32] = {
    // {"file","rank","index","id","pic path"}
    {"0","0","0","BlackPawn1","Recorces/Black/DarkPawn.png"},
    {"0","0","1","BlackPawn2","Recorces/Black/DarkPawn.png"},
    {"0","0","2","BlackPawn3","Recorces/Black/DarkPawn.png"},
    {"0","0","3","BlackPawn4","Recorces/Black/DarkPawn.png"},
    {"0","0","4","BlackPawn5","Recorces/Black/DarkPawn.png"},
    {"0","0","5","BlackPawn6","Recorces/Black/DarkPawn.png"},
    {"0","0","6","BlackPawn7","Recorces/Black/DarkPawn.png"},
    {"0","0","7","BlackPawn8","Recorces/Black/DarkPawn.png"}
};
char BlackQueen[1][4][32] = {
    {"0","0","BlackQueen","Recorces/Black/DarkQueen.png"}
};
char BlackRooks[2][4][32] = {
    // {"file","rank","index","id","pic path"}
    {"0","0","0","BlackRook1","Recorces/Black/DarkRook.png"},
    {"0","0","1","BlackRook2","Recorces/Black/DarkRook.png"}
};
//set up a variable to keep track of whose turn it is
int whoseTurn = 0; // 0 for White, 1 for Black

// Define the move spaces for all pieces in {file, rank} format
int WhiteKnightPossibleMoveCombos[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
int BlackKnightPossibleMoveCombos[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
int WhiteBishopPossibleMoveCombos[15][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
int BlackBishopPossibleMoveCombos[15][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
int WhiteRookPossibleMoveCombos[14][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int BlackRookPossibleMoveCombos[14][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int WhiteQueenPossibleMoveCombos[15][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int BlackQueenPossibleMoveCombos[15][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int WhiteKingPossibleMoveCombos[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int BlackKingPossibleMoveCombos[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int WhitePawnPossibleMoveCombos[4][2] = {{0, 1}, {0, 2}, {-1, 1}, {1, 1}}; // Normal move, double move, and captures
int BlackPawnPossibleMoveCombos[4][2] = {{0, -1}, {0, -2}, {-1, -1}, {1, -1}}; // Normal move, double move, and captures

int ImportFileAndDecompile() {
    // Code to import a file with FEN strings
    // Places it in a 1D char array to store the values as strings
    const char *filename = fileName;
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

    // Function to translate FEN string into piece positions

    int file = 0;
    int rank = 0;
    char nextChar;

        int blackPawnIndex = 0;
        int whitePawnIndex = 0;
        int blackKnightIndex = 0;
        int whiteKnightIndex = 0;
        int blackRookIndex = 0;
        int whiteRookIndex = 0;
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
            sprintf(BlackKing[0][0], "%d", file);
            sprintf(BlackKing[0][1], "%d", rank);
            file++;
        } else if (nextChar == 'K') {
            sprintf(WhiteKing[0][0], "%d", file);
            sprintf(WhiteKing[0][1], "%d", rank);
            file++;
        } else if (nextChar == 'b') {

            if (WhiteSquares[rank][file] == 1) {//check if the square is white or black
                //set the bishop to the correct square
                sprintf(BlackBishops[0][0], "%d", file);
                sprintf(BlackBishops[0][1], "%d", rank);
            }else {
                sprintf(BlackBishops[1][0], "%d", file);
                sprintf(BlackBishops[1][1], "%d", rank);
            }
            file++;
        } else if (nextChar == 'B') {
            if( WhiteSquares[rank][file] == 1) {//check if the square is white or black
                //set the bishop to the correct square(white)
                sprintf(WhiteBishops[0][0], "%d", file);
                sprintf(WhiteBishops[0][1], "%d", rank);
            }else {
                //set the bishop to the correct square(black)
                sprintf(WhiteBishops[1][0], "%d", file);
                sprintf(WhiteBishops[1][1], "%d", rank);
            }
            file++;
        } else if (nextChar == 'q') {
            sprintf(BlackQueen[0][0], "%d", file);
            sprintf(BlackQueen[0][1], "%d", rank);
            file++;
        } else if (nextChar == 'Q') {
            sprintf(WhiteQueen[0][0], "%d", file);
            sprintf(WhiteQueen[0][1], "%d", rank);
            file++;
        } else if (nextChar == 'p') {
            // format{file, rank, index, id, pic path}
            sprintf(BlackPawns[blackPawnIndex][0], "%d", file);
            sprintf(BlackPawns[blackPawnIndex][1], "%d", rank);
            file++;
            blackPawnIndex++;
        } else if (nextChar == 'P') {
            sprintf(WhitePawns[whitePawnIndex][0], "%d", file);
            sprintf(WhitePawns[whitePawnIndex][1], "%d", rank);
            file++;
            whitePawnIndex++;
        } else if (nextChar == 'r') {
            sprintf(BlackRooks[blackRookIndex][0], "%d", file);
            sprintf(BlackRooks[blackRookIndex][1], "%d", rank);
            file++;
            blackRookIndex++;
        } else if (nextChar == 'R') {
            sprintf(WhiteRooks[whiteRookIndex][0], "%d", file);
            sprintf(WhiteRooks[whiteRookIndex][1], "%d", rank);
            file++;
            whiteRookIndex++;
        } else if (nextChar == 'n') {
            sprintf(BlackKnights[blackKnightIndex][0], "%d", file);
            sprintf(BlackKnights[blackKnightIndex][1], "%d", rank);
            file++;
            blackKnightIndex++;
        } else if (nextChar == 'N') {
            sprintf(WhiteKnights[whiteKnightIndex][0], "%d", file);
            sprintf(WhiteKnights[whiteKnightIndex][1], "%d", rank);
            file++;
            whiteKnightIndex++;
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


int minimax(){


    //placeholder for minimax function
}

int main() {
    // Call the function to import the FEN file and decompile it
    int result = ImportFileAndDecompile();
    if (result != 0) {
        printf("Error during FEN import and decompilation.\n");
        return result;
        // Exit if there was an error
    }
    if (debug == 1) {// Debugging output
        printf("Debugging output:\n");
        printf("%d White Rook-1\n", WhiteRooks[1]);
        printf("%d White Rook-0\n", WhiteRooks[0]);
        printf("%d White Bishop-0\n", WhiteBishops[0]);
        printf("%d White Bishop-1\n", WhiteBishops[1]);
        printf("%d White Knight-0\n", WhiteKnights[0]);
        printf("%d White King-1\n", WhiteKing[1]);
        printf("%d White Knight-1\n", WhiteKnights[1]);
        printf("%d White Queen-1\n", WhiteQueen[1]);
        printf("%d White King-0\n", WhiteKing[0]);
        printf("%d White Pawn-1\n", WhitePawns[1]);
        printf("%d White Pawn-0\n", WhitePawns[0]);
        printf("%d Black Rook-1\n", BlackRooks[1]);
        printf("%d Black Rook-0\n", BlackRooks[0]);
        printf("%d Black Knight-1\n", BlackKnights[1]);
        printf("%d Black Knight-0\n", BlackKnights[0]);
        printf("%d Black King-1\n", BlackKing[1]);
        printf("%d Black King-0\n", BlackKing[0]);
        printf("%d Black Queen-1\n", BlackQueen[1]);
        printf("%d Black Queen-0\n", BlackQueen[0]);
        printf("%d Black Pawn-1\n", BlackPawns[1]);
        printf("%d Black Pawn-0\n", BlackPawns[0]);
        printf("%d Black Bishop-0\n", BlackBishops[0]);
        printf("%d Black Bishop-1\n", BlackBishops[1]);
        printf("%d White Queen-0\n", WhiteQueen[0]);
        printf("Whose turn: %s\n", whoseTurn == 0 ? "White" : "Black");
    }else{
        return 0;
    }

    
}
