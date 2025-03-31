/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:49:57 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/31 06:00:20 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_general*	init(char **env_arg)
{
	t_general	*general;
	
	general = (t_general *) ft_calloc(1, sizeof(t_general));
	general->env = get_env(env_arg);
	return (general);
}