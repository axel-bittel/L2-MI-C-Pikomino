/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:15:07 by abittel           #+#    #+#             */
/*   Updated: 2022/01/11 16:43:55 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "test.h"

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
	while (fgetc( stdin ) != '\n');
}

void	print_pikomino(int val, int pts)
{
	printf ("\n");
	printf ("┌──┐"); 
	printf ("\n");
	printf ("│%d│", val); 
	printf ("\n");
	printf ("├──┤"); 
	printf ("\n");
	printf ("│ %d│", pts);
	printf ("\n");
	printf ("└──┘"); 
}

int	get_yes_no(const char *str)
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
			printf ("Mauvaise entre, veuillez entrer o ou n.\n");
			res = 0;
		}
	}
	return (res == 'o');
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

char	*ft_strdup(const char *str)
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

int	**get_blank_screen (int x, int y)
{
	int		i;
	int		j;
	int	**res;

	i = -1;
	res = malloc (sizeof(int *) * (y + 1)); 
	res[y] = NULL;
	while (++i < y)
	{
		j = -1;
		res[i] = malloc (sizeof(int) * (x + 1));
		res[i][x] = 0;
		while (++j < x)
		{
			res[i][j] = ' ';
			if (!i && !j)
				res[i][j] = '┌';
			else if (!i && j == (x - 1))
				res[i][j] = '┐';
			else if (i == (y - 1) && j == (x - 1))
				res[i][j] = '┘'; 
			else if (i == (y - 1) && !j)
				res[i][j] = '└'; 
			else if (!i || i == (y - 1))
				res[i][j] = '─';
			else if (!j || j == (x - 1))
				res[i][j] = '│';
		}
	}
	return (res);
}

int	**get_pikomino(int val, int pts)
{
	int	**pik_res;

	pik_res = malloc (sizeof(int *) * 6);
	pik_res[0] = malloc (sizeof(int) * 5);
	pik_res[0][0] = (int)('┌');
	pik_res[0][1] = (int)('─');
	pik_res[0][2] = (int)('─');
	pik_res[0][3] = (int)('┐');
	pik_res[0][4] = 0;
	pik_res[1] = malloc (sizeof(int) * 5);
	pik_res[1][0] = (int)('│');
	pik_res[1][1] = (int)(' ');
	pik_res[1][2] = (int)(' ');
	pik_res[1][3] = (int)('│');
	pik_res[1][4] = 0;
	pik_res[2] = malloc (sizeof(int) * 5);
	pik_res[2][0] = val ? (int)('├') : (int)('│');
	pik_res[2][1] = val ? (int)('─') : (int)(' ');
	pik_res[2][2] = val ? (int)('─') : (int)(' ');
	pik_res[2][3] = val ? (int)('┤') : (int)('│');
	pik_res[2][4] = 0;
	pik_res[3] = malloc (sizeof(int) * 5);
	pik_res[3][0] = (int)('│');
	pik_res[3][1] = (int)(' ');
	pik_res[3][2] = (int)(' ');
	pik_res[3][3] = (int)('│');
	pik_res[3][4] = 0;
	pik_res[4] = malloc (sizeof(int) * 5);
	pik_res[4][0] = (int)('└');
	pik_res[4][1] = (int)('─');
	pik_res[4][2] = (int)('─');
	pik_res[4][3] = (int)('┘');
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

void	print_in_screen (int**screen, int **obj, int x, int y)
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

void	print_str_in_screen (int**screen, char *obj, int x, int y)
{
	int		i;

	i = -1;
	while (obj[++i])
		screen[y][x + i] = obj[i];
}

void	print_screen (int	**screen)
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

void	print_des (t_data *data)
{
	int		i;
	char	inter;

	i = -1;
	while (++i < 8)
	{
		if (!data->des[i])
			continue ;
		inter = data->des[i] + 48;
		write (1, "[", 1);
		if (data->des[i] == 6)
			write (1, "V", 1);
		else
			write (1, &inter, 1);
		write (1, "] ", 1);
	}
}

void	free_screen (int **screen)
{
	int	i;

	i = -1;
	while (screen[++i])
		free (screen[i]);
	free (screen);
}

void	print_table (t_data *data)
{
	int		i;
	int		**screen;

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
			print_in_screen(screen, get_pikomino(get_lst_pikomino(data, i), get_pts(get_lst_pikomino(data, i))), 27 + i * 30, 3);
		}
	}
	i = 4;
	while (++i < 7)
	{
		if (i < data->nb_players)
		{
			print_str_in_screen (screen, data->players[i].name, 25 + (i - 4) * 30, 23);
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
	print_des (data);
	free_screen (screen);
	write (1, "\n", 1);
}

void	print_playerboard (t_data *data)
{
	int	i;
	int		**screen;

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
//***************************************************************************yy
//#DATA_MANAGEMENT#
//***************************************************************************yy
/*void	init_data(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->nb_players = 7;
	data->players = malloc (sizeof (t_joueur) * data->nb_players);
	while (++i < data->nb_players)
	{
		j = -1;
		data->players[i].name = malloc (sizeof(char ) * 11);
		while (++j < 10)
			data->players[i].name[j] = i + 1 + 48;
		data->players[i].name[10] = 0; 
		data->players[i].pikomino[0] = 0; 
		data->players[i].is_bot = 1; 
	}
	i = -1;
	while (++i < 16)
		data->pikomino[i] = i + 21;
	i = -1;
	while (++i < 8)
		data->des[i] = 0;
}*/

void    init_joueur (t_joueur *joueur, t_data *data, int player) 
{
    char str1[] = "Etes-vous un humain ?";
    char *str2 = malloc (sizeof(char) * 13);
    const char *str[] = {"S.Veil" ,"N.Mandela", "Ghandhi", "M.L.King", "M.Debre" ,"R.Badinter", "G.Cantor"} ;
    int i = 0 ;
    int j = -1 ;
    if (get_yes_no(str1) == 1) 
    {
        do 
        {
			printf ("Entrez votre nom : ");
            scanf ("%s", str2); 
			fill_out_stdin();
			str2[12] = 0;
            if (ft_strlen(str2) <= 10)
                joueur->name = ft_strdup(str2) ;
            else 
                printf ("Veuillez entrez un nom d'au maximum 10 lettres \n") ;
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


void    init_data (t_data *data) 
{
    char str2[] = "A combien de joueur voulez-vous jouer ? \nDonnez un chiffre entre 2 et 7 inclus" ;
    int n ;
    int i = -1 ;
    int j = -1 ;
    int k = -1 ;

	print_playerboard (data);
    do 
    {
        printf("%s : ", str2);
        scanf("%d", &n);
		fill_out_stdin();
        if ( (n < 2) || (n > 7) )
            printf("Vous devez être au moins deux et au maximum 7 pour démarrer une partie, avec ou sans bot. \n") ;
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

int	get_fst_pikomino (t_data *data, int player)
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

int	get_lst_pikomino (t_data *data, int player)
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
			return (i);
	return (i);
}

int	get_max_pikomino (t_data *data, int player)
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

int	pop (int *tab)
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

int	pop_elem (int *tab, int val)
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
			return (val);
		}
	}
	tab[15] = -1; 
	return (-1);
}

int	push_elem (int *tab, int val)
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

int	replace_val (int *tab, int val, int replace)
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

int	is_val_in (int *tab, int val)
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

int	get_joueur_has_val (t_data *data, int val)
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

int	is_table_has_less (t_data *data, int score)
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

int	get_pts(int val)
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

int	is_end_game (t_data *data)
{
	if (get_fst_pikomino(data, -1) == -1)
		return (1);
	return (0);
}

void	tour_ratee (t_data *data, int player)
{
	int	inter;

	write (1, "You fail your turn.\n", 20);
	if ((inter = pop(data->players[player].pikomino)) != -1)
	{
		if (get_max_pikomino (data, -1) > inter)
			replace_val (data->pikomino, get_max_pikomino(data, -1), 0);
		push_elem (data->pikomino, inter);
		write (1, "You loose your pikomino.", 31);
	}
}

void	update_game (t_data *data, int player, int score)
{
	//TOUR RATE
	if (!score)
		tour_ratee (data, player);
	else //TOUR REUSSI
	{
		if (get_joueur_has_val(data, score) == -2 && is_table_has_less(data, score) == -1)
			tour_ratee (data, player);
		else //SI PEUX PRENDRE UN PIKOMINO 
		{
			if (get_joueur_has_val(data, score) && get_yes_no("Do you want steal pikomino ?"))
			{
				push_elem (data->players[player].pikomino, score);
				pop_elem (data->players[get_joueur_has_val(data, score)].pikomino, score);
			}
			else if (is_table_has_less(data, score))
			{
				push_elem (data->players[player].pikomino, score);
				pop_elem (data->pikomino, score);
			}
		}
	}
}

void	lance_jeux (t_data *data)
{
	int	i;
	int	score_inter;

	while (!is_end_game(data))
	{
		i = -1;
		while (++i < data->nb_players)
		{
			score_inter = 33;
			update_game (data, i, score_inter);
			clearScreen();
			print_table(data);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	clearScreen();
	init_data(&data);
	clearScreen();
	print_table(&data);
	return (0);
}
