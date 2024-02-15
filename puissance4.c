#include <stdio.h>
#include <stdlib.h>

#define NBLIN 6
#define NBCOL 7

void	initArray(int nbLin, int nbCol, int iArray[nbLin][nbCol], int value)
{
	int	i;
	int	j;

	for (i = 0; i < nbLin; i++)
	{
		for (j = 0; j < nbCol; j++)
		{
			iArray[i][j] = value;
		}
	}
}

void	showArray(int nbLin, int nbCol, int iArray[nbLin][nbCol])
{
	int	i;
	int	j;

	for (i = 0; i < nbLin; i++)
	{
		for (j = 0; j < nbCol; j++)
		{
			printf("%d ", iArray[i][j]);
		}
		printf("\n");
	}
}

int	placePawn(int nbLin, int nbCol, int iArray[nbLin][nbCol], int pawnCol,
		int pawn)
{
	int	i;

	for (i = nbLin; i >= 0; i--)
	{
		if (iArray[i][pawnCol] == 0)
		{
			iArray[i][pawnCol] = pawn;
			break ;
		}
	}
	return (i);
}

int	getColumnForPawn(int nbLin, int nbCol, int iArray[nbLin][nbCol])
{
	int	choiceCol;
	int	nb;

	nb = 1;
	do
	{
		choiceCol = 0;
		printf("Enter the coordinate of the column you want to put your pawn on: ");
		if (scanf("%d", &choiceCol) != 1)
		{
			printf("Input Error");
			exit(-1);
		}
		else if (choiceCol >= nbCol || choiceCol < 0)
		{
			printf("Wrong number of column (outside of the board), please re-try.\n");
			nb = 0;
		}
		else if (iArray[0][choiceCol] != 0)
		{
			printf("\nThis column is full so you can't add any more pawn, please re-try.\n");
			nb = 0;
		}
		else
		{
			nb = 1;
		}
	} while (nb == 0);
	return (choiceCol);
}

int	checkFourInLine(int nbLin, int nbCol, int iArray[nbLin][nbCol], int pawnLin,
		int pawnCol)
{
	int	i;
	int	sum;

	sum = 1;
	i = 1;
	while (((pawnCol + i) < nbCol) && iArray[pawnLin][pawnCol
		+ i] == iArray[pawnLin][pawnCol] && sum < 4)
	{
		sum++;
		i++;
	}
	i = 1;
	while (((pawnCol - i) >= 0) && iArray[pawnLin][pawnCol
		- i] == iArray[pawnLin][pawnCol] && sum < 4)
	{
		sum++;
		i++;
	}
	if (sum == 4)
	{
		return (1);
	}
	i = 1;
	sum = 1;
	while (((pawnLin + i) < nbLin) && iArray[pawnLin
		+ i][pawnCol] == iArray[pawnLin][pawnCol] && sum < 4)
	{
		sum++;
		i++;
	}
	i = 1;
	while (((pawnLin - i) >= 0) && iArray[pawnLin
		- i][pawnCol] == iArray[pawnLin][pawnCol] && sum < 4)
	{
		sum++;
		i++;
	}
	if (sum == 4)
	{
		return (1);
	}
	i = 1;
	sum = 1;
	while ((pawnLin + i < nbLin) && (pawnCol + i < nbCol)
		&& iArray[pawnLin][pawnCol] == iArray[pawnLin + i][pawnCol + i]
		&& sum < 4)
	{
		sum++;
		i++;
	}
	i = 1;
	while ((pawnLin - i < nbLin) && (pawnCol - i < nbCol)
		&& iArray[pawnLin][pawnCol] == iArray[pawnLin - i][pawnCol - i]
		&& sum < 4)
	{
		sum++;
		i++;
	}
	if (sum == 4)
	{
		return (1);
	}
	sum = 1;
	i = 1;
	while ((pawnLin - i < nbLin) && (pawnCol + i < nbCol)
		&& iArray[pawnLin][pawnCol] == iArray[pawnLin - i][pawnCol + i]
		&& sum < 4)
	{
		sum++;
		i++;
	}
	i = 1;
	while ((pawnLin + i < nbLin) && (pawnCol - i < nbCol)
		&& iArray[pawnLin][pawnCol] == iArray[pawnLin + i][pawnCol - i]
		&& sum < 4)
	{
		sum++;
		i++;
	}
	if (sum == 4)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	runAStep(int nbLin, int nbCol, int iArray[nbLin][nbCol], int numPlayer)
{
	int	colonne;
	int	ligne;

	printf("\n#### Player %d, your turn ####\n", numPlayer);
	colonne = getColumnForPawn(nbLin, nbCol, iArray);
	ligne = placePawn(nbLin, nbCol, iArray, colonne, numPlayer);
	return (checkFourInLine(nbLin, nbCol, iArray, ligne, colonne));
}

void	clearScreen(void)
{
	/* Animation - clear the previous display */
	printf("%c[2J", 0x1B);
	/* Animation - Move the cursor top-left */
	printf("%c[%d;%dH", 0x1B, 1, 1);
}

void	showBoard(int nbLin, int nbCol, int iArray[nbLin][nbCol])
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	f;

	clearScreen();
	for (k = 0; k < nbLin; k++)
	{
		for (l = 0; l < nbCol; l++)
		{
			if (iArray[k][l] == 0)
			{
				printf("|   ");
			}
			else if (iArray[k][l] == 1)
			{
				printf("|\033[31;01m o\033[00m ");
			}
			else if (iArray[k][l] == 2)
			{
				printf("|\033[36;01m o\033[00m ");
			}
		}
		printf("|  ");
		printf("\n");
	}
	for (f = 0; f < NBCOL; f++)
	{
		printf(" ---");
	}
	printf("\n");
	for (f = 0; f < NBCOL; f++)
	{
		printf("  %d ", f);
	}
	printf("\n");
	for (i = 0; i < nbLin; i++)
	{
		for (j = 0; j < nbCol; j++)
		{
			printf("%d ", iArray[i][j]);
		}
		printf("\n");
	}
}

int	runGame(int nbLin, int nbCol, int iArray[nbLin][nbCol])
{
	int	flag;
	int	player;
	int	numPlayer;
	int	nbCase;
	int	gameSet;

	player = 0;
	nbCase = (nbLin + 1) * (nbCol + 1);
	do
	{
		flag = 1;
		numPlayer = (player % 2) + 1;
		gameSet = runAStep(nbLin, nbCol, iArray, numPlayer);
		showBoard(nbLin, nbCol, iArray);
		if (gameSet == 1)
		{
			return (numPlayer);
		}
		nbCase--;
		player++;
		if (nbCase <= 0)
		{
			flag = 0;
		}
	} while (flag == 1);
	showArray(nbLin, nbCol, iArray);
	return (0);
}

void	endOfGame(int numWinner)
{
	if (numWinner == 0)
	{
		printf("\n GAME OVER");
		printf("\nIt's a draw!\n");
	}
	else if (numWinner == 1)
	{
		printf("\n player 1 winner");
		printf("\n game over player 2");
	}
	else if (numWinner == 2)
	{
		printf("\n player 2 winner");
		printf("\n game over player 1");
	}
}

int	main(void)
{
	int	numWinner;
	int	board[NBLIN][NBCOL];

	initArray(NBLIN, NBCOL, board, 0);
	numWinner = runGame(NBLIN, NBCOL, board);
	endOfGame(numWinner);
	return (0);
}
