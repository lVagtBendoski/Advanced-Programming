#include "engine.h"

enum state {start, play, over};
state screen;

// Colors
color lightOff, outlineOn, outlineOff, lightOn;

Engine::Engine() : keys() {
    this->initWindow();
    this->initShaders();
    this->initShapes();

    lightOff = {0.5, 0.5, 0.5, 0.5};
    lightOn = {1, 1, 0, 1};
    outlineOn = {1, 0, 0, 1};
    outlineOff = {0, 0, 0, 1};
}

Engine::~Engine() {}

unsigned int Engine::initWindow(bool debug) {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(width, height, "engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // OpenGL configuration
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    return 0;
}

void Engine::initShaders() {
    // load shader manager
    shaderManager = make_unique<ShaderManager>();

    // Load shader into shader manager and retrieve it
    shapeShader = this->shaderManager->loadShader("../res/shaders/shape.vert", "../res/shaders/shape.frag",  nullptr, "shape");

    // Configure text shader and renderer
    textShader = shaderManager->loadShader("../res/shaders/text.vert", "../res/shaders/text.frag", nullptr, "text");
    fontRenderer = make_unique<FontRenderer>(shaderManager->getShader("text"), "../res/fonts/MxPlus_IBM_BIOS.ttf", 24);

    // Set uniforms
    textShader.setVector2f("vertex", vec4(100, 100, .5, .5));
    shapeShader.use();
    shapeShader.setMatrix4("projection", this->PROJECTION);
}

void Engine::initShapes() {
    // Make initial 25 squares
    int x = 80;
    int y = 80;
    for (int i = 0; i < 25; ++i) {
        if (x <= 800) {
            button.push_back(make_unique<Rect>(shapeShader, vec2{x, y}, vec2{130, 130}, color(1, 1, 0, 1)));
            x += 160;
        }
        else {
            y += 160;
            x = 80;
            --i;
        }
    }

    x = 80;
    y = 80;
    for (int i = 0; i < 25; ++i) {
        if (x <= 800) {
            outlines.push_back(make_unique<Rect>(shapeShader, vec2{x, y}, vec2{150, 150}, color(0, 0, 0, 1)));
            x += 160;
        }
        else {
            y += 160;
            x = 80;
            --i;
        }
    }
}

void Engine::processInput() {
    glfwPollEvents();

    // Set keys to true if pressed, false if released
    for (int key = 0; key < 1024; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    // Close window if escape key is pressed
    if (keys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, true);

    // Mouse position saved to check for collisions
    glfwGetCursorPos(window, &MouseX, &MouseY);

    if (screen == start) {
        if (keys[GLFW_KEY_S]) {
            screen = play;
        }
    }

    // Mouse position is inverted because the origin of the window is in the top left corner
    MouseY = height - MouseY; // Invert y-axis of mouse position
    bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    // Logic for highlighting the outlines on hover
    for (const unique_ptr<Shape>& o : outlines) {
        if (o->isOverlapping(vec2(MouseX, MouseY))) {
            o->setColor(outlineOff);
        } else {
            o->setColor(outlineOn);
        }
    }

    // detection for clicks works now :)
    for (int i = 0; i < button.size(); ++i) {
        if (!button[i]->isOverlapping(vec2(MouseX, MouseY)) && mousePressedLastFrame && !mousePressed
            && button[i]->getColor3() == vec3(lightOn.red, lightOn.green, lightOn.blue)) {
            clickButton(i);
            numPresses ++;
        }
        else if (!button[i]->isOverlapping(vec2(MouseX, MouseY)) && mousePressedLastFrame && !mousePressed
            && button[i]->getColor3() == vec3(lightOff.red, lightOff.green, lightOff.blue)) {
            clickButton(i);
            numPresses ++;
        }
    }


    // Save mousePressed for next frame
    mousePressedLastFrame = mousePressed;

}

void Engine::update() {
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //gameWon parameter created to track if the game has been won, assumed true, and disproved later
    gameWon = true;
    for (const unique_ptr<Shape>& b : button) {
        //if any b is not off gameWon is set to false because game is not won
        if(b->getColor3() != vec3(0.5, 0.5, 0.5)) {
            gameWon = false;
        }
    }
    if (gameWon) {
        screen = over;
    }

}

void Engine::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);

    // Set shader to draw shapes
    shapeShader.use();

    // Render differently depending on screen
    switch (screen) {
        case start: {
            string message = "Press s to start";
            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            // NOTE: This line changes the shader being used to the font shader.
            //  If you want to draw shapes again after drawing text,
            //  you'll need to call shapeShader.use() again first.
            this->fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2 + 100, projection, 1, vec3{1, 1, 1});
            string instructions1 = "Turn out all the lights! When you click on ";
            this->fontRenderer->renderText(instructions1, 20, height/2 + 20, projection, .75, vec3{1, 1, 1});
            string instructions2 = "one of the lights, it toggles itself and";
            this->fontRenderer->renderText(instructions2, 45, height/2, projection, .75, vec3{1, 1, 1});
            string instructions3 = "the (up to) four lights it borders.";
            this->fontRenderer->renderText(instructions3, 80, height/2 - 20, projection, .75, vec3{1, 1, 1});
            //Comment out following line for standard start with all lights lit.
            clickButton(rand() % 25);
            break;
        }
        case play: {
            if(!clockStarted) {
                //start clock
                clockStart = std::chrono::high_resolution_clock::now();
                clockStarted = true;
            }
            for (const unique_ptr<Shape>& o : outlines) {
                o->setUniforms();
                o->draw();
            }


            for (int i = 0; i < button.size(); ++i) {
                button[i]->setUniforms();
                button[i]->draw();
                string text = std::to_string(i);
                fontRenderer->renderText(text, button[i]->getPos().x - 30, button[i]->getPos().y - 5, projection, 0.5, vec3{0, 0, 0});
                shapeShader.use();
            }
            this->fontRenderer->renderText(std::to_string(numPresses), 30, height - 50, projection, .75, vec3{1, 1, 1});
            break;
        }
        case over: {
            if(clockStarted) {
                //stop clock
                clockStop = std::chrono::high_resolution_clock::now();
                clockStarted = false;
            }
            elapsedMicroSeconds = std::chrono::duration_cast<std::chrono::microseconds>(clockStop - clockStart);
            string message = "You win!";
            string timeIntroducer = "The time it took you to win was: ";
            string time = std::to_string(elapsedMicroSeconds.count());

            fontRenderer->renderText(message, width/2 - 60, height/2 - 35, projection, .75, vec3{1, 1, 1});
            fontRenderer->renderText(timeIntroducer, width/2 - width/3, height/2 - 75, projection, .75, vec3{1, 1, 1});
            fontRenderer->renderText(time, width/2 - 60, height/2 - 115, projection, .75, vec3{1, 1, 1});
            fontRenderer->renderText("seconds", width/2 + 120, height/2 - 115, projection, .75, vec3{1, 1, 1});

            break;
        }
    }

    glfwSwapBuffers(window);
}

void Engine::clickButton(int indexOfButton) {
    //when the button is clicked we need to change the color of the button clicked
    //as well as the button above, below, left, and right. These all have indicies of
    //+5, -5, -1, and +1 respectively
    if (button[indexOfButton]->getColor3() == vec3(lightOn.red, lightOn.green,lightOn.blue)) {
        button[indexOfButton]->setColor(lightOff);
    }else {
        button[indexOfButton]->setColor(lightOn);
    }
    //make sure button clicked is not in the top row
    if(indexOfButton < 20) {
        //changing button above
        if (button[indexOfButton + 5]->getColor3() == vec3(lightOn.red, lightOn.green,lightOn.blue)) {
            button[indexOfButton + 5]->setColor(lightOff);
        }else {
            button[indexOfButton + 5]->setColor(lightOn);
        }
    }
    //make sure the button is not on the bottom row
    if (indexOfButton > 4) {
        //changing button below
        if (button[indexOfButton - 5]->getColor3() == vec3(lightOn.red, lightOn.green,lightOn.blue)) {
            button[indexOfButton - 5]->setColor(lightOff);
        }else {
            button[indexOfButton - 5]->setColor(lightOn);
        }
    }
    //make sure the button is not on the left edge
    if(indexOfButton % 5 != 0) {
        //changing button to the left
        if (button[indexOfButton - 1]->getColor3() == vec3(lightOn.red, lightOn.green,lightOn.blue)) {
            button[indexOfButton - 1]->setColor(lightOff);
        }else {
            button[indexOfButton - 1]->setColor(lightOn);
        }
    }
    //make sure the button is not on the right edge
    if (indexOfButton % 5 != 4) {
        //changing button to the right
        if (button[indexOfButton + 1]->getColor3() == vec3(lightOn.red, lightOn.green,lightOn.blue)) {
            button[indexOfButton + 1]->setColor(lightOff);
        }else {
            button[indexOfButton + 1]->setColor(lightOn);
        }
    }

}


bool Engine::shouldClose() {
    return glfwWindowShouldClose(window);
}

GLenum Engine::glCheckError_(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        cout << error << " | " << file << " (" << line << ")" << endl;
    }
    return errorCode;
}