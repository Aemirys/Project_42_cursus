/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:47:22 by estosche          #+#    #+#             */
/*   Updated: 2023/10/31 11:03:06 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void custom_free(void *data) {
  free(data);
}

int main() {
  t_list *list = (t_list *)malloc(sizeof(t_list));
  list->content = ft_strdup("Hello, world!");
  list->next = NULL;

  t_list *list2 = (t_list *)malloc(sizeof(t_list));
  list2->content = ft_strdup("Goodbye, world!");
  list2->next = NULL;

  list->next = list2;

  printf("Liste avant la suppression :\n");
  printf("%s\n", (char *)list->content);
  printf("%s\n", (char *)list2->content);

  ft_lstclear(&list, custom_free);

  if (list == NULL) {
    printf("Liste après la suppression : NULL\n");
  } else {
    printf("Liste après la suppression : Non NULL\n");
  }

  return 0;
}
