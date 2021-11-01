#version 330 core
out vec4 frag_color;

struct material_t
{
	sampler2D diffuse1;
	sampler2D specular1;
	float shininess;
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

in vec2 tex_coords;
in vec3 frag_pos;
in vec3 normal;

uniform material_t material;
uniform point_light_t plight;
uniform vec3 view_pos;

vec3 calculate_point_light(point_light_t light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main()
{
	vec3 result;
	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_pos - frag_pos);

	result += calculate_point_light(plight, norm, frag_pos, view_dir);

	frag_color = vec4(result, 1.0);
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
	vec3 ambient = light.ambient * vec3(texture(material.diffuse1, tex_coords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, tex_coords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular1, tex_coords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient+diffuse+specular);
}