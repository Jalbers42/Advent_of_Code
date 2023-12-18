/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Jalbers42                                         #+#    #+#             */
/*   https://github.com/Jalbers42                     ###   ###########       */
/*                                                                            */
/******************************************************************************/

#include "microshell.h"

int err(char *msg)
{
    int i = 0;

    while (msg[i])
        write(1, &msg[i++], 1);
    return (1);
}

int ft_cd(char **argv, int i)
{
    if (i != 2)
        return (err("error: cd bad arguments\n"));
    if (chdir(argv[1]) == -1)
        return (err("error: cd cannot change directory to: "), err(argv[1]), err("\n"));
    return (0);
}

int exec(char **argv, int end_index, char **env)
{
    int has_pipe = 0;
    int fd[2];
    int pid;
    int status;

    if (argv[end_index] && !strcmp(argv[end_index], "|"))
        has_pipe = 1;
    if (has_pipe && pipe(fd) == -1)
        return (err("error: fatal\n"));
    pid = fork();
    if (pid == 0)
    {
        argv [end_index] = NULL;
        if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1))
            return (err("error: fatal\n"));
        execve(argv[0], argv, env);
        return (err("error: cannot execute\n"));
    }
    waitpid(pid, &status, 1);
    if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) || close(fd[1])))
        return (err("error: fatal\n"));
    return (WIFEXITED(status), WEXITSTATUS(status));
}

int main(int argc, char **argv, char **env)
{
    int i = 0;
    int status = 0;

    if (argc <= 1)
        return (0);
    while (argv[i] && argv[++i])
    {
        argv += i;
        i = 0;
        while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
            i++;
        if (!strcmp(argv[0], "cd"))
            status = ft_cd(argv, i);
        else
            status = exec(argv, i, env);
    }
    return (status);
}