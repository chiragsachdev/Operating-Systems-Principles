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

void ft_exec_cmd(int ac, char **argv)
{
	int result;
	int rc;
	int wc;

	ac += 0; 

	rc = fork();
	if (rc < 0)
	{
		printf("An error has occured\nErrno: %d", errno);
		exit(1);
	}
	else if (rc == 0)
	{
		result = execvp(argv[0],argv);
		if (result < 0)
		{
			printf("An error has occured\nErr No.: %d", errno);
			exit(1);
		}	
	}

	else
	{
		wc = wait(NULL);

		if (wc < 0)
		{
			printf("An error has occured\nErrno: %d\n", errno);
			exit(1);
		}
	}
	return;
}

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

void ft_parse_cmds(char *input_str)
{
	int wc;
	int i;
	char **cmd;
	int wl;

	while(*input_str <= (char)32)
			input_str++;

	while(*input_str)
	{
		if (*input_str == '\n')
		{
			input_str++;
			continue;
		}
		i = 0;
		wc = ft_get_word_count(input_str);
		cmd = (char **)(calloc(wc + 1,sizeof(char *)));
		
		if (cmd == NULL)
		{
			printf("An error has occured\nErrno.: %d", errno);
			exit(1);
		}

		while (i < wc)
		{
			wl = 0;
			while(*input_str <= (char)32)
				input_str++;

			while (*input_str > 32)
			{
				wl++;
				input_str++;
			}
			input_str -= wl;
			cmd[i] = (char *)(calloc(wl,1));
			if (cmd[i] == NULL)
			{
				printf("An error has occured\nErrno.: %d", errno);
				exit(1);
			}
			cmd[i] = strncpy(cmd[i],input_str,wl);
			input_str+=wl;
			i++;
		}			

		cmd[i] = NULL;

		ft_exec_cmd(wc+1, cmd);
	}

	return;
}


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
		printf("An error has occured\nPlease check if file exists\nErrno: %d\n", errno);
		exit(1);
	}

	return (fsize);
}

int main(int ac, char *av[])
{
	if (ac < 2)
	{
		printf("An error has occured\nEnter input and output files as parameters\n");
		exit(1);
	}

	int fp;
	char *input_str;
	int fsize;
	
	fsize = ft_get_filesize(av[1]);
	input_str = (char *)(calloc(fsize+1, 1));
	if (input_str == NULL)
	{
		printf("An error has occured\nErrno: %d", errno);
		exit(1);
	}
	
	fp = open(av[1],O_RDONLY);
	read(fp, input_str, fsize);
	close(fp);
	
	ft_parse_cmds(input_str);

	return (0);
}
