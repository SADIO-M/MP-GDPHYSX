#include "Line.h"

Line::Line(){}
Line::Line(float* verticesArray, string vertPath, string fragPath) {
    for (int i = 0; i < 6; i++) {
        this->verticesArray[i] = verticesArray[i];
    }

    shaderMaker.createShader(vertPath, fragPath);

    loadLine();

}
Line::Line(float* verticesArray, float lineWidth, vec3 color,
    string vertPath, string fragPath) :
    Line(verticesArray, vertPath, fragPath) {

    this->color = color;
    this->lineWidth = lineWidth;
}

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

void Line::update(){
    GLuint colorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "color");
    glUniform3fv(colorAddress, 1, value_ptr(color));
}

void Line::reassignPoints(float* newVertices){
    for (int i = 0; i < 6; i++) {
        this->verticesArray[i] = newVertices[i];
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(verticesArray),
        &verticesArray
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::draw() {
    update();
    glBindVertexArray(VAO);
    glLineWidth(lineWidth);
    glDrawArrays(GL_LINES, 0, 2);
}
