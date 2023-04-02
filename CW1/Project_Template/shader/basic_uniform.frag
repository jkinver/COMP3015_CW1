#version 460

in vec4 FragPosition;
in vec3 FragNormal;

layout (location = 0) out vec4 FragColor;

vec3 Colour;

uniform struct LightInfo
{
    vec4 Position;
    vec3 La;            //ambient light
    vec3 Ld;            //diffuse light
    vec3 Ls;            //specular light
}   lights[3];

uniform struct MaterialInfo
{
    vec3 Ka;            //ambient factor
    vec3 Kd;            //diffuse factor
    vec3 Ks;            //specular factor
    float Shininess;    //material shininess
}   Material;

vec3 Phong(int light, vec3 n, vec4 pos)
{
    vec3 ambient = lights[light].La * Material.Ka;
    vec3 s = normalize(vec3(lights[light].Position - pos * lights[light].Position.w));
    float dotProduct = max(dot(s, n), 0.0);
    vec3 diffuse = lights[light].Ld * Material.Kd * dotProduct;
    vec3 specular = vec3(0.0);
    
    if (dotProduct > 0.0)
    {
        vec3 v = normalize(-pos.xyz);
        vec3 r = reflect(-s, n);
        specular = lights[light].Ls * Material.Ks * pow(max(dot(r, v), 0.0), Material.Shininess);
    }
    
    return ambient + diffuse + specular;
}

void main() 
{
    Colour = vec3(0.0);

    //for loop for adding each component for the RGB of the model
    for (int i = 0; i < 3; i++)
    {
        Colour += Phong(i, FragNormal, FragPosition);
    }

    FragColor = vec4(Colour, 1.0); //displaying the finalised colour
}
