#include <iostream>
#include <cstring>
#include <cstdlib>
#include "SDL.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "RainSystem.hpp"

enum Mode {textMode, graphicMode};

void runTextMode(RainSystem &rain) {
    double t = 0.0;
    for (;;) {
        double dt;
        std::cout << "Current time is " << t << ". Enter dt: ";
        std::cin >> dt;
        if (dt < 0) break;
        t += dt;
        rain.process(dt);
        std::cout << rain << "***************************************" << std::endl;
    }
}

void setNearView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 20, -2, 18, 1, -1);
}

void setFarView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200, 200, -5, 395, 1, -1);
}

void runGraphicMode(RainSystem &rain, double startTime) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16, SDL_OPENGL | SDL_RESIZABLE);

    if (screen == NULL) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glViewport(0, 0, 640, 480);

    setFarView();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat mt[16];
    for (int i = 0; i < 16; i++)
            mt[i] = 0.0;
    mt[0 * 4 + 0] = 1.0;
    mt[1 * 4 + 2] = 1.0;
    mt[2 * 4 + 1] = 1.0;
    mt[3 * 4 + 3] = 1.0;
//    glMultMatrixf(mt);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    bool runFlag = true;
    rain.process(startTime);
    double currentTime = SDL_GetTicks() * 0.001;
    enum {nearView = 0, farView = 1} view;
    view = farView;
    while (runFlag) {
        SDL_Event event;

        std::cerr << "Time: " << rain.getTime()  << std::endl;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                runFlag = false;
            }
            if (event.type == SDL_VIDEORESIZE) {
                screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, SDL_OPENGL | SDL_RESIZABLE);
                glViewport(0, 0, event.resize.w, event.resize.h);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == 's') {
                    if (view == nearView) {
                        view = farView;
                        setFarView();
                    }
                    else {
                        view = nearView;
                        setNearView();
                    }
                }
            }
        }

        double newTime = SDL_GetTicks() * 0.001;
        double dt = newTime - currentTime;
        currentTime = newTime;

        rain.process(dt);
        std::vector <Vector> pC = rain.getCoordinates();
        std::vector <Vector> pV = rain.getVelocities();

        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < (int)pC.size(); ++i) {
            glBegin(GL_LINES);
            glColor4f(0.0, 0.0, 0.0, 0.0);
            Vector prev = pC[i] - 0.05 * pV[i];
            glVertex3f(prev.x, prev.z, 0.0);// prev.z);
//            glColor4f(0.0, 0.0, 0.0, 0.6);
//            glVertex2f(i->r.x-0.01, i->r.y);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(pC[i].x, pC[i].z, 0.0);//pC[i].z);
//            glColor4f(0.0, 0.0, 0.0, 0.6);
//            glVertex2f(i->second.position.x+1, i->second.position.y);
            glEnd();
        }

/*        glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 1.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 1.0);
        glEnd(); */

        glBegin(GL_POLYGON);
            glColor3f(0.0, 0.0, 0.0);
            glVertex2f(0.0, -2.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(20.0, 0.0);
            glVertex2f(20.0, -2.0);
        glEnd();

        glFinish();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Invalid arguments" << std::endl;
        return -1;
    }

    Mode mode = graphicMode;
    if (argc == 2) {
        if (strcmp(argv[1], "text") == 0) {
            mode = textMode;
        }
        else if (strcmp(argv[1], "graphic") == 0) {
            mode = graphicMode;
        }
        else {
            std::cerr << "Invalid arguments" << std::endl;
            return -1;
        }
    }


    Vector wind = Vector(7.0, 3.0, 0.0);
    Vector cloudBegin = Vector(-80.0, -80.0, 300.0);
    Vector cloudEnd = Vector(10.0, 10.0, 310.0);
    RainSystem rain(0.01, 500, cloudBegin, cloudEnd, wind);

    if (mode == textMode)    runTextMode(rain);
    if (mode == graphicMode) runGraphicMode(rain, 0.0);

    return 0;
}
