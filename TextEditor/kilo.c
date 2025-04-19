//step 15

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){
    tcgetattr(STDIN_FILENO,&orig_termios);
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

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main(){
    enableRawMode();
    char c;
    
    while(read(STDIN_FILENO, &c, 1)==1 && c!='q'){
        if(iscntrl(c)){ //tests if it is a control character
            printf("%d\r\n",c); 
        }else{
            printf("%d ('%c')\r\n",c,c);
        }
    }

    return 0;
}