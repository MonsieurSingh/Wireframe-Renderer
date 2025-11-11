//
//  matrix.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#include "matrix.h"

t_mat4	identity4(float i)
{
	return (t_mat4)
	{
		i, 0, 0, 0,
		0, i, 0, 0,
		0, 0, i, 0,
		0, 0, 0, i
	};
}

t_vec4	mat_vec_mul4(t_mat4 mat, t_vec4 vec)
{
	t_vec4 result = {0};
	float v[4] = { vec.x, vec.y, vec.z, vec.w };
	float *r = (float*)&result;
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r[i] += mat.m[i * 4 + j] * v[j];
	return result;
}

t_mat4	mat_mul4(t_mat4 a, t_mat4 b)
{
	t_mat4 result = {0};
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i * 4 + j] += a.m[i * 4 + k] * b.m[k * 4 + j];
			}
		}
	}
	return result;
}


t_mat4	translate4(float tx, float ty, float tz)
{
	return (t_mat4)
	{
		1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1
	};
}

t_mat4	rotate_x4(float theta)
{
	return (t_mat4)
	{
		1, 0, 0, 0,
		0, cosf(theta), -sinf(theta), 0,
		0, sinf(theta), cosf(theta), 0,
		0, 0, 0, 1
	};
}

t_mat4	rotate_y4(float theta)
{
	return (t_mat4)
	{
		cosf(theta), 0, sinf(theta), 0,
		0, 1, 0, 0,
		-sinf(theta), 0, cosf(theta), 0,
		0, 0, 0, 1
	};
}

t_mat4	rotate_z4(float theta)
{
	return (t_mat4)
	{
		cosf(theta), -sinf(theta), 0, 0,
		sinf(theta), cosf(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

t_mat4	scale4(float sx, float sy, float sz)
{
	return (t_mat4)
	{
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1
	};
}

t_mat4	rotate_4(float alpha, float beta, float gamma)
{
	return mat_mul4(mat_mul4(rotate_x4(alpha), rotate_y4(beta)), rotate_z4(gamma));
}

t_mat4	world_4(t_vec3 translate, t_vec3 rotate, t_vec3 scale)
{
//	World matrix = Translate * (Rotate * Scale)
	return mat_mul4(translate4(translate.x, translate.y, translate.z), mat_mul4(
							rotate_4(rotate.x, rotate.y, rotate.z),
							scale4(scale.x, scale.y, scale.z)));
}

t_mat4	transform_world_matrix(t_transform t, int width, int height)
{
	t_mat4	translation_center;
	t_mat4	translation_back;

	translation_center = translate4(width / 2, height / 2, 0);
	translation_back = translate4(-width / 2, -height / 2, 0);
	return mat_mul4(translation_center,
					mat_mul4(world_4(t.translate, t.rotate, t.scale),
							 translation_back)
					);
}

t_vec3	project_point_vec3(int i, int j, t_point **points)
{
	t_vec3	v;
	
	v.x = j;
	v.y = i;
	v.z = points[i][j].z;
	return v;
}

t_vec4	project_point_vec4(int i, int j, t_point **points)
{
	t_vec4	v;
	
	v.x = j;
	v.y = i;
	v.z = points[i][j].z;
	v.w	= 1;
	return v;
}
