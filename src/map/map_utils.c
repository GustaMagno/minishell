#include "minishell.h"
#include "map.h"

char		**to_str(t_map_private *map);
void 		destroy(t_map_private *map);
void		_remove(t_map_private *map, char *key);
void		*_get(t_map_private *map, char *key);
void		__put(t_map_private *map, char *key, void	*value);

t_map *new_map()
{
	struct s_map_private *map;

	map = malloc(sizeof(struct s_map_private));
	map->put = (void *) __put;
	map->get = _get;
	map->remove = _remove;
	map->to_str = to_str;
	map->head = NULL;
	map->end = NULL;
	map->destroy = destroy;
	return ((t_map *)map);
}

int	count_nodes(t_node	*head)
{
	t_node	*temp_node;
	int	i;

	temp_node = head;
	while (temp_node)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}

void	free_node(t_node *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

t_node	*find_node(struct s_map_private *this, char *key)
{
	t_node	*node;

	node = this->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}
