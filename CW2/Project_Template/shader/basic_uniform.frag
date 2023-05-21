#version 460

in vec4 FragPosition;
in vec3 FragNormal;
//in vec2 TexCoord;

layout (binding = 0 ) uniform sampler2D Tex1;
//layout (binding = 1 ) uniform sampler2D Tex2;

layout (location = 0) out vec4 FragColor;

vec3 Colour;
vec3 SpotColour;

uniform float EdgeThreshold;
uniform int Pass;

const vec3 luminance = vec3(0.2126f, 0.7152f, 0.0722f);

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

uniform struct SpotInfo
{
    vec4 Position;      //spotlight position
    vec3 Direction;     //spotlight direction
    float Cutoff;       //spotlight cutoff angle
    vec3 La;            //spotlight ambient
    vec3 Ld;            //spotlight diffuse
    vec3 Ls;            //spotlight specular
    float Exponent;
}   Spot;

vec3 BlinnPhong(int light, vec3 n, vec4 pos)
{
    //vec3 texColour = texture(Tex1, TexCoord).rgb;
    //vec4 texColour2 = texture(Tex2, TexCoord);
    //vec3 mixedColour = mix(texColour.rgb, texColour2.rgb, texColour2.a);

    vec3 ambient = lights[light].La * Material.Ka; //* texColour;
    vec3 s = normalize(vec3(lights[light].Position - pos));
    float dotProduct = max(dot(s, n), 0.0);
    vec3 diffuse = lights[light].Ld * Material.Kd * dotProduct; //* texColour;
    vec3 specular = vec3(0.0);
    
    if (dotProduct > 0.0)
    {
        vec3 v = normalize(-pos.xyz);
        vec3 h = normalize(v + s);
        specular = lights[light].Ls * Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
    }
    
    return ambient + diffuse + specular;
}

float Luminance(vec3 color)
{
    return dot(luminance, color);
}

vec4 EDPass1()
{
    return vec4(BlinnPhong(1, normalize(FragNormal), FragPosition), 1.0f);
}

vec4 EDPass2()
{
    //we grab a pixel to check if edge
    ivec2 pix = ivec2(gl_FragCoord.xy); 

    //pick neighboutring pixels for convolution filter
    float s00 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(-1,1)).rgb);
    float s10 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(-1,0)).rgb);
    float s20 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(-1,-1)).rgb);
    float s01 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(0,1)).rgb);
    float s21 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(0,-1)).rgb);
    float s02 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(1,1)).rgb);
    float s12 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(1,0)).rgb);
    float s22 = Luminance(texelFetchOffset(Tex1, pix, 0, ivec2(1,-1)).rgb);

    float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
    float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);
    float g = sx * sx + sy * sy;
    
    if( g > EdgeThreshold )
    {
        //edge is present
        return vec4(1.0);
    }  
    else
    {
        //no edge is present
        return vec4(0.0,0.0,0.0,1.0); 
    }
    
}

void main() 
{
    Colour = vec3(0.0);
    SpotColour = vec3(0.0);

    //for loop for adding each component for the RGB of the model
    for (int i = 0; i < 3; i++)
    {
        Colour += BlinnPhong(i, FragNormal, FragPosition);
    }

    //----------Edge Detection bit-------------
    if (Pass == 1)
    {
        FragColor = EDPass1();
    }
    if (Pass == 2)
    {
        FragColor = EDPass2();
    }


    //FragColor = vec4(Colour, 1.0); //displaying the finalised colour

    //SpotColour = BlinnPhongSpot(FragNormal, FragPosition);

    //FragColor = vec4(SpotColour, 1.0);
}
