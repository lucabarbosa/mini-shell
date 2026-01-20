#include "../includes/minishell.h"
#include "../includes/executor.h"

t_cmd	*tester_cmd(t_gc **collector)
{
	t_cmd	*cmd;

	cmd = gc_malloc(collector, sizeof(t_cmd));
	cmd->args = gc_malloc(collector, 3 * sizeof(char *));
	cmd->args[0] = ft_strdup("cat", collector);
	cmd->args[1] = NULL;
	cmd->infile = ft_strdup("infile.txt", collector);
	cmd->outfile = ft_strdup("test.txt", collector);
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}