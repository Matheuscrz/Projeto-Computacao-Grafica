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

void desenhaMapa() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glColor3f(1.0, 1.0, 1.0);

    for (int i = 0; i < alturaMapa - 1; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < larguraMapa; j++) {
            glVertex3f(mapa[i][j].x, mapa[i][j].y, mapa[i][j].z);
            glVertex3f(mapa[i + 1][j].x, mapa[i + 1][j].y, mapa[i + 1][j].z);
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

void inicializaIluminacao() {
    GLfloat luzAmbiente[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luzDifusa[] = {0.7, 0.7, 0.7, 1.0}; // "cor"
    GLfloat luzEspecular[] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[] = {20.0, 20.0, 50.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void inicializaOpenGL(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mapa 3D com Iluminação");
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)800 / 600, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.0, 10.0, 10.0, 5.0, 5.0, 0.0, 0.0, 1.0, 0.0);

    inicializaIluminacao();
}

int main(int argc, char** argv) {
    leCoordenadasDoMapa("mapa.txt");
    inicializaOpenGL(argc, argv);
    glutDisplayFunc(desenhaMapa);
    glutMainLoop();
    return 0;
}
