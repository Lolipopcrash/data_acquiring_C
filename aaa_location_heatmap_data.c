/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaa_location_heatmap_data.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:57 by kelevequ          #+#    #+#             */
/*   Updated: 2025/02/21 10:32:37 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char	g_seats[156][8] = {
	"c1r1s1", "c1r1s2", "c1r1s3", "c1r1s4", "c1r1s5", "c1r1s6",
	"c1r2s1", "c1r2s2", "c1r2s3", "c1r2s4", "c1r2s5", "c1r2s6",
	"c1r3s1", "c1r3s2", "c1r3s3", "c1r3s4", "c1r3s5",
	"c1r4s1", "c1r4s2", "c1r4s3", "c1r4s4", "c1r4s5",
	"c1r5s1", "c1r5s2", "c1r5s3", "c1r5s4", "c1r5s5",
	"c1r6s1", "c1r6s2", "c1r6s3", "c1r6s4", "c1r6s5",
	"c1r7s1", "c1r7s2", "c1r7s3", "c1r7s4", "c1r7s5",
	"c1r8s1", "c1r8s2", "c1r8s3", "c1r8s4", "c1r8s5",
	"c1r9s1", "c1r9s2", "c1r9s3", "c1r9s4",
	"c1r10s1", "c1r10s2", "c1r10s3", "c1r10s4",
	"c2r1s1", "c2r1s2", "c2r1s3", "c2r1s4", "c2r1s5", "c2r1s6",
	"c2r2s1", "c2r2s2", "c2r2s3", "c2r2s4", "c2r2s5", "c2r2s6",
	"c2r3s1", "c2r3s2", "c2r3s3", "c2r3s4", "c2r3s5",
	"c2r4s1", "c2r4s2", "c2r4s3", "c2r4s4", "c2r4s5",
	"c2r5s1", "c2r5s2", "c2r5s3", "c2r5s4", "c2r5s5",
	"c2r6s1", "c2r6s2", "c2r6s3", "c2r6s4", "c2r6s5",
	"c2r7s1", "c2r7s2", "c2r7s3", "c2r7s4", "c2r7s5",
	"c2r8s1", "c2r8s2", "c2r8s3", "c2r8s4", "c2r8s5",
	"c2r9s1", "c2r9s2", "c2r9s3", "c2r9s4", "c2r9s5",
	"c2r10s1", "c2r10s2", "c2r10s3", "c2r10s4", "c2r10s5",
	"c3r1s1", "c3r1s2", "c3r1s3", "c3r1s4", "c3r1s5", "c3r1s6",
	"c3r2s1", "c3r2s2", "c3r2s3", "c3r2s4", "c3r2s5", "c3r2s6",
	"c3r3s1", "c3r3s2", "c3r3s3", "c3r3s4", "c3r3s5", "c3r3s6",
	"c3r4s1", "c3r4s2", "c3r4s3", "c3r4s4", "c3r4s5", "c3r4s6",
	"c3r5s1", "c3r5s2", "c3r5s3", "c3r5s4", "c3r5s5", "c3r5s6",
	"c3r6s1", "c3r6s2", "c3r6s3", "c3r6s4", "c3r6s5", "c3r6s6",
	"c3r7s1", "c3r7s2", "c3r7s3", "c3r7s4", "c3r7s5", "c3r7s6",
	"c3r8s1", "c3r8s2", "c3r8s3", "c3r8s4", "c3r8s5", "c3r8s6",
	"c3r9s1", "c3r9s2", "c3r9s3", "c3r9s4", "c3r9s5", "c3r9s6"
};

typedef struct s_user
{
	char			*user_id;
	char			*user_name;
	char			*locations_filename;
	int				seats[156];
	struct s_user	*next;
}	t_user;

t_user	*ft_new_user(char *user_id, char *user_name)
{
	int		i;
	t_user	*new;

	new = malloc(sizeof(t_user));
	if (!new)
		return (NULL);
	new->user_id = user_id;
	new->user_name = user_name;
	i = 0;
	while (new->seats[i])
		new->seats[i++] = 0;
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
/*
void	ft_debug_user(t_user *user)
{
	int		i;

	i = 1;
	while (user->next != NULL)
	{
		printf("\nuser_id		%d: %s\n", i, user->user_id);
		printf("user_name	%d: %s\n", i, user->user_name);
		printf("locations_filename	%d: %s\n", i, user->locations_filename);
		printf("sessions	%d: %d\n", i, user->sessions);
		printf("active_days	%d: %d\n", i, user->active_days);
		printf("total_logtime	%d: %d\n", i, user->total_logtime);
		printf("avrg_day_logtime	%d: %d\n", i, user->avrg_day_logtime);
		printf("avrg_sessions_logtime	%d: %d\n", i, user->avrg_sessions_logtime);
		ft_debug_seat(user->seat);
		user = user->next;
		i++;
	}
	printf("\nuser_id		%d: %s\n", i, user->user_id);
	printf("user_name	%d: %s\n", i, user->user_name);
	printf("locations_filename	%d: %s\n", i, user->locations_filename);
	printf("sessions	%d: %d\n", i, user->sessions);
	printf("active_days	%d: %d\n", i, user->active_days);
	printf("total_logtime	%d: %d\n", i, user->total_logtime);
	printf("avrg_day_logtime	%d: %d\n", i, user->avrg_day_logtime);
	printf("avrg_sessions_logtime	%d: %d\n", i, user->avrg_sessions_logtime);
	ft_debug_seat(user->seat);
}
*/
void	ft_print_file(t_user *user, FILE *file)
{
	int	i = 0;
	int	j;

	fprintf(file, "[");
	while (user)
	{
		if (i != 0)
			fprintf(file, ",{");
		else
			fprintf(file, "{");

		fprintf(file, "\"user_id\": %s,", user->user_id);
		fprintf(file, "\"user_name\": \"%s\",", user->user_name);
		j = -1;
		while (++j < 156)
			fprintf(file, "\"%s\": %d,", g_seats[j], user->seats[j]);
		
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

	char	user_id[10];
	char	user_name[10];
	char	locations_filename[100];
	t_user	*user_head = NULL;
	t_user	*user_tail = NULL;
	t_user	*user_new = NULL;
	int		i = 0;

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
		snprintf(locations_filename, sizeof(locations_filename), "%s_locations_history.json", user_new->user_name);
		user_new->locations_filename = strdup(locations_filename);
		i++;
	}

	fclose(file);
	//ft_debug_user(user_head);
	return (user_head);
}

void	ft_calculate(t_user *user, int size, char seat[size][8])
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < 156 && strcmp(seat[i], g_seats[j]))
			j++;
		if (j < 156)
			user->seats[j]++;
		i++;
	}
}


void	ft_parse_data(t_user *user, int size)
{
	FILE	*file = fopen(user->locations_filename, "r");
	char	seat[size][8];
	char	line[256];
	int		i;

	i = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (strchr(line, '{'))
		{
			while (fgets(line, sizeof(line), file) && !strchr(line, '}'))
			{
				if (strstr(line, "\"host\""))
					sscanf(line, " \"host\" : \" %49[^\"] \"", seat[i]);
			}
			i++;
		}
	}
	fclose(file);
	ft_calculate(user, size, seat);
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
			if (strchr(line, '{'))
				size++;
		}
		fclose(file);
		printf("Size: %d\n", size);
		ft_parse_data(temp, size);
		temp = temp->next;
	}
	//ft_debug_user(top);
}

int	main(void)
{
	FILE	*file = fopen("aaa_seats.txt", "w");
	if (file == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	t_user	*top;

	top = ft_init_users("../extracted_user_id_current_students.txt");
	ft_loop_parse(top);
	ft_print_file(top, file);
	ft_free_users(top);
	fclose(file);
}