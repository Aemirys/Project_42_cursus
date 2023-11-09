/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:42:31 by estosche          #+#    #+#             */
/*   Updated: 2023/10/31 10:24:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>
#include <stdlib.h>

void custom_free(void *content)
{
    free(content); // Supprime la mémoire allouée dynamiquement pour le contenu
}

int main(void)
{
    // Créez un élément de liste
    t_list *element = (t_list *)malloc(sizeof(t_list));
    if (element == NULL)
    {
    	printf("allocation failled\n");
        return 1;
    }
    element->content = ft_strdup("Element data"); // Allouez dynamiquement la mémoire pour le contenu
    element->next = NULL;

    // Affichez le contenu de l'élément avant la suppression
    printf("Contenu avant la suppression : %s\n", (char *)element->content);

    // Appelez ft_lstdelone pour supprimer l'élément en utilisant la fonction de libération personnalisée
    ft_lstdelone(element, custom_free);

    // Vous ne devez pas accéder à 'element' après la suppression
    // Par conséquent, n'essayez pas d'accéder à 'element' ici

    printf("L'élément a été supprimé\n");

    return 0;
}
