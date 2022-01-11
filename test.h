/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:58:25 by abittel           #+#    #+#             */
/*   Updated: 2022/01/10 19:40:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

typedef struct s_joueur 
{
	char	*name;
	int		*pikomino;
	int		is_bot;
}	t_joueur;

typedef struct s_data 
{
	int			nb_players;
	int			des[8];
	t_joueur	*players;
	int			pikomino[16];
}	t_data;
void	print_table (t_data *data);
void	print_des (t_data *data);
int		get_pts(int val);
void	print_screen (int	**screen);
void	print_str_in_screen (int**screen, char *obj, int x, int y);
void	print_in_screen (int**screen, int **obj, int x, int y);
int		**get_pikomino(int val, int pts);
int		**get_blank_screen (int x, int y);
int		get_yes_no(const char *str);
void	clearScreen(void);
#endif

