/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "GLESWidget.h"
#include <openGl/OpenGl.h>

struct GLESWidget::Impl {

        Impl () : programObject (0) {}
        GLuint programObject;
};

GLESWidget::GLESWidget () : impl (new Impl)
{

}

GLESWidget::~GLESWidget ()
{
        delete impl;
}

void GLESWidget::init ()
{
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint linked;

        // Load the vertex/fragment shaders
        vertexShader = loadShader (GL_VERTEX_SHADER, vertex.c_str ());
        fragmentShader = loadShader (GL_FRAGMENT_SHADER, fragment.c_str());

        // Create the program object
        programObject = glCreateProgram ();

        if (programObject == 0)
                return;

        glAttachShader (programObject, vertexShader);
        glAttachShader (programObject, fragmentShader);

        // Bind vPosition to attribute 0
        glBindAttribLocation (programObject, 0, "vPosition");

        // Link the program
        glLinkProgram (programObject);

        // Check the link status
        glGetProgramiv (programObject, GL_LINK_STATUS, &linked);

        if (!linked) {
                GLint infoLen = 0;

                glGetProgramiv (programObject, GL_INFO_LOG_LENGTH, &infoLen);

                if (infoLen > 1) {
                        char* infoLog = new char [infoLen];
                        glGetProgramInfoLog (programObject, infoLen, NULL, infoLog);
                        std::cerr << "Error linking program:" << infoLog << std::endl;
                        delete [] infoLog;
                }

                glDeleteProgram (programObject);
                throw 1;
        }

        // Store the program object
        impl->programObject = programObject;

        glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
}

void GLESWidget::update (Model::IModel *model, Event::UpdateEvent *e)
{
//        GLfloat vVertices[] = { 0.0f, 50.0f, 0.0f, -50.0f, -50.0f, 0.0f, 50.0f, -50.0f, 0.0f };
        GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f };

        // Clear the color buffer
        glClear (GL_COLOR_BUFFER_BIT);

        // Use the program object
        glUseProgram (impl->programObject);

        // Load the vertex data
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
        glEnableVertexAttribArray (0);

        glDrawArrays (GL_TRIANGLES, 0, 3);
}


