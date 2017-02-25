/**
 * fifteen.c
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

// blank tile
int blank_i, blank_j;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
void initBuffer(int []);
bool checkMove(int, int);
bool won(void);

int main(int argc, string argv[])
{
    const long SLEEP_TIME = 500000;
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
    FILE *file = fopen("log.txt", "w");
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
        int tile = get_int();
        
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
            usleep(SLEEP_TIME); // usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(SLEEP_TIME); // usleep(500000);
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
    
    printf("\033[%d;%dm", 37, 46);
}

/**
 * Greets player.
 */
void greet(void)
{
    const long SLEEP_TIME = 2000000;
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(SLEEP_TIME); // usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    /*
    * These constants will be subtracted from the dimention:
    - END_ROW   - bottom row of the board
    - ONE_PLACE - the place where the tile number 1 is located
    - TWO_PLACE - the place where the tile number 2 is located
    MODULO    - it is used to define even or odd dimension
    */
    enum constants {
        END_ROW = 1, ONE_PLACE = 2, MODULO = 2, TWO_PLACE = 3
    };
    int tileNumber = d * d;
    // bottom right corner of the board
    const int CORNER = d - 1;
    blank_i = CORNER;
    blank_j = CORNER;
    
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            // set tile's value
            board[i][j] = --tileNumber;
        }
    }
    if (d % MODULO == 0) {
        // swap 2 and 1
        board[d - END_ROW][d - TWO_PLACE] -= board[d - END_ROW][d - ONE_PLACE]++;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            // condition for underscore in blank tile location
            if(board[i][j] == 0) {
                printf("%4c", '_');
            }
            // print tile's value
            else {
                printf("%4i", board[i][j]);
            }
        }
        // print new line
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    /*
    given: tile number, not the tile location!
    
    OFFSET - offset on the board
    MODULO - it is used to separate rows and columns
    */
    enum constants {
        OFFSET = 1, MODULO = 10
    };
    int tile_i, tile_j;
    const int MAX = d * d;
    int buffer [MAX];
    // is tile number from the board ?
    if (tile < OFFSET || tile > (d * d - OFFSET)) {
        return false;
    }
    
    // find the tile location
    initBuffer(buffer);
    tile_i = buffer[tile] / MODULO;
    tile_j = buffer[tile] % MODULO;
    
    // edit the board array only if the move is legal
    if(!checkMove(abs(blank_i - tile_i), abs(blank_j - tile_j))){
        return false;
    }

    // swap tile and blank tile
    board[blank_i][blank_j] = tile;
    board[tile_i][tile_j] = 0;
    
    // keep track of blank tile location
    blank_i = tile_i;
    blank_j = tile_j;
    
    return true;
}

/**
 * Initializing the buffer to describe tiles.
 */
void initBuffer(int buffer[])
{
    // it is used to separate rows and columns
    const int MODULO = 10;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            buffer[board[i][j]] = i * MODULO + j;
        }
    }
}

/**
 * Check the tile move on legality.
 */
bool checkMove(int abs_i, int abs_j)
{
    // offset on the board
    const int OFFSET = 1;
    // Von Neumann neighborhood || offset more than 1
    if((abs_i == abs_j) || (abs_i > OFFSET || abs_j > OFFSET)){
        return false;
    }
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    /*
    game is won when tiles are in increasing order
        (left to right, top to bottom)
    */
    const int CORNER = d * d;
    int tileNumber = 0;
    
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            // iterate over board and check the values
            if(board[i][j] != (++tileNumber % CORNER)) {
                // if any value is incorrect, return false
                return false;
            }
        }
    }
    // return true once all tiles are checked
    return true;
}
