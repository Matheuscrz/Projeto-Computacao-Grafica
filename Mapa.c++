/**
 * @file Mapa.c++
 * @author Matheus (matheuslimasof.eng@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 * Este programa lê um arquivo contendo as coordenadas de um mapa e desenha as linhas que o compõem.
 * Compilação: g++ -o Mapa Mapa.c++ -lGL -lGLU -lglut
 */

#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Estrutura que representa um ponto no espaço tridimensional
struct Ponto3D {
    float x, y, z;
};

// Vetor que armazena os pontos do mapa
vector<Ponto3D> pontos;

// Função que desenha o mapa
void desenhaMapa() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < pontos.size() - 1; i++) {
        glVertex3f(pontos[i].x, pontos[i].y, pontos[i].z);
        glVertex3f(pontos[i + 1].x, pontos[i + 1].y, pontos[i + 1].z);
    }
    glEnd();
    glFlush();
}

// Função que lê as coordenadas do mapa de um arquivo
void leCoordenadasDoMapa(string nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    string linha;
    int y = 0;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        float z;
        int x = 0;
        while (iss >> z) {
            Ponto3D p = {static_cast<float>(x), static_cast<float>(y), z};
            pontos.push_back(p);
            x++;
        }
        y++;
    }
}

// Função que inicializa o OpenGL
void inicializaOpenGL(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mapa 3D");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 10.0, 5.0, 5.0, 0.0, 0.0, 1.0, 0.0);
}

// Função principal
int main(int argc, char **argv) {
    leCoordenadasDoMapa("mapa.txt");
    inicializaOpenGL(argc, argv);
    gluLookAt(5.0, 10.0, 10.0, 5.0, 5.0, 0.0, 0.0, 1.0, 0.0);
    glutDisplayFunc(desenhaMapa);
    glutMainLoop();
    return 0;
}