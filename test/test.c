#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include"Header Files/shaderClass.h"
#include"Header Files/VAO.h"
#include"Header Files/VBO.h"
#include"Header Files/EBO.h"

int main( void ) {
  //needed for wayland?
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

  //initialize GLFW with versions
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //initialize array
  GLfloat vertices[]= {
    -0.5f, -0.5f * (sqrt(3))/3, 0.0f,
    0.5f, -0.5f * (sqrt(3))/3, 0.0f,
    0.0f, 0.5f * (sqrt(3))*2/3, 0.0f,
    -0.5f/2, 0.5f * sqrt(3)/6, 0.0f,
    0.5f/2, 0.5f*sqrt(3)/6, 0.0f,
    0.0f, -0.5f * sqrt(3) /3, 0.0f
  };

  GLuint indices[]=
  { 
    0,3,5,
    3,2,4,
    5,4,1
  };

  //create window with pointer
  GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
  //check if it actually created, if not kill
  if(window==NULL){
    printf("Failed to Initialize");
    glfwTerminate();
    return -1;
  }
  //focus the window we created
  glfwMakeContextCurrent(window);
  //load GLAD
  gladLoadGL(glfwGetProcAddress);
  //set ViewPort (kind of like axis)
  glViewport(0,0,800,800);

  Shader shaderProgram("default.vert", "default.frag");

  //while loop to keep window running
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.07f,0.13f,0.17f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  
  //terminate window

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}