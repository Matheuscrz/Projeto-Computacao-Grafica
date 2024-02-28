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

struct Point {
    float x, y;
};

std::vector<Point> mapPoints; // Armazena os pontos do mapa

void loadMap(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    Point point;
    while(file >> point.x >> point.y >> point.z){
        mapPoints.push_back(point);
    }
    file.close();
}

void drawMap(){
    glBegin(GL_LINES);
    for(size_t = 0; i < mapPoints.size(); i++){
        size_t next = (i+1) % mapPoints.size();
        glVertex3f(mapPoints[i].x, mapPoints[i].y, mapPoints[i].z);
        glVertex3f(mapPoints[next].x, mapPoints[next].y, mapPoints[next].z);
    }
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Cor branca
    drawMap();
    glSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 500.0); // Adiciona a perspectiva
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Posiciona a câmera
}

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "Uso: " << argv[0] << " <arquivo do mapa>" << std::endl;
        return EXIT_FAILURE;
    }
    gluInit(&argc, argv);
    gluInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Mapa");
    loadMap(argv[1]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(0.0, 0.0, 0.0, 1.0); // Cor de fundo preta
    glutMainLoop();
    return EXIT_SUCCESS;
}