/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaa_points_data_json.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:57 by kelevequ          #+#    #+#             */
/*   Updated: 2025/02/12 17:39:31 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct s_user
{
	int				user_id;
	char			*user_name;
	char			*locations_filename;
	int				correctors[328];
	struct s_user	*next;
}	t_user;

t_user	*ft_new_user(int user_id, char *user_name)
{
	//int		i;
	t_user	*new;

	new = malloc(sizeof(t_user));
	if (!new)
		return (NULL);
	new->user_id = user_id;
	new->user_name = user_name;
	/*i = 0;
	while (i < 368)
		new->correctors[i++] = 0;*/
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
		//free(byebye->user_id);
		//free(byebye->user_name);
		free(byebye);
	}
}

void	ft_print_file(t_user *user, FILE *file, t_user *top)
{
	t_user	*temp;
	int	i = 0;
	int	j;

	fprintf(file, "[");
	while (user)
	{
		if (i != 0)
			fprintf(file, ",{");
		else
			fprintf(file, "{");

		fprintf(file, "\"user_id\": %d,", user->user_id);
		fprintf(file, "\"user_name\": \"%s\",", user->user_name);
		temp = top;
		j = 0;
		while (temp)
		{
			fprintf(file, "\"%s\": %d,", temp->user_name, user->correctors[j]);
			temp = temp->next;
			j++;
		}
		
		fprintf(file, "}");
		user = user->next;
		i++;
	}
	fprintf(file, "]");
}

t_user	*ft_init_users(char *input_file)
{
	FILE	*file = fopen(input_file, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (NULL);
	}

	int		user_id;
	char	user_name[10];
	char	locations_filename[100];
	t_user	*user_head = NULL;
	t_user	*user_tail = NULL;
	t_user	*user_new = NULL;
	int		i = 0;

	while (fscanf(file, "%d %9s", &user_id, user_name) == 2/* && i == 0*/)
	{
		user_new = ft_new_user(user_id, strdup(user_name));
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
		snprintf(locations_filename, sizeof(locations_filename), "%s_scale_team_corrected.json", user_new->user_name);
		user_new->locations_filename = strdup(locations_filename);
		i++;
	}

	fclose(file);
	//ft_debug_user(user_head);
	return (user_head);
}

void	ft_calculate(t_user *user, int size, int *corrector, t_user *top)
{
	int		j;
	int		i;
	t_user	*temp;

	i = 0;
	while (i < size - 1)
	{
		temp = top;
		j = 0;
		while (temp)
		{
			if (corrector[i] == temp->user_id)
			{
				user->correctors[j]++;
				break ;
			}
			temp = temp->next;
			j++;
		}
		i++;
	}
}

/*{ 					DATA FORMAT
	"id": 12508312,
	"scale_team_id": null,
	"reason": "Creation",
	"sum": 5,
	"total": 5,
	"created_at": "2024-08-31T14:43:34.240Z",
	"updated_at": "2024-08-31T14:43:34.240Z"
}*/

void	ft_parse_data(t_user *user, int size, t_user *top)
{
	FILE	*file = fopen(user->locations_filename, "r");
	int		corrector_ids[size];  // Store corrector IDs
	char	line[256];
	int		i = 0;

	if (!file)
	{
		perror("Error opening file");
		return;
	}

	while (fgets(line, sizeof(line), file))
	{
		if (strstr(line, "\"corrector\""))  // Look for corrector block
		{
			while (fgets(line, sizeof(line), file) && !strchr(line, '}')) // Read inside corrector
			{
				if (strstr(line, "\"id\""))
				{
					sscanf(line, " \"id\" : %d", &corrector_ids[i]); // Extract ID
					printf("Corrector ID: %d\n", corrector_ids[i]);
					i++;
				}
			}
		}
	}

	fclose(file);
	ft_calculate(user, i, corrector_ids, top);
}

void	ft_loop_parse(t_user *top)
{
	char	line[256];
	FILE	*file;
	t_user	*temp;
	int		size;

	temp = top;
	while (temp)
	{
		file = fopen(temp->locations_filename, "r");
		size = 0;
		while (fgets(line, sizeof(line), file) != NULL)
		{
			if (strstr(line, "\"corrector\""))
				size++;
		}
		fclose(file);
		printf("Size: %d\n", size);
		ft_parse_data(temp, size, top);
		temp = temp->next;
	}
	//ft_debug_user(top);
}

int	main(void)
{
	FILE	*file = fopen("output.txt", "w");
	if (file == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	t_user	*top;

	top = ft_init_users("../extracted_user_id_current_students.txt");
	ft_loop_parse(top);
	ft_print_file(top, file, top);
	ft_free_users(top);
	fclose(file);
}
