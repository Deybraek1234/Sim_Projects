#include"EBO.h"

VBO::VBO(GLfloat* indices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);    
}

void VBO::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
    glBundBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)
}

void VBO::Delete(){
    glDeleteBuffers(1, &ID);
}