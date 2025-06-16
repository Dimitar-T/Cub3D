/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:56:45 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/10 14:05:01 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_fd(char *str)
{
	int fd;
	int	read_bytes;
	char test_buffer[2];
	
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_fail("Cub3D: Error opening the file check if the file exists and if the permissions are set correctlly");
	read_bytes = read(fd, test_buffer, 0);
    if (read_bytes == -1 && errno == EISDIR)
    {
        close(fd);
    	exit_fail("Cub3D: Error the path that is given goes to a folder and not to a file, you sneaky little ***** "); // It’s a directory
    } 
	return (fd);
}

static void file_name_validation(char *argv)
{
	int i;

	i = -1;
	while(argv[++i])
	{
		if (argv[i] == '.')
		{
			if (ft_strcmp(&argv[i + 1], "cub") == 0)
				break;
			exit_fail("CuB3D: Error please provide a *.cub file!");
		} 
		else if(argv[i + 1] == '\0')
			exit_fail("CuB3D: Error please provide a *.cub file!");
	}
}

static int count_lines(char *str)
{
	int	fd;
	int	count;
	char *line;
	
	count  = 0; 
	fd = get_fd(str);
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**file_parsing(char **argv)
{
	int fd;
	int line_count;
	char **map;
	int i;
	
	file_name_validation(argv[1]);
	line_count = count_lines(argv[1]);
	map  = gc_malloc((sizeof(char *) * (line_count + 1)));
	if (map == NULL)
		exit_fail("Cub3D: Memory allocation error");
	i = -1;
	fd = get_fd(argv[1]);
	while ((map[++i] = get_next_line(fd)))
	{
		gc_track(map[i]);
		if(map[i] == NULL && i != line_count)
		{
			exit_fail("Cub3D: Memory allocation error");
		}
	}
	return(close(fd), map);
}
