/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:34:30 by kelevequ          #+#    #+#             */
/*   Updated: 2025/03/16 18:19:49 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piscine_program.h"

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

bool	ft_get_points_history(t_user *user, const char *bearer_token, int *j, int *i)
{
	char		output_file[100];
	char		command[512];
	bool		data;
	int			page;
	int			exit = 0;

	snprintf(output_file, sizeof(output_file), "points_history/%s_corrections_history.json", user->user_name);
	user->points_filename = strdup(output_file);
	page = 1;
	data = 1;
	while (/*page <= 1 && */data && *j < 1200)
	{
		if (page != 1)
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/correction_point_historics?page=%d\" >> %s",
				bearer_token, user->user_id, page++, output_file);
		}
		else
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/correction_point_historics?page=%d\" > %s",
				bearer_token, user->user_id, page++, output_file);
		}
		printf("Executing: %s\n", command);
		//exit = system(command);
		if (exit == -1)
		{
			perror("Error executing curl command");
			return (0);
		}
		if (!check_last_two(output_file))
			data = 0;
		(*j)++;/*
		if (*j != 1200)
			usleep(500000);
		else
		{
			sleep(3600);
			*j = 0;
			(*i)++;
		}*/
	}
	(*i)++;
	return (1);
}

bool	ft_get_locations_history(t_user *user, const char *bearer_token, int *j, int *i)
{
	char		output_file[100];
	char		command[512];
	bool		data;
	int			page;
	int			exit = 0;

	snprintf(output_file, sizeof(output_file), "data/location_history/%s_locations_history.json", user->user_name);
	user->locations_filename = strdup(output_file);
	page = 1;
	data = 1;
	while (/*page <= 1 && */data && *j < 1200)
	{
		if (page != 1)
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/locations?page=%d\" >> %s",
				bearer_token, user->user_id, page++, output_file);
		}
		else
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/locations?page=%d\" > %s",
				bearer_token, user->user_id, page++, output_file);
		}
		printf("Executing: %s\n", command);
		//exit = system(command);
		if (exit == -1)
		{
			perror("Error executing curl command");
			return (0);
		}
		if (!check_last_two(output_file))
			data = 0;
		(*j)++;/*
		if (*j != 1200)
			usleep(500000);
		else
		{
			sleep(3600);
			*j = 0;
			(*i)++;
		}*/
	}
	(*i)++;
	return (1);
}

bool	ft_get_evaluated_history(t_user *user, const char *bearer_token, int *j, int *i)
{
	char		output_file[100];
	char		command[512];
	bool		data;
	int			page;
	int			exit = 0;

	snprintf(output_file, sizeof(output_file), "scale_team_corrected/%s_scale_team_corrected.json", user->user_name);
	user->evaluated_filename = strdup(output_file);
	page = 1;
	data = 1;
	while (/*page <= 1 && */data && *j < 1200)
	{
		if (page != 1)
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/scale_teams/as_corrected?page=%d\" >> %s",
				bearer_token, user->user_id, page++, output_file);
		}
		else
		{
			snprintf(command, sizeof(command),
				"curl -H \"Authorization: Bearer %s\" -X GET \"https://api.intra.42.fr/v2/users/%s/scale_teams/as_corrected?page=%d\" > %s",
				bearer_token, user->user_id, page++, output_file);			
		}
		printf("Executing: %s\n", command);
		//exit = system(command);
		if (exit == -1)
		{
			perror("Error executing curl command");
			return (0);
		}
		if (!check_last_two(output_file))
			data = 0;
		(*j)++;/*
		if (*j != 1200)
			usleep(500000);
		else
		{
			sleep(3600);
			*j = 0;
			(*i)++;
		}*/
	}
	(*i)++;
	return (1);
}

bool	ft_get_data(t_user	*user, const char *bearer_token)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (user)
	{
		if (!ft_get_points_history(user, bearer_token, &j, &i))
			printf("ft_get_points_history failed\n");
		if (!ft_get_locations_history(user, bearer_token, &j, &i))
			printf("ft_get_locations_history failed\n");
		if (!ft_get_evaluated_history(user, bearer_token, &j, &i))
			printf("ft_get_evaluator_history failed\n");
		user = user->next;
	}
	return (1);
}

void	ft_print_file(t_user *user, char *filename)
{
	FILE	*file = fopen(filename, "w");
	int	i = 0;

	while (user)
	{
		fprintf(file, "%s\t", user->user_id);
		fprintf(file, "%s\t", user->user_name);
		fprintf(file, "%s\t", user->points_filename);
		fprintf(file, "%s\t", user->locations_filename);
		fprintf(file, "%s", user->evaluated_filename);
		
		fprintf(file, "\n");
		user = user->next;
		i++;
	}
	fclose(file);
}

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage: ./program \'Bearer Token\' \'User File\' \'Output File\'\n");
		return (0);
	}
	FILE	*file = fopen(argv[2], "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	char	user_id[10];
	char	user_name[32];
	t_user	*user_head = NULL;
	t_user	*user_tail = NULL;
	t_user	*user_new = NULL;

	while (fscanf(file, "%9s %31s", user_id, user_name) == 2)
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
	if (!ft_get_data(user_head, argv[1]))
		printf("ft_get_data failed\n");
	ft_print_file(user_head, argv[3]);
	ft_free_users(user_head);
	return (0);
}
