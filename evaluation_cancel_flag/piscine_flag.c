/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:57 by kelevequ          #+#    #+#             */
/*   Updated: 2025/03/16 18:29:46 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piscine_program.h"
#include <stdlib.h>

t_user	*ft_init_users(char *input_file)
{
	FILE	*file = fopen(input_file, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (NULL);
	}

	char	user_id[10];
	char	user_name[32];
	char	points_filename[100];
	char	locations_filename[100];
	char	evaluated_filename[100];
	t_user	*user_head = NULL;
	t_user	*user_tail = NULL;
	t_user	*user_new = NULL;
	int		i = 0;

	while (fscanf(file, "%9s %31s %99s %99s %99s", user_id, user_name, points_filename, locations_filename, evaluated_filename) == 5)
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
		user_new->points_filename = strdup(points_filename);
		user_new->locations_filename = strdup(locations_filename);
		user_new->evaluated_filename = strdup(evaluated_filename);
		i++;
	}

	fclose(file);
	//ft_debug_user(user_head);
	return (user_head);
}

void	ft_check_cancel(t_user *user, char *team_id, int *j)
{
	FILE	*file = fopen(user->evaluated_filename, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		printf("%s", user->evaluated_filename);
		return ;
	}

	char	line[1024];
	int		i;

	while (fgets(line, sizeof(line), file))
	{
		if (strstr(line, team_id) != NULL)
		{
			fclose(file);
			return ;
		}
	}
	fclose(file);

	file = fopen(user->points_filename, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		printf("%s", user->points_filename);
		return ;
	}

	i = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (strstr(line, team_id) != NULL)
			i++;
		if (i == 2)
		{
			fclose(file);
			return ;
		}
	}
	fclose(file);
	printf("\nlogin: %s, scale_team_id: %s", user->user_name, team_id);
	(*j)++;
}

void	ft_calculate(t_user *user, int size, char reason[size][128], char team_id[size][32])
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (i < size)
	{
		if (!strncmp(reason[i], "D", 1))
			ft_check_cancel(user, team_id[i], &j);
		i++;
	}
	if (j == 0)
		printf(": OK!\n");
	else
		printf("\n%s has %d cancelations\n", user->user_name, j);
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

void	ft_parse_data(t_user *user, int size)
{
	FILE	*file = fopen(user->points_filename, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		printf("%s", user->points_filename);
		return ;
	}

	char	reason[size][128];
	char	line[256];
	char	team_id[size][32];
	int		i;
	int		j;

	i = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (strchr(line, '{'))
		{
			j = 0;
			while (j < 1 && fgets(line, sizeof(line), file))
				j++;
			fscanf(file, " \"scale_team_id\": %s,", team_id[i]);
			fscanf(file, " \"reason\": \"%[^\"]\",", reason[i]);
			while (fgets(line, sizeof(line), file) && strchr(line, '}'));
			i++;
		}
	}
	fclose(file);
	/*i = 0;
	while (i < size)
	{
		printf("Reason: \"%s\"\n", reason[i]);
		printf("Sum: %d\n", sum[i]);
		printf("Total: %d\n", tot[i]);
		printf("\n");
		i++;
	}*/
	ft_calculate(user, size, reason, team_id);
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
		file = fopen(temp->points_filename, "r");
		if (file == NULL)
		{
			perror("Error opening file");
			printf("%s", temp->points_filename);
			return ;
		}
		size = 0;
		while (fgets(line, sizeof(line), file) != NULL)
		{
			if (strchr(line, '{'))
				size++;
		}
		fclose(file);
		printf("CHECKING %s", temp->user_name);
		ft_parse_data(temp, size);
		temp = temp->next;
	}
	ft_free_users(top);
}

int	main(int argc, char *argv[])
{
	t_user	*top;

	if (argc != 2)
	{
		printf("Usage: ./program \'User File with filenames\'");
		return (0);
	}
	top = ft_init_users(argv[1]);
	ft_loop_parse(top);
}