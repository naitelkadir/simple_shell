#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
/*----------------------------------------*/
#define LSH_DELIM "\t\r\n\a"
char **split_line(char *line)
{
	int bufsize = 64;
	int n = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, LSH_DELIM);
	while (token != NULL)
	{
		tokens[n] = token;
		n++;
		if (n >= bufsize)
		{
			bufsize+= 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
			{
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL,LSH_DELIM);
	}
	tokens[n] = NULL;
	return (tokens);
}
/*-----------------------------------------------------------*/

int lsh_launch(char **args)
{
	pid_t pid , ppid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else if (pid > 0)
	{
		do {
			ppid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
            		if (ppid == -1)
			{
                		perror("waitpid");
                		exit(EXIT_FAILURE);
            		}

            		if (WIFEXITED(status)) 
			{
                		//printf("exited, status=%d\n", WEXITSTATUS(status));
                		return 0;
            		}
			else if (WIFSIGNALED(status))
			{
                		printf("killed by signal %d\n", WTERMSIG(status));
            		}
			else if (WIFSTOPPED(status))
			{
                		printf("stopped by signal %d\n", WSTOPSIG(status));
            		}
			else if (WIFCONTINUED(status))
			{
                		printf("continued\n");
            		}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/*-----------------------------------------------------------*/
int lsh_execute(char **args)
{
	if (args[0] == NULL)
	{
		return (1);
	}
	return (lsh_launch(args));
}

/*-------------------------------------------------------------*/
void lsh_loop(void)
{
	char *line;
	char **args;
	int status;
	do {
		printf("My shell > ");
		line = read_line();
		args = split_line(line);
		status = lsh_execute(args);
		free(line);
		free(args);
	} while (status);
}

/*---------------------------------------------------------------*/
int main(void)
{
	lsh_loop();
	return EXIT_SUCCESS;
}
