#include "minishell.h"
#include "map.h"

t_map 		*new_map();
int			count_nodes(t_node	*head);
void		free_node(t_node *node);
t_node		*find_node(t_map_private *map, char *key);

char	**to_str(struct s_map_private *this)
{
	char	**str;
	t_node	*node;
	int		i;

	i = 0;
	node = this->head;
	str = malloc(count_nodes(this->head) * sizeof(char *) + 1);
	if (!str)
		return (NULL);
	while (node)
	{
		str[i++] = ft_strjoin(ft_strjoin(node->key, "="), node->value);
		node = node->next;
	}
	str[i] = NULL;
	return (str);
}

void destroy(struct s_map_private *this)
{
	t_node	*node;

	node = this->head;
	while (node)
	{
		this->remove(this, node->key);
		node = this->head;
	}
	free(this);
}

void	_remove(struct s_map_private *this, char *key)
{
	t_node	*node;
	t_node	*node_to_free;

	if (!key)
		return ;
	node = this->head;
	if (!ft_strcmp(this->head->key, key))
	{
		this->head = node->next;
		free_node(node);
		return ;
	}
	while (node)
	{
		if (!ft_strcmp(node->next->key, key))
		{
			node_to_free = node->next;
			node->next = node->next->next;
			free_node(node_to_free);
			return ;
		}
		node = node->next;
	}
}

void	*_get(struct s_map_private *this, char *key)
{
	t_node	*node;

	node = find_node(this, key);
	if (!node)
		return (NULL);
	return (node->value);
}

void	__put(struct s_map_private *this, char *key, void	*value)
{
	t_node *node;

	if (!key)
		return ;
	if (this->get(this, key))
	{
		node = find_node(this, key);
		node->value = value;
		return ;
	}
	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	node->key = key;
	node->value = value;
	node->next = NULL;
	if (!this->head)
		this->head = node;
	else
		this->end->next = node;
	this->end = node;
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_map	*map;
// 	char	*s;

// 	map = new_map();
// 	map->put(map, ft_strdup("Nome"), ft_strdup("Gustavo"));
// 	map->put(map, ft_strdup("Idade"), ft_strdup("20"));
// 	map->put(map, ft_strdup("cidade"), ft_strdup("Bahia"));
// 	map->put(map, ft_strdup("Nome"), ft_strdup("Guilherme"));
// 	map->to_str(map);
// 	map->destroy(map);
// }
