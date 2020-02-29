/* Your code goes here */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <math.h>
extern int errno;

// function to print tokens from input line
void ft_exec_cmd(int ac, char **argv)
{
	int i;

	for (i = 0; i < ac - 1; i++)
		printf("%s\n",argv[i]);	
}

// function to get number of tokens from string parameter 
int ft_get_word_count(char *str)
{
	int wc;

	wc = 0;
	while(*str != '\n' && *str)
	{
		if (*str > (char)32)
			wc++;
		while(*str > (char)32)
			str++;
		str++;
	}

	return (wc);		
}

// parse input string to array of tokens for execution
void ft_parse_cmds(char *input_str)
{
	int wc;
	int i;
	char **cmd;
	int wl;

	while(*input_str <= (char)32)
			input_str++;

	i = 0;
	wc = ft_get_word_count(input_str);
	cmd = (char **)(calloc(wc+1, sizeof(char *)));
	if (cmd == NULL)
	{
		printf("An error has occured.\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}

	// tokenizing string
	while (i < wc)
	{
		wl = 0;
		while(*input_str <= (char)32)
			input_str++;

		while ((*input_str > 32) && (*input_str != '\n'))
		{
			wl++;
			input_str++;
		}
		input_str -= wl;
		cmd[i] = (char *)(calloc(wl,1));
		if (cmd[i] == NULL)
		{
			printf("An error has occured.\n");
			// printf("Errno: %d\n", errno);
			exit(1);
		}
		cmd[i] = strncpy(cmd[i],input_str,wl);
		input_str+=wl;
		i++;
	}			
	// null terminate the array
	cmd[i] = NULL;

	if (!strcmp(cmd[0], "exit"))
		exit(0);

	ft_exec_cmd(wc + 1, cmd);

	return;
}


int main(void)
{
	char buff[1024];
	char ch;
	int	i;

	memset(buff, '\0', 1024);
	i = 0;
	while (1)
	{
		if (!(read(0, &ch, 1)) || ch == (char)(4))
			exit(0);
		buff[i++] = ch;
		if (ch == '\n')
		{
			buff[i] = '\0';
			ft_parse_cmds(buff);
			memset(buff, '\0', 1024);
			i = 0;
		}
	}

	return (0);
}
