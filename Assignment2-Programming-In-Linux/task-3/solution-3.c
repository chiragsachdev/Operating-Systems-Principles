/* Your code goes here */
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

void ft_putchar(char c, int fp)
{
	write(fp, &c, 1);
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

void ft_write_hex_to_file(char * buff, char * outfile)
{
	int fp;
	int ctr;
	int hex;

	fp = open(outfile, O_WRONLY | O_TRUNC);
	write(fp, "", 0);
	close(fp);

	fp = open(outfile, O_WRONLY | O_APPEND);
	
	while(*buff)
	{
		ctr = -1;
		hex = 0;
		if (*buff == '\n')
		{
			ft_putchar('\n', fp);
			buff++;
			continue;
		}

		// converting 4 bits to 1 hex 
		while (++ctr < 4)
		{
			hex += (int)pow(2,3-ctr) * (int)(*buff - '0'); 
			buff++;
		}
		if (hex < 10)
			ft_putchar(('0'+ hex), fp);
		else 
			ft_putchar(('a' + hex - 10), fp);
		
	}
	close(fp);

	return;
}

int main(int ac, char *av[])
{
	if (ac < 3)
	{
		printf("An error has occured\nEnter input and output files as parameters\nErrno: %d\n", errno);
		exit(1);
	} 

	int fp;
	char input_str[1024];
	int fsize;
	
	fsize = ft_get_filesize(av[1]);
	memset(input_str, 0, 1024);
	fp = open(av[1],O_RDONLY);
	read(fp, input_str, fsize);
	close(fp);
	

	fp = open(av[2],O_WRONLY | O_CREAT,2);
	if (fp < 0)
	{
		printf("An error has occured\nError opening output file\n");
		close(fp);
		exit(1);
	}
	ft_write_hex_to_file(input_str, av[2]);

	return (0);
}
