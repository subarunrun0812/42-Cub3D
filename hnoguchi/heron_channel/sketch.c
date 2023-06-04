#include <math.h>

// Vector
typedef struct vector_2 {
	float	x;
	float	y;
}	vector_2;

vector_2	vector_2_create(float x, float y)
{
	vector_2	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

vector_2	vector_2_add(vector_2 a, vector_2 b)
{
	vector_2	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;

	return (result);
}

vector_2	vector_2_sub(vector_2 a, vector_2 b)
{
	vector_2	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return (result);
}

vector_2	vector_2_multi_scalar(vector_2 vector, float scalar)
{
	vector_2	result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;

	return (result);
}

vector_2	vector_2_mag(vector_2 vector)
{
	return ((vector.x * vector.x) + (vector.y * vector.y));
}

// Ray
typedef struct ray_2 {
	vector_2	start_point;
	vector_2	direction;
}	ray_2;

ray_2	ray_2_create(vector_2 start_p, vector_2 direction)
{
	ray_2	ray;

	ray.start_point = start_p;
	ray.direction = direction;

	return (ray);
}

vector_2	ray_2_point_at(ray_2 ray, float t)
{
	vector_2	point = vector_2_add(ray.start_point, vector_2_multi_scalar(ray.direction, t));

	return (point);
}
