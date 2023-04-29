#include "main.h"

/**
 * execute_command - ...
 * @cmd: ...
 * Return: ...
 */
int execute_command(command_life *cmd)
{
	pid_t pid;
	int val = 0, status;
	
	val = check_builtins(cmd);
	if (val != -1)
	{
		return(val);
	}
	val = find_p(cmd);
	if(val)
	{
		return (val);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(cmd->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			val = execve(cmd->tokens[0], cmd->tokens, cmd->env);
			if (val == -1)
			{
				perror(cmd->command_name);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				errno = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				errno = 128 + WTERMSIG(status);
			}
		}
	}
	return (0);
}
