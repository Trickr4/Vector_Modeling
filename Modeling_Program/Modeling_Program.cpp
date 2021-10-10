// Modeling_Program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>

#include <cstdio>


// Global Variables
    bool toggle_draw = false;
    int posx = 0, posy = 0, posz = 0;
    int count;

struct Quad
{
    int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    float r, g, b;
    int state;
    int total;
}; Quad Q[100];

void addQuad()
{
    Q[0].state++;
    if (Q[0].state > 4)
        Q[0].state = 0;
    int st = Q[0].state;

    if (st == 1)
    {
        Q[0].total++;
        count = Q[0].total;
        Q[count].x1 = posx;
        Q[count].y1 = posy;
        Q[count].z1 = posz;
    }
    if (st == 1 || st == 2)
    {
        Q[count].x2 = posx;
        Q[count].y2 = posy;
        Q[count].z2 = posz;
    }
    if (st == 1||st == 2|| st == 3)
    {
        Q[count].x3 = posx;
        Q[count].y3 = posy;
        Q[count].z3 = posz;
    }
    if (st == 1 || st == 2 || st == 3 || st == 4)
    {
        Q[count].x4 = posx;
        Q[count].y4 = posy;
        Q[count].z4 = posz;
    }
}

void drawQuad()
{
    for (int i = 1; i < Q[0].total + 1; i++)
    {
        glBegin(GL_QUADS);
        glColor3f(Q[i].r, Q[i].g, Q[i].b);
        glVertex3f(Q[i].x1, Q[i].y1, Q[i].z1);
        glVertex3f(Q[i].x2, Q[i].y2, Q[i].z2);
        glVertex3f(Q[i].x3, Q[i].y3, Q[i].z3);
        glVertex3f(Q[i].x4, Q[i].y4, Q[i].z4);
        glEnd();
    }
}

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
        if (key == GLFW_KEY_1)
            toggle_draw = true;
        if (key == GLFW_KEY_W) posz -= 1;
        if (key == GLFW_KEY_S) posz += 1;
        if (key == GLFW_KEY_A) posx -= 1;
        if (key == GLFW_KEY_D) posx += 1;
        if (key == GLFW_KEY_Q) posy += 1;
        if (key == GLFW_KEY_E) posy -= 1;
        if (key == GLFW_KEY_SPACE) addQuad();
    }
}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

void drawGrid()
{
    int i;
    int gridSize = 40;
    for (int i = 0; i < 40; i++)
    {
        glPushMatrix();
        if (i < 20) 
        {
            glTranslatef(0, 0, i);
        }
        if (i >= 20)
        {
            glTranslatef(i - 20, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }

        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glLineWidth(1);
        glVertex3f(0, -0.1, 0);
        glVertex3f(19, -0.1, 0);
        glEnd();
        glPopMatrix();
    }
}

void drawCube()
{
    GLfloat vertices[] =
    {
        -0.2, -0.2, -0.2,   -0.2, -0.2,  0.2,   -0.2,  0.2,  0.2,   -0.2,  0.2, -0.2,
        0.2, -0.2, -0.2,    0.2, -0.2,  0.2,    0.2,  0.2,  0.2,    0.2,  0.2, -0.2,
        -0.2, -0.2, -0.2,   -0.2, -0.2,  0.2,    0.2, -0.2,  0.2,    0.2, -0.2, -0.2,
        -0.2,  0.2, -0.2,   -0.2,  0.2,  0.2,    0.2,  0.2,  0.2,    0.2,  0.2, -0.2,
        -0.2, -0.2, -0.2,   -0.2,  0.2, -0.2,    0.2,  0.2, -0.2,    0.2, -0.2, -0.2,
        -0.2, -0.2,  0.2,   -0.2,  0.2,  0.2,    0.2,  0.2,  0.2,    0.2, -0.2,  0.2
    };

    GLfloat colors[] =
    {
        1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,
        1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,
        1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,
        1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,
        1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,
        1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1
    };

    static float alpha = 0;
    //attempt to rotate cube
    //glRotatef(alpha, 0, 1, 0);
    glTranslatef(posx, posy, posz);
    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    
    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 24);
   

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    alpha += 1;
}

static void display(GLFWwindow* window)
{
   printf("Display\n");
   
   while (!glfwWindowShouldClose(window))
    {
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);
        

        // Draw stuff
        glClearColor((float)0.3, (float)0.3, (float)0.3, (float)1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(35, 1.0f, 0.1f, 1000.0f);

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(-13, 0, -45);
        glRotatef(40, 1, 1, 0);
       // if (toggle_draw)
        //{
            //drawCube();

            drawGrid();
            drawQuad();
            drawCube();
            
            glfwSwapBuffers(window);
            toggle_draw = false;
       // }
        
        // Update Screen
        //glFlush();
        

        // Check for any input, or window movement
        glfwPollEvents();

    }
}

int main()
{
    GLFWwindow* window = initWindow(1024, 620);
    if (NULL != window)
    {
        display(window);
    }
    printf("Goodbye!\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    /*
    std::cout << "Hello World!\n";
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Rendering", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
