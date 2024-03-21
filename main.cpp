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

#include <iostream>
#include <fstream>
#include <GL/glut.h>

using namespace std;

struct Pixel {
    unsigned char r, g, b;
};

const int WIDTH = 800;
const int HEIGHT = 600;

Pixel *image;
int imageWidth, imageHeight;

void loadPPM(const char *filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        exit(1);
    }

    string format;
    file >> format;
    if (format != "P6") {
        cerr << "Formato de arquivo não suportado. Apenas P6 é suportado." << endl;
        exit(1);
    }

    file >> imageWidth >> imageHeight;
    int maxValue;
    file >> maxValue;
    file.ignore(1);

    image = new Pixel[imageWidth * imageHeight];

    file.read(reinterpret_cast<char *>(image), imageWidth * imageHeight * sizeof(Pixel));
    file.close();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor

    glBegin(GL_POINTS); // Desenhando os pontos
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            Pixel &p = image[y * imageWidth + x];
            float height = (p.r + p.g + p.b) / 3.0f; // Altura proporcional à média das cores
            glColor3ub(0, 0, 0);
            glVertex3f(x, y, height); // Definindo a coordenada Z como a altura do relevo
        }
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float centerX = imageWidth / 2.0f;
    float centerY = imageHeight / 2.0f;
    float centerZ = 100.0f; // Altura da câmera acima do mapa
    float eyeX = centerX;
    float eyeY = centerY;
    float eyeZ = 500.0f; // Distância da câmera ao mapa
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo.ppm>" << endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Mapa de Relevo");

    glEnable(GL_DEPTH_TEST);

    loadPPM(argv[1]);

    glutDisplayFunc(display);
    init();
    glutMainLoop();

    delete[] image;
    return 0;
}
