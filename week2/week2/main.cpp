//========================================================================
// Week 2 - Transformations
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include "W_Common.h"
#include "examples.h"

#define EXAMPLE_2D
//#define EXAMPLE_3D

int main( void )
{
    int width, height, x;
    double t;
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }
    
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    //glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1280, 720, 0,0,0,0, 24,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif
	// Leave this here! On windows machines in Lab, glewInit is generating some mysterious, but apparently
	// harmless, error - and we need it gone.
	glGetError();

    glfwSetWindowTitle( "Week 2" );
    
    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
    
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval( 1 );
    
    glm::vec3 v1(12.0f,4.0f,8.0f);
    glm::vec3 v2(-7.0f,8.0f,2.0f);
    
    glm::vec3 v3 = glm::cross(v1,v2);
    printf("V3 = %f,%f,%f\n", v3.x,v3.y,v3.z);
#if defined(EXAMPLE_2D)
	InitExample2D();
#elif defined(EXAMPLE_3D)
	InitExample3D();
#endif

    do
    {
        t = glfwGetTime();
        glfwGetMousePos( &x, NULL );
        
        // Get window size (may be different than the requested size)
        glfwGetWindowSize( &width, &height );
        
        // Special case: avoid division by zero below
        height = height > 0 ? height : 1;
        
        glViewport( 0, 0, width, height );
        
        // Clear color buffer to black
        glClearColor( 0.4f, 0.4f, 0.4f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
#if defined(EXAMPLE_2D)
		RenderExample2D();
#elif defined(EXAMPLE_3D)
		RenderExample3D();
#endif

        // Swap buffers
        glfwSwapBuffers();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
          glfwGetWindowParam( GLFW_OPENED ) );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    exit( EXIT_SUCCESS );
}

