#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include "framework/shaderManager.h"
#include "font/fontRenderer.h"
#include "shapes/rect.h"
#include "shapes/shape.h"
#include "shapes/circle.h"
#include "shapes/triangle.h"
#include "shapes/arrow.h"
#include "Party.h"
#include "equipment.h"
#include "inventory.h"
#include "character.h"

using std::vector, std::unique_ptr, std::make_unique, glm::ortho, glm::mat4, glm::vec3, glm::vec4;

/**
 * @brief The Engine class.
 * @details The Engine class is responsible for initializing the GLFW window, loading shaders, and rendering the game state.
 */
class Engine {
private:
    /// @brief The actual GLFW window.
    GLFWwindow* window{};

    /// @brief The width and height of the window.
    const unsigned int width = 1600, height = 1200; // Window dimensions
    const unsigned int arrowMargin = 150;
    const double glimboSize = 10;
    double glimboPosX = width/5;
    double glimboPosY = height*.2;
    double charliePosX = width/2;
    double charliePosY = .25*height;
    const double martinPosX = width/5;
    const double martinPosY = 2*height/3;
    const double farLeft = width/5;
    const double middleLeft = farLeft*2;
    const double middleRight = farLeft*3;
    const double farRight = farLeft*4;
    /// @brief The projection matrix
    const glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);


    /// @brief Keyboard state (True if pressed, false if not pressed).
    /// @details Index this array with GLFW_KEY_{key} to get the state of a key.
    bool keys[1024];

    /// @brief Responsible for loading and storing all the shaders used in the project.
    /// @details Initialized in initShaders()
    unique_ptr<ShaderManager> shaderManager;

    /// @brief Responsible for rendering text on the screen.
    /// @details Initialized in initShaders()
    unique_ptr<FontRenderer> fontRenderer;

    // Shapes
    vector<unique_ptr<Shape>> buttons;
    vector<unique_ptr<Shape>> glimbosHouseBackground;
    vector<unique_ptr<Shape>> townBackground;
    vector<string> townSigns;
    vec2 tavernSignPos{farLeft , 2*height/3};
    vec2 donoBoxPos{middleLeft, height/2};
    vec2 blacksmithSignPos{middleRight , 2*height/3};
    vec2 marketSignPos{farRight + 175, height/3 +125};
    vector<unique_ptr<Shape>> tavernBackground;
    vector<unique_ptr<Shape>> glimboRendering;
    vector<unique_ptr<Shape>> guardRendering;
    vector<unique_ptr<Shape>> charlieRendering;
    vector<unique_ptr<Shape>> martinSkrelliRendering;
    vector<unique_ptr<Shape>> martinMinion1Rendering;
    vector<unique_ptr<Shape>> martinMinion2Rendering;
    vector<unique_ptr<Shape>> rat1;
    vector<unique_ptr<Shape>> rat2;
    vector<unique_ptr<Shape>> rat3;
    vector<unique_ptr<Shape>> rat4;

    // Shaders
    Shader shapeShader;
    Shader textShader;

    double MouseX, MouseY;
    bool mousePressedLastFrame = false;
    bool firstTimeHere = true;
    bool aIsAvailable = true;
    bool bIsAvailable = true;
    bool cIsAvailable = true;
    bool dIsAvailable = true;
    bool beenToBlacksmith = false;
    bool beenToTavern = false;
    bool beenToDonationBox = false;
    bool inputUsed = false;
    int buttonPressed = -1;
    vector<string> text;
    Party playerParty;
    Party ratParty;
    Party theMarts;
    inventory emptyInventory;
    equipment noEquipment;
    equipment charliesRatBashinStick;
    equipment glimbosVeryOwnRatBashinStick;


    /// @note Call glCheckError() after every OpenGL call to check for errors.
    GLenum glCheckError_(const char *file, int line);
    /// @brief Macro for glCheckError_ function. Used for debugging.
#define glCheckError() glCheckError_(__FILE__, __LINE__)

public:
    /// @brief Constructor for the Engine class.
    /// @details Initializes window and shaders.
    Engine();

    /// @brief Destructor for the Engine class.
    ~Engine();

    /// @brief Initializes the GLFW window.
    /// @return 0 if successful, -1 otherwise.
    unsigned int initWindow(bool debug = false);

    /// @brief Loads shaders from files and stores them in the shaderManager.
    /// @details Renderers are initialized here.
    void initShaders();

    /// @brief Initializes the shapes to be rendered.
    void initShapes();
    void initRPGStuff();

    /// @brief Processes input from the user.
    /// @details (e.g. keyboard input, mouse input, etc.)
    void processInput();
    void processButtons(int buttonPressed);
    static void parseText(vector<string>& text, string& s);
    void playerCombatTurn(Party& playerParty, Party &enemies);
    void enemyCombatTurn(Party &playerParty, Party &enemies);
    void combat(Party &playerParty, Party &enemies);

    /// @brief Updates the game state.
    /// @details (e.g. collision detection, delta time, etc.)
    void update();

    /// @brief Renders the game state.
    /// @details Displays/renders objects on the screen.
    void render();
    void renderButtons();
    void renderText();
    void renderModel(vector<unique_ptr<Shape>> &model);
    void renderCombatText(Party &playerParty, Party &enemies);
    /* deltaTime variables */
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame (used to calculate deltaTime)

    // -----------------------------------
    // Getters
    // -----------------------------------

    /// @brief Returns true if the window should close.
    /// @details (Wrapper for glfwWindowShouldClose()).
    /// @return true if the window should close
    /// @return false if the window should not close
    bool shouldClose();
    void setAvailability(vector<bool> options);

    /// Projection matrix used for 2D rendering (orthographic projection).
    /// We don't have to change this matrix since the screen size never changes.
    /// OpenGL uses the projection matrix to map the 3D scene to a 2D viewport.
    /// The projection matrix transforms coordinates in the camera space into normalized device coordinates (view space to clip space).
    /// @note The projection matrix is used in the vertex shader.
    // 4th quadrant
    mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    // 1st quadrant
//        mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

};

#endif //GRAPHICS_ENGINE_H