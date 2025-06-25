#pragma once

#include "../Shaders/Shader.h"
#include "../../Config/namespace.h"

/*
    The parent class of all the objects
        - Contains all information and functions required by all objects
        - Loads the objects, sets up the VBOs and deals with general object loading

    [Created by: Megan Sadio]
*/
class Model3D {
protected:
    // Information required by all models
    string path;
    bool loadSuccess;
    vector<shape_t> shapes;
    vector<material_t> material;
    string warning, error;
    attrib_t attributes;
    vector<GLuint> meshIndices;
    vector<GLfloat> fullVertexData;

    // VBO of the object
    GLuint VBO;
    // Where the shader program is made and stored
    Shader shaderMaker;

    // For Transformations
    mat4 transformationMatrix;
    mat4 identityMatrix = mat4(1.0f);

    // Vectors on relevant transformation info
    vec3 position;
    vec3 scaling;
    vec3 rotation;

public:
    //CONSTRUCTORS
    Model3D();
    Model3D(
        string pathName,
        vec3 pos, vec3 scale, vec3 rotate,
        string vertPath, string fragPath
    );

    //FUNCTIONS
    virtual void loadModel();
    virtual void setUpVBO();

    virtual void updatePos(Vector newPos);

       //Requires definition in child classes
    virtual void update() = 0;
    virtual void draw() = 0;

    //GETTERS
    virtual Shader getShader();
    
    //DECONSTRUCTOR
    ~Model3D();
};
