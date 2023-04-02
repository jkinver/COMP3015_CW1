#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 Colour;

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

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

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

void GetCameraSpaceValues(out vec3 n, out vec3 pos)
{
    n = normalize(NormalMatrix * VertexNormal);
    pos = (ModelViewMatrix * vec4(VertexPosition, 1.0)).xyz;
}

void main()
{
    vec3 camNorm;
    vec3 camPos;
    GetCameraSpaceValues(camNorm, camPos);

    Colour = vec3(0.0);

    for (int i = 0; i < 3; i++)
    {
        Colour += Phong(i, camNorm, vec4(camPos, 1.0));
    }

    gl_Position = MVP * vec4(VertexPosition, 1.0); 
}
