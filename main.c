/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:12:38 by abittel           #+#    #+#             */
/*   Updated: 2022/01/17 12:13:46 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "jeux.h"
#include <stdlib.h>
#include <time.h>

int	main(int argc, char **argv)
{
	t_data	data;
	int		player_save;
	srand(time(NULL));
	clearScreen();
	player_save = menu(&data);
	clearScreen();
	if (player_save == -1)
		lance_jeux (&data, 0);
	else 
		lance_jeux (&data, &player_save);
	free_data (&data);
	return (0);
}
