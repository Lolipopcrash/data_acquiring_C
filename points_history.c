/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaa_points_data_json.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:57 by kelevequ          #+#    #+#             */
/*   Updated: 2025/02/20 09:12:58 by kelevequ         ###   ########.fr       */
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
	char			*user_id;
	char			*user_name;
	char			*points_filename;
	int				pool_refunded;
	int				nbr_refunded;
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
	new->pool_refunded = 0;
	new->nbr_refunded = 0;
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

void	ft_debug_user(t_user *user)
{
	int		i;

	i = 1;
	while (user->next != NULL)
	{
		printf("\nuser_id		%d: %s\n", i, user->user_id);
		printf("user_name	%d: %s\n", i, user->user_name);
		printf("points_filename	%d: %s\n", i, user->points_filename);
		printf("pool_refunded	%d: %d\n", i, user->pool_refunded);
		printf("nbr_refunded	%d: %d\n", i, user->nbr_refunded);
		user = user->next;
		i++;
	}
	printf("\nuser_id		%d: %s\n", i, user->user_id);
	printf("user_name	%d: %s\n", i, user->user_name);
	printf("points_filename	%d: %s\n", i, user->points_filename);
	printf("pool_refunded	%d: %d\n", i, user->pool_refunded);
	printf("nbr_refunded	%d: %d\n", i, user->nbr_refunded);
}

void	ft_print_file(t_user *user, FILE *file)
{
	int	i = 0;

	fprintf(file, "[");
	while (user)
	{
		if (i != 0)
			fprintf(file, ",{");
		else
			fprintf(file, "{");

		fprintf(file, "\"user_id\": %s,", user->user_id);
		fprintf(file, "\"user_name\": \"%s\",", user->user_name);
		fprintf(file, "\"points_filename\": \"%s\",", user->points_filename);
		fprintf(file, "\"pool_refunded\": %d,", user->pool_refunded);
		fprintf(file, "\"nbr_refunded\": %d,", user->nbr_refunded);
		
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
	char	points_filename[100];
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
		snprintf(points_filename, sizeof(points_filename), "%s_corrections_history.json", user_new->user_name);
		user_new->points_filename = strdup(points_filename);
	}

	fclose(file);
	//ft_debug_user(user_head);
	return (user_head);
}

long	ft_get_epoch(const char *timestamp) {
	struct tm tm_time = {0};
	int milliseconds;
	
	// Parse the string (ignoring milliseconds and 'Z')
	if (sscanf(timestamp, "%d-%d-%dT%d:%d:%d.%dZ", 
			   &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday,
			   &tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec, &milliseconds) != 7) {
		fprintf(stderr, "Invalid timestamp format\n");
		return -1;
	}

	// Adjust values
	tm_time.tm_year -= 1900;  // tm_year is years since 1900
	tm_time.tm_mon -= 1;      // tm_mon is 0-based (0 = January)
	
	// Convert to epoch (mktime assumes local time, so use timegm() if available)
	time_t epoch = mktime(&tm_time);
	
	// Adjust for UTC (only needed if mktime() is used instead of timegm())
	//epoch -= timezone;  // timezone is a global variable in <time.h>

	return ((long)epoch);
}

void	ft_calculate(t_user *user, int size, int *sum, int *tot, char reason[size][128], char time[size][128])
{
	(void)tot;
	long	timestamp;
	int		i;

	i = 1;
	while (i < size)
	{
		timestamp = ft_get_epoch(time[i]);
		if (1721974740 < timestamp && timestamp < 1722014430)
		{
			if (!strncmp(reason[i], "Ea", 2))
			{
				if (sum[i] % 2 == 0)
					user->pool_refunded += sum[i] / 2;
				user->nbr_refunded++;
			}
			else if (!strncmp(reason[i], "Refund d", 8))
			{
				user->pool_refunded += sum[i];
				user->nbr_refunded++;
			}
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

void	ft_parse_data(t_user *user, int size)
{
	FILE	*file = fopen(user->points_filename, "r");
	char	reason[size][128];
	char	time[size][128];
	char	line[256];
	int		sum[size];
	int		tot[size];
	int		i;
	int		j;

	i = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (strchr(line, '{'))
		{
			j = 0;
			while (j < 2 && fgets(line, sizeof(line), file))
				j++;
			fscanf(file, " \"reason\": \"%[^\"]\",", reason[i]);
			fscanf(file, " \"sum\": %d,", &sum[i]);
			fscanf(file, " \"total\": %d,", &tot[i]);
			fscanf(file, " \"created_at\": \"%[^\"]\",", time[i]);
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
	ft_calculate(user, size, sum, tot, reason, time);
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
	FILE	*file = fopen("aaa_output.txt", "w");
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