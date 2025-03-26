/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:43 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/08 10:53:27 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	double_free(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int main(int argc, char** arg/*, char **env*/)
{
	if (argc !=2 )
		return (1);

	if (chdir(arg[1]) == -1){
		printf("cd: %s\n", strerror(errno));
	}
	else{
		printf("We are in %s\n", getenv("PWD"));
	}
	return (0);
}
