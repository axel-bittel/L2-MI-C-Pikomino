/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:58:25 by abittel           #+#    #+#             */
/*   Updated: 2022/01/13 16:56:34 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

typedef struct s_joueur 
{
	char	*name;
	int		pikomino[16];
	int		is_bot;
}	t_joueur;

typedef struct s_data 
{
	char		*name_game;
	int			nb_players;
	int			des[8];
	t_joueur	*players;
	int			pikomino[16];
}			t_data;
void		print_table (t_data *data, int *score, int player);
void		print_des (t_data *data, int nbr_des, int *valeurs);
int			get_pts(int val);
void		print_screen (long long	**screen);
void		print_str_in_screen (long long**screen, char *obj, int x, int y);
void		print_in_screen (long long **screen, long long **obj, int x, int y);
long long	**get_pikomino(int val, int pts);
long long	**get_blank_screen (int x, int y);
int			get_yes_no(const char *str);
void		clearScreen(void);
int			ft_strlen(char *str);
int			get_lst_pikomino (t_data *data, int player);
#endif

