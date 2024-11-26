/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisald <marisald@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 15:12:40 by marisald          #+#    #+#             */
/*   Updated: 2024-11-26 15:12:40 by marisald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Free and update the list with the new clean node */
static void	free_and_update_list(t_list **list, t_list *clean_node)
{
	t_list	*last_node;

	if (!list || !*list)
		return ;
	last_node = find_last_node(*list);
	if (last_node)
	{
		free(last_node->str_buf);
		free(last_node);
	}
	*list = clean_node;
}

/* Removes used-up parts of the list after extracting the line */
void	polish_list(t_list **list)
{
	t_list	*clean_node;
	char	*buf;
	int		i;
	int		k;

	if (!list || !*list)
		return ;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
	{
		free(buf);
		free(clean_node);
		return ;
	}
	i = 0;
	k = 0;
	while ((*list)->str_buf[i] && (*list)->str_buf[i] != '\n')
		i++;
	while ((*list)->str_buf[i] && (*list)->str_buf[++i])
		buf[k++] = (*list)->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	free_and_update_list(list, clean_node);
}

/* Allocates and appends a new node to the list */
void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	if (!buf)
		return ;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buf);
		return ;
	}
	new_node->str_buf = buf;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		last_node = find_last_node(*list);
		last_node->next = new_node;
	}
}

/* Reads the file and creates the linked list */
void	create_list(t_list **list, int fd)
{
	char	*buf;
	int		chars_read;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[chars_read] = '\0';
		append(list, buf);
	}
}

/* Retrieves the next line from the file descriptor */
char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_linev(list);
	polish_list(&list);
	return (next_line);
}
