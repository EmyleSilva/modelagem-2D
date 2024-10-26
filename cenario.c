#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926

void display(void);
void drawRectangle(float x, float y, float height, float width);
void drawCircle(float cx, float cy, float r, int numTriangles);
void drawTriangle(float x, float y, float width, float heigth);
void sky(void);
void ground(void);
void drawJerryLowerBody(float, float, float, float);
void drawJerryUpperBody(float, float, float, float);
void drawLine(float, float, float, float);
void drawEllipse(float cx, float cy, float rx, float ry, int numTriangles);
void drawEllipseOutLine(float cx, float cy, float rx, float ry, int numTriangles);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800); 
    glutInitWindowPosition (00, 00); 
    glutCreateWindow (argv[1]); 
    glClearColor(0.0118f, 0.9412f, 0.6039f, 1.0f);
    glOrtho (-1, 1,-1, 1, -1 ,1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    sky();
    ground();

    drawJerryLowerBody(0.75f, -0.5f, 0.2f, 0.03f);
    drawJerryUpperBody(0.75f, -0.28f, 0.1f, 0.07f);
    glFlush();
}

void drawRectangle(float x, float y, float height, float width)
{
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

void drawCircle(float cx, float cy, float r, int numTriangles)
{
    float angle = 0.0;
    float x = 0.0;
    float y = 0.0;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= numTriangles; i++)
        {
            float angle = 2.0f * PI * (float)i / (float)numTriangles;
            x = r * cos(angle);
            y = r * sin(angle);
            glVertex2f(x + cx, y + cy);
        }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int numTriangles)
{
    float angle = 0.0;
    float x = 0.0;
    float y = 0.0;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= numTriangles; i++)
        {
            float angle = 2.0f * PI * (float)i / (float)numTriangles;
            x = rx * cos(angle);
            y = ry * sin(angle);
            glVertex2f(x + cx, y + cy);
        }
    glEnd();
}

/**
 * @todo Tentar corrigir dps
 */
void drawEllipseOutLine(float cx, float cy, float rx, float ry, int numTriangles)
{
    float angle = 0.0;
    float x = 0.0;
    float y = 0.0;

    glBegin(GL_LINE_STRIP);
        glVertex2f(cx, cy);
        for (int i = 0; i < numTriangles-1; i++)
        {
            glLineWidth(0.1f);
            float angle = 2.0f * PI * (float)i / (float)(numTriangles - 1);
            x = rx * cos(angle);
            y = ry * sin(angle);
            glVertex2f(x + cx, y + cy);
        }
    glEnd();
}

void drawTriangle(float x, float y, float width, float heigth)
{
    /*
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y);
        glVertex2f(x - width, y);
        glVertex2f(x + width, y - heigth);
    glEnd();*/

    /**
     * @todo VERIFICAR COMO FICAM OS PONTOS
     */
}

void drawLine(float x, float y, float heigth, float width)
{
    glColor3ub(0, 0, 0); //Define a cor da linha como preto
    glLineWidth(width);

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y+heigth);
    glEnd();
}

void sky(void)
{
    glBegin(GL_POLYGON);
        glColor3ub(126, 21, 224);
        glVertex2f(-1,-0.5);
        glColor3ub(170, 0, 239);
        glVertex2f(-1,1);
        glColor3ub(66, 11, 230);
        glVertex2f(1,1);
        glColor3ub(219, 5, 219);
        glVertex2f(1,-0.5);
    glEnd();
}

void ground(void)
{
    glBegin(GL_POLYGON);
        glColor3ub(60, 70, 127);
        glVertex2f(1.0f, -0.5f);
        glColor3ub(60, 70, 104);
        glVertex2f(-1.0f, -0.5f);
        glColor3ub(60, 70, 90);
        glVertex2f(-1.0f, -1.0f);
        glColor3ub(60, 70, 217);
        glVertex2f(1.0f, -1.0f);
    glEnd();
}

void drawJerryLowerBody(float x, float y, float heigth, float width)
{
    //Desenha a calça
    glColor3ub(95,158,160); //Cor azul da calça
    drawRectangle(x, y, heigth, width);   
    drawRectangle(x+0.04, y, heigth, width);
    drawRectangle(x, y+heigth, 0.02f, width+width+0.01);

    //Desenha os sapatos
    /**
     * @todo Desenhar os sapatos dele... mas como?
     */
}

void drawJerryUpperBody(float x, float y, float heigth, float width)
{   
    glColor3ub(53, 78, 50); //Cor verde da Blusa
    drawRectangle(x, y, heigth, width); //Base da blusa
    drawRectangle(x+width, y+heigth-0.05f, 0.05f, 0.03f); //Desenha manga direita
    drawRectangle(x-0.03f, y+heigth-0.05f, 0.05f, 0.03f);//Desenha manga esquerda
   
    /** Arredonda a borda superior da blusa */
    drawCircle(x+(width/2.0), y+heigth, 0.065f, 100);

    /** Detalhes da blusa */
    glColor3ub(189, 89, 40); // Cor da Primeira Linha (Laranja)
    drawRectangle(x, y+heigth-0.03f, 0.01f, width); //Cria o primeiro retângulo da blusa
    glColor3ub(209, 177, 122);//Cor da segunda Linha (laranja clara)
    drawRectangle(x, y+heigth-0.04f, 0.01f, width); //Cria o segundo retângulo da blusa
    drawLine(x+width, y+heigth-0.05f, 0.04f, 0.1f);
    drawLine(x, y+heigth-0.05, 0.04f, 0.1f);

    // Desenha o pescoço
    glColor3ub(255, 210, 128);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + width / 2.0f, y + heigth+0.02f); // Vértice central na parte superior da blusa
        glVertex2f(x + (width / 2.0f) - 0.02f, y + heigth + 0.05f); // Vértice esquerdo acima da blusa
        glVertex2f(x + (width / 2.0f) + 0.02f, y + heigth + 0.05f); // Vértice direito acima da blusa
    glEnd();

    drawEllipse(x + width/2.0f, y+heigth+0.098f, 0.04f, 0.05f, 100);
    glColor3ub(0,0,0);
    drawEllipseOutLine(x + width/2.0f, y+heigth+0.098f, 0.04f, 0.05f, 100);
}
