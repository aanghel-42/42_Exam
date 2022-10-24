#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define ERROR "Error: argument"
#define E_FILE "Error: Operation file corrupted"

typedef struct s_zone
{
    int w;
    int h;
    char bck;
}   t_zone;

typedef struct s_shape
{
    char type;
    float x;
    float y;
    float radius;
    char  color;
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
    write(1, "\n", 1);
    return 1;
}

char *ft_get_zone(FILE *file, t_zone *zone)
{
    char *tmp;
    int i;

    if (fscanf(file, "%d %d %c\n", &zone->w, &zone->h, &zone->bck) != 3)
        return NULL;
    if ((zone->w <= 0 || zone->w > 300) || (zone->h <= 0 || zone->h > 300))
        return NULL;
    if (!(tmp = (char *)malloc(sizeof(*tmp) * (zone->w * zone->h))))
        return NULL;
    i = 0;
    while (i < zone->w * zone-> h)
        tmp[i++] = zone->bck;
    return tmp;    
}

int ft_circle(float x, float y, t_shape *shape)
{
    float distance;

    distance = sqrtf(powf(y - shape->y, 2.) + powf(x - shape->x, 2.));
    if (distance <= shape->radius)
    {
        if ((shape->radius - distance) < 1.000000000)
            return 2;
        return 1;
    }
    return 0;
}

void    ft_draw_shape(t_shape *shape, char *drawing, t_zone *zone)
{
    int x, y, is_it;

    y = 0;
    while (y < zone->h)
    {
        x = 0;
        while (x < zone->w)
        {
            is_it = ft_circle((float)x, (float)y, shape);
            if ((shape->type == 'c' && is_it == 2) || (shape->type == 'C' && is_it))
                drawing[(y * zone->w) + x] = shape->color;
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
            return 0;
        ft_draw_shape(&tmp, drawing, zone);
    }
    if (ret != -1)
        return 0;
    return 1;
}

void ft_draw_drawing(char *drawing, t_zone *zone)
{
    int i = 0;
    while (i < zone-> h)
    {
        write(1, drawing + (i * zone->w), zone-> w);
        write (1, "\n", 1);
        i++;
    }
}

int ft_clear(FILE *file, char *drawing, char *error)
{
    if (file)
        fclose(file);
    if (drawing)
        free(drawing);
    if (error)
        ft_error(error);
    return 1;
}

int main(int argc, char **argv)
{
    FILE *file;
    t_zone zone;
    char *drawing;

    zone.w = 0;
    zone.h = 0;
    zone.bck = 0;
    drawing = NULL;

    if (argc != 2)
        ft_error(ERROR);
    if (!(file = fopen(argv[1], "r")))
        ft_error(E_FILE);
    if (!(drawing = ft_get_zone(file, &zone)))
        ft_clear(file, NULL, E_FILE);
    if (!(ft_draw_shapes(file, drawing, &zone)))
        ft_clear(file, drawing, E_FILE);
    ft_draw_drawing(drawing, &zone);
    ft_clear(file, drawing, NULL);
    return 0;
}