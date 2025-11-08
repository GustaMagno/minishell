#ifndef MAP_H
# define MAP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef	struct s_map t_map;
typedef	struct s_map_private t_map_private;
typedef struct s_node t_node;

struct s_node
{
	char	*key;
	void	*value;
	t_node	*next;
};

struct s_map
{
	void	(*put)(t_map *map, char *key, void	*value);
	void	(*remove)(t_map *map, char *key);
	void	*(*get)(t_map *map, char *key);
	void	(*destroy)(t_map *map);
	char	**(*to_str)(t_map *map);
	size_t	size;
};

struct s_map_private
{
	void	(*put)(t_map_private *map, char *key, void	*value);
	void	(*remove)(t_map_private *map, char *key);
	void	*(*get)(t_map_private *map, char *key);
	void	(*destroy)(t_map_private *map);
	char	**(*to_str)(t_map_private *map);
	size_t	size;
	t_node	*head;
	t_node	*end;
	void	(*destriy_node)(t_node *node);
};

#endif