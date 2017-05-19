#version 330 core
out vec4 color;
in vec4 vertex_color;
in vec2 texture_coord;
//uniform sampler2D ourTexture1, ourTexture2;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightcolor;
uniform vec3 objectColor;
in vec3 FragPos;  
in vec3 Normal; 
void main()
{
float ambientStrength = 0.1f;
vec3 ambient = ambientStrength * lightcolor;

 // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

	// Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightcolor;  
//
//color = mix(texture(ourTexture1, texture_coord), texture(ourTexture2,texture_coord),0.5);
color = vec4(objectColor * (ambient + diffuse + specular), 1.0f);
}