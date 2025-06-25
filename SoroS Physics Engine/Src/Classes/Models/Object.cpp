#include "Object.h"

//CONSTRUCTORS
Object::Object(){}
Object::Object(
    string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	vec3 color) :

	Model3D(pathName, pos, scale, rotate, vertPath, fragPath) {

	this->color = color;  
  
    loadObject();
}

//FUNCTIONS
   //Loads Object
void Object::loadObject() {
	Model3D::loadModel();

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[0].mesh.indices[i].vertex_index);
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);

        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);

        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
    }

	Model3D::setUpVBO();
}

   //Object transformations
void Object::update(){
    transformationMatrix = translate(identityMatrix, position);
    transformationMatrix = scale(transformationMatrix, scaling);
    transformationMatrix = rotate(transformationMatrix, radians(rotation.x), vec3(1, 0, 0));
    transformationMatrix = rotate(transformationMatrix, radians(rotation.y), vec3(0, 1, 0));
    transformationMatrix = rotate(transformationMatrix, radians(rotation.z), vec3(0, 0, 1));

    GLuint transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformationMatrix));

    GLuint colorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "color");
    glUniform3fv(colorAddress, 1, value_ptr(color));
}

   //Draws object
void Object::draw(){
    update();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
}

vec3 Object::getColor() { return color; }

void Object::setColor(vec3 newColor) {
    color = newColor;
}