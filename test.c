/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:15:07 by abittel           #+#    #+#             */
/*   Updated: 2022/01/10 14:51:39 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	clearScreen(void)
{
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
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
		printf ("\n%s (o/n) : ", str);
		scanf ("%c", &res);
		printf ("\n");
		if (res != 'o' && res != 'n')
		{
			printf ("Mauvaise entre, veuillez entrer oui ou non.\n");
			scanf ("%c", &res);
			res = 0;
		}
	}
	return (res == 'o');
}

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

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

char	*ft_strdup_int(char *str)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc (sizeof(char) * (ft_strlen(str) + 1));
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
	pik_res[2][0] = (int)('├');
	pik_res[2][1] = (int)('─');
	pik_res[2][2] = (int)('─');
	pik_res[2][3] = (int)('┤');
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
	pik_res[1][1] = val / 10 + 48;
	pik_res[1][2] = (val % 10) + 48;
	pik_res[3][2] = (pts % 10) + 48;
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

void	print_table (t_data *data)
{
	int		i;
	int		**screen;

	i = -1;
	screen = get_blank_screen(150, 30);
	//ptint table
	print_in_screen (screen, get_blank_screen(100, 15), 25, 8);
	//print players
	print_str_in_screen (screen, data->players[0].name, 25, 2);
	print_str_in_screen (screen, data->players[1].name, 55, 2);
	print_str_in_screen (screen, data->players[2].name, 85, 2);
	print_str_in_screen (screen, data->players[3].name, 115, 2);
	//print pikomino
	while (++i < 16)
		if (data->pikomino[i] != -1)
			print_in_screen(screen, get_pikomino(data->pikomino[i], get_pts(data->pikomino[i])), 22 + (i + 1) * 6, 12);
	//print screen final
	print_screen (screen);
	print_des (data);
	write (1, "\n", 1);
}

void	init_data(t_data *data)
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
		data->players[i].pikomino = malloc(sizeof(int) * 16);
		data->players[i].pikomino[0] = 0; 
		data->players[i].is_bot = 0; 
	}
	i = -1;
	while (++i < 16)
		data->pikomino[i] = i + 21;
	i = -1;
	while (++i < 8)
		data->des[i] = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	clearScreen();
	init_data(&data);
	print_table(&data);
	return (0);
}
