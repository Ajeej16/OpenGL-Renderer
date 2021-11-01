#version 330 core

struct material_t
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct directional_light_t
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct point_light_t
{
	vec3 pos;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

struct spot_light_t
{
	vec3 pos;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cut_off;
	float outer_cut_off;
	float constant;
	float linear;
	float quadratic;
};

#define MAX_POINT_LIGHTS 4

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

out vec4 frag_color;

uniform vec3 view_pos;
uniform material_t material;
uniform directional_light_t d_light;
uniform point_light_t p_light[MAX_POINT_LIGHTS];
uniform spot_light_t s_light;

vec3 calculate_directional_light(directional_light_t light, vec3 norm, vec3 v_dir);
vec3 calculate_point_light(point_light_t light, vec3 norm, vec3 f_pos, vec3 v_dir);
vec3 calculate_spot_light(spot_light_t light, vec3 norm, vec3 f_pos, vec3 v_dir);

void main()
{

	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_pos - frag_pos);
	
	vec3 result = calculate_directional_light(d_light, norm, view_dir);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		result += calculate_point_light(p_light[i], norm, frag_pos, view_dir);
	}

	result += calculate_spot_light(s_light, norm, frag_pos, view_dir);

	frag_color = vec4(result, 1.0);
}

vec3 calculate_directional_light(directional_light_t light, vec3 normal, vec3 view_dir)
{
	vec3 light_dir = normalize(-light.direction);

	//diffuse shading
	float diff = max(dot(normal, light_dir), 0.0);
	
	//specular shading
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
	
	//combined result
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));

	return (ambient+diffuse+specular);
}

vec3 calculate_point_light(point_light_t light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
	vec3 light_dir = normalize(light.pos - frag_pos);

	//diffuse shading
	float diff = max(dot(normal, light_dir), 0.0);
	
	//specular shading
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
	
	//attenuation
	float distance = length(light.pos - frag_pos);
	float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*(distance*distance));
	
	//combined result
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient+diffuse+specular);
}

vec3 calculate_spot_light(spot_light_t light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
	vec3 light_dir = normalize(light.pos-frag_pos);

	//diffuse shading
	float diff = max(dot(normal, light_dir), 0.0);
	
	//specular shading
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

	//attenuation
	float distance = length(light.pos - frag_pos);
	float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*(distance*distance));

	//smooth spotlight
	float theta = dot(light_dir, normalize(-light.direction));
	float epsilon = light.cut_off - light.outer_cut_off;
	float intensity = clamp((theta-light.outer_cut_off)/epsilon, 0.0, 1.0);
	
	vec3 ambient = light.ambient*vec3(texture(material.diffuse, tex_coords));
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, tex_coords));
	vec3 specular = light.specular*spec*vec3(texture(material.specular, tex_coords));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient+diffuse+specular);
}