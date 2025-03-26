/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:34:30 by kelevequ          #+#    #+#             */
/*   Updated: 2025/02/10 12:26:09 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_user
{
	char			*user_id;
	char			*user_name;
	struct s_user	*next;
}	t_user;

t_user	*ft_new_user(char *user_id, char *user_name)
{
	t_user	*new;

	new = malloc(sizeof(t_user));
	if (!new)
		return (NULL);
	new->user_id = user_id;
	new->user_name = user_name;
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

bool	check_last_two(const char *filename)
{
	FILE	*file = fopen(filename, "rb");
	if (file == NULL)
	{
		perror("Error opening file");
		return (0);
	}
	fseek(file, -2, SEEK_END);
	char	ch1 = fgetc(file);
	char	ch2 = fgetc(file);
	fclose(file);
	if (ch1 == '[' && ch2 == ']')
		return (0);
	return (1);
}

bool	ft_get_data(t_user	*user)
{
	const char	*bearer_token = "bd90c3cb70589b46d85c88bd822b82dd4f719ee523acb687f3bbc5f68a8cff4b";
	char		output_file[100];
	char		command[512];
	bool		data;
	int			page;
	int			exit;
	int			i;

	i = 0;
	while (user)
	{
		snprintf(output_file, sizeof(output_file), "slots/%s_slots.json", user->user_name);
		page = 1;
		data = 1;
		while (i >= 0 && page <= 1 && data)
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/slots?page=%d\" >> %s",
				bearer_token, user->user_id, page++, output_file);
			
			printf("Executing: %s\n", command);
			exit = system(command);
			if (exit == -1)
			{
				perror("Error executing curl command");
				return (0);
			}
			if (!check_last_two(output_file))
				data = 0;
			usleep(500000);
		}
		user = user->next;
		i++;
	}
	return (1);
}

int	main(void)
{
	FILE	*file = fopen("extracted_user_id_current_students.txt", "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	char	user_id[10];
	char	user_name[10];
	t_user	*user_head = NULL;
	t_user	*user_tail = NULL;
	t_user	*user_new = NULL;

	while (fscanf(file, "%9s %9s", user_id, user_name) == 2)
	{
		user_new = ft_new_user(strdup(user_id), strdup(user_name));
		if (!user_head)
		{
			user_head = user_new;
		}
		else if (!user_tail)
		{
			user_tail = user_new;
			user_head->next = user_tail;
		}
		else
		{
			user_tail->next = user_new;
			user_tail = user_new;
		}
	}

	fclose(file);
	ft_debug_user(user_head);
	if (!ft_get_data(user_head))
		printf("ft_get_data failed");
	return (0);
}
