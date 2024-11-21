# include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//Utility functions

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (char *)malloc(size * nmemb);
	if (ptr == NULL)
		return (NULL);
	return (ft_memset(ptr, 0, size * nmemb));
}



//Utility functions

char  *get_next_line(int fd)
{
  int  bytes_read;
  char *cup_buffer;
  
  cup_buffer = ft_calloc (3 + 1, sizeof(char));
  if (cup_buffer == NULL)
    return (NULL);
  bytes_read = read(fd, cup_buffer, 3);
  if (bytes_read <= 0)
  if (bytes_read <= 0)
    {
        free(cup_buffer); // Free explicitly
        return (NULL);
    }
  return (cup_buffer);
}	

//test
int main(void)
{
  int    fd;
  char  *next_line;
  int  count;

  count = 0;
  fd = open("example.txt", O_RDONLY);
  if (fd == -1)
 {
   printf("Error opening file");
  return (1);
 } 
  while (1)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
      break ;
    count++;
    printf("[%d]:%s\n", count, next_line);
	free(next_line);
    next_line = NULL;
  }
  close(fd);
  return (0);
}