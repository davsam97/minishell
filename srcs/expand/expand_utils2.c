/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 12:01:00 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 12:36:45 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"
#include "../../libft/libft.h"

static void	shift_element(char **argv, int i, int end)
{
	int		j;
	char	*tmp;

	j = i - 1;
	while (++j < end)
	{
		tmp = argv[j];
		argv[j] = argv[j + 1];
		argv[j + 1] = tmp;
	}
}

static void	shift_empty_args(char **argv)
{
	int	i;
	int	size;

	size = 0;
	while (argv[size] != NULL)
		size++;
	i = size;
	while (--i >= 0)
	{
		if (argv[i][0] == '\0')
		{
			free(argv[i]);
			shift_element(argv, i, size);
		}
	}
}

void	handle_empty_args(char ***argv)
{
	shift_empty_args(*argv);
	if (*argv && (*argv)[0] == NULL)
	{
		free_argv(*argv);
		(*argv) = safe_malloc(2 * sizeof(char *));
		(*argv)[0] = ft_strdup("true");
		(*argv)[1] = NULL;
	}
}
