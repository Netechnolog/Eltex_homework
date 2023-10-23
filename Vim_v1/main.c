#include "main.h"

/*Standart func's call window*/
void sig_winch(int signo)
{
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
resizeterm(size.ws_row, size.ws_col);
}

int len(int lineno, int COLS);

int main(void){
    bool state_file = FALSE;
    char FILE_NAME[150];
    int coord_x = 0, coord_y = 0;
    int l, i, n;
    int ch = 0;
    int line = 0;

/*Here we start work with window, with help "start_color"
turn on work's func with color. Func "cbreak" turn off
raw(full control over keypad). Curs_set turn on cursor.
"Keypad(TRUE)" turn on input all cheracters of keypad*/

    initscr();
    start_color();
    cbreak();
    curs_set(TRUE);
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attrset(COLOR_PAIR(1));

    while(ch != KEY_F(3)){
  
    refresh();
    ch = getch();

    switch(ch){

/*Screen navigation*/

    case KEY_DOWN:
    if(coord_y >= 0)
    ++coord_y;
    /*This will be in v.2*/
    //scrl(1);
    break;


    case KEY_UP:
    if(coord_y > 0)
    --coord_y;
    /*This will be in v.2*/
    //scrl(-1);
    break;


    case KEY_LEFT:
    if(coord_x > 0)
    --coord_x;
    break;


    case KEY_RIGHT:
    if(coord_x >= 0)
    ++coord_x;
    break;   


    case KEY_BACKSPACE:
    delch();
    if(coord_x > 0)
    --coord_x;
    break;


    case '\n':
    ++coord_y;
    break;

/*At first input full path to the file, next open file,
and if file is exist, then output its information,  
if file wasn't searched - will creating file*/

    case KEY_F(1):


    WINDOW* mywin = newwin(4, 70, 33, 100);
    box(mywin,0,0);
    int x1,y1;
    getyx(mywin,y1,x1);
    wmove(mywin, x1+1, y1+1);
    wprintw(mywin, "Enter full path to the file, which you want open:");
    wmove(mywin, x1+2, y1+1);    
    wgetnstr(mywin, FILE_NAME, 150);


    FILE * new_file;
    new_file = fopen(FILE_NAME, "r");
    if (new_file == 0)
    {
        wclear(mywin);
        wrefresh(mywin);
        delwin(mywin);
        move(35, 110);
        printw("Could not open the file so it was created");
        new_file = fopen(FILE_NAME,"w");
        getch();
        curs_set(TRUE);
        wclear(stdscr);
        state_file = TRUE;
        break;
    }
    wclear(mywin);
    wrefresh(mywin);
    delwin(mywin);


    while ((ch = getc(new_file)) != EOF) {
           if (ch == '\n'){
           line++;
           } 
           if (line > LINES - 2){ 
           break;
           }
           addch(ch);
         }
    line = 0;
    fclose (new_file);
    state_file = TRUE;
    coord_x = 0, coord_y = 0;
    move(coord_y, coord_x);
    break;
    

/*Save data of screen in file*/

    case KEY_F(2):
    if(state_file == TRUE){
    new_file = fopen(FILE_NAME, "w");
         for (l = 0; l < LINES - 1; l++) {
           n = len(l, COLS);
           for (i = 0; i < n; i++)
             putc (mvinch (l, i) & A_CHARTEXT, new_file);
           putc('\n', new_file);
         }
    fclose(new_file);
    wclear(stdscr);
    refresh();
    move(35, 110);
    printw("The file was saved successfully.");
    getch();
    wclear(stdscr);
    refresh();
    move(0,0);
    state_file = FALSE;
    }

    else{
    WINDOW* permision = subwin(stdscr, 5, 50, 33, 100); 
        box(permision, 0, 0);
        int coord_x, coord_y;
        getyx(permision, coord_y, coord_x);
        wmove(permision, coord_y+1, coord_x+15);
        waddstr(permision ,"Impossiple save file");
        wmove(permision, coord_y+2, coord_x+10);
        waddstr(permision ,"Press any button to continue...");
        wrefresh(permision);
        getch();
        wclear(permision);
        delwin(permision);
    }
    break;


    default:
    ++coord_x;
    break;


    }
    if(ch == KEY_DOWN || ch == KEY_UP ||ch == KEY_RIGHT || ch == KEY_LEFT || ch =='\n' || ch == KEY_BACKSPACE){
        move(coord_y,coord_x);
    }
    }
    endwin();
    exit(EXIT_SUCCESS);
    return 0;
}

    