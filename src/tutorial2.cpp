// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core.h"
#include "app.h"
#include "input.h"

#include "geometry/body.h"
#include "geometry/grid.h"
#include "geometry/cube.h"

#include "tutorial2.h"

Application* Tutorial2::Create() {
    auto tutorial2 = new Tutorial2();
    tutorial2->init();
    return tutorial2;
}

void Tutorial2::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    grid = Grid::Create();

    dice = Cube::Create();
    dice->setMass(200.0);
    dice->setVelocity(30.0, 40.0, 0.0);
    dice->setAcceleration(-10.0, 0.0, 0.0);
    dice->setDamping(0.99f, 0.99f);
}

void Tutorial2::draw() {
    grid->draw(*this);
    dice->draw(*this);
}

void Tutorial2::dispose() {
    Application::dispose();

    delete dice;
    delete grid;
    delete input;
}
