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

struct Ponto3D {
    float x, y, z;
};

vector<vector<Ponto3D>> mapa;
int larguraMapa, alturaMapa;
float escala = 1.0; // Ajuste essa escala para aumentar o espaçamento entre os pontos

void desenhaMapa() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Removendo a definição de cor anterior e aplicando material cinza
    GLfloat corMaterial[] = {0.5, 0.5, 0.5, 1.0}; // Cor cinza
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);

    for (int i = 0; i < alturaMapa - 1; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < larguraMapa; j++) {
            glVertex3f(mapa[i][j].x * escala, mapa[i][j].y * escala, mapa[i][j].z);
            glVertex3f(mapa[i + 1][j].x * escala, mapa[i + 1][j].y * escala, mapa[i + 1][j].z);
        }
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void leCoordenadasDoMapa(string nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    string linha;
    float z;
    int y = 0;

    while (getline(arquivo, linha)) {
        vector<Ponto3D> linhaMapa;
        istringstream iss(linha);
        int x = 0;
        while (iss >> z) {
            linhaMapa.push_back(Ponto3D{static_cast<float>(x), static_cast<float>(y), z});
            x++;
        }
        mapa.push_back(linhaMapa);
        y++;
    }

    alturaMapa = mapa.size();
    larguraMapa = mapa[0].size();
}

void inicializaOpenGL(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mapa 3D - Visualização Melhorada");
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)800 / 600, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Ajuste a posição da câmera de acordo com o tamanho do seu mapa
    gluLookAt(alturaMapa * escala / 2.0, larguraMapa * escala / 2.0, alturaMapa, alturaMapa * escala / 2.0, larguraMapa * escala / 2.0, 0.0, 0.0, 0.0, 1.0);

    inicializaIluminacao();
}

int main(int argc, char** argv) {
    leCoordenadasDoMapa("mapa.txt");
    inicializaOpenGL(argc, argv);
    glutDisplayFunc(desenhaMapa);
    glutMainLoop();
    return 0;
}
