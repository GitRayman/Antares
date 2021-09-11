//MIT Licensed Tetris game from here: https://github.com/Gregwar/ASCII-Tetris

//Background image by David Emrich via unsplash.com

//Adapted for P2 and FlexSpin by Raymond Allen
//Currently uses host's keyboard for control so leave terminal window open

#include "../Antares/Antares.h" //RJA
#include "Colors.h"

char filename[] = "Tetris1.png";  //background image

//Game data
#define Blocks_x 12  //playing screen width in blocks
#define Blocks_y 15  //playing screen height in blocks


//block data
#define Block_pix 32
#define Block_add 0xE2000  //address of block image in GRAM
#define Block_handle 2

struct tetris_level {
    int score;
    int nsec;
};

struct tetris {
    char **game;
    int w;
    int h;
    int level;
    int gameover;
    int score;
    struct tetris_block {
        char data[5][5];
        int w;
        int h;
    } current;
    int x;
    int y;
};

struct tetris_block blocks[] =
{
    {{"##", 
         "##"},
    2, 2
    },
    {{" X ",
         "XXX"},
    3, 2
    },
    {{"@@@@"},
        4, 1},
    {{"OO",
         "O ",
         "O "},
    2, 3},
    {{"&&",
         " &",
         " &"},
    2, 3},
    {{"ZZ ",
         " ZZ"},
    3, 2}
};

struct tetris_level levels[]=
{
    {0,
        1200000},
    {1500,
        900000},
    {8000,
        700000},
    {20000,
        500000},
    {40000,
        400000},
    {75000,
        300000},
    {100000,
        200000}
};

#define TETRIS_PIECES (sizeof(blocks)/sizeof(struct tetris_block))
#define TETRIS_LEVELS (sizeof(levels)/sizeof(struct tetris_level))


void
tetris_init(struct tetris *t,int w,int h) {
    int x, y;
    t->level = 1;
    t->score = 0;
    t->gameover = 0;
    t->w = w;
    t->h = h;
    t->game = malloc(sizeof(char *)*w);
    for (x=0; x<w; x++) {
        t->game[x] = malloc(sizeof(char)*h);
        for (y=0; y<h; y++)
            t->game[x][y] = ' ';
    }
}

void
tetris_clean(struct tetris *t) {
    int x;
    for (x=0; x<t->w; x++) {
        free(t->game[x]);
    }
    free(t->game);
}

//RJA:  Terminal escape sequenses
#define ESC "\x1b"
#define CSI "\x1b["

void
tetris_print(struct tetris *t) {
    //start eve with background image
    Clear();
    BitmapHandle(0);  //handle for background image
    Begin(BITMAPS);
    Vertex2f(0, 0);  //RJA: This paints the background image.  
    
    //set vertex scale format to 1:1
    FormatVertex(VERTEX_FORMAT_ONE);  //change Vertex2f scale to 1:1

    //draw text at top
    DrawText(HSIZE / 2, VSIZE / 16, 34, OPT_CENTERX, (char*)"TETRIS", BlueRibbon);

    //draw score on bottom
    char score[255];
    sprintf(score,"Level= %d, Score = %d",t->level, t->score);
    DrawText(HSIZE / 2, 665, 25, OPT_CENTERX, (char*)score, GuardsmanRed);

    
    
    //Draw play area in dark blue
    ColorRGB24(Stratos);
    int Offset_x = (HSIZE / 2 - Blocks_x * 32 / 2);  //xoffset in pixels to upper left corner of play area
    int Offset_y = (VSIZE / 2 - Blocks_y * 32 / 2)+50;  //yoffset in pixels to upper left corner of play area
    //change origin
    TranslateY(Offset_y);  
    TranslateX(Offset_x);
    //draw play area rectangle
    Begin(RECTS);
    Vertex2f(0, 0);
    Vertex2f((Blocks_x<<5), (Blocks_y<<5));

    //Prepare to draw blocks
    Begin(BITMAPS);
    BitmapHandle(Block_handle);



    //rja clearing screen with escape codes
    printf(CSI "2J"); // Clear screen
    printf(CSI "1;1H"); // Home

    int x,y;
    //for (x=0; x<30; x++)
    //    printf("\n");
    printf("[LEVEL: %d | SCORE: %d]\n", t->level, t->score);
    for (x=0; x<2*t->w+2; x++)
        printf("~");
    printf("\n");
    for (y=0; y<t->h; y++) {
        printf ("!");
        for (x=0; x<t->w; x++) {
            if (x>=t->x && y>=t->y 
                    && x<(t->x+t->current.w) && y<(t->y+t->current.h) 
                    && t->current.data[y-t->y][x-t->x]!=' ')
            {//RJA:  Print the currently falling block
                printf("%c ", t->current.data[y-t->y][x-t->x]);
                char c = t->current.data[y - t->y][x - t->x];                
                if (c != ' ')
                    DrawBlock(x, y, c); //draw this block
            }
            else
            {//RJA:  Print everthing except the falling block
                printf("%c ", t->game[x][y]);
                char c = t->game[x][y];
                if (c != ' ')
                    DrawBlock(x, y, c); //draw this block
            }
        }
        printf ("!\n");
    }
    for (x=0; x<2*t->w+2; x++)
        printf("~");
    printf("\n");

    //finish eve
    swap();

}

int DrawBlock(int x, int y, char c)
{//Draw block with color depending on c
    COLORREF clr;
    switch (c)
    {
        case '#':
            clr = Yellow;
            break;
        case 'X':
            clr = BlueBell;
            break;
        case '@':
            clr = RazzleDazzleRose;
            break;
        case 'O':
            clr = ScreaminGreen4;
            break;
        case '&':
            clr = Supernova;
            break;
        case 'Z':
            clr = AtomicTangerine;
            break;
        default:
            clr = White;
            break;
    }
    ColorRGB24(clr); //set color
    Vertex2f(x <<5, y <<5);
}

int
tetris_hittest(struct tetris *t) {
    int x,y,X,Y;
    struct tetris_block b=t->current;
    for (x=0; x<b.w; x++)
        for (y=0; y<b.h; y++) {
            X=t->x+x;
            Y=t->y+y;
            if (X<0 || X>=t->w)
                return 1;
            if (b.data[y][x]!=' ') {
                if ((Y>=t->h) || 
                        (X>=0 && X<t->w && Y>=0 && t->game[X][Y]!=' ')) {
                    return 1;
                }
            }
        }
    return 0;
}

void
tetris_new_block(struct tetris *t) {
    uint32_t r = _rnd();
    t->current=blocks[r%TETRIS_PIECES]; //RJA random to rand(), then to getrnd()
    t->x=(t->w/2) - (t->current.w/2);
    t->y=0;
    if (tetris_hittest(t)) {
        t->gameover=1;
    }
}

void
tetris_print_block(struct tetris *t) {
    int x,y,X,Y;
    struct tetris_block b=t->current;
    for (x=0; x<b.w; x++)
        for (y=0; y<b.h; y++) {
            if (b.data[y][x]!=' ')
                t->game[t->x+x][t->y+y]=b.data[y][x];
        }
}

void
tetris_rotate(struct tetris *t) {
    struct tetris_block b=t->current;
    struct tetris_block s=b;
    int x,y;
    b.w=s.h;
    b.h=s.w;
    for (x=0; x<s.w; x++)
        for (y=0; y<s.h; y++) {
            b.data[x][y]=s.data[s.h-y-1][x];
        }
    x=t->x;
    y=t->y;
    t->x-=(b.w-s.w)/2;
    t->y-=(b.h-s.h)/2;
    t->current=b;
    if (tetris_hittest(t)) {
        t->current=s;
        t->x=x;
        t->y=y;
    }
}

void
tetris_gravity(struct tetris *t) {
    int x,y;
    t->y++;
    if (tetris_hittest(t)) {
        t->y--;
        tetris_print_block(t);
        tetris_new_block(t);
    }
}

void
tetris_fall(struct tetris *t, int l) {
    int x,y;
    for (y=l; y>0; y--) {
        for (x=0; x<t->w; x++)
            t->game[x][y]=t->game[x][y-1];
    }
    for (x=0; x<t->w; x++)
        t->game[x][0]=' ';
}

void
tetris_check_lines(struct tetris *t) {
    int x,y,l;
    int p=100;
    for (y=t->h-1; y>=0; y--) {
        l=1;
        for (x=0; x<t->w && l; x++) {
            if (t->game[x][y]==' ') {
                l=0;
            }
        }
        if (l) {
            t->score += p;
            p*=2;
            tetris_fall(t, y);
            y++;
        }
    }
}

int
tetris_level(struct tetris *t) { //RJA this appears to adjust level by current score and set the speed of the game via the return value
    int i;
    for (i=0; i<(int)TETRIS_LEVELS; i++) {
        if (t->score>=levels[i].score) {
            t->level = i+1;
        } else break;
    }
    return levels[t->level-1].nsec;
}


//RJA Original used timespec and nanosleep to set game speed, but we don't have nanosleep, so adjusting a bit
uint32_t ns; //nanoseconds to sleep



void
tetris_run(int w, int h) {

    //Note:  Clock frequency set with enum in Platform.h
    //RJA:  check clock freq
    int cf = _clockfreq();
    printf("clock freq= %d\n", cf);


    struct tetris t;
    char cmd;
    int count=0;
    tetris_init(&t, w, h);
    srand(time(NULL));

    ns =1000000;


    tetris_new_block(&t);
    while (!t.gameover) {
        usleep(ns/1000);//RJA nanosleep(&tm, NULL);
        count++;
        if (count%50 == 0) {
            tetris_print(&t);
        }
        if (count%350 == 0) {
            tetris_gravity(&t);
            tetris_check_lines(&t);
        }

        int cmd2;//RJA need signed cmd to handle -1 return value
        cmd2 = _rxraw(1);//rja using this to avoid blocking with getchar()
        while (cmd2>0) {    
            switch (cmd2) {//RJA changing to WASD
                case 'a':
                    t.x--;
                    if (tetris_hittest(&t))
                        t.x++;
                    break;
                case 'd':
                    t.x++;
                    if (tetris_hittest(&t))
                        t.x--;
                    break;
                case 's':
                    tetris_gravity(&t);
                    break;
                case 'w':
                    tetris_rotate(&t);
                    break;
            }
            cmd2 = _rxraw(1);
        }
        ns =tetris_level(&t);  //RJA:  Adjust game speed
    }

    tetris_print(&t);
    printf("*** GAME OVER ***\n");

}



void main(void) 
{//Tetris main 
    begin();  //Start Antares display



    //load and configure background imate
    BitmapHandle(0);  //Note:  The load() command overwrite settings of the selected handle
    load(filename);
    //Configure_Bitmap_Handle(0, 512, 0, 0, 0, 1280, 720, 1280, PALETTED565);  //Don't need to do this because load() does it for us

    //load and configure block image
    Load_RAW(Block_add, (char*)"tblock1.raw");
    Configure_Bitmap_Handle(Block_handle, Block_add, 0, 0, 0, 32, 32, 64, ARGB4);

    swap();
    tetris_run(Blocks_x, Blocks_y);  //Play Tetris
    for (;;) {}
    return;
}
