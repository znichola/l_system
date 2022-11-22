/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:38:00 by marvin            #+#    #+#             */
/*   Updated: 2022/11/22 13:38:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsystem.h"


/**
 * @brief string manipulation program
 * 
 * @param argv[1] variables		AB
 * @param argv[2] constants		[]
 * @param argv[3] axiom/start	A
 * @param argv[4] rules 		A AB B A 
 */

int	rule_applicator(char **src, char **ret, t_genus *g)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (g->rules[i])
	{
		printf("checking src<%c> rule<%c> const<%c>\n", **src, g->rules[i]->initial[0], g->consts[j]);
		if (g->rules[i]->initial[0] == **src)
		{
			printf("applied rule:%d ", i);
			dump_rule(g->rules[i]); printf("\n");
			int t = ft_strlcpy(*ret, g->rules[i]->result, 10);
			printf("new ret:<%s>\n", *ret);
			*ret += t;
			break ;
		}
		else if (g->consts[j] == **src)
		{
			printf("copying const:%c\n", g->consts[j]);
			**ret = g->consts[j];
			*ret++;
			break ;
		}
		else
			printf("NO RULES! BIG ERROR\n");
		if (i < g->nr)
			i++;
		if (j < g->nc)
			j++;
	}
	*src += 1;
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_genus		g;
	t_strplus	alice;
	t_strplus	bob;
	t_strplus	tmp;

	init_strplus(&alice);
	init_strplus(&bob);
	// tmp = (char *)calloc(10000, sizeof(char));
	if (init_genus(&g, argv + 1))
		return (-1);
	printf("init genus finished\n");
	dump_genus(&g);
	alice.root[0] = g.axiom[0];

	for (int i = 1; i < 4; i++)
	{
		printf("\n -- NEW ITTERATION --\na:<%s>\nb:<%s>\n", alice.root, bob.root);
		while (*alice.seek)
			rule_applicator(&alice.seek, &bob.seek, &g);
		printf("n = %d : %s\n", i, bob.root);
		printf("---alice:<%s>\n---bob:<%s>\n", alice.root, bob.root);
		tmp = alice;
		alice = bob;
		bob = tmp;  
		reset_strplus(&bob, 1);
		reset_strplus(&alice, 0);
	}
	return (0);
}