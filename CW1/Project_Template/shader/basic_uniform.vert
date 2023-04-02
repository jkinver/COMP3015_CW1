#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec4 FragPosition;
out vec3 FragNormal;

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
    //FragPosition = vec4(VertexPosition, 1.0);             //?????????????
    //FragNormal = VertexNormal;                            //?????????????

    GetCameraSpaceValues(FragNormal, FragPosition);

    gl_Position = MVP * vec4(VertexPosition, 1.0); 
}
