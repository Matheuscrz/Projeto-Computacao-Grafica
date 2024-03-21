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
#include <GL/glut.h>
#include <fstream>
#include <iostream>

struct Pixel {
    unsigned char r, g, b;
};

Pixel* image;
int imageWidth, imageHeight;

void readPPM(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return;
    }

    std::string header;
    file >> header;
    if (header != "P6") {
        std::cerr << "Formato inválido" << std::endl;
        return;
    }

    file >> imageWidth >> imageHeight;

    int maxColor;
    file >> maxColor;

    file.ignore(256, '\n');

    image = new Pixel[imageWidth * imageHeight];

    file.read(reinterpret_cast<char*>(image), imageWidth * imageHeight * 3);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)imageWidth / (double)imageHeight, 0.1, 100.0);
    gluLookAt(imageWidth / 2.0, imageHeight, imageHeight / 2.0, imageWidth / 2.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    for (int y = 0; y < imageHeight - 1; ++y) {
        for (int x = 0; x < imageWidth - 1; ++x) {
            Pixel &p1 = image[y * imageWidth + x];
            Pixel &p2 = image[(y + 1) * imageWidth + x];
            Pixel &p3 = image[y * imageWidth + x + 1];
            Pixel &p4 = image[(y + 1) * imageWidth + x + 1];

            glColor3f(p1.r / 255.0f, p1.g / 255.0f, p1.b / 255.0f);
            glVertex3f(x, y, p1.r / 255.0f);

            glColor3f(p2.r / 255.0f, p2.g / 255.0f, p2.b / 255.0f);
            glVertex3f(x, y + 1, p2.r / 255.0f);

            glColor3f(p3.r / 255.0f, p3.g / 255.0f, p3.b / 255.0f);
            glVertex3f(x + 1, y, p3.r / 255.0f);

            glColor3f(p4.r / 255.0f, p4.g / 255.0f, p4.b / 255.0f);
            glVertex3f(x + 1, y + 1, p4.r / 255.0f);
        }
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    readPPM("mapa.ppm");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(imageWidth, imageHeight);
    glutCreateWindow("PPM Image");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    delete[] image;

    return 0;
}