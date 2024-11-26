# include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

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



size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = -1;
	while (*(s + ++i))
		;
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(s) + 1)
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	return (NULL);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		len = 0;
	else if (len > str_len - start)
		len = str_len - start;
	newstr = (char *)malloc(len + 1);
	if (!newstr)
		return (NULL);
	newstr[len] = '\0';
	while (len--)
		newstr[len] = s[start + len];
	return (newstr);
}



void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstc;
	const char	*srccc;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	dstc = (char *)dst;
	srccc = (const char *)src;
	while (n--)
		dstc[n] = srccc[n];
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*rtn;
	size_t	len;

	len = ft_strlen(s1) + 1;
	rtn = malloc(sizeof(char) * len);
	if (!rtn)
		return (0);
	rtn = ft_memcpy(rtn, s1, len);
	return (rtn);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	stot_len;
	char	*rtn;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen(s2);
	stot_len = s1_len + s2_len + 1;
	rtn = malloc(sizeof(char) * stot_len);
	if (!rtn)
		return (0);
	ft_memmove(rtn, s1, s1_len);
	ft_memmove(rtn + s1_len, s2, s2_len);
	rtn[stot_len - 1] = '\0';
	return (rtn);
}




//Utility functions

/* ------------------------------------------------------------------- */
/* Function to convert and print the newline character as ?            */
/* ------------------------------------------------------------------- */
void    print_newline_helper(char *buffer)
{

    while (*buffer &&  *buffer != '\0')
    {
        if (*buffer == '\n') 
        {
            *buffer= '\\';
        }
        printf("%c",*buffer);
        buffer++;
    }
}

/* -------------------------------------------------------------------------- */
/* Function to append the read buffer data to the partial content (line).     */
/* The explorer (get_next_line) gracefully adds a scoop of water (read        */
/* buffer) to the current cup (line) and returns the updated line for         */
/* further examination.                                                       */
/* -------------------------------------------------------------------------- */

char *append_buffer(char *basin_buffer, char *read_buffer)
{
 char *temp;

 temp = ft_strjoin(basin_buffer, read_buffer);
 free(basin_buffer);
 return (temp);
}

/* -------------------------------------------------------------------- */
/* Function to read data from the file and append it to partial content */
/* -------------------------------------------------------------------- */
char *read_from_file(char *basin_buffer, int fd)
{
 char *cup_buffer;
 int  bytes_read;

 cup_buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
 if (!cup_buffer)
  return (NULL);
 bytes_read = 1;
 while (bytes_read > 0)
 {
  bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
  if (bytes_read == -1)
   return (free(cup_buffer), NULL);
  cup_buffer[bytes_read] = '\0';
  basin_buffer = append_buffer(basin_buffer, cup_buffer);
  if (ft_strchr(basin_buffer, '\n'))
   break ;
 }
 free (cup_buffer);
 return (basin_buffer);
}

char *extract_line(char *basin_buffer)
{
    int i = 0;
    char *line;

    if (!basin_buffer || !*basin_buffer)
        return (NULL);
    while (basin_buffer[i] && basin_buffer[i] != '\n')
        i++;
    line = ft_substr(basin_buffer, 0, i + (basin_buffer[i] == '\n'));
    return (line);
}

char *obtain_remaining(char *basin_buffer)
{
    int i = 0;
    char *remaining;

    if (!basin_buffer || !*basin_buffer)
        return (NULL);
    while (basin_buffer[i] && basin_buffer[i] != '\n')
        i++;
    if (!basin_buffer[i]) // No newline found, free the buffer
        return (free(basin_buffer), NULL);
    remaining = ft_strdup(basin_buffer + i + 1);
    free(basin_buffer);
    return (remaining);
}





/* ------------------------------------------------------------------- */
/* The get_next_line function to get the next line from the fd         */
/* ------------------------------------------------------------------- */
char *get_next_line(int fd)
{
 static char *basin_buffer;
 char  *line;

 if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0) 
  return (NULL);
 if (!basin_buffer)
  basin_buffer = ft_calloc(1, sizeof (char)); 
 if (!ft_strchr(basin_buffer, '\n'))
  basin_buffer = read_from_file(basin_buffer, fd);
 if (!basin_buffer)
  return (free(basin_buffer), NULL);
 line = extract_line(basin_buffer);
 basin_buffer = obtain_remaining(basin_buffer);
 return (line);
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