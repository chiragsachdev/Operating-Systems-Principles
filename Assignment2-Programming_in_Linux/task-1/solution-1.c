/* Your code goes here */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <math.h>
extern int errno;

// function to execute a command as a child process
void ft_exec_cmd(int ac, char **argv)
{
	int result;
	int rc;
	int wc;

	ac += 0; 

	// spawn a child process
	rc = fork();
	if (rc < 0)
	{
		printf("An error has occured\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}
	// overwrite child process with new command to be executed
	else if (rc == 0)
	{
		result = execvp(argv[0],argv);
		if (result < 0)
		{
			printf("An error has occured\n");
			// printf("Errno: %d\n", errno);
			exit(1);
		}	
	}
	// return to parent process
	else
	{
		// wait for child process to finish
		wc = wait(NULL);

		if (wc < 0)
		{
			printf("An error has occured\n");
			// printf("Errno: %d\n", errno);
			exit(1);
		}
	}
	return;
}

// function get the number of tokens from a string
int ft_get_word_count(char *str)
{
	int wc;

	wc = 0;
	while(*str != '\n' && *str)
	{
		if (*str == ' ' || *str == '\t')
			wc++;
		while(*str == ' ' || *str == '\t')
			str++;
		str++;
	}

	return (wc+1);
}

// function to parse multiple bash commands from a file and construct array for exec() 
void ft_parse_cmds(char *input_str)
{
	// token count
	int wc;
	int i;
	// array for exec()
	char **cmd;
	// length of 1 token
	int wl;

	// skip whitespaces
	while(*input_str <= (char)32)
			input_str++;

	while(*input_str)
	{
		// '\n' termination condition for 1 command to be executed
		if (*input_str == '\n')
		{
			input_str++;
			continue;
		}
		i = 0;
		wc = ft_get_word_count(input_str);
		// allocate memory for number of tokens + 1 for NULL termination
		cmd = (char **)(calloc(wc + 1,sizeof(char *)));
		if (cmd == NULL)
		{
			printf("An error has occured\n");
			// printf("Errno: %d\n", errno);
			exit(1);
		}

		// filling in cmd array 
		while (i < wc)
		{
			wl = 0;
			// skipping whitespaces
			while(*input_str <= (char)32)
				input_str++;

			// calculating length of token
			while (*input_str > 32)
			{
				wl++;
				input_str++;
			}
			input_str -= wl;
			cmd[i] = (char *)(calloc(wl,1));
			if (cmd[i] == NULL)
			{
				printf("An error has occured\n");
				// printf("Errno: %d\n", errno);
				exit(1);
			}
			// copy token to cmd array
			cmd[i] = strncpy(cmd[i],input_str,wl);
			input_str+=wl;
			i++;
		}			
		// null terminate the array
		cmd[i] = NULL;

		ft_exec_cmd(wc+1, cmd);
	}

	return;
}

// function to get file size from name of file
int ft_get_filesize(char *fname)
{
	int fsize;
	struct stat stats;

	if (stat(fname, &stats) == 0)
    {
        fsize = stats.st_size;
    }
    else
    {
		printf("An error has occured\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}

	return (fsize);
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("An error has occured\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}

	int fp;
	char *input_str;
	int fsize;
	
	fsize = ft_get_filesize(av[1]);
	input_str = (char *)(calloc(fsize+1, 1));
	if (input_str == NULL)
	{
		printf("An error has occured\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}
	
	fp = open(av[1],O_RDONLY);
	if (fp < 0)
	{
		printf("An error has occured.\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}
	read(fp, input_str, fsize);
	close(fp);
	
	ft_parse_cmds(input_str);

	return (0);
}
