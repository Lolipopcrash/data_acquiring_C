/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_user.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:55:51 by kelevequ          #+#    #+#             */
/*   Updated: 2025/03/16 16:02:08 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piscine_program.h"

t_user	*ft_new_user(char *user_id, char *user_name)
{
	t_user	*new;

	new = malloc(sizeof(t_user));
	if (!new)
		return (NULL);
	new->user_id = user_id;
	new->user_name = user_name;
	new->points_filename = NULL;
	new->locations_filename = NULL;
	new->evaluated_filename = NULL;
	new->next = NULL;
	return (new);
}

t_user	*ft_user_last(t_user *users)
{
	t_user	*temp;

	if (!users)
		return (0);
	temp = users;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_user_addback(t_user **users, t_user *new)
{
	t_user	*last;

	if (!users || !new)
		return ;
	if (*users == NULL)
	{
		*users = new;
		return ;
	}
	last = ft_user_last(*users);
	last->next = new;
}

void	ft_free_users(t_user *user)
{
	t_user	*temp;
	t_user	*byebye;

	temp = user;
	while (temp)
	{
		byebye = temp;
		temp = temp->next;
		free(byebye->user_id);
		free(byebye->user_name);
		free(byebye->points_filename);
		free(byebye->locations_filename);
		free(byebye->evaluated_filename);
		free(byebye);
	}
}

void	ft_debug_user(t_user *user)
{
	int		i;

	i = 1;
	while (user->next != NULL)
	{
		printf("\nuser_id		%d: %s\n", i, user->user_id);
		printf("user_name	%d: %s\n", i, user->user_name);
		user = user->next;
		i++;
	}
	printf("\nuser_id		%d: %s\n", i, user->user_id);
	printf("user_name	%d: %s\n", i, user->user_name);
}
