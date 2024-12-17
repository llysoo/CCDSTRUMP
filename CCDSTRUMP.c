/*
Description: The program is a mixture of the tic-tactoe and sudoku game that lets two players, A and B, play against each other.
Programmed by: Chryzza Jorjet De Guzman, Gwyneth Allyson Moral, Dennise Nicole Tongol; S15
Last modified: 04/07/2023
Version: 1.0
*/

#include <stdio.h>
#include <stdlib.h>

/* function to clear the terminal*/
void clear()
{
      system ("cls");
}

void displayDivider()
{
     printf("========================================================================================================================");
}

/*displays the menu*/
void displayMenu(){
	printf (" \n Please Choose: \n");
	printf (" '1' for Play \n '2' for How to Play \n '3' for Quit\n");
}

/*Displays the board with coordinates 1-3*/
void displayBoard(int board[][3])
{
  int nRow, nCol;

  printf("\n  +---+---+---+\n");

  for (nRow = 0; nRow < 3; nRow++){
    printf("%d |", nRow + 1); // prints numbers at the side of the board
    for (nCol = 0; nCol < 3; nCol++){
      printf(" %d |", board[nRow][nCol]);
    }
    printf("\n");
    printf("  +---+---+---+\n");
  }
  for (nCol = 0; nCol < 3; nCol++){ // prints the numbers at the bottom of board
    printf("   %d", nCol + 1);
  }
  printf("\n");
}

/*displays instruction*/
void displayInstruc()
{
  printf("-Each player (Player A and Player B) will take turns putting pieces on the board");
  printf("\n");
  printf("\n-Players will choose from available pieces (1-9), \npieces that are already used cannot be used again");
  printf("\n");
  printf("\n-Players will choose from available spaces from the table");
  printf("\n");
  printf("\n-Once a straight row or column is made, \nthe total will be checked if it is less than of equal to 15");
}

//checkd if the game is over or not
int gameOver(int board[3][3])
{
  int i, j, over = 0, sumRows, sumCols;
  int rElements = 0, cElements = 0;

//for row
  for (i = 0; i < 3; i++)
  {
    sumRows = 0;
    rElements = 0;

    for (j = 0; j < 3; j++)
    {
      if (board[i][j] != 0)
      {
        sumRows = sumRows + board[i][j]; //calculates the sum in a row
        rElements++;
      }
    }

    if (rElements == 3 && (sumRows == 15 || sumRows < 15)) //checkes if winning conditions in a row is met
      over = 1;
  }

//for column
  for (j = 0; j < 3; j++)
  {
    sumCols = 0;
    cElements = 0;

    for (i = 0; i < 3; i++)
    {
      if (board[i][j] != 0)
      {
        sumCols = sumCols + board[i][j]; //calculates sum in a column
        cElements++;
      }
    }

    if (cElements == 3 && (sumCols == 15 || sumCols < 15)) //checkes if winning conditions in a cloumn is met
      over = 1;
  }

  return over;
}

//function to check who and declare the winner
int declareWinner(int board[3][3], char currentPlayer)
{
  int i, j, sumRows, sumCols;
  int rElements = 0, cElements = 0;
  // initialize variables
  char winner = '\0';

//checking for rows
  for (i = 0; i < 3; i++)
  {
    sumRows = 0;
    rElements = 0;

    for (j = 0; j < 3; j++)
    {
      if (board[i][j] != 0)
      {
        sumRows = sumRows + board[i][j]; 
        rElements++;
      }
    }

    if (rElements == 3 && sumRows == 15)
    {
      if (currentPlayer == 'A')
        winner = 'B';

      else
        winner = 'A';
    }

    else if (rElements == 3 && sumRows < 15)
    {
      winner = currentPlayer;
    }
  }

//checking for columns
  for (j = 0; j < 3; j++)
  {
    sumCols = 0;
    cElements = 0;

    for (i = 0; i < 3; i++)
    {
      if (board[i][j] != 0)
      {
        sumCols = sumCols + board[i][j];
        cElements++;
      }
    }

    if (cElements == 3 && sumCols == 15)
    {
      if (currentPlayer == 'A')
        winner = 'B';

      else
        winner = 'A';
    }

    else if (cElements == 3 && sumCols < 15)
    {
      winner = currentPlayer;
    }
  }

  return winner;
}

//Shows all available pegs from 1-9
void showAvailablePiece(int piece[9])
{
  int i = 0;
  printf("\nAvailable pieces: ");
  for (i = 0; i < 9; i++)
  {
    if (piece[i] != 0)
    {
      printf("%d ", piece[i]);
    }
  }
  printf("\n");
}

//function for gameplay 
void gameStart(int board[3][3], int piece[9]) 
{
  int row, col, nPiece, nExists;
  char player = 'A';

  while (!gameOver(board))
  {
    displayBoard(board);
    showAvailablePiece(piece);
    printf("Player %c, choose a piece: ", player);
    scanf("%d", &nPiece);
    if (nPiece > 9 || nPiece < 1)
    {
      clear();
      printf("Invalid input! Number entered is out of scope. Try again.");
      
    }
    else
    {
      nExists = 0;
      int i = 0;
      for (i = 0; i < 9; i++)
      {
        if (nPiece == piece[i])
        {
          nExists = 1;
        }
      }
      if (nExists == 0)
      {
      	clear();
        printf("Piece already used! Try again.");
      }
      else
      {
        printf("Player %c, Enter a position (row, column): ", player);
        scanf("%d %d", &row, &col);
        clear();
        if (row > 3 || row < 1 || col > 3 || col < 1)
        {
          printf("Invalid input! Position is out of bound. Try again.");
        }
        else
        {
          if (board[row - 1][col - 1] != 0)
          {
            printf("Space already taken! Try again.");
          }
          else
          {
            board[row - 1][col - 1] = nPiece;
            int i = 0;
            for (i = 0; i < 9; i++)
            {
              if (nPiece == piece[i])
              {
                piece[i] = 0;
              }
            }
            if (player == 'A') //for changing of players
            {
              player = 'B';
            }
            else
            {
              player = 'A';
            }
          }
        }
      }
    }
  }
  printf("Player %c wins!\n", declareWinner(board, player));

}

/*causes a delay*/
void delay(){
	int c, d;
	for (c = 1; c <= 100000; c++)
      	 for (d = 1; d <= 100000; d++)
       		{}
}

int main(){
  
  displayDivider();
  printf ("Welcome to our CCDSTRU Machine Project! \nCreated by: Chryzza De Guzman, Allyson Moral, Dennise Tongol\n");
  displayDivider();
  	
  int nQuit = 0;
  

  while (!nQuit)
  { // continue if quit != 1
  	int nChoice = 0;

    displayMenu();
    printf("\nEnter choice: "); // user input
    scanf("%d", &nChoice);


    switch (nChoice) // determine what the user wants to do
    { 
    case 1: // starts the game
    { 
    	clear();
    	int board[3][3] = {// initialize board with 0's first
                     {0, 0, 0},
                     {0, 0, 0},
                     {0, 0, 0}};
  		int piece[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    	gameStart(board, piece);
    }
    break;
    case 2: //shows the instruction
    {
      clear();
      displayInstruc();
      delay();
      clear();
    }
    break;
    case 3: //terminates the game
    {
      nQuit = 1;
      clear();
      printf("Game will terminate");
      delay();
      clear();
    }
    break;

    default: //shows if value entered is not within the scope of the sitch values
    {
      clear();
      printf("Invalid Input! Try again.");
    }
    }
  }
  return 0;
}
