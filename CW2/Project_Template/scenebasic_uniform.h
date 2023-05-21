#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/torus.h"
#include "helper/teapot.h"
#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/cube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    GLuint fsQuad, intermediateTex, renderTex, renderFBO, intermediateFBO;

    //Torus torus;
    //Teapot teapot;
    Plane plane;
    unique_ptr<ObjMesh> mesh;
    //Cube cube;

    void compile();
    void setupFBO();
    void Pass1();
    void Pass2();
    void Pass3();
    float Gauss(float, float);

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
    void setMatrices();
};

#endif // SCENEBASIC_UNIFORM_H
