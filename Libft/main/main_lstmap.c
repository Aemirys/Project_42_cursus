/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:36:00 by estosche          #+#    #+#             */
/*   Updated: 2023/10/31 13:35:34 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h" 

void *map_function(void *content)
{
	char	*str = (char *)content;
	char	*result = ft_strdup(str);
	for (int i = 0; str[i] != '\0'; i++)
		result[i] = ft_toupper((unsigned char)str[i]);
	return result;
}

void delete_function(void *content)
{
    free(content);
}

int main()
{
    t_list *lst = ft_lstnew(ft_strdup("abc"));
    lst->next = ft_lstnew(ft_strdup("def"));
    lst->next->next = ft_lstnew(ft_strdup("ghi"));

    t_list *new_list = ft_lstmap(lst, map_function, delete_function);

    if (new_list)
    {
        t_list *current = new_list;
        while (current)
        {
            printf("%s\n", (char *)current->content);
            current = current->next;
        }

        // Ne pas oublier de libérer la nouvelle liste
        ft_lstclear(&new_list, delete_function);
    }
    else
    {
        printf("Erreur lors de la création de la nouvelle liste.\n");
    }

    // Libérer la liste d'origine
    ft_lstclear(&lst, free);

    return 0;
}
