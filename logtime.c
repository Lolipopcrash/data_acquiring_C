/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaa_points_data_json.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:57 by kelevequ          #+#    #+#             */
/*   Updated: 2025/02/21 09:03:20 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct s_seat
{
	char			*name;
	int				nbr;
	struct s_seat	*next;
}	t_seat;

typedef struct s_user
{
	char			*user_id;
	char			*user_name;
	char			*locations_filename;
	int				sessions;
	int				active_days;
	long			total_logtime;
	long			avrg_day_logtime;
	long			avrg_sessions_logtime;
	//t_seat			*seat;
	struct s_user	*next;
}	t_user;

t_seat	*ft_new_seat(char *name)
{
	t_seat	*new;

	new = malloc(sizeof(t_seat));
	if (!new)
		return (NULL);
	new->name = name;
	new->nbr = 0;
	new->next = NULL;
	return (new);
}

t_seat	*ft_seat_last(t_seat *seats)
{
	t_seat	*temp;

	if (!seats)
		return (0);
	temp = seats;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_seat_addback(t_seat **seats, t_seat *new)
{
	t_seat	*last;

	if (!seats || !new)
		return ;
	if (*seats == NULL)
	{
		*seats = new;
		return ;
	}
	last = ft_seat_last(*seats);
	last->next = new;
}

void	ft_free_seats(t_seat *seat)
{
	t_seat	*temp;
	t_seat	*byebye;

	temp = seat;
	while (temp)
	{
		byebye = temp;
		temp = temp->next;
		free(byebye);
	}
}

void	ft_debug_seat(t_seat *seat)
{
	int		i;

	i = 1;
	while (seat->next != NULL)
	{
		printf("\nname	%d: %s\n", i, seat->name);
		printf("nbr	%d: %d\n", i, seat->nbr);
		seat = seat->next;
		i++;
	}
	printf("\nname	%d: %s\n", i, seat->name);
	printf("nbr	%d: %d\n", i, seat->nbr);
}

t_user	*ft_new_user(char *user_id, char *user_name)
{
	t_user	*new;

	new = malloc(sizeof(t_user));
	if (!new)
		return (NULL);
	new->user_id = user_id;
	new->user_name = user_name;
	new->sessions = 0;
	new->active_days = 0;
	new->total_logtime = 0;
	new->avrg_day_logtime = 0;
	new->avrg_sessions_logtime = 0;
	//new->seat = NULL;
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

	fprintf(file, "[");
	while (user)
	{
		if (i != 0)
			fprintf(file, ",{
        ");
		else
			fprintf(file, "{
        ");

		fprintf(file, "\"user_id\": %s,
        ", user->user_id);
		fprintf(file, "\"user_name\": \"%s\",
        ", user->user_name);
		fprintf(file, "\"sessions\": %d,
        ", user->sessions);
		fprintf(file, "\"active_days\": %d,
        ", user->active_days);
		fprintf(file, "\"total_logtime\": %ld,
        ", user->total_logtime);
		fprintf(file, "\"avrg_day_logtime\": %ld,
        ", user->avrg_day_logtime);
		fprintf(file, "\"avrg_sessions_logtime\": %ld,
        ", user->avrg_sessions_logtime);
		
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

void	ft_calculate(t_user *user, int size, long *start, long *end)
{
	long	day;
	int		i;

	day = 0;
	user->sessions = size;
	i = 0;
	while (i < size)
	{
		user->total_logtime += end[i] - start[i];
		if (start[i] / 86400 != day)
		{
			day = start[i] / 86400;
			user->active_days++;
		}
		if (end[i] / 86400 != day)
		{
			day = end[i] / 86400;
			user->active_days++;
		}
		i++;
	}
	user->avrg_day_logtime = user->total_logtime / user->active_days;
	user->avrg_sessions_logtime = user->total_logtime / user->sessions;
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

static long	ft_get_epoch(const char *timestamp) {
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

void	ft_parse_data(t_user *user, int size)
{
	FILE	*file = fopen(user->locations_filename, "r");
	long	start_time[size];
	long	end_time[size];
	char	line[256];
	char	time[64];
	int		i;

	i = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (strchr(line, '{'))
		{
			while (fgets(line, sizeof(line), file) && !strchr(line, '}'))
			{  // Read inside the JSON block
				if (strstr(line, "\"end_at\""))
				{
					sscanf(line, " \"end_at\" : \" %49[^\"] \"", time);
					end_time[i] = ft_get_epoch(time);
				}
				else if (strstr(line, "\"begin_at\""))
				{
					sscanf(line, " \"begin_at\" : \" %49[^\"] \"", time);
					start_time[i] = ft_get_epoch(time);
				}/*/
				else if (strstr(line, "\"host\""))
					sscanf(line, " \"host\" : \" %49[^\"] \"", seat[i]);*/
			}
			i++;
		}
	}
	fclose(file);
	/*i = 0;
	while (i < size)
	{
		printf("start_time: %ld\n", start_time[i]);
		printf("end_time: %ld\n", end_time[i]);
		printf("seat: %s\n", seat[i]);
		printf("\n");
		i++;
	}*/
	ft_calculate(user, size, start_time, end_time);
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
	FILE	*file = fopen("output.txt", "w");
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