#include "texture.h"

void	load_wall_texture(void)
{
	int bpp = 32;
	int endian = 0;
	int img_width;
	int img_height;
	void *img_ptr;
	int i = 0;

	while (i++ < NUM_TEXTURES)
	{
		img_ptr= mlx_xpm_file_to_image(mlx_ptr, texture[i].tex_path, &img_width, &img_height);
		int size_line = img_width;
		texture[i].width = img_width;
		texture[i].height = img_height;
		int *img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
		texture[i].tex = (int *)malloc(sizeof(int) * (img_width * img_height + 1));

		for (int y = 0; y < img_height; y++)
		{
			for (int x = 0; x < img_width; x++)
			{
				texture[i].tex[img_width * y + x] = img_data[img_width * y + x];
			}
		}
		texture[i].tex[img_width * img_height] = '\0';
		mlx_destroy_image(mlx_ptr, img_ptr);
		free(texture[i].tex_path);
	}
}

void	destroy_texture(void)
{
	free(texture);
}
