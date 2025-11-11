//
//  images.h
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/8/2025.
//

#ifndef images_h
#define images_h

#include "wireframe.h"

void	image_init(t_data *data);
void	image_add(t_data *data, int width, int height);
void	image_destroy_all(t_data *data);

#endif /* images_h */
