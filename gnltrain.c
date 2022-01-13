/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnltrain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:21:54 by emcariot          #+#    #+#             */
/*   Updated: 2022/01/13 14:16:20 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *s1)
{
	char *s2;
	int i;
	int len;

	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(sizeof(char) * len + 1);
	if (!s2)
		return (NULL);
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *cpy;
	int i;
	int j;

	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (s1 == NULL)
	{
		cpy = ft_strdup(s2);
		return(cpy);
	}
	cpy = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[++i])
		cpy[i] = s1[i];
	while (s2[j])
		cpy[i++] = s2[j++];
	cpy[i] = '\0';
	return (cpy);
}

