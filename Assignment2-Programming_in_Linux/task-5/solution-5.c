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

// printing usage
void ft_help()
{
	write(2, "usage: ./fastsort [inputfile] [outputfile]\n",44);
}

// structure to simplify input to create a hash table
typedef struct instance
{
	unsigned int key;
	unsigned int values[24];
} instance;

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

// sorting based on bubble sort
instance *ft_sort(instance *data, int ac)
{
	instance temp;
	int i;
	int j;

	for (i = 0; i < ac; i++)
	{
		for (j = 0; j < ac - 1; j++)
		{
			if (data[j].key > data[j+1].key)
			{
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}				
		}
	}

	return (data);
}

// funtion to read data from file and sort it out based on key values
instance *ft_read_and_sort(char *fname)
{
	int instance_count;
	int i;
	int fsize;
	int fp;
	instance *data;

	fsize = ft_get_filesize(fname);

	// instance count is sizeof file / size of 1 blob
	instance_count = fsize / 100;
	data = (instance *)(calloc(instance_count,sizeof(instance)));

	i = -1;
	fp = open(fname,O_RDONLY);
	if (fp < 0)
	{
		printf("Error: Cannot open file %s\n", fname);
		// printf("Errno: %d\n", errno);
		exit(1);
	}
	while (read(fp, &data[++i], sizeof(instance)));
	close(fp);
	data = ft_sort(data, instance_count);

	return data;
}

// function to write output to file without breaks 
void ft_write_output(char *fname, instance *data, char *input_fname)
{
	int fp;
	int i;
	int ctr;
	int bytes_written;

	ctr = ft_get_filesize(input_fname)/sizeof(instance);
	i = -1;
	fp = open(fname,O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fp < 0)
	{
		printf("An error has occured.\n");
		// printf("Errno: %d\n", errno);
		exit(1);
	}

	while (++i < ctr)
	{
		bytes_written = write(fp, &data[i], sizeof(instance));
		if (bytes_written != sizeof(instance))
		{
		printf("An error has occured.\n");
		// printf("Errno: %d\n", errno);
		exit(1);			
		}
	}
	close(fp);

	return;
}

int main(int ac, char *av[])
{
	if (ac != 3)
	{
		ft_help();
		// printf("Errno: %d\n", errno);
		exit(1);
	} 
	instance *data;
	data = ft_read_and_sort(av[1]);
	ft_write_output(av[2], data, av[1]);

	return (0);
}
