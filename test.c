/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:15:07 by abittel           #+#    #+#             */
/*   Updated: 2021/12/14 10:37:08 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	clearScreen(void)
{
	const char *CLEAR_SCREEN = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN, 12);
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

int	main(int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < 20)
		printf ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	clearScreen();
	/*printf("Enter nb :");
	scanf("%d", &i);
	clearScreen();
	printf ("nb is %d\n", i);*/
	print_pikomino (35, 1);
	printf ("res : %d\n", get_yes_no("Axel est-il un bg ?"));
	return (0);
}
