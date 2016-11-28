/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// current position of 0
int c_r;
int c_c;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    c_r = d-1;
    c_c = d-1;
    int k = d*d -1;
    for (int i=0; i < d ; i++)
    {
        for (int j=0; j < d ; j++)
        {
           if ( d % 2 == 0)
            {
                board[i][j] = k;
                if ( k == 1)
                {
                    board[i][j] = 2;
                }
                else
                    if ( k == 2)
                    {
                        board[i][j] = 1;
                    }
                k--;
               
                // nested of 1 I want 2
                // int temp = board[d-1][d-3];
                // board[d-1][d-3] = board[d-1][d-2];
                // board[d-1][d-2] = temp;
            }
            else
            {
                board[i][j] = k;
                k--;
            }
            
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i=0; i < d ; i++)
    {
        for (int j=0; j < d ; j++)
        {
            if ( board[i][j] == 0)
                printf(" _ ");
            else
                printf("%2d ",board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int r = c_r;
    int c = c_c;
    int foo = 0;
    int bar = 0;

    // if ( c_r > 0 && c_r < d-1)
    // {
    	if (board[c_r - 1][c_c] == tile) // Top
    	{bar = -1;}
    	else 
    	{
    	    if (board[c_r + 1][c_c] == tile) // bottom
        	{bar = 1;}
        	else bar = 0;
    	}
    // }
    	
    // if ( c_c > 0 || c_c < d-1)
    // {	
    	if (board[c_r][c_c - 1] == tile) // left 
    	{foo = -1;}
    	else 
    	{
        	if (board[c_r][c_c + 1] == tile) // right
        	{foo = 1;}
        	else foo = 0;
    	}
    // }
    
    
    
    if ( bar != 0 || foo != 0 )
    {	
    	r = c_r + bar;
    	c = c_c + foo;
    	board[c_r][c_c] = board[r][c];
    	board[r][c] = 0;
    	c_r = r;
    	c_c = c;
    	return true;
    }
    else printf("Invalid Move!!!\n");
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int k = 1;
    int won = 0;

    for (int i=0; i < d ; i++)
    {
        for (int j=0; j < d ; j++)
        {
         	 if ( board[i][j] == k )
         	 	won++;

         	 k++;
        }
    }
    if (board[d-1][d-1] == 0)
        {
          	won++;
        }
    if ( won == d*d)
    	return true;
    
    return false;
}