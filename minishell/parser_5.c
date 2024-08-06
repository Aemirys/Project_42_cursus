/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:46:03 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 12:09:42 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes_parser(char *val, char **new_val, t_data *d)
{
	if (val[d->i] == d->q_c && (val[d->i + 1] == '\0' || val[d->i + 1] == '\''))
	{
		d->i++;
		d->quote_open = false;
		(*new_val)[d->j] = val[d->i];
		if (val[d->i + 1] == ' ')
		{
			d->i++;
			(*new_val)[d->j] = val[d->i];
			d->j++;
		}
	}
	else if (val[d->i] == d->q_c && (val[d->i + 1] == ' '))
	{
		d->quote_open = false;
	}
}

void	copy_characters(char *val, char **new_val, t_data *d)
{
	if (val[d->i] != '\0' && val[d->i] != d->q_c)
	{
		(*new_val)[d->j] = val[d->i];
		d->j++;
		if (val[d->i + 1] == ' ')
		{
			d->i++;
			(*new_val)[d->j] = val[d->i];
			d->j++;
		}
	}
	else if (val[d->i] != d->q_c && val[d->i] != '\0')
	{
		(*new_val)[d->j] = val[d->i];
		d->j++;
	}
}

void	default_case(char *val, char **new_val, t_data *d)
{
	size_t	val_len;

	val_len = ft_strlen(val);
	if ((size_t)d->i >= val_len)
		return ;
	if ((size_t)d->i + 1 < val_len)
	{
		handle_quotes_parser(val, new_val, d);
		copy_characters(val, new_val, d);
	}
	else
	{
		if (val[d->i] != d->q_c && val[d->i] != '\0')
		{
			(*new_val)[d->j] = val[d->i];
			d->j++;
		}
	}
	if (val[d->i] == '\0')
		return ;
	d->i++;
}
