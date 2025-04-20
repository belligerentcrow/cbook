//step 19

/*** includes ***/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** data ***/
struct termios orig_termios;


/*** terminal ***/

//error handling
void die(const char *s){
    perror(s);
    exit(1);
}


void disableRawMode(){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1){die("tcsetattr");}
}

void enableRawMode(){
    if(tcgetattr(STDIN_FILENO,&orig_termios)==-1){ die("tcgetattr"); }
    atexit(disableRawMode); //calls disable raw mode on program exit
    
    struct termios raw = orig_termios;

    //blocks software flow control - IXON blocks usage of ctrl-s and ctrl-q 
    //ICRNL - for Input_flag, CR-CarriageReturn NL-Newline -> ctrl-m
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    //turn off output processing features - turn off OPOST flag. postprocessing of input
    //now we need to add \r before \n for newline
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    //checks for ISIG, turns off SIGINT and SIGTSTP inputs (ctrl-c, ctrl-z)
    //the not operator lets program filter out these flags.
    //IEXTEN blocks ctrl-v, control character
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //local flags. echo is a bitflag-> with NOT operator
    //control characters
    raw.c_cc[VMIN]=0;
    raw.c_cc[VTIME] =1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)==-1){die("tcsetattr");};
}

/*** init ***/

int main(){
    enableRawMode();
    while(1){
        char c = '\0';
        if(read(STDIN_FILENO, &c, 1) == -1 && errno !=EAGAIN){die("read");}
        if(iscntrl(c)){
            printf("%d\r\n",c); 
        }else{
            printf("%d ('%c')\r\n",c,c);
        }
        if(c == 'q') break;
    }
    return 0;
}