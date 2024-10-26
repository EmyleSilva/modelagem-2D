#include "modelagem.h"

//Posição Inicial da nave 
float sShipX = -8.0f;
float sShipY = 0.0f;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800); 
    glutInitWindowPosition (00, 00); 
    glutCreateWindow (argv[1]); 
    glClearColor(0.0118f, 0.9412f, 0.6039f, 1.0f);
    glOrtho (-10, 10,-10, 10, -1 ,1);
    glutDisplayFunc(display);
    glutSpecialFunc(Special_keyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    sky();
    ground();
    road();
    clound(0.0f, 4.5f, 1.0f);
    clound(-3.0f, 7.0f, 1.0f);
    clound(-5.0, 5.0, 0.65);
    sun(-7.0f, 7);
    tree_circle(-8.0f, -5.0f, 3.0f, 1.0f);
    tree_triangle(8.0f, -5.0f, 3.0f, 1.0f);
    tree_triangle(-9.0f, -9.0f, 3.0f, 1.0f);
    tree_circle(-5.0f, -7.0f, 5.0f, 1.0f);
    target();
    spaceship();
    clound(5.0f, 7.0f, 1.5f);
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

void drawTriangle(float x, float y, float width, float heigth)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y+heigth);
        glVertex2f(x-(width/2), y);
        glVertex2f(x+(width/2), y);
    glEnd();
}

void drawHorizontalLine(float x, float y, float length, float width)
{
    glLineWidth(width);

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x+length, y);
    glEnd();
}

void drawVerticalLine(float x, float y, float heigth, float width)
{
    glLineWidth(width);

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y+heigth);
    glEnd();
}

void sky(void)
{
    glBegin(GL_POLYGON);
        glColor3ub(0, 150, 168);
        glVertex2f(-10,-5);
        glColor3ub(0, 183, 158);
        glVertex2f(-10,10);
        glColor3ub(0, 183, 216);
        glVertex2f(10,10);
        glColor3ub(0, 254, 255);
        glVertex2f(10,-5);
    glEnd();
}

void ground(void)
{
    glBegin(GL_POLYGON);
        glColor3ub(16, 71, 18);       
        glVertex2f(10.0f, -5.0f);
        glColor3ub(252, 251, 218);
        glVertex2f(-10.0f, -5.0f);
        glColor3ub(16, 104, 18); 
        glVertex2f(-10.0f, -10.0f);
        glColor3ub(0, 71, 0);
        glVertex2f(10.0f, -10.0f);
    glEnd();
}

void road(void)
{
    //Desenha a parte principal da estrada
    glColor3ub(15, 14, 14);
    
    glBegin(GL_POLYGON);
        glVertex2f(-3.0, -10.0);
        glVertex2f(3.0, -10.0);
        glVertex2f(1.0, -5);
        glVertex2f(-1.0, -5.0);
    glEnd();

    //Desenha as faixas brancas da estrada
    glColor3ub(255, 255, 255);
    drawRectangle(0.0, -9.8, 0.75, 0.1);
    drawRectangle(0.01, -8.8, 0.75, 0.1);
    drawRectangle(0.02, -7.8, 0.75, 0.1);
    drawRectangle(0.03, -6.8, 0.75, 0.1);
    drawRectangle(0.04, -5.8, 0.75, 0.1);
}

void tree_circle(float x, float y, float heigth, float width)
{
    //Desenha o troco da arvore
    glColor3ub(54, 0, 0); //Cor marrom
    drawRectangle(x, y, heigth, width);
    //Desenha a folhagem da arvore
    glColor3ub(36, 80, 36); //Cor Verde
    drawCircle(x+0.5f, y+heigth, 1.0f, 100);
}

void tree_triangle(float x, float y, float heigth, float width)
{
    //Desenha o troco da arvore
    glColor3ub(54, 0, 0);
    drawRectangle(x, y, heigth, width);
    //Desenha a folhagem da arvore
    glColor3ub(36, 80, 36);
    drawTriangle(x+0.5f, y+heigth, width+2.0, 3.0f);
}

void clound(float x, float y, float radius)
{
    glColor3ub(255, 240, 250);
    //Circulo esquerdo
    drawCircle(x, y, radius, 100);
    //Circulo do meio
    x += radius + 0.5;
    drawCircle(x, y, radius+0.3, 100);
    //Circulo da direita
    x+= radius + 0.5;
    drawCircle(x, y, radius, 100);
}

void sun(float cx, float cy)
{
    glColor3ub(213, 173, 14);

    float angle = 0.0;
    float x = 0.0;
    float y = 0.0;
    float r = 3.0f;
    int green_level = 160;

    //Desenha o sol, variando as cores do laranja
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 100; i++, green_level+=0.5)
        {
            glColor3ub(244, (int)green_level, 33);
            float angle = 2.0f * PI * (float)i / (float)100;
            x = r * cos(angle);
            y = r * sin(angle);
            glVertex2f(x + cx, y + cy);
        }
    glEnd();
}

void spaceship(void)
{
    //Desenha o corpo principal da nave
    glColor3ub(59, 58, 58);
    drawRectangle(sShipX, sShipY, 2.0f, 6.0f);
    
    //Desenha a ponta da nave
    glBegin(GL_TRIANGLES);
        glVertex2f(sShipX+8.0f, sShipY+1.0f);
        glVertex2f(sShipX+6.0f, sShipY);
        glVertex2f(sShipX+6.0f, sShipY+2.0f);
    glEnd();

    drawCircle(sShipX+6.0f, sShipY+1.0, 1.0f, 100);
    
    //Desenha a cauda de nave
    glBegin(GL_POLYGON);
        glVertex2f(sShipX+1.0, sShipY+2.0f); 
        glVertex2f(sShipX-0.5f, sShipY+2.0f); 
        glVertex2f(sShipX-0.5f, sShipY+4.0f); 
        glVertex2f(sShipX, sShipY+4.0f);
    glEnd();

    //Desenha a asa
    glBegin(GL_POLYGON);
        glVertex2f(sShipX+4.0f, sShipY+2.0f);
        glVertex2f(sShipX+2.0f, sShipY+2.0f);
        glVertex2f(sShipX+2.0f, sShipY+5.0f);
        glVertex2f(sShipX+3.0f, sShipY+5.0f);
    glEnd();

    //Desenha os detalhes no corpo da nave
    glColor3ub(103, 103, 103);
    drawHorizontalLine(sShipX+0.5f, sShipY+0.5f, 4.0f, 1.0f);
    drawHorizontalLine(sShipX+0.5f, sShipY+1.5f, 4.0f, 1.0f);
    
    for (double i = 0.5f; i < 5; i+=1.0)
        drawVerticalLine(sShipX+i, sShipY+0.5f, 1.0f, 1.0f);  

    glColor3ub(103, 103, 103);
    drawEllipse(sShipX+6.0f, sShipY+1.0f, 0.4f, 0.75f, 100);
}

void target()
{
    //Desenha os pés 
    glColor3ub(5, 5, 5);
    drawEllipse(5.0, -7.0, 1.0, 0.1, 100);

    //Desenha o short
    glColor3ub(207, 78, 5);
    drawRectangle(4.3, -7.0, 0.5, 1.5);

    //Desenha o corpo
    glColor3ub(207, 65, 5);
    drawEllipse(5.05, -5.8, 1.0, 1.0, 100);

    //Desenha a cabeça
    glColor3ub(207, 78, 5);
    drawCircle(5.0, -4.8, 1.0, 100);

    //Desenha as linhas da blusa
    glColor3ub(0, 0, 0);
    drawVerticalLine(5.05, -6.8, 0.9, 1.0);
    drawVerticalLine(4.3, -6.5, 0.6, 1.0);
    drawVerticalLine(5.8, -6.5, 0.6, 1.0);

    //Desenha as mãos
    glColor3ub(54, 25, 5);
    drawCircle(4.3, -6.3, 0.2, 100);
    drawCircle(5.8, -6.3, 0.2, 100);

    //Desenha a parte marrom do capuz
    drawEllipse(5.0, -4.8, 0.6, 0.5, 100);

    //Desenha a cabeça
    glColor3ub(224, 155, 77);
    drawEllipse(5.0, -4.8, 0.4, 0.5, 100);
    
    //Desenha os olhos
    glColor3ub(255, 255, 255);
    drawEllipse(4.8, -4.7, 0.2, 0.2, 100);
    drawEllipse(5.2, -4.7, 0.2, 0.2, 100);
    glPointSize(3.0);
    glColor3ub(0, 0, 0);
    glBegin(GL_POINTS);
        glVertex2f(4.9, -4.7);
        glVertex2f(5.1, -4.7);
    glEnd();
}

void Special_keyboard(GLint tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_UP: //Movimenta para cima
        sShipY+=0.5;
        break;
    case GLUT_KEY_DOWN: //Movimenta para baixo
        sShipY-=0.5;
        break;
    case GLUT_KEY_LEFT: //Movimenta para a esquerda
        sShipX-=0.5;
        break;
    case GLUT_KEY_RIGHT: //Movimenta para a direita
        sShipX+=0.5;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Tecla ESC
    case 'e':
    case 'E':
        printf("\nPrograma Finalizado!\n");
        exit(0);
        break;
    }
}