#include <stdlib.h>
#include <stdio.h>
#include <test.h> 

void    init_joueur (t_joueur *joueur) 
{
    char str1[] = "Etes-vous un humain ?";
    char str2[] ;
    const char *str[] = {"S.Veil" ; "N.Mandela"; "Ghandhi" ; "M.L.King" ; "M.Debre" ; "R.Badinter"} ;
    int i = 0 ;
    int j = -1 ;
    if (get_yes_no(str1) == 1) 
    {
        do 
        {
            scanf ("entrez votre nom : %s \n", str2) ; 
            if (ft_strlen(str2) <= 10)
                joueur->name = str2 ;
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
        joueur->name = ft_strdup(str[i]) ; 
        joueur->is_bot = 1 ;
        i += 1 ;
        while (++j < 16) 
            joueur->pikomino[j] = -1 ;
    }
}


void    init_data (t_data *data) 
{
    char str2[] = "A combien de joueur voulez-vous jouer ? \n Donnez un chiffre entre 2 et 7 inclus \n" ;
    int n ;
    int i = -1 ;
    int j = -1 ;
    int k = -1 ;

    do 
    {
        printf("%s \n", str2);
        scanf("%d \n", &n);
        if ( (n < 2) || (n > 7) )
            printf("Vous devez être au moins deux et au maximum 7 pour démarrer une partie, avec ou sans bot. \n") ;
         
        else 
        {
            data->nb_players = n ;
            data->players = malloc (sizeof (t_joueur) * data->nb_players) ;
            while (++i < data->nb_players)
            { 
                data->players[i].pikomino = malloc(sizeof(int) * 16) ;
                init_joueur (data->players[i]) ;
            }  
            while (++j < 8)
                data->des[j] = 0 ;
            while (++k < 16)
                data->pikomino = -1 ;
        }
    } while ((n < 2) || (n > 7)) ;
}
