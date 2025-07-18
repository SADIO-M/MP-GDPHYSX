#include "Line.h"

//CONSTRUCTORS
Line::Line(){}
Line::Line(float* verticesArray, string vertPath, string fragPath) {
    for (int i = 0; i < 6; i++) {
        this->verticesArray[i] = verticesArray[i];
    }
    //Create shader, similar to Object.cpp
    shaderMaker.createShader(vertPath, fragPath);
    //Loads line, does not use the one from model because the line is loaded differently (no texture or normals)
    loadLine();

}
Line::Line(float* verticesArray, float lineWidth, vec3 color,
    string vertPath, string fragPath) :
    Line(verticesArray, vertPath, fragPath) {
    //If user wants to assign color and width
    this->color = color;
    this->lineWidth = lineWidth;
}

//Loads the line
void Line::loadLine() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticesArray),
        verticesArray,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GLfloat),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//Updates the line's color (if ever)
void Line::update(){
    GLuint colorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "color");
    glUniform3fv(colorAddress, 1, value_ptr(color));
}

//Reassigns the line's vertices (so that it properly follows the particle and the anchor)
void Line::reassignVertices(float* newVertices){
    for (int i = 0; i < 6; i++) {
        this->verticesArray[i] = newVertices[i];
    }
    
    //Uses glBufferSubData to replace the vertices stored in the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(verticesArray),
        &verticesArray
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Draws the lines by binding vao, setting line width, then render
void Line::draw() {
    update();
    glBindVertexArray(VAO);
    glLineWidth(lineWidth);
    glDrawArrays(GL_LINES, 0, 2);
}
