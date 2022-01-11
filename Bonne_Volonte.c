#include <stdlib.h>
#include <stdio.h>
#include <test.h> 

void    init_joueur (t_joueur *joueur) 
{
    char str1[] = "Voulez-vous ajouter un joueur ?" ;
    char str2[] = "Etes-vous un humain ?";

    if (get_yes_no(str1) == 1)
    {
        scanf ("entrez votre nom : %s \n", joueur->name) ; 
        joueur->pikomino = 0 ;
        if (get_yes_no(str2) == 1) 
            joueur->is_bot = 0;
        else 
            joueur->is_bot = 1;
    }
}


void    init_data (t_data *data) 
{

}
