/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:23 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/19 14:39:59 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_ARGC "Error: argument\n"
#define ERROR_FILE "Error: Operation file corrupted\n"

typedef struct s_zone
{
    int width;
    int height;
    char background;
} t_zone;

typedef struct s_shape
{
    char type;
    float x;
    float y;
    float radius;
    char color;
} t_shape;

int ft_strlen(char *line)
{
    int i = 0;
    while (line[i] != '\0')
        i++;
    return i;
}

int ft_error(char *error)
{
    write(1, error, ft_strlen(error));
    return 1;
}

int ft_clear(FILE * file, char *drawing, char *error)
{
    if(file)
        fclose(file);
    if(drawing)
        free(drawing);
    if (error)
        ft_error(error);
    return 1;
}

char *ft_get_zone

int main(int argc, char **argv)
{
    FILE *file;
    t_zone zone;
    char *drawing;

    zone.width = 0;
    zone.height = 0;
    zone.background = 0;
    drawing = NULL;
    if(argc != 2)
        return (ft_error(ERROR_ARGC));
    if (!(file = fopen(argv[1], "r")))
        return (ft_error(ERROR_FILE));
    if (!(drawing = ft_get_zone(file, &zone)))
        return (ft_clear(file, NULL, ERROR_FILE));
    ft_clear(file, drawing, NULL);
    return (0);
}