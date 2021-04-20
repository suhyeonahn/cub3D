#include "sprite.h"
#include <stdio.h>

t_sprites_buffer *sprites_buffer;
t_sprite *sprite;
t_sprites_buffer *sprites_buffer_head;
t_sprite *sprite_head;

float distance_between_points(float x1, float y1, float x2, float y2)
{
	return sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
}

t_sprites_buffer *sprites_buffer_add_back(t_sprites_buffer **sprites_buffer, int x, int y)
{
	t_sprites_buffer	*first;
	t_sprites_buffer	*new;
	
	if (!x || !y)
		return (NULL);
	if (!(new = (t_sprites_buffer*)malloc(sizeof(*new))))
		return (0);
	new->x = x;
    new->y = y;
	new->next = NULL;
	if (!*sprites_buffer)
	{
		*sprites_buffer = new;
		sprites_buffer_head = *sprites_buffer;
	}
	else
	{
		first = *sprites_buffer;
		while ((*sprites_buffer)->next)
			*sprites_buffer = (*sprites_buffer)->next;
		(*sprites_buffer)->next = new;
		*sprites_buffer = first;
	}
	return (new);
}

t_sprite *sprite_add_back(t_sprite **sprite, float first_x, float last_x, float y, float inc, float b)
{
	t_sprite	*first;
	t_sprite    *new;
	
	if (!first_x || !last_x || !y || !inc || !b)
		return (NULL);
	if (!(new = (t_sprite*)malloc(sizeof(*new))))
		return (0);
	new->first_x = first_x;
	new->last_x = last_x;
    new->y = y;
	new->inc = inc;
	new->b = b;

	new->next = NULL;
	if (!*sprite)
	{
		*sprite = new;
		sprite_head = *sprite;
	}
	else
	{
		first = *sprite;
		while ((*sprite)->next)
			*sprite = (*sprite)->next;
		(*sprite)->next = new;
		*sprite = first;
	}
	return (new);
}