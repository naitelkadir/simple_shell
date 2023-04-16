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

char **split_line(char *line)
{
	int bufsize = 64;
	char *delim = " \n";
	int n = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[n] = strdup(token);
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
		token = strtok(NULL, delim);
	}
	tokens[n] = token;
	return (tokens);
}
/*-----------------------------------------------------------*/
char *builtin_str[] = {"cd", "exit"};
int lsh_cd(char ** args);
int lsh_exit();

int (*builtin_func[]) (char **) = {&lsh_cd, &lsh_exit};
int lsh_cd(char ** args)
{
	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			printf(" %s: no such directory\n", args[1]);
		}
		if (chdir(args[1]) == 0)
		{
			chdir(getenv(args[1]));
		}
	}
	return (1);
}
int lsh_exit()
{
  return 0;
}
/*-----------------------------------------------------------*/

int lsh_launch(char **args)
{
	pid_t pid , ppid;
	int status;
	
	int i;

	for (i = 0; i < 2; i++)
	{
		if (strcmp(args[1], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
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
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/*-----------------------------------------------------------*/

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
		status = lsh_launch(args);
	} while (status);
	free(line);
        free(args);
}

/*---------------------------------------------------------------*/
int main(void)
{
	lsh_loop();
	return EXIT_SUCCESS;
}
