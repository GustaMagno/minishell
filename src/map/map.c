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
	str = calloc(count_nodes(this->head), sizeof(char *));
	if (!str)
		return (NULL);
	while (node)
	{	
		str[i++] = ft_mapstrjoin(ft_mapstrjoin(node->key, "="), node->value);
		node = node->next;
	}
	return (str);
}

void	destroy(struct s_map_private *this)
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

	if (!key || !this->get(this, key))
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

char	*_get(struct s_map_private *this, char *key)
{
	t_node	*node;

	node = find_node(this, key);
	if (!node)
		return (NULL);
	return (node->value);
}

void	__put(struct s_map_private *this, char *key, char *value)
{
	t_node *node;
	t_node *temp;

	if (!key)
		return ;
	node = find_node(this, key);
	if (node)
	{
		(free(key), free(node->value));
		node->value = value;
		return ;
	}
	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	*node = (t_node){key, value, NULL};
	if (!this->head)
	{
		this->head = node;
		return ;
	}
	temp = this->head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

// t a minishell: export a b c d e
// minishell: unset b
// minishell: unset d
// minishell: export a b c d e f
// minishell: unset a b c d e f
// minishell: export a b c d e f
// ==1031696== Invalid write of size 8
// ==1031696==    at 0x405974: __put (map.c:99)
// ==1031696==    by 0x403843: export_str (ft_export.c:65)
// ==1031696==    by 0x4039CE: ft_export (ft_export.c:88)
// ==1031696==    by 0x403306: exec_functions (exec.c:101)
// ==1031696==    by 0x403052: exec (exec.c:8)
// ==1031696==    by 0x405A66: run (main.c:22)
// ==1031696==    by 0x4059C3: main (main.c:35)
// ==1031696==  Address 0x4b6cc40 is 16 bytes inside a block of size 24 free'd
// ==1031696==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==1031696==    by 0x40558D: free_node (map_utils.c:46)
// ==1031696==    by 0x405818: _remove (map.c:61)
// ==1031696==    by 0x403A71: ft_unset (ft_unset.c:11)
// ==1031696==    by 0x4032D2: exec_functions (exec.c:99)
// ==1031696==    by 0x403052: exec (exec.c:8)
// ==1031696==    by 0x405A66: run (main.c:22)
// ==1031696==    by 0x4059C3: main (main.c:35)
// ==1031696==  Block was alloc'd at
// ==1031696==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==1031696==    by 0x405900: __put (map.c:92)
// ==1031696==    by 0x403843: export_str (ft_export.c:65)
// ==1031696==    by 0x4039CE: ft_export (ft_export.c:88)
// ==1031696==    by 0x403306: exec_functions (exec.c:101)
// ==1031696==    by 0x403052: exec (exec.c:8)
// ==1031696==    by 0x405A66: run (main.c:22)
// ==1031696==    by 0x4059C3: main (main.c:35)
// ==1031696== 
// minishell: export 1=c
// bash: export: not a valid identifier