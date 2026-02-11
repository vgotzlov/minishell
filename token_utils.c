/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:38:14 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/02/11 18:39:51 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(type, lexeme);

void	token_add_back(head, new);

void	free_tokens(head);