/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaa_points_data_json.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:57 by kelevequ          #+#    #+#             */
/*   Updated: 2025/02/12 08:44:35 by kelevequ         ###   ########.fr       */
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
	char			*points_filename;
	char			*languages[12];
	int				nbr_lang;
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
		user = user->next;
		i++;
	}
	printf("\nuser_id		%d: %s\n", i, user->user_id);
	printf("user_name	%d: %s\n", i, user->user_name);
	printf("points_filename	%d: %s\n", i, user->points_filename);
}

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
		fprintf(file, "\"points_filename\": \"%s\",", user->points_filename);
		j = -1;
		while (user->languages[++j] != NULL)
			fprintf(file, "\"language %d\": \"%s\",", j, user->languages[j]);
		fprintf(file, "\"nbr_lang\": %d,", user->nbr_lang);
		
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

void	ft_calculate(t_user *user, int size, int *lang)
{
	int	i;

	i = 0;
	while (lang[i] != 0)
	{
		if (lang[i] == 1)
			user->languages[i] = strdup("fr");
		else if (lang[i] == 2)
			user->languages[i] = strdup("en");
		else if (lang[i] == 3)
			user->languages[i] = strdup("ro");
		else if (lang[i] == 5)
			user->languages[i] = strdup("uk");
		else if (lang[i] == 6)
			user->languages[i] = strdup("ru");
		else if (lang[i] == 9)
			user->languages[i] = strdup("pt");
		else if (lang[i] == 11)
			user->languages[i] = strdup("es");
		else if (lang[i] == 13)
			user->languages[i] = strdup("ja");
		else if (lang[i] == 14)
			user->languages[i] = strdup("ko");
		else if (lang[i] == 15)
			user->languages[i] = strdup("hy");
		else if (lang[i] == 16)
			user->languages[i] = strdup("it");
		else if (lang[i] == 17)
			user->languages[i] = strdup("pt_br");
		else if (lang[i] == 18)
			user->languages[i] = strdup("tr");
		else if (lang[i] == 19)
			user->languages[i] = strdup("ca_es");
		else if (lang[i] == 20)
			user->languages[i] = strdup("nl");
		else if (lang[i] == 21)
			user->languages[i] = strdup("de");
		else if (lang[i] == 24)
			user->languages[i] = strdup("pl");
		i++;
	}
	user->nbr_lang = size;
}

/*{
	"id":1032160,
	"language_id":2,
	"user_id":201565,
	"position":1,
	"created_at":"2024-08-31T14:43:34.417Z"
}*/

void	ft_parse_data(t_user *user, int size)
{
	FILE	*file = fopen(user->points_filename, "r");
	char	line[256];
	int		lang[size];
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
			fscanf(file, " \"language_id\": %d,", &lang[i]);
			while (fgets(line, sizeof(line), file) && strchr(line, '}'));
			i++;
		}
	}
	fclose(file);
	/*i = 0;
	while (i < size)
	{
		printf("Language ID: %d\n", lang[i]);
		printf("\n");
		i++;
	}*/
	ft_calculate(user, size, lang);
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