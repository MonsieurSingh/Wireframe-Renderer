//
//  images.h
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/8/2025.
//

#ifndef images_h
#define images_h

#include "wireframe.h"

typedef enum e_image_id
{
	IMG_MAIN = 0,
	IMG_OVERLAY,
	IMG_UI,
	IMG_COUNT_PLACEHOLDER	// keep last
}	t_image_id;

void	images_init(t_data *d, size_t initial_capacity);
t_image	*images_add(t_data *d, t_image_id id, int width, int height,
					int offset_x, int offset_y);
t_image	*images_get(t_image_id id);
void	images_draw_all(const t_data *d);
void	images_free(t_data *d);

#endif /* images_h */
