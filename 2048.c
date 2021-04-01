#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int score = 0;

int displayBoard(int board[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d  ", board[i][j]);
        }
        printf("\n");
    }
    return 1;
}

int placeNumber(int board[5][5])
{

    //find valid candidates

    int validCan[25][2] = {0};
    int k = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == 0)
            {
                validCan[k][0] = i;
                validCan[k][1] = j;
                k++;
            }
        }
    }

    if (k == 0)
    { // if all positions are full
        return 0;
    }

    //assign random to either 2 or 4

    int r = rand() % k;
    int p = rand() % 2;
    board[validCan[r][0]][validCan[r][1]] = ((p == 1) ? 2 : 4);
    return 1;
}

void rotateBoard(int board[5][5])
{ // rotate board clockwise
    int n = 5;
    for (int i = 0; i < n; i++)
    { // first we transpose the matrix
        for (int j = i; j < n; j++)
        {
            int temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }

    for (int i = 0; i < n; i++)
    { //then flip the values to get rotated array
        for (int j = 0; j < (n / 2); j++)
        {
            int temp = board[i][j];
            board[i][j] = board[i][n - j - 1];
            board[i][n - j - 1] = temp;
        }
    }
}

void slideOneRowLeft(int row[5])
{
    int n = 5;
    for (int k = 0; k < n - 1; k++) // loop n-1 times to shift all elements to left
    {
        for (int i = (n - 1); i > 0; i--) // shift elements to left
        {
            if (row[i - 1] == 0)
            {
                row[i - 1] = row[i];
                row[i] = 0;
            }
        }
    }

    for (int i = 0; i < n - 1; i++) // merge similar elements
    {
        if (row[i] == row[i + 1])
        {
            row[i] = row[i] * 2;
            score = score + row[i]; // add the score
            row[i + 1] = 0;
        }
    }

    for (int k = 0; k < n - 1; k++) // loop n-1 times to shift all elements to left
    {
        for (int i = (n - 1); i > 0; i--) // shift elements to left
        {
            if (row[i - 1] == 0)
            {
                row[i - 1] = row[i];
                row[i] = 0;
            }
        }
    }
}

void slideAllRowsLeft(int board[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        slideOneRowLeft(board[i]);
    }
}

int goUp(int board[5][5])
{
    rotateBoard(board);
    rotateBoard(board);
    rotateBoard(board);
    slideAllRowsLeft(board);
    rotateBoard(board);
    placeNumber(board);
    return 1;
}
int goDown(int board[5][5])
{
    rotateBoard(board);
    slideAllRowsLeft(board);
    rotateBoard(board);
    rotateBoard(board);
    rotateBoard(board);
    placeNumber(board);
    return 1;
}
int goLeft(int board[5][5])
{
    slideAllRowsLeft(board);
    placeNumber(board);
    return 1;
}
int goRight(int board[5][5])
{
    rotateBoard(board);
    rotateBoard(board);
    slideAllRowsLeft(board);
    rotateBoard(board);
    rotateBoard(board);
    placeNumber(board);
    return 1;
}

int main()
{
    srand(time(0));

    int board[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    };

    //init
    placeNumber(board);
    placeNumber(board);
    int c;

    //actual game starts
    while (1)
    {
        system("clear");
        displayBoard(board);
        printf("Score: %d\n", score);
        printf("Enter your choice:");
        scanf("%d", &c);
        printf("asdadasdasdas\n");
        int ex = 0;
        switch (c)
        {
        case 1: //go right
            goRight(board);
            break;
        case 2: //go left
            goLeft(board);
            break;
        case 3: //go up
            goUp(board);
            break;
        case 4: //go down
            goDown(board);
            break;
        default:
            ex = 1;
            break;
        }
        if (ex == 1)
        {
            printf("\nEnd.");
            break;
        }
    }
    return 0;
}