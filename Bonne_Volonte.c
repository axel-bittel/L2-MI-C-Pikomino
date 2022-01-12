#include <stdlib.h>
#include <stdio.h>
#include <test.h> 

void    init_joueur (t_joueur *joueur) 
{
    char str1[] = "Etes-vous un humain ?";
    char *str2 ;
    const char *str[] = {"S.Veil" , "N.Mandela", "Ghandhi" , "M.L.King" , "M.Debré" , "R.Badinter"} ;
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
                data->pikomino[k] = -1 ;
        }
    } while ((n < 2) || (n > 7)) ;
}


int score_des (t_data *data, int player )
{
    int score ;                          /* Score à retourner                                                                       */
    int possibilites = 5 ;               /* Nombre valeurs déja prises pour les dés                                                 */
    int nbr_des = 8 ;                    /* Nombre dés à lancer                                                                     */
    int nbr_lancers = 0 ;                /* Nombre de lancers effectués et ayant aboutis                                            */
    int n ;                              /* Valeur dé que joueur veut garder                                                        */
    int cpt = 0 ;                        /* Compteur                                                                                */
    int i = -1 ;
    int valeurs[6] = {-1};               /* Tableau où indice = valeur du dé gardé ; valeur case = nbr dés gardés pour cette valeur */
    char str[] = "Voulez-vous relancer les dés ?" ;

    do
    {
        if (nbr_lancers == 0)            /* cas du premier lancer                                                                   */
        {
            while (++i < 9)
                data->des[i] = (rand(void) % 6) ;
            printf("Quels dés voulez-vous garder ? \n") ;
            scanf("Entrez la valeur : %d", &n ) ;
            fill_out_stdin(void) ;
            i = -1 ;
            while (++i < 9) 
                {
                    if (data->des[i] = n )
                        cpt += 1;
                }
            if (cpt == 0)
                printf("Vous ne disposez pas de cette valeur, veuillez en choisir une delivrée par les dés") ;
            else
                nbr_des -= cpt ;
                nbr_lancers += 1 ;
                valeurs[n] = cpt ; 
        } 
        else 
        {
            if (get_yes_no(str) == 1)    /* Si le joueur n'en est pas à son premier lancer, et qu'il veut lancer les dés             */
            {
                i = -1 ;
                cpt = 0 ;
                while (++i < (nbr_des+1))
                    data->des[i] = (rand(void) % 6) ;
                i = -1 ;
                while (++i < 6)
                {
                    if (valeurs[i] != -1)
                        possibilites -= 1 ; 
                   
                }
                if (possibilites != 0) 
                {
                    printf("Quels dés voulez-vous garder ? \n") ;
                    scanf("Entrez la valeur : %d", &n ) ;
                    fill_out_stdin(void) ;
                    i = -1 ;
                    while (++i < 9) 
                    {
                        if (valeurs[n] == -1)
                        {
                            if (data->des[i] = n )
                                cpt += 1 ;
                        }
                        else 
                            break ;
                    }
                    if (cpt == 0) 
                        printf("Vous ne disposez pas de cette valeur, veuillez en choisir une delivrée par les dés que vous n'avez pas déjà gardée") ;
                    else
                    {
                        nbr_des -= cpt ;
                        nbr_lancers += 1 ;
                        valeurs[n] = cpt ;
                    }
                }
                else 
                    break ;
            } 
            else 
                break ; 
        }
    } while ( (nbr_lancers == 0) || (possibilites != 0) || (get_yes_no(str)) ) 

    i = -1 ;
    if ((valeurs[0] = -1) ||(possibilites == 0)) 
        score = 0 ;
    else 
    {
        i = 0 ;
        score += valeurs[i] * 5          /* La face V du dé est représentée par la valeur 0, or elle vaut (en score) 5 points        */
        while (++i < 6)
        {
            if (valeurs[i] != -1)
                score += i * valeurs[i] ;
        }
    }
    return (score) ;
}