/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_program.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:54:15 by kelevequ          #+#    #+#             */
/*   Updated: 2025/03/16 15:46:39 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PISCINE_PROGRAM_H
# define PISCINE_PROGRAM_H

# include <string.h>
# include <unistd.h>

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
/*
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
*/
typedef struct s_user
{
	char			*user_id;
	char			*user_name;
	char			*points_filename;
	char			*locations_filename;
	char			*evaluated_filename;
	int				seats[156];
	struct s_user	*next;
}	t_user;

void	ft_user_addback(t_user **users, t_user *new);
t_user	*ft_new_user(char *user_id, char *user_name);
t_user	*ft_user_last(t_user *users);
void	ft_free_users(t_user *user);
void	ft_debug_user(t_user *user);

#endif
