/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:47:55 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/07/16 15:06:30 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		is_charset(char c, char *charset);
int		ft_count_char(char *str, char *charechter);
char	*ft_strndup(char *str, int n);

char	**ft_split_plus(char *str, char *charset)
{
	int		i;
	int		j;
	int		k;
	char	**return_val;

	return_val = malloc(sizeof(char *) * (ft_count_char(str, charset) + 1));
	if (!return_val)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_charset(str[i], charset))
			i++;
		j = i;
		while (str[i] != '\0' && !is_charset(str[i], charset))
			i++;
		if (i > j)
			return_val[k++] = ft_strndup(str + j, i - j);
	}
	return_val[k] = NULL;
	return (return_val);
}

// int main(void)
// {
// 	char string[] = ",apple ,,,banana,,cherry,date,";
// 	char separeter = ',';
// 	char **result = ft_split(string, &separeter);
// 		 int i = 0;
//     while (result[i] != NULL)
//     {
//         printf("%s\n", result[i]);
//         free(result[i]);
//         i++;
//     }
//     free(result);
//     return (0);
// }

int	ft_count_char(char *str, char *charechter)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (!is_charset(str[i], charechter) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_charset(str[i], charechter))
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

char	*ft_strndup(char *str, int n)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
