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
}  t_zone;


typedef struct s_shape
{
    char    type;
    float   x;
    float   y;
    float   radius;
    char    color;

}   t_shape;

int ft_strlen(char *line, int i)
{
    i = 0;
    while (line[i] != '\0')
        i++;
    return (i);
}

int   ft_error(char *error)
{
    int i;

    i = ft_strlen(error, i);
    write(1, error, i);
    return (1);
}

int    ft_clear(FILE *file, char *drawing, char *error)
{
    if (file)
        fclose(file);
    if (drawing)
        free(drawing);
    if (error)
        ft_error(error);
    return (1);
}

char    *ft_get_zone(FILE *file, t_zone *zone)
{
    int     i;
    char    *tmp;

    if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
        return (NULL);
    if (zone->height <= 0 || zone->height > 300 && zone->width <= 0 || zone->width > 300)
        return (NULL);
    if (!(tmp = (char *)malloc(sizeof(*tmp) * (zone->width * zone->height))))
        return (NULL);
    i = 0;
    while (i < zone->width * zone->height)
        tmp[i++] = zone->background;
    return (tmp);
}

int ft_circle(float x, float y, t_shape *shape)
{
    float distance;

    distance = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));
    if (distance <= shape->radius)
    {
        if ((shape->radius - distance) < 1.00000000)
            return 2;
        return 1; 
    }
    return 0;
}

void    ft_draw_shape(t_shape *shape, t_zone *zone, char *drawing)
{
    int x;
    int y;
    int is_it;

    y = 0;
    while (y < zone->height)
    {
        x = 0;
        while (x < zone->width)
        {
            is_it = ft_circle((float)x, (float)y, shape);
            if ((shape->type == 'c' && is_it == 2) \
             || (shape->type == 'C' && is_it))
             drawing[(y * zone->width) + x] = shape->color;
             x++;
        }
        y++;
    }
}

int ft_draw_shapes(FILE *file, char *drawing, t_zone *zone)
{
    t_shape tmp;
    int ret;

    while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
    {
        if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
            return (0);
        ft_draw_shape(&tmp, zone, drawing);
    }
    if (ret != -1)
        return (0);
    return (1);
}

void    ft_draw_drawing(t_zone *zone, char *drawing)
{
    int i;

    i = 0;
    while (i < zone->height)
    {
        write(1, drawing + (i * zone->width), zone->width);
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    FILE    *file;
    t_zone  zone;
    char    *drawing;

    zone.height = 0;
    zone.background = 0;
    zone.width = 0;
    drawing = NULL;
    if (argc != 2)
        return (ft_error(ERROR_ARGC));
    if (!(file = fopen(argv[1], "r")))
        return (ft_error(ERROR_FILE));
    if (!(drawing = ft_get_zone(file, &zone)))
        return (ft_clear(file, NULL, ERROR_FILE));
    if (!(ft_draw_shapes(file, drawing, &zone)))
        return (ft_clear(file, drawing, ERROR_FILE));
    ft_draw_drawing(&zone, drawing);
    ft_clear(file, drawing, NULL);
    return (0);
}