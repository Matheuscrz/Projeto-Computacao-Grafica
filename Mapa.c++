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

struct Vertex {
    float x, y, z;
};

struct Line {
    float v1, v2;
};

std::vector<Vertex> vertices; 
std::vector<Line> lines;

void loadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (type == "l") {
            Line line;
            iss >> line.v1 >> line.v2;
            lines.push_back(line);
        }
    }

    file.close();
}

void drawMap() {
    glBegin(GL_LINES);
    for (const Line& line : lines) {
        const Vertex& v1 = vertices[line.v1 - 1];
        const Vertex& v2 = vertices[line.v2 - 1];
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // Cor branca
    // glEnable(GL_LIGHTING);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawMap();
    glutSwapBuffers();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Erro OpenGL: " << gluErrorString(error) << std::endl;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo do mapa>" << std::endl;
        return EXIT_FAILURE;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Mapa");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    loadMap(argv[1]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Cor de fundo preta
    glutMainLoop();

    return EXIT_SUCCESS;
}