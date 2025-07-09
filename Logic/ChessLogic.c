#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
 FILE *FEN
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