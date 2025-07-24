



using System;
using System.IO;

class ChessBoard
{
    static char[,] board = new char[8, 8];
    static bool whiteToMove = true;

    static void Main()
    {
        LoadFEN("fen.txt");
        PrintBoard();
        PrintFEN();
    }

    static void LoadFEN(string filename)
    {
        if (!File.Exists(filename))
        {
            Console.WriteLine("FEN file not found.");
            return;
        }

        string fen = File.ReadAllText(filename).Trim();
        string[] parts = fen.Split(' ');

        if (parts.Length < 2)
        {
            Console.WriteLine("Invalid FEN string.");
            return;
        }

        string[] rows = parts[0].Split('/');
        for (int i = 0; i < 8; i++)
        {
            int col = 0;
            foreach (char c in rows[i])
            {
                if (char.IsDigit(c))
                {
                    int empty = c - '0';
                    for (int j = 0; j < empty; j++)
                        board[i, col++] = ' ';
                }
                else
                {
                    board[i, col++] = c;
                }
            }
        }

        whiteToMove = parts[1] == "w";
    }

    static void PrintBoard()
    {
        Console.WriteLine();
        for (int i = 0; i < 8; i++)
        {
            Console.Write(8 - i + " ");
            for (int j = 0; j < 8; j++)
            {
                Console.Write((board[i, j] == '\0' ? ' ' : board[i, j]) + " ");
            }
            Console.WriteLine();
        }
        Console.WriteLine("  a b c d e f g h\n");
    }

    static void PrintFEN()
    {
        string fen = "";

        for (int i = 0; i < 8; i++)
        {
            int emptyCount = 0;
            for (int j = 0; j < 8; j++)
            {
                char c = board[i, j];
                if (c == ' ' || c == '\0')
                {
                    emptyCount++;
                }
                else
                {
                    if (emptyCount > 0)
                    {
                        fen += emptyCount.ToString();
                        emptyCount = 0;
                    }
                    fen += c;
                }
            }
            if (emptyCount > 0)
                fen += emptyCount.ToString();
            if (i < 7)
                fen += "/";
        }

        fen += whiteToMove ? " w" : " b";
        fen += " - - 0 1"; // placeholder: no castling, en passant, half/full move count

        Console.WriteLine("FEN: " + fen);
    }
}
