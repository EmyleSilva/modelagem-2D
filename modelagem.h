#ifndef MODELAGEM_H_INCLUDED
#define MODELAGEM_H_INCLUDED

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.1415926

typedef struct spaceship
{
    GLfloat tX, tY; //Coordenadas do centro da nave
    GLfloat scaleX, scaleY; //Variaveis usadas para escalonar a nave em x e y
}Spaceship;

typedef struct cartman
{
    GLfloat legs, torso, head; //Angulo de rotação para TGs hierárquicas
}Cartman;

typedef struct object{
    GLfloat x, y; //Posição inicial do objeto
    GLfloat x_min, x_max, y_min, y_max; //Coordenadas do bounding box
}Object;

void display(void);
void Special_keyboard(GLint tecla, int x, int y);
void keyboard(unsigned char key, int x, int y);

/**
 * @brief Desenha um retangulo
 * 
 * @param x Posição x do primeiro vertice
 * @param y Posição y do primeiro vertice
 * @param heigth ALtura 
 * @param width Largura
 */
void drawRectangle(float x, float y, float heigth, float width);

/**
 * @brief Desenha um circulo
 * 
 * @param cx Posição x do ponto central do criculo
 * @param y Posição y do ponto central do circulo
 * @param r Raio do circulo 
 * @param numTriangles Quantidade de triangulos a ser usada para criar o circulo
 */
void drawCircle(float cx, float cy, float r, int numTriangles);

/**
 * @brief Desenha uma elipse 
 * 
 * @param cx Posição x do ponto central da elipse
 * @param y Posição y do ponto central da elipse
 * @param rx Raio da elipse no sentido horizontal
 * @param ry Raio da elipse no sentido vertical
 * @param numTriangles Quantidade de triangulos a ser usada para criar a elipse
 */
void drawEllipse(float cx, float cy, float rx, float ry, int numTriangles);

/**
 * @brief Desenha uma elipse rotacionada (A função também varia a cor dos vertices) 
 * Usada para desenhar extremidades da nave espacial.
 * 
 * @param cx Posição x do ponto central da elipse
 * @param y Posição y do ponto central da elipse
 * @param rx Raio da elipse no sentido horizontal
 * @param ry Raio da elipse no sentido vertical
 * @param angle Angulo de rotação da elipse
 */
void drawEllipseRotate(float cx, float cy, float rx, float ry, float angle);

/**
 * @brief Desenha um triangulo
 * 
 * @param x Posição x do primeiro vertice 
 * @param y Posição y do primeiro vertice
 * @param width Largura do triangulo
 * @param heigth Altura do triangulo
 */
void drawTriangle(float x, float y, float width, float heigth);

/**
 * @brief Desenha uma linha vertical
 * @param x Posição x do primeiro vertice
 * @param y Posição y do primeiro vertice
 * @param heigth Altura da linha
 * @param width Espessura da linha
 */
void drawVerticalLine(float x, float y, float heigth, float width);

/**
 * @brief Desenha o céu
 */
void sky(void);

/**
 * @brief Desenha as montanhas 
 */
void mountains(void);

/**
 * @brief Desenha o chão
 */
void ground(void);


/**
 * @brief Desenha um modelo de pinheiro com base no sistema de referência do objeto
 */
void tree_model(int greenLevel);

/**
 * @brief Desenha um pinheiro no universo
 * 
 * @param x Posição x do primeiro vertice
 * @param y Posição y do primeiro vertice
 * @param greenLevel Valor inicial do verde
 */
void tree(float x, float y, int greenLevel);

/**
 * @brief Desenha um modelo de uma nuvem com base no sistema de referência do objeto
 */
void cloud_model();

/**
 * @brief Desenha uma nuvem em um ponto do universo
 * @param scale Escala da nuvem
 * @param x Posição x do primeiro vertice
 * @param y Posição y do primeiro vertice
 */
void cloud(float scale, float x, float y);

/**
 * @brief Desenha o sol
 * @param x Posição x do centro da circunferencia
 * @param y Posição y do centro da circunferencia
 */
void sun(float x, float y);

/**
 * @brief Desenha a estrada
 */
void road(void);

/**
 * @brief Desenha a nave
 */
void spaceship(void);

/**
 * @brief Desenha o alvo
 */
void target(void);

/**
 * @brief Modela o projétil
 */
void draw_projectile(void);

/**
 * @brief Desenha o cartman
 */
void draw_cartman(void);

/**
 * @brief Desenha a placa amarela
 */
void signpost(void);

/**
 * @brief Inicializa as variaveis globais com os valores de estado inicial dos objetos (Nave, cartman, kenny e projétil)
 */
void init(void);

void Animate(int interacoes);
void animate_kenny(int);

void collision_detection(void);
#endif //MODELAGEM_H_INCLUDED