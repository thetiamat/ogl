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
#include "geometry/sphere.h"

#include "tutorial1.h"

Application* Tutorial1::Create() {
    auto tutorial1 = new Tutorial1();
    tutorial1->init();
    return tutorial1;
}

void Tutorial1::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    body = Sphere::Create();
}

void Tutorial1::draw() {
    body->draw(*this);
}

void Tutorial1::dispose() {
    Application::dispose();

    delete body;
    delete input;
}