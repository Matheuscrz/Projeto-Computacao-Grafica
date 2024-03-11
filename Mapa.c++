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

vector<Ponto3D> pontos;

void desenhaMapa() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Habilita limpeza do buffer de profundidade
    glColor3f(1.0, 1.0, 1.0); // Cor branca
    glBegin(GL_LINES);
    for (size_t i = 0; i < pontos.size() - 1; ++i) {
        glVertex3f(pontos[i].x, pontos[i].y, pontos[i].z);
        glVertex3f(pontos[i + 1].x, pontos[i + 1].y, pontos[i + 1].z);
    }
    glEnd();
    glFlush();
}

void leCoordenadasDoMapa(const string& nomeArquivo) {
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

void inicializaOpenGL(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Habilita o buffer de profundidade
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mapa 3D");
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Ajusta a perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Ajusta a posição da câmera para melhor visualizar o mapa
    gluLookAt(5.0, 10.0, 20.0, // Posição da câmera
              5.0, 5.0, 0.0,  // Para onde a câmera aponta
              0.0, 1.0, 0.0); // Vetor Up
}

int main(int argc, char **argv) {
    leCoordenadasDoMapa("mapa.txt"); // Certifique-se que o arquivo existe e está no formato correto
    inicializaOpenGL(argc, argv);
    glutDisplayFunc(desenhaMapa);
    glutMainLoop();
    return 0;
}
