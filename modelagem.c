#include "modelagem.h"

Spaceship sShip; //Variavel usada para guardar valores referentes a nave espacial
Cartman cartman; //Variavel usada para controlar os angulos de rotação do cartman

//RGB para controlar a cor da nave
int R = 0, G = 0, B = 0; 

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (1024, 1024); 
    glutInitWindowPosition (00, 00); 
    glutCreateWindow (argv[1]); 
    glClearColor(0.0118f, 0.9412f, 0.6039f, 1.0f);
    glOrtho (-10, 10,-10, 10, -1 ,1);
    glutDisplayFunc(display);
    glutSpecialFunc(Special_keyboard);
    glutKeyboardFunc(keyboard);
    initSship(); //Inicializa os valores da nave
    initCartman(); //Inicializa os valores do cartman
    glutMainLoop();
    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    sky();
    mountains();

    tree(2.0, -2.0, 175);
    tree(-1.0, 0.0, 216);
    tree(15.0, 0.0, 148);
    tree(11.0,-2.5, 180);

    ground();
    road();

    cloud(0.5, 0.0, 5.5);
    cloud(0.7, -5.0, 6.0);
    cloud(0.3, -8.5, 4.0);
    cloud(1.0, -6.0, 6.0);
    cloud(0.2, 4.5, 4.0); 
    cloud(0.6, 0.0, 8.0);

    //Desenha uma nuvem rotacionada
    glPushMatrix();
        glRotatef(40, 0.0, 0.0, 1.0);
        cloud(0.6, 2.0, 9.0);
    glPopMatrix();

    sun(-9.0f, 9.0);

    signpost();
    
    printf("grau perna: %.2f | grau torso: %.2f | grau cabeça: %.2f\n\n", cartman.legs, cartman.torso, cartman.head);
    draw_cartman();
    
    target();

    glPushMatrix();
            glTranslatef(sShip.tX, sShip.tY, 0.0); 
            glScalef(sShip.scaleX, sShip.scaleY, 1.0);
            glTranslatef(-sShip.tX, -sShip.tY, 0.0);
            spaceship(); 
    glPopMatrix();

    cloud(1.5, 5.0, 8.0);
    glutSwapBuffers();
}

void drawRectangle(float x, float y, float height, float width)
{
    glBegin(GL_POLYGON);
        glVertex2f(x, y); //Vertice da ponta inferior esquerda
        glVertex2f(x + width, y); //Ponta inferior direita
        glVertex2f(x + width, y + height); //Ponta superior direita
        glVertex2f(x, y + height); //Ponta superior esquerda
    glEnd();
}

void drawCircle(float cx, float cy, float r, int numTriangles)
{
    float angle = 0.0; //Angulo (atual) calculado para cada ponto do circulo
    float x = 0.0;
    float y = 0.0;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= numTriangles; i++)
        {
            float angle = 2.0f * PI * (float)i / (float)numTriangles; //Calcula o angulo atual (varia de 0 a 360 graus)
            x = r * cos(angle); //Calcula a coordenada x de acordo com o angulo (multiplica por r para manter a distancia correta do centro)
            y = r * sin(angle); //Calcula a coordenada y de acordo com o angulo
            glVertex2f(x + cx, y + cy); //Desenha o vertice
        }
    glEnd();
}

/** 
 * Difere da função drawCircle apenas pelo calculo de x e y, que possuem raios diferentes (rx e ry)
 */
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

void drawEllipseRotate(float cx, float cy, float rx, float ry, float angle)
{
    float x = 0.0;
    float y = 0.0;
    float rot_x = 0.0, rot_y = 0.0; //Valores de x e y apos rotação
    float rad_angle = angle * (PI / 180); //Converte o angulo informado para radiano
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 100; i++, R-= 1.0, G-=1.0, B-=1.0)
        {
            float angle = 2.0f * PI * (float)i / (float)100;
            x = rx * cos(angle);
            y = ry * sin(angle);

            //Aplica a rotacao
            rot_x = cx + (x * cos(rad_angle) - y * sin(rad_angle)); //Formula de rotação no plano cartesiano
            rot_y = cy + (x * sin(rad_angle) - y * cos(rad_angle)); //Formula de rotação no plano cartesiano


            glColor3ub(R, G, B);
            glVertex2f(rot_x, rot_y); //Desenha o vertice já rotacionado
        }
    glEnd();
}

void drawTriangle(float x, float y, float width, float heigth)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y); //Vertice inferior esquerdo
        glVertex2f(x+width, y); //Vertice inferior direito
        glVertex2f(x+(width/2), y+heigth); //Vertice superior
    glEnd();
}

void drawVerticalLine(float x, float y, float heigth, float width)
{
    glLineWidth(width);

    glBegin(GL_LINES);
        glVertex2f(x, y); //Vertice inferior
        glVertex2f(x, y+heigth); //Vertice superior
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

void mountains()
{
    //Desenha montanhas da extremidade
    glColor3ub(28, 72, 20);
    drawEllipse(-7.0, -5.0, 6.0, 7.0, 100); //Montanha da esquerda
    drawTriangle(-11.7, -1.0, 9, 5); //Ponta da montanha esquerda
    drawEllipse(7.0, -5.0, 6.0, 7.0, 100); //Montanha da direita
    drawTriangle(3.0, -1.0, 10, 6); //Ponta da montanha da direita

    //Desenha montanha do centro
    glColor3ub(28, 89, 20);
    drawEllipse(0.0, -5.0, 7.0, 9.0, 100);

    //Desenha a neve no topo da montanha esquerda
    glColor3ub(255, 255, 255);
    drawTriangle(-9.15, 1.9171589835926, 4.0, 2.09);
    drawCircle(-8.6, 1.91, 0.5, 100);
    drawCircle(-8.0, 1.91, 0.5, 100);
    drawCircle(-7.4, 1.91, 0.5, 100);
    drawCircle(-7.0, 1.91, 0.5, 100);
    drawCircle(-6.4, 1.91, 0.5, 100);
    drawCircle(-5.8, 1.91, 0.5, 100);

    //Desenha a neve no topo da montanha direita
    drawTriangle(6.0, 3.0, 4.0, 2.09);
    drawCircle(6.5, 3.0, 0.5, 100);
    drawCircle(6.8, 3.0, 0.5, 100);
    drawCircle(7.1, 3.0, 0.5, 100);
    drawCircle(7.9, 3.0, 0.5, 100);
    drawCircle(8.1, 3.0, 0.5, 100);
    drawCircle(8.8, 3.0, 0.5, 100);
    drawCircle(9.5, 3.0, 0.5, 100);

    //Desenha a neve no topo da montanha central
    drawEllipse(0.0, 3.0, 3.5, 1.5, 100);
    drawCircle(-3.5, 2.2, 1.0, 100);
    drawCircle(-2.5, 2.2, 1.0, 100);
    drawCircle(-1.5, 1.5, 1.0, 100);
    drawCircle(0.0, 2.0, 1.0, 100);
    drawCircle(2.0, 2.0, 1.0, 100);
    drawCircle(3.0, 2.5, 1.0, 100);
}

void ground(void)
{
    glColor3ub(255, 255, 255);
    drawEllipse(8.0, -9.0, 4.0, 4.0, 100);
    drawEllipse(4.0, -9.0, 4.0, 4.0, 100);
    drawEllipse(0.0, -9.0, 4.0, 4.0, 100);
    drawEllipse(-4.0, -9.0, 4.0, 4.0, 100);
    drawEllipse(-8.0, -9.0, 4.0, 4.0, 100);
}

void road(void)
{
    //Desenha a estrada
    glColor3ub(15, 14, 14); //Cinza escuro
    drawRectangle(-10.0, -10.0, 2.0, 20.0);
}

void tree_model(int greenLevel)
{
    //Desenha triangulos para formar um pinheiro
    //O valor do verde incrementa sempre que um novo vertice é desenhado
    //para que as cores não fiquem tão sólidas

    //Os poligonos são desenhado de baixo pra cima
    glColor3ub(43, greenLevel, 0);

    glBegin(GL_POLYGON);
        glVertex2f(-6.08, -2.64);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-10.42, -5.82);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-1.28, -5.88);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-6.0, -1.82);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-10.32, -4.86);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-2.0, -4.82);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-6.0, -1.0);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-10.0, -4.0);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-2.64, -4.0);
    glEnd();
    
    glBegin(GL_POLYGON);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-9.46, -3.04);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-3.0, -3.0);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-6.06, 0.0);
    glEnd();
    
    glBegin(GL_POLYGON);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-9.0, -2.0);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-3.32, -1.92);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-6.0, 1.24);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-8.52, -1.1);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-3.6, -1.02);
        glColor3ub(43, ++greenLevel, 0);
        glVertex2f(-6.02, 2.28);
    glEnd();
}

void tree(float x, float y, int greenLevel)
{
    glPushMatrix();
        glTranslatef(x, y, 0.0);
        tree_model(greenLevel);
    glPopMatrix();
}

void cloud_model()
{
    float x = 0.0;
    glColor3ub(255, 240, 250);
    //Circulo esquerdo
    drawCircle(x, 0.0, 1.0, 100);
    //Circulo do meio
    x += 1.0 + 0.5;
    drawCircle(x, 0.0, 1.3, 100);
    //Circulo da direita
    x+= 1.0 + 0.5;
    drawCircle(x, 0.0, 1.0, 100);
}

void cloud(float scale, float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, 1.0);
    cloud_model();
    glPopMatrix();
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
    //Desenha os detalhes vermelhos das extremidades
    glColor3ub(124, 17, 8);
    glLineWidth(4.0);
    glBegin(GL_LINES);
        //Linha da esquerda
        glVertex2f(sShip.tX, sShip.tY - 2.3); //Vertice da base
        glVertex2f(sShip.tX - 3.5, sShip.tY - 0.3); //Vertice mais alto
        //Linha da direita
        glVertex2f(sShip.tX, sShip.tY - 2.3); //Vertice da base
        glVertex2f(sShip.tX + 3.5, sShip.tY - 0.3); //Vertice mais alto
    glEnd();

    // //Desenha a parte inferior da nave
    R = 170, G = 170, B = 170;
    glColor3ub(R, G, B);
    drawEllipseRotate(sShip.tX, sShip.tY - 2.3, 2.0, 0.5, 0);
    drawRectangle(sShip.tX - 1.0, sShip.tY - 2, 3.0, 2.0);

    // //Desenha as extremidades do corpo da nave
    R = 154, G = 154, B = 154;
    glColor3ub(R, R, B); 
    drawEllipseRotate(sShip.tX - 4.3, sShip.tY - 0.7, 1.0, 1.1, 30); //Extremidade esquerda
    R = 154, G = 154, B = 154;
    glColor3ub(R, G, B);
    drawEllipseRotate(sShip.tX + 4.4, sShip.tY - 0.7, 1.0, 1.1, -30); //Extremidade direita

    // //Desenha o corpo principal da nave
    R = 154, G = 154, B = 154;
    glColor3ub(R, G, B);
    float angle = 0.0; 
    float x = 0.0, y = 0.0;
    float rx = 4.0, ry = 0.8;
    float cx = sShip.tX, cy = sShip.tY; 
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 100; i++, R-= 1, G-= 1, B-=1)
        {
            glColor3ub(R, G, B);
            angle = 2.0f * PI * (float)i / (float)100;
            x = rx * cos(angle);
            y = ry * sin(angle);
            glVertex2f(x + cx, y + cy);
        }
    glEnd();

    //Desenha a 'antena' da nave
    glColor3ub(170, 170, 170); //Tom mais claro de cinza
    drawEllipse(sShip.tX, sShip.tY + 2.1, 0.2, 0.1, 100);
    glColor3ub(124, 17, 8); //POnta vermelha
    drawCircle(sShip.tX, sShip.tY + 2.2, 0.1, 100);

    //Desenha a parte superior (cabine) da nave
    R = 240, G = 240, B = 240;
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(sShip.tX - 2.0, sShip.tY + 0.7);
        glColor3ub(R-10, G-10, B-10);
        glVertex2f(sShip.tX - 1.02, sShip.tY + 1.94);
        glColor3ub(R-20, G-20, B-20);
        glVertex2f(sShip.tX + 1.02, sShip.tY + 1.94);
        glColor3ub(R-20, G-20, B-20);
        glVertex2f(sShip.tX + 2.0, sShip.tY + 0.7);
    glEnd();

    //Desenha a parte mais interna da cabine
    R = 170, G = 170, B = 170;
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(sShip.tX - 2.0, sShip.tY + 0.7);
        glColor3ub(R-10, G-10, B-10);
        glVertex2f(sShip.tX - 0.98, sShip.tY + 1.95);
        glColor3ub(R-20, G-20, B-20);
        glVertex2f(sShip.tX + 0.91, sShip.tY + 1.85);
        glColor3ub(R-30, G-30, B-30);
        glVertex2f(sShip.tX + 2.0, sShip.tY + 0.7);
    glEnd();

    //Desenha detalhe vermelho no centro 
    glColor3ub(124, 17, 8);
    drawVerticalLine(sShip.tX, sShip.tY - 2, 1.2, 2.0);
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

void draw_cartman()
{
    glPushMatrix(); //ESCOPO 1 (pernas)

        glScalef(1.4, 1.0, 1.0);
        glTranslatef(0.0, -7.0, 0.0);
        glRotatef(cartman.legs, 0.0, 0.0, 1.0); 
        glTranslatef(0.0, 7.0, 0.0);
        /*** PERNA */
        //Desenha os sapatos
        glColor3ub(5, 5, 5);
        drawEllipse(0.0, -7.0, 1.0, 0.1, 100); //Em x, vai de -1 a 1, em y, começa em -7

        //Desenha o short
        glColor3ub(54, 25, 5);
        drawRectangle(-0.8, -7.0, 0.5, 1.6);

        glPushMatrix(); //ESCOPO 2 (tronco)
            glTranslatef(0.0,  -6.1, 0.0);
            glRotatef(cartman.torso, 0.0, 0.0, 1.0);
            glTranslatef(0.0, 6.1, 0.0);
            //Desenha a blusa
            glColor3ub(175, 2, 19);
            drawEllipse(0.0, -6.1, 1.05, 0.7, 100);

            //Desenha as mãos
            glColor3ub(225, 217, 27);
            drawCircle(-1.07, -6.1, 0.2, 100);
            drawCircle(1.07, -6.1, 0.2, 100);

            //Desenha a linha vertical da camisa e os botões
            glColor3ub(0, 0, 0);
            drawVerticalLine(0.0, -6.8, 0.7, 1.0);

            glPointSize(3.0);
            glBegin(GL_POINTS);
                glVertex2f(-0.1, -6.6);
                glVertex2f(-0.1, -6.4);
                glVertex2f(-0.1, -6.2);
            glEnd();
            
            glPushMatrix(); //ESCOPO 3 (cabeça)
                glTranslatef(0.0, -5.0, 0.0);
                glRotatef(cartman.head, 0.0, 0.0, 1.0);
                glTranslatef(0.0, 5.0, 0.0);
                //Desenha o chapéu
                glColor3ub(9, 171, 144);
                drawCircle(0.0, -5.0, 1.0, 100);

                //Desenha o rosto
                glColor3ub(224, 155, 77);
                drawEllipse(0.0, -5.3, 1.0, 0.8, 100);

                //Corrige o espaço do chapéu em cima do rosto
                glColor3ub(9, 171, 144);
                drawEllipse(0.0, -4.6, 0.5, 0.2, 100);
                drawRectangle(-1.0, -5.1, 0.5, 2.0);

                //Desenha os detalhes amarelos do chapéu
                glColor3ub(225, 217, 27);
                drawRectangle(-1.0, -5.2, 0.1, 2.0);
                drawEllipse(0.0, -4.0, 0.2, 0.1, 100); //Y vai até -4.0

                //Desenha os olhos
                glColor3ub(255, 255, 255);
                drawEllipse(-0.2, -5.4, 0.2, 0.25, 100);
                drawEllipse(0.2, -5.4, 0.2, 0.25, 100);

                glColor3ub(0,0,0); 
                glPointSize(3.0);   
                glBegin(GL_POINTS);
                    glVertex2f(-0.1, -5.4);
                    glVertex2f(0.2, -5.4);
                glEnd();

                //Desenha a boca
                glLineWidth(1.2);
                glBegin(GL_LINES);
                    glVertex2f(-0.1, -5.9);
                    glVertex2f(0.1, -5.9);

                    glVertex2f(-0.1, -5.9);
                    glVertex2f(-0.2, -5.85);
                glEnd();
            glPopMatrix(); // ESCOPO 3
        glPopMatrix(); // ESCOPO 2
    glPopMatrix(); //ESCOPO 1
}

void signpost()
{
    //Desenha a base da blaca
    glColor3ub(59, 26, 0); //Marrom
    drawRectangle(-8.0, -6.5, 4.0, 0.2);

    //Desenha o fundo da placa 
    glColor3ub(233, 213, 0); //Amarelo
    glBegin(GL_POLYGON);
        glVertex2f(-7.8968252797266,-3.5245926902277);
        glVertex2f(-6.3304762066716,-2.24870456646);
        glVertex2f(-7.9196072448239,-1.1287455490955);
        glVertex2f(-9.4936037016604,-2.3243774730386);
    glEnd();

    //Desenha a borda interna da placa
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(-7.8976669178103,-3.3710389657406); //Vertice inferior
        glVertex2f(-6.4891131131697,-2.2535757273554); //Vertice da direita
        glVertex2f(-6.4891131131697,-2.2535757273554); //Vertice da direita
        glVertex2f(-7.9140105334379,-1.2521000036908);//vertice superior
        glVertex2f(-7.9140105334379,-1.2521000036908);//vertice superior
        glVertex2f(-9.3201263056903,-2.3190998851751);//vertice da esquerda
        glVertex2f(-9.3201263056903,-2.3190998851751);//vertice da esquerda
        glVertex2f(-7.8976669178103,-3.3710389657406); //vertice inferior
    glEnd();

    //Desenha o boneco da placa
    drawCircle(-8.35, -1.75, 0.15, 100); //Desenha a cabeça

    //A partir daqui desenha o corpo
    glBegin(GL_POLYGON);
       glVertex2f(-8.2341869969138, -1.9156627497147);
       glVertex2f(-8.3686359597953, -2.266964878534);
       glVertex2f(-8.2428611235513, -2.3190096383591);
       glVertex2f(-8.1864793004075, -2.123841789015);
       glVertex2f(-8.0607044641636, -2.0240893326837);
       glVertex2f(-7.8, -2);
       glVertex2f(-7.8872219314133, -1.911325686396);
    glEnd();

    glBegin(GL_POLYGON);
       glVertex2f(-8.1864793004075, -2.123841789015);
       glVertex2f(-8.0607044641636, -2.0240893326837);
       glVertex2f(-7.8828848680946, -2.3016613850841);
       glVertex2f(-8.0390191475698, -2.3840655881404);
    glEnd();

    glBegin(GL_POLYGON);
       glVertex2f(-8.0390191475698, -2.3840655881404);
       glVertex2f(-7.8828848680946, -2.3016613850841);
       glVertex2f(-7.7274797265965, -2.4464267531352);
       glVertex2f(-7.8077198825834, -2.5339614687573);
       glVertex2f(-7.9390219560166, -2.4172485145945);
       glVertex2f(-7.9609056349222, -2.6069070651091);
       glVertex2f(-8.0739713092674, -2.5959652256563);
    glEnd();
    
    //Desenha as pernas 
    drawEllipse(-8.0255710766493, -2.6609328393438, 0.04, 0.2, 100);
    drawEllipse(-7.7744119659502,-2.4172710155313, 0.04, 0.2, 100);
}

void initSship()
{
    sShip.tX = 0.0;
    sShip.tY = 0.0;
    sShip.scaleX = 1.0;
    sShip.scaleY = 1.0; 
}

void initCartman()
{
    cartman.head = 0.0;
    cartman.torso = 0.0;
    cartman.legs = 0.0;
}

void Special_keyboard(GLint tecla, int x, int y)
{
    switch (tecla)
    {
        case GLUT_KEY_UP:   //Movimenta para cima
            sShip.tY+=0.5;
            break;
        case GLUT_KEY_DOWN: //Movimenta para baixo
            sShip.tY-=0.5;
            break;
        case GLUT_KEY_LEFT: //Movimenta para a esquerda
            sShip.tX-=0.5;
            break;
        case GLUT_KEY_RIGHT: //Movimenta para a direita
            sShip.tX+=0.5;
            break;
        case GLUT_KEY_PAGE_UP: //Aumenta o tamanho do objeto
            sShip.scaleX+=0.01;
            sShip.scaleY+=0.01;
            break;
        case GLUT_KEY_PAGE_DOWN: //Diminui o tamanho do objeto
            sShip.scaleX-=0.01;
            sShip.scaleY-=0.01;
            //Quando as variaveis de escala atingem valores negativos, a nave é espelhada
            //A verificação abaixo garante que os numeros variem apenas entre valores positivos e 0
            if(sShip.scaleX < 0 && sShip.scaleY < 0) 
                sShip.scaleX = sShip.scaleY = 0;
            printf("escala x: %.2f | escala y: %.2f | x: %.2f | y: %.2f\n", sShip.scaleX, sShip.scaleY, sShip.tX, sShip.tY);
            break;
        case GLUT_KEY_F1: 
            cartman.legs += 1.0;
            break;
        case GLUT_KEY_F2:
            cartman.legs -= 1.0;
            break;
        case GLUT_KEY_F3:
            cartman.torso += 1.0;
            break;
        case GLUT_KEY_F4:
            cartman.torso -= 1.0;
            break;
        case GLUT_KEY_F5:
            cartman.head += 1.0;
            break;
        case GLUT_KEY_F6:
            cartman.head -= 1.0;
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