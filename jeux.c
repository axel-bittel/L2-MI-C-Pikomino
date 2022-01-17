/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeux.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:15:07 by abittel           #+#    #+#             */
/*   Updated: 2022/01/17 21:29:43 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "jeux.h"

//***************************************************************************
//#PRINT#
//***************************************************************************
void	clearScreen(void)
{
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void	fill_out_stdin(void)
{
	int	c;

	fflush(stdin);
	while((c=getchar()) != EOF && c != '\n');
}

int	get_yes_no(const char *str) // Pose une question au joueur
{
	char	res;
	
	res = 0;
	while (!res)
	{
		printf ("%s (o/n) : ", str);
		scanf ("%c", &res);
		fill_out_stdin();
		if (res != 'o' && res != 'n')
		{
			printf ("Wrong input, please write o or n.\n");
			res = 0;
		}
	}
	return (res == 'o');
}

int	ft_strlen(char *str) //Taille d'une chaine
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2) // Join deux chaine dans une nouvelle malloc
{
	int	i;
	int	j;
	char	*res;

	i = -1;
	res = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!res)
		return (NULL);
	if (!s1 || !s2)
		return (0);
	while (s1[++i])
		res[i] = s1[i];
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = 0;
	return (res);
}

char	*ft_strdup(const char *str) //Copie chaine dans un nouvelle chaine malloc
{
	int		i;
	char	*res;

	i = -1;
	res = malloc (sizeof(char) * (ft_strlen((char *)str) + 1));
	while (str[++i])
		res[i] = str[i];
	res[i] = 0;
	return (res);
}

long long	**get_blank_screen (int x, int y) //Genere un screen vide
{
	int		i;
	int		j;
	long long	**res;

	i = -1;
	res = malloc (sizeof(long long *) * (y + 1)); 
	res[y] = NULL;
	while (++i < y)
	{
		j = -1;
		res[i] = malloc (sizeof(long long) * (x + 1));
		res[i][x] = 0;
		while (++j < x)
		{
			res[i][j] = ' ';
			if (!i && !j)
				res[i][j] = 14849164;
			else if (!i && j == (x - 1))
				res[i][j] = 14849168;
			else if (i == (y - 1) && j == (x - 1))
				res[i][j] = 14849176; 
			else if (i == (y - 1) && !j)
				res[i][j] = 14849172; 
			else if (!i || i == (y - 1))
				res[i][j] = 14849152;
			else if (!j || j == (x - 1))
				res[i][j] = 14849154;
		}
	}
	return (res);
}

long long	**get_pikomino(int val, int pts)
{
	long long	**pik_res;

	val = val == -1 ? 0 : val;
	pik_res = malloc (sizeof(long long *) * 6);
	pik_res[0] = malloc (sizeof(long long) * 5);
	pik_res[0][0] = 14849164; // chr = ┌
	pik_res[0][1] = 14849152; // chr = ─
	pik_res[0][2] = 14849152; // chr = ─
	pik_res[0][3] = 14849168; // chr = ┐
	pik_res[0][4] = 0;  
	pik_res[1] = malloc (sizeof(long long) * 5); 
	pik_res[1][0] = 14849154; // chr = │
	pik_res[1][1] = (long long)(' ');
	pik_res[1][2] = (long long)(' ');
	pik_res[1][3] = 14849154; // chr = │
	pik_res[1][4] = 0;
	pik_res[2] = malloc (sizeof(long long) * 5);
	pik_res[2][0] = val ? 14849180 : 14849154; // chr = ├ ou │
	pik_res[2][1] = val ? 14849152 : (long long)(' '); //chr = ─ ou space
	pik_res[2][2] = val ? 14849152 : (long long)(' '); //chr = ─ ou space
	pik_res[2][3] = val ? 14849188 : 14849154; // chr = ┤ ou │
	pik_res[2][4] = 0;
	pik_res[3] = malloc (sizeof(long long) * 5);
	pik_res[3][0] = 14849154; // chr = │
	pik_res[3][1] = (long long)(' ');
	pik_res[3][2] = (long long)(' ');
	pik_res[3][3] = 14849154; // chr = │
	pik_res[3][4] = 0;
	pik_res[4] = malloc (sizeof(long long) * 5);
	pik_res[4][0] = 14849172; // chr = └
	pik_res[4][1] = 14849152; // chr = ─
	pik_res[4][2] = 14849152; // chr = ─
	pik_res[4][3] = 14849176; // chr = ┘  
	pik_res[4][4] = 0;
	if (val)
	{
		pik_res[1][1] = val / 10 + 48;
		pik_res[1][2] = (val % 10) + 48;
		pik_res[3][2] = (pts % 10) + 48;
	}
	pik_res[5] = NULL;
	return (pik_res);
}

void	print_in_screen (long long**screen, long long **obj, int x, int y) //Rempli screen avec obj en (x, y)
{
	int		i;
	int		j;

	i = -1;
	while (obj[++i])
	{
		j = -1;
		while (obj[i][++j])
			screen[y + i][x + j] = obj[i][j];
		free (obj [i]);
	}
	free (obj);
}

void	print_str_in_screen (long long**screen, char *obj, int x, int y) //Rempli screen avec la chaine obj en (x, y)
{
	int		i;

	i = -1;
	while (obj[++i])
		screen[y][x + i] = obj[i];
}

void	print_screen (long long	**screen) //Affiche le tableau, en decomposant lel'entier de 64 bits en octets
{
	int		i;
	int		j;
	char	inter;

	i = -1;
	while (screen[++i])
	{
		j = -1;
		while (screen[i][++j])
		{
			inter = (char)(screen[i][j] >> 56);
			write (1, &inter, 1);
			inter = (char)(screen[i][j] >> 48);
			write (1, &inter, 1);
			inter = (char)(screen[i][j] >> 40);
			write (1, &inter, 1);
			inter = (char)(screen[i][j] >> 32);
			write (1, &inter, 1);
			inter = (char)(screen[i][j] >> 24);
			write (1, &inter, 1);
			inter = (char)(screen[i][j] >> 16);
			write (1, &inter, 1);
			inter = (char)(screen[i][j] >> 8);
			write (1, &inter, 1);
			inter = (char)screen[i][j];
			write (1, &inter, 1);
		}
		write (1, "\n", 1);
	}
}

void	print_des (t_data *data, int nbr_des, int *valeurs) //Affiche les des
{
	int		i;
	int		j;
	char	inter;

	if (data)
	{
		i = -1;
		while (++i < nbr_des)
		{
			if (data->des[i] == -1)
				continue ;
			inter = data->des[i] + 48;
			write (1, "[", 1);
			if (data->des[i] == 0)
				write (1, "V", 1);
			else
				write (1, &inter, 1);
			write (1, "] ", 1);
		}
		write (1, "                              ", 30);
	}
	i = -1;
	while (++i < 6)
	{
		j = -1;
		if (valeurs[i] == -1)
			continue ;
		while (++j < valeurs[i])
		{
			inter = i + 48;
			write (1, "[", 1);
			if (i == 0)
				write (1, "V", 1);
			else
				write (1, &inter, 1);
			write (1, "] ", 1);
		}
	}
	printf ("	|	Interim score : %d\n", compute_score(valeurs));
}

void	free_screen (long long **screen) //Free tableau screen
{
	int	i;

	i = -1;
	while (screen[++i])
		free (screen[i]);
	free (screen);
}

void	print_table (t_data *data, int *score, int player) //Affiche le jeux
{
	int			i;
	long long	**screen;

	i = -1;
	screen = get_blank_screen(150, 30);
	//ptint table
	print_in_screen (screen, get_blank_screen(100, 15), 25, 8);
	//print players
	while (++i < 4)
	{
		if (i < data->nb_players)
		{
			print_str_in_screen (screen,  data->players[i].name, 25 + i * 30, 2);
			if (i == player)
			{
				screen [2][25 + ft_strlen(data->players[i].name) + i * 30] = '[';
				screen [2][26 + ft_strlen(data->players[i].name)+ i * 30] = '*';
				screen [2][27 + ft_strlen(data->players[i].name)+ i * 30] = ']';
			}
			print_in_screen(screen, get_pikomino(get_lst_pikomino(data, i), get_pts(get_lst_pikomino(data, i))), 27 + i * 30, 3);
		}
	}
	i = 3;
	while (++i < 7)
	{
		if (i < data->nb_players)
		{
			print_str_in_screen (screen, data->players[i].name, 25 + (i - 4) * 30, 23);
			if (i == player)
			{
				screen [23][25 + ft_strlen(data->players[i].name)+ (i - 4) * 30] = '[';
				screen [23][26 + ft_strlen(data->players[i].name)+ (i - 4) * 30] = '*';
				screen [23][27 + ft_strlen(data->players[i].name)+ (i - 4) * 30] = ']';
			}
			print_in_screen(screen, get_pikomino(get_lst_pikomino(data, i), get_pts(get_lst_pikomino(data, i))), 27 + (i - 4) * 30, 24);
		}
	}
	//print pikomino
	i = -1;
	while (++i < 16)
		if (data->pikomino[i] != -1)
			print_in_screen(screen, get_pikomino(data->pikomino[i], get_pts(data->pikomino[i])), 22 + (i + 1) * 6, 12);
	//print screen final
	print_screen (screen);
	if (score)
	{
		char	d = *score / 10 + 48;
		write (1, "Score : ",8);
		write (1, &d, 1);
		d = *score % 10 + 48; 
		write (1, &d, 1);
		write (1, "\n", 1);
	}
	free_screen (screen);
	write (1, "\n", 1);
}

void	print_playerboard (t_data *data) //Affiche le tableau des joeurs (chargement des donnees)
{
	int			i;
	long long	**screen;

	i = -1;
	screen = get_blank_screen(150, 30);
	print_str_in_screen (screen, "PLAYER BOARD : ", 1, 1);
	while (++i < data->nb_players)
	{
		if (data->players[i].name)
		{
			print_str_in_screen (screen, "player ", 3, i + 3 + (i * 3));
			screen[i + 3 + (i * 3)][10] = (i + 1) + 48;
			screen[i + 3 + (i * 3)][11] = ':';
			print_str_in_screen (screen, data->players[i].name, 13 , i + 3 + (i * 3));
			if (data->players[i].is_bot)
				print_str_in_screen (screen, "[ BOT ]", 14 + ft_strlen(data->players[i].name) , i + 3 + (i * 3));
		}
	}
	print_screen (screen);
	free_screen (screen);
	write (1, "\n", 1);
}

void	print_score (t_data *data, int winner) //Affiche tableau de resultats
{
	int			i;
	int			j;
	long long	**screen;

	i = -1;
	screen = get_blank_screen(150, 43);
	print_str_in_screen (screen, "SCORE : ", 1, 1);
	while (++i < data->nb_players)
	{
		if (data->players[i].name)
		{
			print_str_in_screen (screen, data->players[i].name, 2 , i + 3 + (i * 5));
			j = -1;
			while (++j < 16)
				if (data->players[i].pikomino[j] != -1)
					print_in_screen(screen, get_pikomino(data->players[i].pikomino[j], get_pts(data->players[i].pikomino[j])), 4 + 10 + (j + 1) * 6, i + 1  + (i * 5));
		}
	}
	print_screen (screen);
	free_screen (screen);
	write (1, "\n", 1);
}
//***************************************************************************yy
//#DATA_MANAGEMENT#
//***************************************************************************yy
void    init_joueur (t_joueur *joueur, t_data *data, int player) //Initialise un joueur
{
	printf ("Player %d : \n", player + 1);
    char str1[] = "Are you human ?";
    char *str2 = malloc (sizeof(char) * 13);
    const char *str[] = {"S.Veil" , "D.Knuth", "M.Debre", "A.Lovelace", "G.Hopper", "Ghandhi", "N.Mandela"} ;
    int i = 0 ;
    int j = -1 ;
    if (get_yes_no(str1) == 1) 
    {
        do 
        {
			printf ("Write your name : ");
            scanf ("%s", str2); 
			fill_out_stdin();
			str2[12] = 0;
            if (ft_strlen(str2) <= 10)
                joueur->name = ft_strdup(str2) ;
            else 
                printf ("Please, write a name with less than 10 letters.\n") ;
        } while (ft_strlen(str2) > 10) ;
        joueur->is_bot = 0 ;
        i += 1 ;
        while (++j < 16) 
            joueur->pikomino[j] = -1 ;
    }
    else 
    { 
        joueur->name = ft_strdup(str[player]) ; 
        joueur->is_bot = 1 ;
        while (++j < 16) 
            joueur->pikomino[j] = -1 ;
    }
	free (str2);
	clearScreen();
	print_playerboard (data);
}


void    init_data (t_data *data)//Initialise les donnees du jeux 
{
    char str2[] = "Decide on a number of players. You need to be between 2 and 7 players (included)\nWrite this number : " ;
    int n ;
    int i = -1 ;
    int j = -1 ;
    int k = -1 ;

	print_playerboard (data);
    do 
    {
		data->name_game = malloc (sizeof(char) * 11);
		printf("Give a name to your game play : ");
		scanf("%s", data->name_game);
		data->name_game[10] = 0;
		fill_out_stdin();
        printf("%s : ", str2);
        scanf("%d", &n);
		fill_out_stdin();
        if ( (n < 2) || (n > 7) )
            printf("You need to be between 2 and 7 players (included) to begin a game, with or without robot. \n") ;
        else 
        {
            data->nb_players = n ;
            data->players = malloc (sizeof (t_joueur) * data->nb_players) ;
            while (++i < data->nb_players)
				data->players[i].name = 0;
			i = -1;
            while (++i < data->nb_players)
                init_joueur (data->players + i, data, i) ;
            while (++j < 8)
                data->des[j] = 0 ;
            while (++k < 16)
                data->pikomino[k] = 21 + k;
        }
    } while ((n < 2) || (n > 7)) ;
}

int	get_fst_pikomino (t_data *data, int player)//Renvoie le premier pikomono d'un joeur (-1 est le plateau)
{
	int	*tab;
	int	i;

	if (player == -1)
		tab = data->pikomino;
	else
		tab = data->players[player].pikomino;
	i = -1;
	while (++i < 16)
		if (tab[i] != -1)
			return (tab[i]);
	return (-1);
}

int	get_lst_pikomino (t_data *data, int player)//Renvoie le dernier pikomono d'un joeur (-1 est le plateau)
{
	int	*tab;
	int	i;

	if (player == -1)
		tab = data->pikomino;
	else
		tab = data->players[player].pikomino;
	i = -1;
	while (++i < 15)
		if (tab[i + 1] == -1)
			return (tab[i]);
	return (i);
}

int	get_max_pikomino (t_data *data, int player) //Renvoie le pikomono max d'un joeur (-1 est le plateau)
{
	int	*tab;
	int	i;
	int	res;

	if (player == -1)
		tab = data->pikomino;
	else
		tab = data->players[player].pikomino;
	i = -1;
	res = tab[0];
	while (++i < 16)
		if (tab[i] > res)
			res = tab[i];
	return (res);
}

int	pop (int *tab) // Supprime le dernier elelemt de la pile
{
	int	i;
	int	res;

	i = -1;
	while (++i < 16)
	{
		if (tab[i] == -1 && i)
		{
			res = tab[i - 1];
			tab[i - 1] = -1;
			return (res);
		}
		else if (tab[i] == -1)
			return (-1);
	}
}

int	pop_elem (int *tab, int val) //Supprime une element dans la pile
{
	int	i;
	int	j;
	int	res;

	i = -1;
	while (++i < 16)
	{
		if (tab[i] == val)
		{
			j = i;
			while (++j < 16)
				tab[j - 1] = tab[j];
			tab[15] = -1; 
			return (val);
		}
	}
	return (-1);
}

int	push_elem (int *tab, int val) //Ajoute une element dans la pile
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		if (tab[i] == -1)
		{
			tab[i] = val;
			return (1);
		}
	}
	return (0);
}

int	replace_val (int *tab, int val, int replace) //Remplace la valeur dans la pile
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		if (tab[i] == val)
		{
			tab[i] = replace;
			return (i);
		}
	}
	return (-1);
}

int	is_val_in (int *tab, int val) // val est dans tab ?
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		if (tab[i] == val)
			return (1);
	}
	return (0);
}

int	get_joueur_has_val (t_data *data, int val) // Donne le joueur qui possede val au sommet de sa pile (test le plateau aussi)
{
	int	i;

	i = -1;
	while (++i < data->nb_players)
		if (get_lst_pikomino (data, i) == val)
				return (i);
	if (is_val_in(data->pikomino, val))
		return (-1);
	return (-2);
}

int	is_table_has_less (t_data *data, int score) //Revoie la valeur inferieur ou egale sur le plateau de jeux (-1 sinon)
{
	while (score >= 21)
	{
		if (is_val_in(data->pikomino, score))
			return (score);
		score--;
	}
	return (-1);
}
//***************************************************************************
//#GAME#
//***************************************************************************

int	get_pts(int val) //Points d'un pikomono
{
	if (val >= 21 && val <= 24)
		return (1);
	else if (val >= 25 && val <= 28)
		return (2);
	else if (val >= 29 && val <= 32)
		return (3);
	else if (val >= 33 && val <= 36)
		return (4);
	return (0);
}

int	compute_score(int *valeurs) //Donne le score d'un joueur
{
	int	i;
	int	score = 0;

	i = 0;
	if (valeurs[i] != -1)
		score += valeurs[0] * 5;                                /* La face V du dé est représentée par la valeur 0, or elle vaut (en score) 5 points        */
	while (++i < 6)
		if (valeurs[i] != -1)
			score += i * valeurs[i];
	return (score); 
}

void	get_new_dice(t_data *data, int nbr_des) //Initialise un nouveau set de des
{
	int	i;

	i = -1; 
	while (++i < (nbr_des+1))
		data->des[i] = (rand() % 6) ;
}

int	can_take_dice(int *valeurs, int *des, int nbr_des) //Le joueur peut-il prendre un des ?
{
	int	i;

	i = -1 ;
	while (++i < nbr_des)
		if (valeurs[des[i]] == -1)
			break ;
	if (i == nbr_des)
		return (0);
	else 
		return (1);
}

int	is_value_in_dice(int *des, int value, int nb_dice) //Value est-elle dans le tableau de des ? 
{
	int	i;
	int	cpt;

	i = -1 ;
	cpt = 0;
	while (++i < nb_dice) 
	{
		if (des[i] == value)
			cpt += 1;
	}
	return (cpt);
}

int score_des (t_data *data, int player) //Systeme de lance de des pour le joueur.
{
	int i = -1 ;
	int n = 0;								    	/* Valeur dé que joueur veut garder                                                      		        */
	int possibilites = 6;					    	/* Nombre valeurs déja prises pour les dés                                                              */
	int nbr_des = 8;							    /* Nombre dés à lancer                                                                                  */
	int nbr_lancers = 0;							/* Nombre de lancers effectués et ayant aboutis                                                         */
	int valeurs[6] = {-1, -1, -1, -1, -1, -1};		/* Tableau où indice = valeur du dé gardé ; valeur case = nbr dés gardés pour cette valeur              */
	char str[] = "Do you want to roll the dice again ?" ;
	char inter[] = "          ";

	do
	{
		get_new_dice(data, nbr_des);
		clearScreen();
		print_table (data, 0, player);
		printf ("%s :\n", data->players[player].name);
		print_des(data, nbr_des, valeurs);
		if (nbr_lancers)
		{
			i = -1 ;
			possibilites = 6;
			while (++i < 6)
				if (valeurs[i] != -1)
					possibilites -= 1; 
		}
		if (possibilites) 
		{
			int	err;
			do {
				err = 0;
				if (!can_take_dice(valeurs, data->des, nbr_des))
				{
					printf ("You can't take a dice !\n");
					sleep (3);
					return (0);
				}
				printf("\nWhich dice do you want to keep ? \n") ;
				printf("Write the value : ") ;
				scanf("%s", inter);
				n = !strcmp(inter,"V\n") ? 0 : atoi(inter);
				fill_out_stdin();
				if (!is_value_in_dice(data->des, n, nbr_des))
					err = printf("You don't have this value, please, choose one present on the dice.\n") ;
				else if (valeurs[n] != -1)
					err = printf("You've already choosen this value, please, take another one.\n") ;
				else
				{
					valeurs[n] = is_value_in_dice(data->des, n, nbr_des); 
					nbr_des -= is_value_in_dice(data->des, n, nbr_des);
					nbr_lancers++;
				}
			} while (err);
			clearScreen();
			print_table (data, 0, player);
			print_des(0, nbr_des, valeurs);
			printf ("You have %d dice to play \n", nbr_des);
		} 
	} while (possibilites && get_yes_no(str)); 
	if (valeurs[0] == -1)
		return (0);
	return (compute_score(valeurs));
}

int max_des_prenables (int nbr_des, int n, int V)
{
    int nbr_prenables ;

    if ( n <= 3)
    {
        if (nbr_des >= 7)
            nbr_prenables = 4 ;
        else if ( (nbr_des >= 5) && (nbr_des < 7) )
            nbr_prenables = 3 ;
        else 
            nbr_prenables = 2 ;
    }
    else 
    {
        if (V != 0)                                      /* V représentra le nombre de face V gardée  (ie : valeurs_prises[0] )                             */
            nbr_prenables = nbr_des ;
        else 
            nbr_prenables = nbr_des - 1;
    }
	return (nbr_prenables);
}


int stop_bot (t_data *data, int nbr_des, int n, int *valeurs_prises) 
{
    int stop = 0;                                       /* Vaut 0 si on s'arrête, 1 sinon                                                                   */
    int i = -1 ;
    int cpt = 0 ;                                       /* Compte nombre de valeurs différentes qu'on a déjà prises, sans considérer le nbr de dés          */
    int score  = 0;

    while (++i < 6)
        if (valeurs_prises[i] != 0)
            cpt += 1 ;
    if ((nbr_des > 2))                                 /* Risque toléré en ce qui concerne le rapport entre nbr_des et nbr de valeurs pas encore prises     */
    {
        score = compute_score(valeurs_prises) ;
        if (get_joueur_has_val(data, score) != -2 || is_table_has_less(data, score) != -1)   /* Comparaison aux derniers dominos des joueurs                */
            stop = 1;
    }
	if (!nbr_des)
		stop = 1;
	return (stop);
}

int score_des_bot (t_data *data, int player)
{
    int possibilites = 6 ;
    int nbr_des = 8 ;
    int i = -1 ;
    int n ;                                              /* La valeur de dé choisie par le bot                                                              */
    int valeurs_prises[6] = {0, 0, 0, 0, 0, 0} ;         /* Tableau où indice = valeur dé ; valeur case = nbr dés déjà pris portant cette valeur            */
    int valeurs_possibles[6] = {0, 0, 0, 0, 0, 0} ;      /* Tableau où indice = valeur dé ; valeur case = nbr dés portant cette valeur présents sur table   */

    do 
    {
		clearScreen ();
		print_table (data, 0, player);
        get_new_dice(data, nbr_des) ;
		print_des (data, nbr_des, valeurs_prises);
		i = -1;
        while (++i < nbr_des)
        {
            if (valeurs_prises[ data->des[i] ] == 0) 
                valeurs_possibles[ data->des[i] ] += 1;
        }
        if (valeurs_possibles[0] != 0 && valeurs_prises[0] == 0)
                n = 0 ;
        else 
        {
            i = 1;
            n = valeurs_possibles[i] ;
            while (++i < 6)
                if (( (valeurs_possibles[i] * i) > n) && (valeurs_possibles[i] <= max_des_prenables(nbr_des, n, valeurs_possibles[0])) )
                    n = i ;
			if (!n)
				break ;
        }
        valeurs_prises[n] = valeurs_possibles[n] ;
        nbr_des -= valeurs_prises[n] ;
        possibilites -= 1 ;
        i = -1 ;
        while (++i < 6)
            valeurs_possibles[i] = 0;
		printf("\nWhich dice do you want to keep ? \n");
		printf("Write the value : ");
		if (n != 0)
			printf("%d\n", n);
		else
			printf("V\n");
		sleep (2);
    } while (!stop_bot (data, nbr_des, n, valeurs_prises));
	clearScreen ();
	print_table (data, 0, player);
	print_des (data, nbr_des, valeurs_prises);
    if (valeurs_prises[0] == 0)
		return (0);
	return (compute_score(valeurs_prises)) ;
}

int	is_end_game (t_data *data)
{
	int	i;

	i = -1;
	while (++i < 16)
		if (data->pikomino[i] != -1 && data->pikomino[i] != 0)
			return (0);
	return (1);
}

void	tour_ratee (t_data *data, int player, int score)
{
	int	inter;

	if ((inter = pop(data->players[player].pikomino)) != -1)
	{
		if (get_max_pikomino (data, -1) > inter)
			replace_val (data->pikomino, get_max_pikomino(data, -1), 0);
		push_elem (data->pikomino, inter);
	}
	write (1, "You fail your turn.\n", 20);
	clearScreen();
	print_table(data, &score, player);
	if (inter == -1)
		write (1, "You loose your pikomino.", 31);
}

void	update_game (t_data *data, int player, int score)
{
	//TOUR RATE
	clearScreen ();
	print_table(data, &score, player);
	if (!score)
		tour_ratee (data, player, score);
	else //TOUR REUSSI
	{
		if (get_joueur_has_val(data, score) == -2 && is_table_has_less(data, score) == -1)
			tour_ratee (data, player, score);
		else //SI PEUX PRENDRE UN PIKOMINO 
		{
			if (get_joueur_has_val(data, score) >= 0)
			{
				push_elem (data->players[player].pikomino, score);
				pop_elem (data->players[get_joueur_has_val(data, score)].pikomino, score);
				clearScreen ();
				print_table(data, &score, player);
				write (1, "You steal a pikomino to your opponent\n", 38);
			}
			else if (is_table_has_less(data, score))
			{
				push_elem (data->players[player].pikomino, is_table_has_less(data, score));
				pop_elem (data->pikomino, is_table_has_less(data, score));
				clearScreen ();
				print_table(data, &score, player);
				write (1, "You get a pikomino\n", 19);
			}
		}
	}
}

int	get_pts_player(t_data *data, int player)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (++i < 16)
		if (data->players[player].pikomino[i] != -1)
			res += get_pts(data->players[player].pikomino[i]); 
	return (res);
}

int	get_winner (t_data *data)
{
	int	i;
	int	idx_win;
	int	pts_win;

	i = -1;
	idx_win = 0;
	while (++i < data->nb_players)
	{
		if (get_pts_player(data, i) > get_pts_player(data, idx_win)                                                              /* Le joueur a plus de pts que le gagnant actuel */
		|| (get_pts_player(data, i) == get_pts_player(data, idx_win) && get_max_pikomino(data, i) > get_max_pikomino(data, i)) ) /* Meme nombre de pts, mais pikomino de val sup  */
			idx_win = i;
	}
	return (idx_win);
}

void	save(t_data *data, char *name, int player)
{
	int		i;
	int		j;
	FILE	*file;

	i = -1;
	name = ft_strjoin(name, ".save");
	file = fopen(name, "w");
	free (name);
	if (!file)
		return ;
	fprintf (file, "%d ", player); 
	fprintf (file, "%d ", data->nb_players);
	while (++i < data->nb_players)
	{
		fprintf (file, "%s ", data->players[i].name);
		j = -1;
		while (++j < 16)
			fprintf (file, "%d ", data->players[i].pikomino[j]);
		fprintf (file, "%d ", data->players[i].is_bot);
	}
	j = -1;
	while (++j < 16)
		fprintf (file, "%d ", data->pikomino[j]);
	fclose (file);
}

int	load_game(t_data *data, char *name)
{
	int		i;
	int		j;
	int		player;
	FILE	*file;

	data->name_game = name;
	name = ft_strjoin(name, ".save");
	file = fopen(name, "r");
	if (!file)
	{
		free (name);
		return (-1);
	}
	fscanf (file, "%d", &player);
	fscanf (file, "%d", &data->nb_players);
	data->players = malloc (sizeof(t_joueur) * data->nb_players);
	i = -1;
	while (++i < data->nb_players)
	{
		data->players[i].name = malloc (sizeof(char) * 11);
		fscanf(file, "%s", data->players[i].name);
		data->players[i].name[10] = 0;
		j = -1;
		while (++j < 16)
			fscanf (file, "%d ", data->players[i].pikomino + j);
		fscanf (file, "%d ", &data->players[i].is_bot);
	}
	j = -1;
	while (++j < 16)
		fscanf (file, "%d ", data->pikomino + j);
	fclose (file);
	return (player);
}

void	lance_jeux (t_data *data, int *player_save)
{
	int	i;
	int	j;
	int	score_inter;
	int	winner;

	if (player_save)
	{
		i = *player_save - 1;
		if (i < 0)
			i = data->nb_players - 1;
	}
	else
		i = -1;
	while (!is_end_game(data))
	{
		while (++i < data->nb_players && !is_end_game(data))
		{
			if (!data->players[i].is_bot)
				score_inter = score_des (data, i);
			else
				score_inter = score_des_bot(data, i);
			update_game (data, i, score_inter);
			printf ("game round finished, click on ENTER\n");
			if (!data->players[i].is_bot)
			{
				while (getchar() != '\n');
				fill_out_stdin();
			}
			else
				sleep (1);
			if (i + 1 < data->nb_players)
				save (data, data->name_game, i + 1);
			else
				save (data, data->name_game, 0);
		}
		i = -1;
	}
	winner = get_winner(data);
	clearScreen ();
	print_score(data, winner);
	printf ("The winner is : 🏆%s🏆 | Congratulations !!!!\n", data->players[winner].name);
}

int		menu(t_data *data)
{
	char	*res;
	int		player;

	res = malloc (sizeof(char) * 11);
	while (get_yes_no("Do you want to resume an existent play ?"))
	{
		printf("Write the playing name : ");
		scanf ("%s", res);
		fill_out_stdin();
		res[10] = 0;
		if ((player = load_game(data, res)) != -1)
			return player;
		printf("This name doesn't exist.\n");
	}
	init_data(data);
	return (-1);
}
 
void	free_data(t_data *data)
{
	int	i;

	free(data->name_game);
	while (++i < data->nb_players)
		free(data->players[i].name);
	free(data->players);
}
