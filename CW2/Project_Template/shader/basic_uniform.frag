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
uniform float Weight[5];

const vec3 luminance = vec3(0.2126f, 0.7152f, 0.0722f);

uniform struct LightInfo
{
    vec4 Position;
    vec3 La;            //ambient light
    vec3 Ld;            //diffuse light
    vec3 Ls;            //specular light
}   light;

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

vec3 BlinnPhong(vec3 n, vec4 pos)
{
    //vec3 texColour = texture(Tex1, TexCoord).rgb;
    //vec4 texColour2 = texture(Tex2, TexCoord);
    //vec3 mixedColour = mix(texColour.rgb, texColour2.rgb, texColour2.a);

    vec3 ambient = light.La * Material.Ka; //* texColour;
    vec3 s = normalize(vec3(light.Position - pos));
    float dotProduct = max(dot(s, n), 0.0);
    vec3 diffuse = light.Ld * Material.Kd * dotProduct; //* texColour;
    vec3 specular = vec3(0.0);
    
    if (dotProduct > 0.0)
    {
        vec3 v = normalize(-pos.xyz);
        vec3 h = normalize(v + s);
        specular = light.Ls * Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
    }
    
    return ambient + diffuse + specular;
}

float Luminance(vec3 color)
{
    return dot(luminance, color);
}

vec4 Pass1()
{
    return vec4(BlinnPhong(normalize(FragNormal), FragPosition), 1.0f);
}

vec4 Pass2()
{
    ivec2 pix = ivec2( gl_FragCoord.xy );
    vec4 sum = texelFetch(Tex1, pix, 0) * Weight[0];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,1) ) * Weight[1];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,-1) ) * Weight[1];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,2) ) * Weight[2];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,-2) ) * Weight[2];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,3) ) * Weight[3];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,-3) ) * Weight[3];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,4) ) * Weight[4];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(0,-4) ) * Weight[4];
    return sum;
}

vec4 Pass3()
{
    ivec2 pix = ivec2( gl_FragCoord.xy );
    vec4 sum = texelFetch(Tex1, pix, 0) * Weight[0];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(1,0) ) * Weight[1];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(-1,0) ) * Weight[1];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(2,0) ) * Weight[2];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(-2,0) ) * Weight[2];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(3,0) ) * Weight[3];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(-3,0) ) * Weight[3];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(4,0) ) * Weight[4];
    sum += texelFetchOffset(Tex1, pix, 0, ivec2(-4,0) ) * Weight[4];
    return sum;
}

void main() 
{
    Colour = vec3(0.0);
    SpotColour = vec3(0.0);

    Colour += BlinnPhong(FragNormal, FragPosition);

    //----------Edge Detection bit-------------
    if (Pass == 1)
    {
        FragColor = Pass1();
    }
    else if (Pass == 2)
    {
        FragColor = Pass2();
    }
    else if (Pass == 3)
    {
        FragColor = Pass3();
    }
}
