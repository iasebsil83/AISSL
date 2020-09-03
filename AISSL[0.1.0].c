// ------------------------ Importations ------------------------
//standard
#include <stdio.h>
#include <stdlib.h>






// ------------------------ Declarations ------------------------
//user
#define CMD_LEN 50

//symbols
#define SYMBOL_NAMES_LEN 10
#define SYMBOLS_LEN 4
const char* symbols [SYMBOLS_LEN] = { //list of symbol names
    "///cri1///",
    "///cri2///",
    "///cri3///",
    "///cri4///"
};
static int symbolsNbr[SYMBOLS_LEN];

//channels
#define CHANNEL_NAMES_LEN 14
#define CHANNELS_LEN 5
const char* channels[CHANNELS_LEN] = { //list of channel names
    "~-~ 165 Hz ~-~",
    "~-~ 240 Hz ~-~",
    "~-~ 350 Hz ~-~",
    "~-~ 440 Hz ~-~",
    "~-~ 540 Hz ~-~"
};

//AISSL data
static unsigned int AISSL_data[SYMBOLS_LEN][CHANNELS_LEN];






// ------------------------ Functions ------------------------
//useful
int strcmpN(const char* s1, char* s2, int len){ //compare first N characters of the 2 strings
    //compare each character
    for(int c=0; c < len; c++)
        if(s1[c] != s2[c])
            return 0;
    return 1;
}

int char2int(char c){ //convert a char to its corresponding integer
    switch(c){
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
    return 0;
}

void printIn4(int i){
    if(i > 9999)
        printf("XXXX");
    else if(i > 999)
        printf("%i",i);
    else if(i > 99)
        printf("0%i",i);
    else if(i > 9)
        printf("00%i",i);
    else
        printf("000%i",i);
}



//AI brain
int getNearest(int ref, int value[SYMBOLS_LEN]){
    //set differences
    for(int s=0; s < SYMBOLS_LEN; s++)
        value[s] = abs(ref-value[s]);

    //get min
    int min = value[0];
    for(int s=1; s < SYMBOLS_LEN; s++)
        if(value[s] < min)
            min = value[s];

    //check if min value exists several times
    int minFound = -1;
    for(int s=0; s < SYMBOLS_LEN; s++){
        if(value[s] == min){
            if(minFound == -1)
                minFound = s; //min value index
            else
                return -1;//found min value 2 times => no conclusion
        }
    }

    return minFound; //index of nearest value
}



//commands
void show(){
    //show full AI data
    printf("AISSL > displaying all AI data :\n");

    //print channel names
    for(int sn=0; sn < SYMBOL_NAMES_LEN; sn++)
        printf(" ");
    for(int c=0; c < CHANNELS_LEN; c++)
        printf(" | %s", channels[c]);
    printf("\n");

    //for each symbol
    for(int s=0; s < SYMBOLS_LEN; s++){

        //print separation line
        for(int sn=0; sn < SYMBOL_NAMES_LEN; sn++)
            printf("-");
        for(int c=0; c < CHANNELS_LEN; c++){
            printf("-+-");
            for(int cn=0; cn < CHANNEL_NAMES_LEN; cn++)
                printf("-");
        }
        printf("\n");

        //print symbol name and values
        printf("%s", symbols[s]);
        for(int c=0; c < CHANNELS_LEN; c++){
            printf(" | ");

            //space before value
            for(int cn=0; cn < CHANNEL_NAMES_LEN/2-2; cn++)
                printf(" ");

            //value
            printIn4(AISSL_data[s][c]);

            //space after value
            for(int cn=0; cn < CHANNEL_NAMES_LEN/2-2; cn++)
                printf(" ");
        }
        printf("\n");
    }
}

void learn(char* cmd){
    //find symbol index
    int si = -1;
    for(int s=0; s < SYMBOLS_LEN; s++){
        if(strcmpN( symbols[s],cmd, SYMBOL_NAMES_LEN)){
            si = s;
            break;
        }
    }

    //error case
    if(si == -1){
        printf("AISSL > Incorrect symbol name \"");
        for(int sn=0; sn < SYMBOL_NAMES_LEN; sn++)
            printf("%c", cmd[sn]);
        printf("\"\n");
        return;
    }

    //add a new value to symbol[si]
    cmd += SYMBOL_NAMES_LEN+1;
    symbolsNbr[si]++;
    for(int c=0; c < CHANNELS_LEN; c++){
        AISSL_data[si][c] =
            (
                AISSL_data[si][c] * (symbolsNbr[si]-1) +
                1000*char2int(cmd[0]) +
                 100*char2int(cmd[1]) +
                  10*char2int(cmd[2]) +
                     char2int(cmd[3])
            )
        /symbolsNbr[si];
        cmd += 5;
    }
}

void ask(char* cmd){
    //get input values
    int values[CHANNELS_LEN];
    for(int c=0; c < CHANNELS_LEN; c++){
        values[c] =
            1000*char2int(cmd[0]) +
             100*char2int(cmd[1]) +
              10*char2int(cmd[2]) +
                 char2int(cmd[3])
        ;
        cmd += 5;
    }
    printf("AISSL > Calculating result...\n");

    //for each channel
    int channel[SYMBOLS_LEN];
    for(int c=0; c < CHANNELS_LEN; c++){
        //create channel c list
        for(int s=0; s < SYMBOLS_LEN; s++)
            channel[s] = AISSL_data[s][c];

        //values become an index table
        values[c] = getNearest(values[c], channel);
    }

    //print nearest for each channel
    printf("AISSL > Result found :\n");
    for(int c=0; c < CHANNELS_LEN; c++){
        if(values[c] == -1)
            printf("Channel %s : No Symbol Found\n", channels[c]);
        else
            printf("Channel %s : Symbol %s\n", channels[c], symbols[ values[c] ]);
    }
}

void analyseCommand(char* cmd){
    //help command
    if(strcmpN(cmd,"help",4)){
        printf("AISSL > Here is all the available commands :\n");
        printf(" - help                    : Shows the list of available commands\n");
        printf(" - show                    : Shows all AISSL data\n");
        printf(" - learn_<s>_<4i>_..._<4i> : Add a new value to symbol s\n");
        printf(" - ask_<4i>_..._<4i>       : Ask for the symbol corresponding to the values\n");
        printf(" - reset                   : Reset all AI values\n");
        printf(" - exit                    : Exit AISSL program\n");
    }

    //show command
    else if(strcmpN(cmd,"show",4))
        show();

    //learn command
    else if(strcmpN(cmd,"learn",5)){
        cmd += 6;
        learn(cmd);
    }

    //ask command
    else if(strcmpN(cmd,"ask",3)){
        cmd += 4;
        ask(cmd);
    }

    //reset command
    else if(strcmpN(cmd,"reset",5)){
        //reset
        for(int s=0; s < SYMBOLS_LEN; s++){
            for(int c=0; c < CHANNELS_LEN; c++)
                AISSL_data[s][c] = 0;
        }
        printf("AISSL > All AI data reset successfully\n");
    }

    //exit command
    else if(strcmpN(cmd,"exit",4))
        exit(EXIT_SUCCESS);

    //invalid command
    else
        printf("AISSL > Invalid command \"%s\"\n", cmd);
}






// ------------------------ Execution ------------------------
//main
int main(){
    //init vars
    for(int s=0; s < SYMBOLS_LEN; s++){
        symbolsNbr[s] = 0;
        for(int c=0; c < CHANNELS_LEN; c++)
            AISSL_data[s][c] = 0;
    }
    char* cmd = malloc(CMD_LEN);
    printf("AISSL > Welcome to AISSL [0.1.0]\n");

    //main loop
    while(1){
        //init command string
        for(int a=0; a < CMD_LEN; a++)
            cmd[a] = '\0';
        printf("User > ");

        //get input
        scanf("%s", cmd);
        analyseCommand(cmd);
    }

    return EXIT_SUCCESS;
}
