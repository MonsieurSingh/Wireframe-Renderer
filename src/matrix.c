//
//  matrix.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#include "matrix.h"
//	TODO: Seperate this file

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

t_vec3 minus(t_vec3 a, t_vec3 b)
{
	return (t_vec3){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
	};
}

float dot(t_vec3 a, t_vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;
	
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

t_vec3	normalize(t_vec3 v)
{
	float	length;
	
	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length > 0.0001f)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return v;
}

t_vec4	mat_vec_mul4(t_mat4 mat, t_vec4 vec)
{
	t_vec4 result = {0};
	float v[4] = { vec.x, vec.y, vec.z, vec.w };
	float *r = (float*)&result;
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r[i] += mat.m[i * 4 + j] * v[j];
	if (result.w != 0.0f && result.w != 1.0f)
	{
		result.x /= result.w;
		result.y /= result.w;
		result.z /= result.w;
		result.w = 1.0f;
	}
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

t_mat4 look_at4(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_vec3 f = normalize((t_vec3){ target.x - eye.x, target.y - eye.y, target.z - eye.z });
	t_vec3 s = normalize(cross(f, up));
	t_vec3 u = cross(s, f);

	t_mat4 view = {
		s.x,  s.y,  s.z,  -dot(s, eye),
		u.x,  u.y,  u.z,  -dot(u, eye),
		-f.x, -f.y, -f.z,   dot(f, eye),
		0.0f, 0.0f, 0.0f,   1.0f
	};
	return view;
}

t_mat4 perspective4(float fov_deg, float aspect, float near, float far)
{
	float f = 1.0f / tanf((fov_deg * 0.5f) * M_PI / 180.0f);
	return (t_mat4){
		f / aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (far + near) / (near - far), (2 * far * near) / (near - far),
		0, 0, -1, 0
	};
}

t_mat4	world_4(t_vec3 translate, t_vec3 rotate, t_vec3 scale)
{
	return mat_mul4(translate4(translate.x, translate.y, translate.z), mat_mul4(
							rotate_4(rotate.x, rotate.y, rotate.z),
							scale4(scale.x, scale.y, scale.z)));
}

t_mat4	transform_world_matrix(t_render_state state, int width, int height)
{
	t_mat4		translation_center;
	t_mat4		translation_back;
	t_model		model;
	t_camera	cam;

	translation_center = translate4(width / 2, height / 2, 0);
	translation_back = translate4(-width / 2, -height / 2, 0);
	model = state.model;
	cam = state.camera;
	t_mat4 vp = mat_mul4(perspective4(60.0f, (float)width / height, 0.1f, 100.0f),
						 look_at4(cam.eye, cam.target, cam.up));
	t_mat4 final = mat_mul4(vp, world_4(model.translate, model.rotate, model.scale));
	return mat_mul4(translation_center,
					mat_mul4(final, translation_back));
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
