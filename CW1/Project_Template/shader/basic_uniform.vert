#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec4 FragPosition;
out vec3 FragNormal;
out vec2 TexCoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
uniform mat4 ProjectionMatrix;

void GetCameraSpaceValues(out vec3 n, out vec4 pos)
{
    n = normalize(NormalMatrix * VertexNormal);
    pos = (ModelViewMatrix * vec4(VertexPosition, 1.0));
}

void main()
{
    TexCoord = VertexTexCoord;

    FragPosition = (ModelViewMatrix * vec4(VertexPosition,1.0));
    FragNormal = normalize( NormalMatrix * VertexNormal);

    GetCameraSpaceValues(FragNormal, FragPosition);

    gl_Position = MVP * vec4(VertexPosition, 1.0); 
}
