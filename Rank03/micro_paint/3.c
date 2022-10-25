#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ERROR "Error: argument"
#define FILES "Error: Operation file corrupted"

typedef struct s_zone
{
    int w;
    int h;
    char bck;
} t_zone;

typedef struct s_shape
{
    char type;
    float x;
    float y;
    float width;
    float height;
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
    write(1, "\n", 1);
    return 1;
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

char *ft_get_zone(FILE *file, t_zone *zone)
{
    char *tmp;
    int i;

    if (fscanf(file, "%d %d %c\n", &zone->w, &zone->h, &zone->bck) != 3)
        return NULL;
    if (zone->w < 0 || zone->w >= 300 || zone->h < 0 || zone->h >= 300)
        return NULL;
    if (!(tmp = (char*)malloc(sizeof(*tmp) * (zone->w * zone->h))))
        return NULL;
    i = 0;
    while (i < zone->w * zone->h)
        tmp[i++] = zone->bck;
    return tmp;
}

int ft_ret(float x, float y, t_shape *shape)
{
    if (x < shape->x || y < shape->y || (shape->y + shape->height) < y || (shape->x + shape->width) < x)
        return 0;
    if (x - shape->x < 1.00000000 || y - shape->y < 1.00000000 || (shape->y + shape->height) - y < 1.00000000 || (shape->x + shape->width) - x < 1.00000000)
        return 2;
    return 1;
}

void ft_draw_shape(t_shape *shape, char **drawing, t_zone *zone)
{
    int x, y, is;
    y = 0;
    while (y < zone->h)
    {
        x = 0;
        while (x < zone->w)
        {
            is = ft_ret((float)x, (float)y, shape);
            if ((shape->type == 'r' && is == 2) || (shape->type == 'R' && is))
                (*drawing)[(y * zone->w) + x] = shape->color;
            x++;
        }
        y++;
    }
}

int ft_draw_shapes(FILE *file, char **drawing, t_zone *zone)
{
    t_shape tmp;
    int ret;

    while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6)
    {
        if (tmp.width < 0.00000000 && tmp.height < 0.00000000 && (tmp.type != 'r' || tmp.type != 'R'))
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
    while (i < zone->h)
    {
        write(1, drawing + (i * zone->w), zone->w);
        write(1, "\n", 1);
        i++;
    }
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
        return ft_error(ERROR);
    if (!(file = fopen(argv[1], "r")))
        return ft_error(FILES);
    if (!(drawing = ft_get_zone(file, &zone)))
        return ft_clear(file, NULL, FILES);
    if (!(ft_draw_shapes(file, &drawing, &zone)))
        return ft_clear(file, drawing, FILES);
    ft_draw_drawing(drawing, &zone);
    ft_clear(file, drawing, NULL);
    return 0;
}
