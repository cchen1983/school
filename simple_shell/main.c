#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define LINE_MAX 512

#define SEP_ARG " \t\'\""
#define SEP_CMD ";\n"

#define DEBUG 0

#if (DEBUG == 1)
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

/*single command info*/
typedef struct cmd_s {
    char exec[LINE_MAX];
    char *args[LINE_MAX];
} cmd_t;

cmd_t *cmds[LINE_MAX] = {NULL}; //commands buffer

/*debug: dump the cmd buffer*/
static void cmd_dump(void) {
#if (DEBUG == 1)
    int i = 0, j = 0;

    while (cmds[i]) {
        dbg("cmd[%d]: ", i);
        
        j = 0;
        while (cmds[i]->args[j]) {
            dbg("%s ", cmds[i]->args[j]);
            j++;
        }
        
        dbg("\n");
        i++;
    }
#endif
}

/*return 0 if it's a complete input line, or else return 1.*/
static int line_overflow(char *line) {
    while (*line != 0) {
        if (*line == '\n') {
            return 0;
        }
        line++;
    }
    return 1;
}

static void cmd_parser(char *line) {
    int cnt_cmds = 0, cnt_args = 0;
    char content[LINE_MAX];
    char *cmd, *arg, *ctx_cmds, *ctx_args;
    cmd_t *action = NULL;

    for (cmd = strtok_r(line, SEP_CMD, &ctx_cmds); 
         cmd; 
         cmd = strtok_r(NULL, SEP_CMD, &ctx_cmds)) { /*extract cmds in line*/

        dbg("cmd: %s\n", cmd);
        
        /*pepare for current cmd parsing*/
        strcpy(content, cmd);
        action = NULL;
        cnt_args = 0;

        for (arg = strtok_r(content, SEP_ARG, &ctx_args);
             arg;
             arg = strtok_r(NULL, SEP_ARG, &ctx_args)) { /*extract args in cmd*/

            /*parsing and build up single cmd*/
            dbg("----->arg: %s\n", arg);
            if (!action) {
                action = (cmd_t *)malloc(sizeof(cmd_t));
                if (!action){
                    perror("fail to allocate cmd memory : ");
                    return;  
                }
                memset(action, 0, sizeof(cmd_t));
            }
            
            if (cnt_args == 0) {
                strcpy(action->exec, arg);
            }
           
            action->args[cnt_args] = strdup(arg);
            if (!action->args[cnt_args]) {
                perror("fail to allocate args memory : ");
                free(action);  //drop the left cmds of current input.
                return;
            }
            cnt_args++;
        }

        if (action) {
            cmds[cnt_cmds++] = action;
        }
    }
}

/*return 1 if 'quit' found, else return zero.*/
static int cmd_exec(void) {
    int i = 0;
    int res;
    int status;
    int quit = 0;

    //cmd_dump();
    while (cmds[i]) {
        pid_t pid;

        if (!quit && strcmp(cmds[i]->exec, "quit") == 0) {
            /*quit command should be executed after all jobs finished*/
            quit = 1;
            i++;
            continue;
        }

        pid = fork();
        if (pid == -1) {    /*if fail to fork, drop current cmds.*/
            perror("fail to create process : ");
            break;
        }
        else if (pid == 0) {  /*children to execute cmd*/
            res = execvp(cmds[i]->exec, cmds[i]->args);            
            if (res < 0) {
                fprintf(stderr, "<%s> -- ", cmds[i]->exec);
                perror("error happens : ");
                exit(1);
            }
        } 
        else {  /*parent keep executing the next cmd.*/
            dbg("pid<%d>: %s\n", pid, cmds[i]->exec);
        }
        i++;
    }

    waitpid(-1, &status, 0);  //waiting for all cmds execution are finished

    return quit;
}

/*free all excuted cmds, and clear for next loop*/
static void cmd_recycle(void) {
    int i = 0, j = 0;

    while (cmds[i]) {
        j = 0;
        while (cmds[i]->args[j]) {
            free(cmds[i]->args[j]);
            j++;
        }
        free(cmds[i]);
        cmds[i] = NULL;
        i++;
    }
}

int main(int argc, char **argv) {
    FILE *in = stdin;
    char line[LINE_MAX] = {0};
    
    if (argc > 2 || (argc == 2 && !argv[1])) {
        fprintf(stderr, "invalid arguments.\n");
        exit(1);
    }

    if (argc == 2) {  /*batch mode*/
        in = fopen(argv[1], "r");
        if (!in) {
            perror("Fail to open batch file : ");
            exit(1);
        }
    }

    /*exception gc callback*/
    atexit(cmd_recycle);

    /*shell loop*/
    while (1) {
        char *content;

        fprintf(stdout, "mysh>");   //prompt
        
        content = fgets(line, LINE_MAX, in);
        if (!content) { /*EOF or error happens*/
            if (errno != 0) {
                perror("\ninputs end of : ");
            }
            break;
        }
    
        if (in != stdin) {   /*batch mode, print the cmd.*/
            fprintf(stdout, "%s", content);
        }

        if (line_overflow(content)) {
            fprintf(stderr, "error: input exceed size limit (%d bytes).\n", LINE_MAX);
            //fpurge(in);  //clean the input buffer. (This requires glibc 2.1.95 or later) 
            continue;
        }

        cmd_parser(content);
        if (cmd_exec() == 1) {  /* 'quit' */
            cmd_recycle();
            break;
        }
        cmd_recycle();

    }

    if (in != stdin) {
        fclose(in); //close batch file.
    }
    return 0;
}

