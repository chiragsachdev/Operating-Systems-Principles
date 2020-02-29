/* Your code goes here */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
extern int errno;

// fucntion to print 1 character on file desriptor passed
void ft_putchar(char c, int fp)
{
	write(fp, &c, 1);
}

// function to convert input number to binary and write to file with file descriptor fp
void ft_putnbr_bin(int n, int fp)
{
	if (n < 2)
		ft_putchar('0' + n, fp);
	else
	{
		ft_putnbr_bin(n/2, fp);
		ft_putnbr_bin(n%2, fp);
	}
}

// function to get size of file
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

// function to parse input string and write it's binary to output file provided
void ft_write_bin_to_file(char * buff, char * outfile)
{
	int fp;

	// open output file and erase its contents
	fp = open(outfile, O_WRONLY | O_TRUNC);
	write(fp, "", 0);
	close(fp);

	// open file again ain append mode
	fp = open(outfile, O_WRONLY | O_APPEND);
	while(*buff)
	{
		if (*buff == '\n')
		{
			ft_putchar('\n', fp);
			buff++;
			continue;
		}
		// adding relevant leading 0's
		if ((*buff == '0') || (*buff == '1'))
			write(fp,"000", 3);
		else if ((*buff > '1') && (*buff < '4'))
			write(fp,"00", 2);
		else if ((*buff > '3') && (*buff < '8'))
			write(fp,"0", 1);

		// converting 1 hex character to int
		if ((*buff >= '0') && (*buff <= '9'))
			ft_putnbr_bin((int)(*buff - '0'), fp);
		else if ((*buff >= 'a') && (*buff <= 'f'))
			ft_putnbr_bin(10 +(int)(*buff - 'a'), fp);

		buff++;
	}
	close(fp);

	return;
}

int main(int ac, char *av[])
{
	if (ac < 3)
	{
		printf("An error has occured\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	} 

	int fp;
	char *input_str;
	int fsize;
	
	fsize = ft_get_filesize(av[1]);
	input_str = (char *)(malloc(fsize));
	memset(input_str, 0, 1024);
	fp = open(av[1],O_RDONLY);
	if (fp < 0)
	{
		printf("An error has occured.\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}
	read(fp, input_str, fsize);
	close(fp);
	

	fp = open(av[2],O_WRONLY | O_CREAT, S_IRWXU);
	if (fp < 0)
	{
		printf("An error has occured.\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}
	ft_write_bin_to_file(input_str, av[2]);

	return (0);
}
