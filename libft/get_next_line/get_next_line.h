/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:41:06 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/14 16:09:00 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*get_next_line(int fd);
char	*read_and_find(int fd, char *buffer, char **remainder, char *new_line);
char	*divide(char *new_line, char **remainder);
char	*empty_remainder_and_first_read(int fd, char *buffer, char **remainder);
char	*f_strchr(const char *string, int symbol);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	f_strlen(const char *s);
char	*f_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*f_strdup(const char *s1);

#endif
