#version 330

precision highp float;

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;

	float linear;
	float quadratic;
};


uniform struct{
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    vec3 solidColor;
}Illumination;

uniform vec3 cameraPos;
uniform int nLight;
uniform Light lights[100];

in struct{
	vec3 normal;
	vec3 position;
}VSO;

out vec4 fragmentColor;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (1 + light.linear * distance + light.quadratic * (distance * distance));    
    // ambient
    vec3 ambient  = Illumination.ambient * light.ambient * Illumination.solidColor;
    // diffuse
    float diffuseStrength = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = Illumination.diffuse * diffuseStrength * light.diffuse * Illumination.solidColor;
    //specular
    float cosa = dot(normal, lightDir);
    float cosb = clamp(dot(normal, viewDir), 0, 1);
    vec3 halfWayVector = normalize(viewDir + lightDir);
    
    float specamount = pow(max(dot(halfWayVector, normal), 0), Illumination.shininess) * (cosa / max(cosa, cosb));
    vec3 specular = specamount * Illumination.specular * light.specular * Illumination.solidColor;
    
    
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

void main(){
    vec3 norm = normalize(VSO.normal);
    vec3 viewDir = normalize(cameraPos - VSO.position);
    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < nLight; i++)
        result += CalcPointLight(lights[i], norm, VSO.position, viewDir);


    fragmentColor = vec4(result, 1.0f);
}