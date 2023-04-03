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

using namespace std;
using namespace glm;

//SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50.0f, 50.0f) {}
//SceneBasic_Uniform::SceneBasic_Uniform() : teapot(50, translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0f))) {}
SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.0f, 100.0f, 100.0f) //, teapot(14, mat4(1.0f)), torus(1.75f * 0.75f, 0.75f, 50, 50)
{
    mesh = ObjMesh::load("../Project_Template/media/pig_triangulated.obj", true);
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
    view = lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //plane view
    projection = mat4(1.0f);

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
    prog.setUniform("lights[0].La", vec3(0.0f, 0.0f, 0.2f));
    prog.setUniform("lights[1].La", vec3(0.0f, 0.5f, 0.0f));
    prog.setUniform("lights[2].La", vec3(0.2f, 0.0f, 0.0f));

    prog.setUniform("lights[0].Ld", vec3(0.0f, 0.0f, 0.5f));
    prog.setUniform("lights[1].Ld", vec3(0.0f, 1.0f, 0.0f));
    prog.setUniform("lights[2].Ld", vec3(1.0f, 0.0f, 0.0f));

    prog.setUniform("lights[0].Ls", vec3(0.0f, 0.0f, 0.5f));
    prog.setUniform("lights[1].Ls", vec3(0.0f, 1.0f, 0.0f));
    prog.setUniform("lights[2].Ls", vec3(1.0f, 0.0f, 0.0f));

    //set spotlight uniforms
    /*prog.setUniform("Spot.La", vec3(0.5f));
    prog.setUniform("Spot.Ls", vec3(0.9f));
    prog.setUniform("Spot.Ld", vec3(0.9f));
    prog.setUniform("Spot.Exponent", 50.0f);
    prog.setUniform("Spot.Cutoff", glm::radians(15.0f));*/

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
    
    ////set the position and direction of the spotlight
    //vec4 lightPos = vec4(0.0f, 10.0f, 0.0f, 1.0f);
    //prog.setUniform("Spot.Position", vec3(view * lightPos));
    //mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    //prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));
    
    ////set teapot material uniforms
    //prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
    //prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    //prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
    //prog.setUniform("Material.Shininess", 100.0f);

    ////set teapot
    //model = mat4(1.0f);
    //model = glm::translate(model, vec3(0.0f, 0.0f, -2.0f));
    //model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    //setMatrices();
    //teapot.render();

    ////set torus material uniforms
    //prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
    //prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    //prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
    //prog.setUniform("Material.Shininess", 100.0f);

    ////set torus
    //model = mat4(1.0f);
    //model = glm::translate(model, vec3(-1.0f, 0.75f, 3.0f));
    //model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    //setMatrices();
    //torus.render();


    //set mesh material uniforms
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ka", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 5.0f);
    
    //set mesh model
    model = mat4(1.0f);
    model = rotate(model, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    setMatrices();
    mesh->render();

    //set plane material uniforms
    prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
    prog.setUniform("Material.Ka", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 180.0f);

    //set plane model
    model = mat4(1.0f);
    model = translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();
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
