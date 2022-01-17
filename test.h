/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:58:25 by abittel           #+#    #+#             */
/*   Updated: 2022/01/17 10:33:17 by abittel          ###   ########.fr       */
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
}	t_data;
/*Fonctions interation avec le joueur*/
int		get_yes_no(const char *str);
void	fill_out_stdin(void);
/*Fonctions affichage du jeux*/
void			clearScreen(void);
void			print_pikomino(int val, int pts);
long long		**get_blank_screen (int x, int y);
long long		**get_pikomino(int val, int pts);
void			print_in_screen (long long **screen, long long **obj, int x, int y);
void			print_str_in_screen (long long **screen, char *obj, int x, int y);
void			print_screen (long long **screen);
void			print_des (t_data *data, int nbr_des, int *valeurs);
void			print_table (t_data *data, int *score, int player);
void			print_playerboard (t_data *data);
/*Fonctions utils*/
int		ft_strlen(char *str); //Renvoie taille de la chaine de chr
char	*ft_strdup(const char *str); //Revoie une copie (malloc) de la chaine
void	free_data(t_data *data) ; // Free les donnees mallocs
void	free_screen (long long **screen); // Free le tableau screen
/*Fonctions entree des donnees*/
void    init_joueur (t_joueur *joueur, t_data *data, int player) ;
void    init_data (t_data *data) ;
/*Fonctions de traitements des tableaux/piles des joeurs et du plateau*/
int		get_fst_pikomino (t_data *data, int player);
int		get_lst_pikomino (t_data *data, int player);
int		get_max_pikomino (t_data *data, int player);
int		pop (int *tab);
int		pop_elem (int *tab, int val);
int		push_elem (int *tab, int val);
int		replace_val (int *tab, int val, int replace);
int		is_val_in (int *tab, int val);
int		get_joueur_has_val (t_data *data, int val);
int		is_table_has_less (t_data *data, int score);
/*Fonctions concernantm les des pour les joueurs*/
int		get_pts(int val);
int		compute_score(int *valeurs);
void	get_new_dice(t_data *data, int nbr_des);
int		can_take_dice(int *valeurs, int *des, int nbr_des);
int		is_value_in_dice(int *des, int value, int nb_dice);
int 	score_des (t_data *data, int player) ;
/*Fonctions pour les joueurs autonomes*/
int 	max_des_prenables (int nbr_des, int n, int V) ;
int 	stop_bot (t_data *data, int nbr_des, int n, int *valeurs_prises) ;
int 	score_des_bot (t_data *data, int player) ;
/*Fonctions logique du jeux*/
int		is_end_game (t_data *data) ;
void	tour_ratee (t_data *data, int player, int score) ;
int		get_pts_player(t_data *data, int player) ;
int		get_winner (t_data *data) ;
void	update_game (t_data *data, int player, int score) ;
void	lance_jeux (t_data *data, int *player_save) ;
int		menu(t_data *data) ;
/*Fonctions sauvegarde/chargement dujeux*/
void	save(t_data *data, char *name, int player) ;
int		load_game(t_data *data, char *name) ;
#endif
