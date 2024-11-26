/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisald <marisald@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-21 15:03:42 by marisald          #+#    #+#             */
/*   Updated: 2024-11-21 15:03:42 by marisald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3 //can be set to whatever and should work with whatever
# endif

# include <fcntl.h> //???
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list //????
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;



#endif