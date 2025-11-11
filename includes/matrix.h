//
//  matrix.h
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#ifndef matrix_h
#define matrix_h

#include <math.h>

typedef struct s_point
{
	int x;
	int y;
	int z;
	unsigned int color;
}	t_point;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_mat4
{
	float	m[16];
}	t_mat4;

// transformation state container
typedef struct s_transform
{
	t_vec3	translate;
	t_vec3	rotate;
	t_vec3	scale;
}	t_transform;


// matrix and vector operations
t_mat4	identity4(float i);
t_vec4	mat_vec_mul4(t_mat4 mat, t_vec4 vec);
t_mat4	mat_mul4(t_mat4 a, t_mat4 b);
t_mat4	translate4(float tx, float ty, float tz);
t_mat4	rotate_x4(float theta);
t_mat4	rotate_y4(float theta);
t_mat4	rotate_z4(float theta);
t_mat4	scale4(float sx, float sy, float sz);
t_mat4	rotate_4(float alpha, float beta, float gamma);

// helpers
t_vec3	project_point_vec3(int i, int j, struct s_point **points);
t_vec4	project_point_vec4(int i, int j, struct s_point **points);
t_mat4	world_4(t_vec3 translate, t_vec3 rotate, t_vec3 scale);
t_mat4	transform_world_matrix(t_transform t, int width, int height);

#endif /* matrix_h */
