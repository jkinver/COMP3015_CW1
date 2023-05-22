#include "scenebasic_uniform.h"

#include <sstream>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
#include "helper/glutils.h"
#include "helper/texture.h"

using namespace std;
using namespace glm;

//SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50.0f, 50.0f) {}
//SceneBasic_Uniform::SceneBasic_Uniform() : teapot(50, translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0f))) {}
SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.0f, 100.0f, 100.0f) //teapot(14, mat4(1.0f))
{
    mesh = ObjMesh::load("media/Spiky Ball.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();

    //enable the depth test
    glEnable(GL_DEPTH_TEST);

    //initialise matrices
    model = mat4(1.0f);
    model = rotate(model, radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    //view = lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //torus view
    //view = lookAt(vec3(0.0f, 4.0f, 5.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //teapot view
    view = lookAt(vec3(3.5f, 3.75f, 3.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //plane view
    projection = mat4(1.0f);

    //set up things for the projector matrix
    vec3 projPos = vec3(2.0f, 5.0f, 5.0f);
    vec3 projAt = vec3(-2.0f, -4.0f, 0.0f);
    vec3 projUp = vec3(0.0f, 1.0f, 0.0f);
    mat4 projView = glm::lookAt(projPos, projAt, projUp);
    mat4 projProj = glm::perspective(glm::radians(30.0f), 1.0f, 0.2f, 1000.0f);
    mat4 bias = glm::translate(mat4(1.0f), vec3(0.5f));
    bias = glm::scale(bias, vec3(0.5f));
    prog.setUniform("ProjectorMatrix", bias * projProj * projView);
    
    // Load texture file
    GLuint flowerTex = Texture::loadTexture("media/texture/flower.png");
    
    //set up and send the projected texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, flowerTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float x, z;
    for (int i = 0; i < 3; i++)
    {
        stringstream name;
        name << "lights [" << i << "].Position";
        x = 2.0f * cosf((two_pi<float>() / 3) * i);
        z = 2.0f * sinf((two_pi<float>() / 3) * i);
        prog.setUniform(name.str().c_str(), view * vec4(x, 1.2f, z + 1.0f, 1.0f));
    }

    //set the light uniforms
    prog.setUniform("lights[0].La", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].La", vec3(0.0f, 0.75f, 0.0f));
    prog.setUniform("lights[2].La", vec3(0.25f, 0.0f, 0.0f));

    prog.setUniform("lights[0].Ld", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].Ld", vec3(0.0f, 0.8f, 0.0f));
    prog.setUniform("lights[2].Ld", vec3(0.8f, 0.0f, 0.0f));

    prog.setUniform("lights[0].Ls", vec3(0.0f, 0.0f, 0.6f));
    prog.setUniform("lights[1].Ls", vec3(0.0f, 0.6f, 0.0f));
    prog.setUniform("lights[2].Ls", vec3(0.6f, 0.0f, 0.0f));

    //add, activate, and bind the first texture
    /*GLuint textureID = Texture::loadTexture("media/texture/cement.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);*/

    //add, activate, and bind the second texture
    /*GLuint textureID2 = Texture::loadTexture("media/texture/moss.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID2);*/

}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update(float t)
{
	//update your angle here
}

void SceneBasic_Uniform::render()
{
    //clear the colour and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //set mesh material uniforms
    prog.setUniform("Material.Kd", 0.75f, 0.75f, 0.75f);
    prog.setUniform("Material.Ka", 0.25f, 0.25f, 0.25f);
    prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 105.0f);
    
    //set mesh model
    model = mat4(1.0f);
    model = rotate(model, radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
    model = translate(model, vec3(0.0f, 2.0f, 0.0f));
    setMatrices();

    //add, activate, and bind the first texture
    GLuint textureID = Texture::loadTexture("media/texture/cement.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    mesh->render();

    //set plane material uniforms
    prog.setUniform("Material.Kd", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ka", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ks", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 180.0f);

    //set plane model
    model = mat4(1.0f);
    model = translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();

    textureID = Texture::loadTexture("media/texture/brick1.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    plane.render();
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = perspective(radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic_Uniform::setMatrices()
{
    //set model matrix
    prog.setUniform("ModelMatrix", model);

    //set mv matrix
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);

    //set normal matrix
    prog.setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));

    //set projection matrix
    prog.setUniform("ProjectionMatrix", projection);

    //set the mvp matrix
    prog.setUniform("MVP", projection * mv);
}
