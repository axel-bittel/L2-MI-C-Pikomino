#include <stdlib.h>
#include <stdio.h>
#include "test.h"
/*
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



int score_des (t_data *data, int player)
{
	int i = -1 ;
	int n = 0;								 */ /* Valeur dé que joueur veut garder                                                        */
//	int possibilites = 6;						/* Nombre valeurs déja prises pour les dés                                                 */
//	int nbr_des = 8;							/* Nombre dés à lancer                                                                     */
//	int nbr_lancers = 0;						/* Nombre de lancers effectués et ayant aboutis                                            */
//	int valeurs[6] = {-1, -1, -1, -1, -1, -1};	/* Tableau où indice = valeur du dé gardé ; valeur case = nbr dés gardés pour cette valeur */
//	char str[] = "Voulez-vous relancer les dés ?" ;

/*
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
					return (0);
				printf("\nQuels dés voulez-vous garder ? \n") ;
				printf("Entrez la valeur : ") ;
				scanf("%c", (char *)&n ) ;
				n = (n == 'V') ? 0 : n - 48;
				fill_out_stdin() ;
				if (!is_value_in_dice(data->des, n, nbr_des))
					err = printf("Vous ne disposez pas de cette valeur, veuillez en choisir une delivrée par les dés\n") ;
				else if (valeurs[n] != -1)
					err = printf("Vous avez deja pris cette valeur, veuillez en choisir une autre\n") ;
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
		} 
	} while (possibilites && get_yes_no(str)); 
	if (valeurs[0] == -1)
		return (0);
	return (compute_score(valeurs));
}
*/


/*
Stratégie choix des dés du BOT  :   - lorsqu'on a lancé les dés, on prend un V (donc valeur 0) dès que possible (pour éviter le tour nul) 
                                    - si on n'a pas de V dans le lancer obtenu, ou qu'on en a déjà au moins récupéré un : 
                                    on cherche à faire le maximum de points.
                                    - condition d'arrêt : tour raté ou on choisit de s'arrêter quand on a score supérieur au minimum de ce qui est sur la table
Pour ne pas perdre trop de dés d'un coup, et risquer de faire un score trop faible par la suite, on n'autorise qu'un nbr limité de dés à prendre par lancers 
sauf si la valeur qu'on veut prendre est supérieure stricte à 3.
En ce qui concerne l'arrêt par choix, il faut prender en compte les dominos sur la table : on continue au moins tant qu'on n'est pas supérieur à la valeur 
minimale. En revanche on ne s'arrête pas dès qu'on l'a atteinte ou dépasée, en fonction du nombre de dés à lancer et du nombre de valeurs différentes déjà 
gardées, on continue (ratio à mettre en place en dur)
*/

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
        if (V != 0)                                      /* V représentra le nombre de face V gardée  (ie : valeurs_prises[0] )                               */
            nbr_prenables = nbr_des ;
        else 
            nbr_prenables = nbr_des - 1;
    }
	return (nbr_prenables);
}


int stop_bot (t_data *data, int nbr_des, int n, int *valeurs_prises) 
{
    int stop = 0;                                           /* Vaut 0 si on s'arrête, 1 sinon                                                                    */
    int i = -1 ;
    int score  = 0;

    if ((nbr_des > 2))                      /* Risque toléré en ce qui concerne le rapport entre nbr_des et nbr de valeurs pas encore prises     */
    {
        score = compute_score(valeurs_prises) ;
        if (get_joueur_has_val(data, score) != -2 || is_table_has_less(data, score) != -1)   /* Comparaison aux derniers dominos des joueurs           */
            stop = 1;
    }
	if (!nbr_des)
		stop = 1;
	return (stop);
}

#include <unistd.h>
#include <time.h>
int score_des_bot (t_data *data)
{
    int possibilites = 6 ;
    int nbr_des = 8 ;
    int i = -1 ;
    int n ;                                              /* La valeur de dé choisie par le bot                                                                */
    int valeurs_prises[6] = {0, 0, 0, 0, 0, 0} ;         /* Tableau où indice = valeur dé ; valeur case = nbr dés déjà pris portant cette valeur              */
    int valeurs_possibles[6] = {0, 0, 0, 0, 0, 0} ;      /* Tableau où indice = valeur dé ; valeur case = nbr dés portant cette valeur présents sur table     */

    do 
    {
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
		printf("\nQuels dés voulez-vous garder ? \n") ;
		printf("Entrez la valeur : ") ;
		sleep (1);
		if (n != 0)
			printf("%d\n", n);
		else
			printf("V\n", n);
		sleep (1);
		printf ("*---------------*");
    } while (!stop_bot (data, nbr_des, n, valeurs_prises));
	printf ("Score : %d\n", compute_score(valeurs_prises));
    if (valeurs_prises[0] == 0 || !n)
		return (0);
	return (compute_score(valeurs_prises)) ;
}

int	main()
{
	srand (time ( NULL ) );
	t_data	dt;
	score_des_bot (&dt);
}
