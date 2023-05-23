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
SceneBasic_Uniform::SceneBasic_Uniform() : 
    plane(50.0f, 50.0f, 1.0f, 1.0f),
    angle(0.0f),
    tPrev(0.0f),
    rotSpeed(glm::pi<float>() / 8.0f)
{
    mesh = ObjMesh::load("media/Spiky Ball.obj", true);
}
//SceneBasic_Uniform::SceneBasic_Uniform() :
//    angle(0.0f),
//    tPrev(0.0f),
//    rotSpeed(glm::pi<float>() / 8.0f),
//    plane(50.0f, 50.0f, 1, 1),
//    teapot(14, mat4(1.0f)),
//    torus(0.7f * 1.5f, 0.3f * 1.5f, 50, 50) 
//{}

void SceneBasic_Uniform::initScene()
{
    #pragma region OriginalCode
    //compile();

    ////enable the depth test
    //glEnable(GL_DEPTH_TEST);

    ////initialise matrices
    //model = mat4(1.0f);
    //model = rotate(model, radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    ////view = lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //torus view
    ////view = lookAt(vec3(0.0f, 4.0f, 5.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //teapot view
    //view = lookAt(vec3(3.5f, 3.75f, 3.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //plane view
    //projection = mat4(1.0f);

    //float x, z;
    //for (int i = 0; i < 3; i++)
    //{
    //    stringstream name;
    //    name << "lights [" << i << "].Position";
    //    x = 2.0f * cosf((two_pi<float>() / 3) * i);
    //    z = 2.0f * sinf((two_pi<float>() / 3) * i);
    //    prog.setUniform(name.str().c_str(), view * vec4(x, 1.2f, z + 1.0f, 1.0f));
    //}

    ////set the light uniforms
    //prog.setUniform("lights[0].La", vec3(0.0f, 0.0f, 0.8f));
    //prog.setUniform("lights[1].La", vec3(0.0f, 0.75f, 0.0f));
    //prog.setUniform("lights[2].La", vec3(0.25f, 0.0f, 0.0f));

    //prog.setUniform("lights[0].Ld", vec3(0.0f, 0.0f, 0.8f));
    //prog.setUniform("lights[1].Ld", vec3(0.0f, 0.8f, 0.0f));
    //prog.setUniform("lights[2].Ld", vec3(0.8f, 0.0f, 0.0f));

    //prog.setUniform("lights[0].Ls", vec3(0.0f, 0.0f, 0.6f));
    //prog.setUniform("lights[1].Ls", vec3(0.0f, 0.6f, 0.0f));
    //prog.setUniform("lights[2].Ls", vec3(0.6f, 0.0f, 0.0f));

    ////add, activate, and bind the first texture
    //GLuint textureID = Texture::loadTexture("media/texture/cement.jpg");
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, textureID);

    //add, activate, and bind the second texture
    /*GLuint textureID2 = Texture::loadTexture("media/texture/moss.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID2);*/

    //set spotlight uniforms
    /*prog.setUniform("Spot.La", vec3(0.5f));
    prog.setUniform("Spot.Ls", vec3(0.9f));
    prog.setUniform("Spot.Ld", vec3(0.9f));
    prog.setUniform("Spot.Exponent", 50.0f);
    prog.setUniform("Spot.Cutoff", glm::radians(15.0f));*/
#pragma endregion

    compile();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    projection = mat4(1.0f);
    angle = glm::pi<float>() / 4.0f;

    setupFBO();

    // Array for full-screen quad
    GLfloat verts[] = 
    {
    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
    };
    GLfloat tc[] = 
    {
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    
    // Set up the buffers
    unsigned int handle[2];
    glGenBuffers(2, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);
    
    // Set up the vertex array object
    glGenVertexArrays(1, &fsQuad);
    glBindVertexArray(fsQuad);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0); // Vertex position
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2); // Texture coordinates

    glBindVertexArray(0);
    prog.setUniform("EdgeThreshold", 0.05f);
    prog.setUniform("lights[0].La", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].La", vec3(0.0f, 0.75f, 0.0f));
    prog.setUniform("lights[2].La", vec3(0.25f, 0.0f, 0.0f));

    prog.setUniform("lights[0].Ld", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].Ld", vec3(0.0f, 0.8f, 0.0f));
    prog.setUniform("lights[2].Ld", vec3(0.8f, 0.0f, 0.0f));

    prog.setUniform("lights[0].Ls", vec3(0.0f, 0.0f, 0.6f));
    prog.setUniform("lights[1].Ls", vec3(0.0f, 0.6f, 0.0f));
    prog.setUniform("lights[2].Ls", vec3(0.6f, 0.0f, 0.0f));

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

void SceneBasic_Uniform::setupFBO()
{
    // Generate and bind the framebuffer
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

    // Create the texture object
    glGenTextures(1, &renderTex);
    glBindTexture(GL_TEXTURE_2D, renderTex);

    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

    // Bind the texture to the FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTex, 0);

    // Create the depth buffer
    GLuint depthBuf;
    glGenRenderbuffers(1, &depthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    // Bind the depth buffer to the FBO
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);

    // Set the targets for the fragment output variables
    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);

    // Unbind the framebuffer, and revert to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneBasic_Uniform::update(float t)
{
    float deltaT = t - tPrev;
    
    if (tPrev == 0.0f)
    {
        deltaT = 0.0f;
    }
        
    tPrev = t;
    angle += rotSpeed * deltaT;

    if (angle > glm::two_pi<float>())
    {
        angle -= glm::two_pi<float>();
    }
}

void SceneBasic_Uniform::render()
{
    #pragma region OriginalCode

    ////clear the colour and depth buffers
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //
    ////set the position and direction of the spotlight
    ///*vec4 lightPos = vec4(0.0f, 10.0f, 0.0f, 1.0f);
    //prog.setUniform("Spot.Position", vec3(view * lightPos));
    //mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    //prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));*/

    ////set mesh material uniforms
    //prog.setUniform("Material.Kd", 0.75f, 0.75f, 0.75f);
    //prog.setUniform("Material.Ka", 0.25f, 0.25f, 0.25f);
    //prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    //prog.setUniform("Material.Shininess", 105.0f);
    //
    ////set mesh model
    //model = mat4(1.0f);
    //model = rotate(model, radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
    //model = translate(model, vec3(0.0f, 2.0f, 0.0f));
    //setMatrices();

    ////add, activate, and bind the first texture
    //GLuint textureID = Texture::loadTexture("media/texture/cement.jpg");
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, textureID);

    //mesh->render();

    ////set plane material uniforms
    //prog.setUniform("Material.Kd", 0.5f, 0.5f, 0.5f);
    //prog.setUniform("Material.Ka", 1.0f, 1.0f, 1.0f);
    //prog.setUniform("Material.Ks", 0.2f, 0.2f, 0.2f);
    //prog.setUniform("Material.Shininess", 180.0f);

    ////set plane model
    //model = mat4(1.0f);
    //model = translate(model, vec3(0.0f, -0.45f, 0.0f));
    //setMatrices();

    //textureID = Texture::loadTexture("media/texture/brick1.jpg");
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, textureID);

    //plane.render();
    #pragma endregion

    Pass1();
    glFlush();
    Pass2();
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

void SceneBasic_Uniform::Pass1()
{
    prog.setUniform("Pass", 1);

    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(vec3(7.0f * cos(angle), 4.0f, 7.0f * sin(angle)), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);

    //prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, 2.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    setMatrices();
    mesh->render();

    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.75f, 0.0f));
    setMatrices();
    plane.render();
}

void SceneBasic_Uniform::Pass2()
{
    prog.setUniform("Pass", 2);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderTex);

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    model = mat4(1.0f);
    view = mat4(1.0f);
    projection = mat4(1.0f);
    setMatrices();

    // Render the full-screen quad
    glBindVertexArray(fsQuad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}