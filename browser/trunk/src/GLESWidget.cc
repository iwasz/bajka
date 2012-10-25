/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "GLESWidget.h"

struct GLESWidget::Impl {

        Impl () : programObject (0) {}

        GLuint loadShader (GLenum type, const char *shaderSrc);
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
        const char *vShaderStr = "attribute vec4 vPosition;    \n"
                                "void main()                  \n"
                                "{                            \n"
                                "   gl_Position = vPosition;  \n"
                                "}                            \n";

        const char *fShaderStr = "precision mediump float;\n"
                                "void main()                                  \n"
                                "{                                            \n"
                                "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
                                "}                                            \n";

        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint linked;

        // Load the vertex/fragment shaders
        vertexShader = impl->loadShader (GL_VERTEX_SHADER, vShaderStr);
        fragmentShader = impl->loadShader (GL_FRAGMENT_SHADER, fShaderStr);

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

///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint GLESWidget::Impl::loadShader (GLenum type, const char *shaderSrc)
{
        GLuint shader;
        GLint compiled;

        // Create the shader object
        shader = glCreateShader (type);

        if (shader == 0) {
                GLenum error = glGetError ();
                std::cerr << error << std::endl;
                throw 1;
        }

        // Load the shader source
        glShaderSource (shader, 1, &shaderSrc, NULL);

        // Compile the shader
        glCompileShader (shader);

        // Check the compile status
        glGetShaderiv (shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
                GLint infoLen = 0;

                glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLen);

                if (infoLen > 1) {
                        char* infoLog = new char [infoLen];
                        glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
                        std::cerr << "Error compiling shader:" << infoLog << std::endl;
                        delete [] infoLog;
                        throw 1;
                }

                glDeleteShader (shader);
                return 0;
        }

        return shader;

}
