#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
#include "helper/glutils.h"

using namespace std;
using namespace glm;

SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50.0f, 50.0f) {}
//SceneBasic_Uniform::SceneBasic_Uniform() : teapot(50, translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f))) {}

void SceneBasic_Uniform::initScene()
{
    compile();

    //enable the depth test
    glEnable(GL_DEPTH_TEST);

    //initialise matrices
    model = mat4(1.0f);
    view = lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    //view = lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);

    //set the uniforms
    prog.setUniform("Light.Position", view * vec4(5.0f, 5.0f, 2.0f, 1.0f));
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
    prog.setUniform("Material.Ka", 0.2f, 0.55f, 0.9f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Shininess", 100.0f);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setMatrices();
    torus.render();
    //teapot.render();
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
    //set mv matrix
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);

    //set normal matrix
    prog.setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));

    //set the mvp matrix
    prog.setUniform("MVP", projection * mv);
}
