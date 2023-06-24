#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/wait.h>
#include <vector>
#include "colors.h"
#include "history.h"

char *line;
char **args;
int status;

#define ACMShell_RL_BUFSIZE 512
const char *ACMShell_TOK_DELIM = " ";

char *ACMShell_read_line()
{
    int bufsize = 1024;
    int position = 0;
    char *buffer = (char *)malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "ACMShell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();
        if (c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position++] = c;
        }
        if (position >= bufsize)
        {
            buffer = (char *)realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "ACMShell: allocation error\n");
                exit(EXIT_FAILURE);
            }
            bufsize += ACMShell_RL_BUFSIZE;
        }
    }

    return buffer;
}

char **ACMShell_split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char *));
    char *token;
    if (!tokens)
    {
        fprintf(stderr, "ACMShell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, ACMShell_TOK_DELIM);

    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "ACMShell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, ACMShell_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int ACMShell_launch(char **args)
{
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("ACMShell");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int builtin_exit(char **args)
{
    PRINT(ANSI_BACKGROUND_BLUE, "Exiting from ACMShell...");
    exit(0);
    return 0;
}

std::vector<const char *> builtins = {"exit", "history"};
int (*builtin_func[])(char **args) = {&builtin_exit, builtin_history};

int ACMShell_execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < builtins.size(); i++)
    {
        if (strcmp(args[0], builtins[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return ACMShell_launch(args);
}

int main(void)
{
    PRINT(ANSI_COLOR_GREEN, "################################################");
    PRINT(ANSI_STYLE_BOLD,  "                    ACMShell                    ");
    PRINT(ANSI_COLOR_GREEN, "################################################");
    do
    {
        printf("%s%s> %s", ANSI_STYLE_BOLD, ANSI_COLOR_YELLOW, ANSI_RESET_ALL);
        line = ACMShell_read_line();
        args = ACMShell_split_line(line);
        add_to_hist(args);
        status = ACMShell_execute(args);

        free(line);
        free(args);
    } while (status);
    return 0;
}