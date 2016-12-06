# Operation System Midterm Project
# A simple shell program
# Project Name: mysh
# Author: cchen.rough@gmail.com
# Initial Date : 2015-03-18

-----------------------------------------
- Version Control
-----------------------------------------
This project use GIT to manage sources. It can also be checkout in github website: 
    
    https://github.com/cchen1983/mysh

-----------------------------------------
- Design Overview
-----------------------------------------
This mysh program basically consists of below parts: 

1).Main loop for receive the inputs line by line, implement by fgets() api. As the project requests,
 a maxmium length limit of each input here is set to 512 bytes. 

    #define LINE_MAX 512

2).Command Parser, check and parse the user input line and extract all valid commands & arguments 
into a commands buffer:
    
    /*single command info*/
    typedef struct cmd_s {
        char exec[LINE_MAX];
        char *args[LINE_MAX];
    } cmd_t;

    /*commands buffer*/
    cmd_t *cmds[LINE_MAX] = {NULL};

    /*command parser*/
    static void cmd_parser(char *line);

3). Command Executor, execute the parsed commands out of commands buffer simultaneously.

    /*executor*/
    static int cmd_exec(void);

4). Command Buffer Recycle Method, free all excuted command buffers.

    /*free all excuted cmds, and clear for next loop*/
    static void cmd_recycle(void);

5). A debug switch can be set to enable/disable all debug message.

    #define DEBUG 0


-----------------------------------------
- Specification
-----------------------------------------
0). Compile: 
    
    make            //generate the mysh executable binary file
    make clean      //clear all binary files

1). Usage:
    
    ./mysh                      //entering interactive mode of shell command line
    ./mysh <batch_filename>     //entering batch mode to execute a pre-defined batch file, 
                                //which contains a set of commands, until EOF or 'quit' happens.

2).Command Line:

    single command:  
        mysh>executable arg1 arg2 .... argN   
    
    multiple commands:
        mysh>command1;command2;command3;....;commandN

    
    a).Users can use RETURN key to input a new line to active execution;
    b).Single command can contains multiple arguments, separated by space or tab characters;
    c).An input line can contains multiple commands, separated by semi-colons;
    d).All space, tab, semi-colons characters and null commands(eg: ; ;) will be filtered out after parsing;
    e).Multiple commands in one line will be executed simultaneously, and if a 'quit' command presents, it
       will only be executed after all other commands finished.
    f).User can escape from the interactive mode by press CTRL-D.

      

-----------------------------------------
- Known Problems
-----------------------------------------
It's just a simple practice, therefore the functionality is not complete:
 
1). No smart input helper:  Users can't automatically complete their inputs by press TAB, UPWARD/DOWNWARD keys;

2). It didn't implement the cursor control, users can't insert content by press LEFTWARD/RIGHTWARD keys. 

3). Background execution (cmd &) isn't implemented.

4). Because the project requires simultaneous execution of multiple commands, the output message may be intermixed.


-
