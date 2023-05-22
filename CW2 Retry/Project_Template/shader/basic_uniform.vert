#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec4 FragPosition;
out vec3 FragNormal;
out vec4 EyePosition;
out vec3 EyeNormal;
out vec4 ProjTexCoord;

uniform mat4 ProjectorMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void GetCameraSpaceValues(out vec3 n, out vec4 pos)
{
    n = normalize(NormalMatrix * VertexNormal);
    pos = (ModelViewMatrix * vec4(VertexPosition, 1.0));
}

void main()
{
    //casting VertexPosition to four dimensions
    vec4 vertPos = vec4(VertexPosition, 1.0);

    //turning normals from model coordinates into eye coordinates
    EyeNormal = normalize(NormalMatrix * VertexNormal);

    //turning vertPos into eye coordinates
    EyePosition = ModelViewMatrix * vertPos;

    //assigning projected texture coordinates
    ProjTexCoord = ProjectorMatrix * (ModelMatrix * vertPos);
    
    

    //TexCoord = VertexTexCoord;

    //FragPosition = (ModelViewMatrix * vec4(VertexPosition,1.0));
    //FragNormal = normalize( NormalMatrix * VertexNormal);

    //GetCameraSpaceValues(FragNormal, FragPosition);



    gl_Position = MVP * vertPos; 
}

    
