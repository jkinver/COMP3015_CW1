#version 460

in vec4 FragPosition;
in vec3 FragNormal;
out vec2 TexCoord;

in vec3 EyeNormal;
in vec4 EyePosition;
in vec4 ProjTexCoord;

layout (binding = 0 ) uniform sampler2D Tex1;
//layout (binding = 1 ) uniform sampler2D Tex2;

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

vec3 BlinnPhong(int light, vec3 n, vec4 pos)
{
    vec3 texColour = texture(Tex1, TexCoord).rgb;
    //vec4 texColour2 = texture(Tex2, TexCoord);
    //vec3 mixedColour = mix(texColour.rgb, texColour2.rgb, texColour2.a);

    vec3 ambient = lights[light].La * Material.Ka * texColour;
    vec3 s = normalize(vec3(lights[light].Position - pos));
    float dotProduct = max(dot(s, n), 0.0);
    vec3 diffuse = lights[light].Ld * Material.Kd * dotProduct * texColour;
    vec3 specular = vec3(0.0);
    
    if (dotProduct > 0.0)
    {
        vec3 v = normalize(-pos.xyz);
        vec3 h = normalize(v + s);
        specular = lights[light].Ls * Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
    }
    
    return ambient + diffuse + specular;
}

void main() 
{
    Colour = vec3(0.0);

    //for loop for adding each component for the RGB of the model
    for (int i = 0; i < 3; i++)
    {
        Colour += BlinnPhong(i, EyeNormal, normalize(EyePosition));
    }

    vec3 projTexColor = vec3(0.0);
    if( ProjTexCoord.z > 0.0 )
    {
        projTexColor = textureProj(Tex1, ProjTexCoord).rgb;
    }

    FragColor = vec4(Colour + projTexColor * 0.5, 1); //displaying the finalised colour
}
