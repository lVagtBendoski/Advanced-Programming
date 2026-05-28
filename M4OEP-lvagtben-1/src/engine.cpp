#include "engine.h"
#include <vector>
enum state {start, stayedHome, walkingPastGuard, talkingToGuard, town, tavern, ratFight, ratFightVictory,
    kissedCharlie, didntKissCharlie, blacksmith, donationBox, market, win, lose, forfeit};
state screen;
enum turnTracker {glimbosTurn, charliesTurn, enemyTurn};
enum turnTracker turn;
enum figtTracker {fightMenue, targetingMenue};
enum figtTracker fightTracker;
// Colors
color red(1.0f, 0.0f, 0.0f, 1.0f), hoverFill(0.0f, 1.0f, 0.0f, 1.0f), pressFill(0.0f, 0.0f, 1.0f, 1.0f);
color goblinGreen(0.635294117647f, 0.776470588235, 0.243137254902), earHole(0.0f, 0.0f, 1.0f, .25f), white(1.0f, 1.0f, 1.0f, 1.0f);
color black(0.0f, 0.0f, 0.0f, 1.0f), hillGreen(0.501960784314f, 0.945098039216f, 0.41568627451f, 1);
color woodBrown(0.521568627451f, 0.427450980392f, 0.270588235294f, 1), yellow(1.0f, 1.0f, 0.0f, 1);
color sandleWood(0.611764705882f, 0.611764705882f, 0.611764705882f, 1), cardboard(0.403921568627f, 0.337254901961f, 0.298039215686f, 1);
color cobbleStone(0.380392156863f, 0.380392156863f, 0.380392156863f, 1);
color charlieDay(1.0f, 0.78431372549f, 0.788235294118, 1), charlieShirt(0.325490196078f, 0.63137254902f, 0.639215686275f, 1);
color charliesPants(0.223529411765f, 0.192156862745f, 0.501960784314, 1);
color ratBody(0.529411764706f, 0.529411764706f, 0.529411764706f, 1), ratPink(1.0f, 0.643137254902f, 0.650980392157f, 1);
// TODO Note: complete the drawing TODOs in render before the other TODOs,
//  otherwise you won't be able to see if your code is correct

Engine::Engine() : keys() {
    this->initWindow();
    this->initShaders();
    this->initShapes();
    this->initRPGStuff();

    red = {1, 0, 0, 1};
    hoverFill.vec = red.vec + vec4{0.5, 0.5, 0.5, 0};
    pressFill.vec = red.vec - vec4{0.5, 0.5, 0.5, 0};
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
    // red spawn button centered in the top left corner
    buttons.push_back(make_unique<Rect>(shapeShader, vec2{width/2,height/2}, vec2{100, 50}, color{1, 0, 0, 1}));
    buttons.push_back(make_unique<Rect>(shapeShader, vec2{farLeft, height/3}, vec2{110, 50}, color{1, 0, 0, 1}));
    buttons.push_back(make_unique<Rect>(shapeShader, vec2{middleLeft, height/3}, vec2{110, 50}, color{1, 0, 0, 1}));
    buttons.push_back(make_unique<Rect>(shapeShader, vec2{middleRight, height/3}, vec2{110, 50}, color{1, 0, 0, 1}));
    buttons.push_back(make_unique<Rect>(shapeShader, vec2{farRight, height/3}, vec2{110, 50}, color{1, 0, 0, 1}));
    //glimbos body
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX, glimboPosY - 10*glimboSize}, vec2{glimboSize, glimboSize*2}, goblinGreen));
    //glimbos arms
    for(int i = 0; i < 25; i++ ) {
        glimboRendering.push_back(make_unique<Rect>(shapeShader, vec2{glimboPosX + glimboSize*(i/(glimboSize/2)) + glimboSize*4.7, glimboPosY - glimboSize*7.50 - glimboSize*(i/(glimboSize/2))}, vec2{glimboSize, glimboSize},goblinGreen));
    }
    for(int i = 0; i < 25; i++ ) {
        glimboRendering.push_back(make_unique<Rect>(shapeShader, vec2{glimboPosX - glimboSize*(i/(glimboSize/2)) - glimboSize*4.7, glimboPosY - glimboSize*7.50 - glimboSize*(i/(glimboSize/2))}, vec2{glimboSize, glimboSize},goblinGreen));
    }
    //glimbos legs
    for(int i = 0; i < 50; i++ ) {
        glimboRendering.push_back(make_unique<Rect>(shapeShader, vec2{glimboPosX - glimboSize*(i/15) - glimboSize*4, glimboPosY -glimboSize*17 - glimboSize*(i/9)}, vec2{glimboSize, glimboSize},goblinGreen));
    }
    for(int i = 0; i < 50; i++ ) {
        glimboRendering.push_back(make_unique<Rect>(shapeShader, vec2{glimboPosX + glimboSize*(i/15) + glimboSize*4, glimboPosY -glimboSize*17 - glimboSize*(i/9)}, vec2{glimboSize, glimboSize},goblinGreen));
    }
    //glimbos ears
    glimboRendering.push_back(make_unique<Triangle>(shapeShader, vec2{glimboPosX - 3*glimboSize, glimboPosY + 6*glimboSize}, vec2{8*glimboSize, 8*glimboSize}, goblinGreen));
    glimboRendering.push_back(make_unique<Triangle>(shapeShader, vec2{glimboPosX + 3*glimboSize, glimboPosY + 6*glimboSize}, vec2{8*glimboSize, 8*glimboSize}, goblinGreen));
    glimboRendering.push_back(make_unique<Triangle>(shapeShader, vec2{glimboPosX - 3*glimboSize, glimboPosY + 6*glimboSize}, vec2{4*glimboSize, 4*glimboSize}, earHole));
    glimboRendering.push_back(make_unique<Triangle>(shapeShader, vec2{glimboPosX + 3*glimboSize, glimboPosY + 6*glimboSize}, vec2{4*glimboSize, 4*glimboSize}, earHole));
    //glimbos head
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX, glimboPosY}, vec2{glimboSize+glimboSize*.25, glimboSize}, goblinGreen));
    //glimbos smile
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX, glimboPosY - 2*glimboSize}, vec2{glimboSize, glimboSize*.7}, black));
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX, glimboPosY - 1.5*glimboSize}, vec2{glimboSize, glimboSize*.7}, goblinGreen));
    //glimbos eyes
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX - 3*glimboSize, glimboPosY + 2*glimboSize}, vec2{glimboSize*.7, glimboSize*.7}, white));
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX + 3*glimboSize, glimboPosY + 2*glimboSize}, vec2{glimboSize*.7, glimboSize*.7}, white));
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX - 3*glimboSize, glimboPosY + 2*glimboSize}, vec2{glimboSize*.5, glimboSize*.5}, black));
    glimboRendering.push_back(make_unique<Circle>(shapeShader, vec2{glimboPosX + 3*glimboSize, glimboPosY + 2*glimboSize}, vec2{glimboSize*.5, glimboSize*.5}, black));

    //charlie
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charliePosX, charliePosY}, vec2{glimboSize*15, glimboSize*15}, charlieDay));
    //charlie's smile
    charlieRendering.push_back(make_unique<Circle>(shapeShader, vec2{charliePosX, charliePosY - 2*glimboSize}, vec2{glimboSize, glimboSize*.7}, black));
    charlieRendering.push_back(make_unique<Circle>(shapeShader, vec2{charliePosX, charliePosY - 1.5*glimboSize}, vec2{glimboSize, glimboSize*.7}, charlieDay));
    //charlie's eyes
    charlieRendering.push_back(make_unique<Circle>(shapeShader, vec2{charliePosX - 3*glimboSize, charliePosY + 2*glimboSize}, vec2{glimboSize*.7, glimboSize*.7}, white));
    charlieRendering.push_back(make_unique<Circle>(shapeShader, vec2{charliePosX + 3*glimboSize, charliePosY + 2*glimboSize}, vec2{glimboSize*.7, glimboSize*.7}, white));
    charlieRendering.push_back(make_unique<Circle>(shapeShader, vec2{charliePosX - 3*glimboSize, charliePosY + 2*glimboSize}, vec2{glimboSize*.5, glimboSize*.5}, black));
    charlieRendering.push_back(make_unique<Circle>(shapeShader, vec2{charliePosX + 3*glimboSize, charliePosY + 2*glimboSize}, vec2{glimboSize*.5, glimboSize*.5}, black));
    //charlie's body
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charliePosX,charlieRendering[0]->getBottom() - glimboSize * 10}, vec2{glimboSize*15, glimboSize *20}, charlieShirt));
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charliePosX,charlieRendering[7]->getBottom() - glimboSize * 10}, vec2{glimboSize*15, glimboSize *20}, charliesPants));
    //charlies arms
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charlieRendering[7]->getLeft() - glimboSize*4,charlieRendering[7]->getTop() - glimboSize * 3}, vec2{glimboSize*8, glimboSize *6}, charlieShirt));
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charlieRendering[7]->getRight() + glimboSize*4,charlieRendering[7]->getTop() - glimboSize * 3}, vec2{glimboSize*8, glimboSize *6}, charlieShirt));
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charlieRendering[9]->getPosX(),charlieRendering[9]->getBottom() - glimboSize * 8}, vec2{glimboSize*8, glimboSize *16}, charlieDay));
    charlieRendering.push_back(make_unique<Rect>(shapeShader, vec2{charlieRendering[10]->getPosX(),charlieRendering[10]->getBottom() - glimboSize * 8}, vec2{glimboSize*8, glimboSize *16}, charlieDay));

    //glimbosHouseBackground
    //hill
    glimbosHouseBackground.push_back(make_unique<Circle>(shapeShader, vec2{7*width/8, height - height*1.75}, vec2{width*.03, height*.05}, hillGreen));
    //house on the hill
    glimbosHouseBackground.push_back(make_unique<Rect>(shapeShader, vec2{glimbosHouseBackground[0]->getPosX(), height/2 - 10}, vec2{glimboSize*10, glimboSize*10}, woodBrown));
    glimbosHouseBackground.push_back(make_unique<Triangle>(shapeShader, vec2{glimbosHouseBackground[0]->getPosX(), glimbosHouseBackground[1]->getTop() + glimboSize * 5}, vec2{glimboSize*15, glimboSize*15}, red));
    //townBackground
    //outside of tavern
    townBackground.push_back(make_unique<Rect>(shapeShader, vec2{width/2, height/4}, vec2{width, height/2}, cobbleStone));
    townBackground.push_back(make_unique<Rect>(shapeShader, vec2{farLeft , height/2}, vec2{width/4, height*.6666}, woodBrown));
    townBackground.push_back(make_unique<Triangle>(shapeShader, vec2{townBackground[1]->getPosX(), townBackground[1]->getTop() + glimboSize * 25}, vec2{glimboSize*55, glimboSize*55}, woodBrown));
    townBackground.push_back(make_unique<Rect>(shapeShader, vec2{farLeft, height/3}, vec2{150, 300}, sandleWood));
    townBackground.push_back(make_unique<Circle>(shapeShader, vec2{farLeft - 50, height/3 - 35}, vec2{5, 5}, black));
    //sign for the tavern
    townBackground.push_back(make_unique<Rect>(shapeShader, tavernSignPos, vec2{300, 150}, sandleWood));
    townSigns.push_back("Pimly's Pub");
    //donation box
    townBackground.push_back(make_unique<Rect>(shapeShader, donoBoxPos, vec2{200, 200}, cardboard));
    townSigns.push_back("Donos");
    //blacksmith
    townBackground.push_back(make_unique<Rect>(shapeShader, vec2{middleRight + 100, height/2}, vec2{width/3, height*.6666}, cobbleStone));
    townBackground.push_back(make_unique<Triangle>(shapeShader, vec2{townBackground[7]->getPosX(), townBackground[7]->getTop() + glimboSize * 27}, vec2{glimboSize*55, glimboSize*55}, woodBrown));
    townBackground.push_back(make_unique<Rect>(shapeShader, vec2{middleRight, height/3}, vec2{150, 300}, sandleWood));
    townBackground.push_back(make_unique<Circle>(shapeShader, vec2{middleRight - 50, height/3 - 35}, vec2{5, 5}, black));
    //sign for the blacksmith
    townBackground.push_back(make_unique<Rect>(shapeShader, blacksmithSignPos, vec2{300, 150}, sandleWood));
    townSigns.push_back("Blacksmith");
    //sign to market
    townBackground.push_back(make_unique<Rect>(shapeShader, vec2{farRight + 150, height/3}, vec2{50, 250}, sandleWood));
    townBackground.push_back(make_unique<Rect>(shapeShader, marketSignPos, vec2{200, 100}, sandleWood));
    townBackground.push_back(make_unique<Triangle>(shapeShader, vec2{townBackground[13]->getRight(), townBackground[13]->getPosY()}, vec2{150, 100}, sandleWood));
    townSigns.push_back("Market");
    tavernBackground.push_back(make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{width, height}, woodBrown));
    //rats
    rat1.push_back(make_unique<Rect>(shapeShader, vec2{farLeft, 2*height/3}, vec2{300, 200}, ratBody));
    rat1.push_back(make_unique<Triangle>(shapeShader, vec2{rat1[0]->getRight(), rat1[0]->getTop()}, vec2{20, 300}, ratPink));
    rat1.push_back(make_unique<Circle>(shapeShader, vec2{rat1[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat1.push_back(make_unique<Circle>(shapeShader, vec2{rat1[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat1.push_back(make_unique<Circle>(shapeShader, vec2{rat1[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat1.push_back(make_unique<Circle>(shapeShader, vec2{rat1[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat1.push_back(make_unique<Triangle>(shapeShader, vec2{rat1[0]->getLeft() + 6*glimboSize, 2*height/3 - 30}, vec2{30, 20}, ratPink));

    rat2.push_back(make_unique<Rect>(shapeShader, vec2{middleLeft, 2*height/3}, vec2{300, 200}, ratBody));
    rat2.push_back(make_unique<Triangle>(shapeShader, vec2{rat2[0]->getRight(), rat2[0]->getTop()}, vec2{20, 300}, ratPink));
    rat2.push_back(make_unique<Circle>(shapeShader, vec2{rat2[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat2.push_back(make_unique<Circle>(shapeShader, vec2{rat2[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat2.push_back(make_unique<Circle>(shapeShader, vec2{rat2[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat2.push_back(make_unique<Circle>(shapeShader, vec2{rat2[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat2.push_back(make_unique<Triangle>(shapeShader, vec2{rat2[0]->getLeft() + 6*glimboSize, 2*height/3 - 30}, vec2{30, 20}, ratPink));

    rat3.push_back(make_unique<Rect>(shapeShader, vec2{middleRight, 2*height/3}, vec2{300, 200}, ratBody));
    rat3.push_back(make_unique<Triangle>(shapeShader, vec2{rat3[0]->getRight(), rat3[0]->getTop()}, vec2{20, 300}, ratPink));
    rat3.push_back(make_unique<Circle>(shapeShader, vec2{rat3[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat3.push_back(make_unique<Circle>(shapeShader, vec2{rat3[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat3.push_back(make_unique<Circle>(shapeShader, vec2{rat3[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat3.push_back(make_unique<Circle>(shapeShader, vec2{rat3[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat3.push_back(make_unique<Triangle>(shapeShader, vec2{rat3[0]->getLeft() + 6*glimboSize, 2*height/3 - 30}, vec2{30, 20}, ratPink));

    rat4.push_back(make_unique<Rect>(shapeShader, vec2{farRight, 2*height/3}, vec2{300, 200}, ratBody));
    rat4.push_back(make_unique<Triangle>(shapeShader, vec2{rat4[0]->getRight(), rat4[0]->getTop()}, vec2{20, 300}, ratPink));
    rat4.push_back(make_unique<Circle>(shapeShader, vec2{rat4[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat4.push_back(make_unique<Circle>(shapeShader, vec2{rat4[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.7, glimboSize*.7}, white));
    rat4.push_back(make_unique<Circle>(shapeShader, vec2{rat4[0]->getLeft() + 3*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat4.push_back(make_unique<Circle>(shapeShader, vec2{rat4[0]->getLeft() + 9*glimboSize, 2*height/3}, vec2{glimboSize*.5, glimboSize*.5}, black));
    rat4.push_back(make_unique<Triangle>(shapeShader, vec2{rat4[0]->getLeft() + 6*glimboSize, 2*height/3 - 30}, vec2{30, 20}, ratPink));

    
    //Martin
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinPosX, martinPosY}, vec2{glimboSize*15, glimboSize*15}, charlieDay));
    //Martin's frown
    martinSkrelliRendering.push_back(make_unique<Circle>(shapeShader, vec2{martinPosX, martinPosY - 7*glimboSize}, vec2{glimboSize, glimboSize*.7}, black));
    martinSkrelliRendering.push_back(make_unique<Circle>(shapeShader, vec2{martinPosX, martinPosY - 7.5*glimboSize}, vec2{glimboSize, glimboSize*.7}, charlieDay));
    //Martin's eyes
    martinSkrelliRendering.push_back(make_unique<Circle>(shapeShader, vec2{martinPosX - 3*glimboSize, martinPosY + 2*glimboSize}, vec2{glimboSize*.7, glimboSize*.7}, white));
    martinSkrelliRendering.push_back(make_unique<Circle>(shapeShader, vec2{martinPosX + 3*glimboSize, martinPosY + 2*glimboSize}, vec2{glimboSize*.7, glimboSize*.7}, white));
    martinSkrelliRendering.push_back(make_unique<Circle>(shapeShader, vec2{martinPosX - 3*glimboSize, martinPosY + 2*glimboSize}, vec2{glimboSize*.5, glimboSize*.5}, black));
    martinSkrelliRendering.push_back(make_unique<Circle>(shapeShader, vec2{martinPosX + 3*glimboSize, martinPosY + 2*glimboSize}, vec2{glimboSize*.5, glimboSize*.5}, black));
    //Martin's body
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinPosX,martinSkrelliRendering[0]->getBottom() - glimboSize * 10}, vec2{glimboSize*15, glimboSize *20}, black));
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinPosX,martinSkrelliRendering[7]->getBottom() - glimboSize * 10}, vec2{glimboSize*15, glimboSize *20}, charliesPants));
    //Martin arms
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinSkrelliRendering[7]->getLeft() - glimboSize*4,martinSkrelliRendering[7]->getTop() - glimboSize * 3}, vec2{glimboSize*8, glimboSize *6}, black));
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinSkrelliRendering[7]->getRight() + glimboSize*4,martinSkrelliRendering[7]->getTop() - glimboSize * 3}, vec2{glimboSize*8, glimboSize *6}, black));
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinSkrelliRendering[9]->getPosX(),martinSkrelliRendering[9]->getBottom() - glimboSize * 8}, vec2{glimboSize*8, glimboSize *16}, charlieDay));
    martinSkrelliRendering.push_back(make_unique<Rect>(shapeShader, vec2{martinSkrelliRendering[10]->getPosX(),martinSkrelliRendering[10]->getBottom() - glimboSize * 8}, vec2{glimboSize*8, glimboSize *16}, charlieDay));


    //minions

    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{middleRight, martinPosY}, vec2{glimboSize* .7*15, glimboSize* .7*15}, charlieDay));
    //Martin's frown
    martinMinion1Rendering.push_back(make_unique<Circle>(shapeShader, vec2{middleRight, martinPosY - 7*glimboSize* .7}, vec2{glimboSize* .7, glimboSize* .7*.7}, black));
    martinMinion1Rendering.push_back(make_unique<Circle>(shapeShader, vec2{middleRight, martinPosY - 7.5*glimboSize* .7}, vec2{glimboSize* .7, glimboSize* .7*.7}, charlieDay));
    //Martin's eyes
    martinMinion1Rendering.push_back(make_unique<Circle>(shapeShader, vec2{middleRight - 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.7, glimboSize* .7*.7}, white));
    martinMinion1Rendering.push_back(make_unique<Circle>(shapeShader, vec2{middleRight + 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.7, glimboSize* .7*.7}, white));
    martinMinion1Rendering.push_back(make_unique<Circle>(shapeShader, vec2{middleRight - 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.5, glimboSize* .7*.5}, black));
    martinMinion1Rendering.push_back(make_unique<Circle>(shapeShader, vec2{middleRight + 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.5, glimboSize* .7*.5}, black));
    //Martin's body
    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{middleRight,martinMinion1Rendering[0]->getBottom() - glimboSize* .7 * 10}, vec2{glimboSize* .7*15, glimboSize* .7 *20}, black));
    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{middleRight,martinMinion1Rendering[7]->getBottom() - glimboSize* .7 * 10}, vec2{glimboSize* .7*15, glimboSize* .7 *20}, charliesPants));
    //Martin arms
    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion1Rendering[7]->getLeft() - glimboSize* .7*4,martinMinion1Rendering[7]->getTop() - glimboSize* .7 * 3}, vec2{glimboSize* .7*8, glimboSize* .7 *6}, black));
    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion1Rendering[7]->getRight() + glimboSize* .7*4,martinMinion1Rendering[7]->getTop() - glimboSize* .7 * 3}, vec2{glimboSize* .7*8, glimboSize* .7 *6}, black));
    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion1Rendering[9]->getPosX(),martinMinion1Rendering[9]->getBottom() - glimboSize* .7 * 8}, vec2{glimboSize* .7*8, glimboSize* .7 *16}, charlieDay));
    martinMinion1Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion1Rendering[10]->getPosX(),martinMinion1Rendering[10]->getBottom() - glimboSize* .7 * 8}, vec2{glimboSize* .7*8, glimboSize* .7 *16}, charlieDay));



    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight, martinPosY}, vec2{glimboSize* .7*15, glimboSize* .7*15}, charlieDay));
    //Martin's frown
    martinMinion2Rendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight, martinPosY - 7*glimboSize* .7}, vec2{glimboSize* .7, glimboSize* .7*.7}, black));
    martinMinion2Rendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight, martinPosY - 7.5*glimboSize* .7}, vec2{glimboSize* .7, glimboSize* .7*.7}, charlieDay));
    //Martin's eyes
    martinMinion2Rendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight - 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.7, glimboSize* .7*.7}, white));
    martinMinion2Rendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight + 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.7, glimboSize* .7*.7}, white));
    martinMinion2Rendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight - 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.5, glimboSize* .7*.5}, black));
    martinMinion2Rendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight + 3*glimboSize* .7, martinPosY + 2*glimboSize* .7}, vec2{glimboSize* .7*.5, glimboSize* .7*.5}, black));
    //Martin's body
    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight,martinMinion2Rendering[0]->getBottom() - glimboSize* .7 * 10}, vec2{glimboSize* .7*15, glimboSize* .7 *20}, black));
    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight,martinMinion2Rendering[7]->getBottom() - glimboSize* .7 * 10}, vec2{glimboSize* .7*15, glimboSize* .7 *20}, charliesPants));
    //Martin arms
    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion2Rendering[7]->getLeft() - glimboSize* .7*4,martinMinion2Rendering[7]->getTop() - glimboSize* .7 * 3}, vec2{glimboSize* .7*8, glimboSize* .7 *6}, black));
    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion2Rendering[7]->getRight() + glimboSize* .7*4,martinMinion2Rendering[7]->getTop() - glimboSize* .7 * 3}, vec2{glimboSize* .7*8, glimboSize* .7 *6}, black));
    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion2Rendering[9]->getPosX(),martinMinion2Rendering[9]->getBottom() - glimboSize* .7 * 8}, vec2{glimboSize* .7*8, glimboSize* .7 *16}, charlieDay));
    martinMinion2Rendering.push_back(make_unique<Rect>(shapeShader, vec2{martinMinion2Rendering[10]->getPosX(),martinMinion2Rendering[10]->getBottom() - glimboSize* .7 * 8}, vec2{glimboSize* .7*8, glimboSize* .7 *16}, charlieDay));


    //guard
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight, height/2}, vec2{glimboSize* .7*15, glimboSize* .7*15}, charlieDay));
    //Martin's frown
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight, height/2 - 7*glimboSize* .7 + 6}, vec2{glimboSize*2, glimboSize* .2}, black));
    guardRendering.push_back(make_unique<Circle>(shapeShader, vec2{9999, height/2 - 7.5*glimboSize* .7}, vec2{glimboSize* .7, glimboSize* .7*.7}, charlieDay));
    //Martin's eyes
    guardRendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight - 3*glimboSize* .7, height/2 + 2*glimboSize* .7}, vec2{glimboSize* .7*.7, glimboSize* .7*.7}, white));
    guardRendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight + 3*glimboSize* .7, height/2 + 2*glimboSize* .7}, vec2{glimboSize* .7*.7, glimboSize* .7*.7}, white));
    guardRendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight - 3*glimboSize* .7, height/2 + 2*glimboSize* .7}, vec2{glimboSize* .7*.5, glimboSize* .7*.5}, black));
    guardRendering.push_back(make_unique<Circle>(shapeShader, vec2{farRight + 3*glimboSize* .7, height/2 + 2*glimboSize* .7}, vec2{glimboSize* .7*.5, glimboSize* .7*.5}, black));
    //Martin's body
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight,guardRendering[0]->getBottom() - glimboSize* .7 * 10}, vec2{glimboSize* .7*15, glimboSize* .7 *20}, yellow));
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{farRight,guardRendering[7]->getBottom() - glimboSize* .7 * 10}, vec2{glimboSize* .7*15, glimboSize* .7 *20}, charliesPants));
    //Martin arms
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{guardRendering[7]->getLeft() - glimboSize* .7*4,guardRendering[7]->getTop() - glimboSize* .7 * 3}, vec2{glimboSize* .7*8, glimboSize* .7 *6}, yellow));
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{guardRendering[7]->getRight() + glimboSize* .7*4,guardRendering[7]->getTop() - glimboSize* .7 * 3}, vec2{glimboSize* .7*8, glimboSize* .7 *6}, yellow));
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{guardRendering[9]->getPosX(),guardRendering[9]->getBottom() - glimboSize* .7 * 8}, vec2{glimboSize* .7*8, glimboSize* .7 *16}, charlieDay));
    guardRendering.push_back(make_unique<Rect>(shapeShader, vec2{guardRendering[10]->getPosX(),guardRendering[10]->getBottom() - glimboSize* .7 * 8}, vec2{glimboSize* .7*8, glimboSize* .7 *16}, charlieDay));
}

void Engine::initRPGStuff() {
    equipment noEquip;
    inventory noInv;
    character Glimbo("Glimbo", 7, 3, 1, 10, emptyInventory,
        noEquip, noEquipment, noEquipment);
    Glimbo.setTurn(true);
    playerParty.addMember(Glimbo);
    character rat1("Leonardo", 2, 1, 1, 0, emptyInventory, noEquip, noEquip, noEquip);
    character rat2(rat1);
    rat2.setName("Raphael");
    character rat3(rat1);
    rat3.setName("Donatello");
    character rat4(rat1);
    rat4.setName("Mikey");
    ratParty.addMember(rat1);
    ratParty.addMember(rat2);
    ratParty.addMember(rat3);
    ratParty.addMember(rat4);
    equipment MartinSpecialDagger(10, 0, "Stabbed the american people in the back", "Martins Special Dagger", "WEAPON", "NONE");
    equipment expensiveLawyers(0, 3, "They only protect the rich", "expensiveLawyers", "ARMOR", "NONE");
    character martinShkreli("Martin Shkreli", 14, 5, 5, 999, emptyInventory,MartinSpecialDagger, noEquipment, expensiveLawyers);
    character martinMinion1("Insurance fraud", 7, 3, 2, 0, emptyInventory, noEquipment, noEquipment, expensiveLawyers);
    character martinMinion2(martinMinion1);
    martinMinion2.setName("securities fraud");
    theMarts.addMember(martinShkreli);
    theMarts.addMember(martinMinion1);
    theMarts.addMember(martinMinion2);

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
     MouseY = height - MouseY; // Invert y-axis of mouse position
     buttonPressed =-1;
     bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
     for(int i = 0; i < buttons.size(); ++i) {
         bool buttonOverlapsMouse = buttons[i]->isOverlapping(vec2(MouseX, MouseY));
         if (buttonOverlapsMouse) {
             buttons[i]->setColor(hoverFill);
         }
         if (buttonOverlapsMouse && mousePressed) {
             buttons[i]->setColor(pressFill);
         }
         if(buttonOverlapsMouse && mousePressedLastFrame && !mousePressed) {
             buttonPressed = i;
         }
         // TODO: Make sure the spawn button is its original color when the user is not hovering or clicking on it.
         if(!buttonOverlapsMouse) {
             buttons[i]->setColor(red);
         }
     }
     processButtons(buttonPressed);
     inputUsed = false;
     //Save mousePressed for next frame
    mousePressedLastFrame = mousePressed;

}
void Engine::processButtons(int buttonPressed) {
    if(buttonPressed == 1) {
        switch (screen) {
            case start:{
                screen = walkingPastGuard;
                firstTimeHere = true;
                break;}
            case walkingPastGuard:{
                screen = talkingToGuard;
                firstTimeHere = true;
                break;}
            case talkingToGuard:{
                screen = town;
                firstTimeHere  = true;
                break;}
            case town:{
                screen = tavern;
                firstTimeHere = true;
                beenToTavern = true;
                break;}
            case tavern:{
                equipment charliesRatBashinStick(4, 0, "Bashes rats.", "charliesRatBashinStick", "WEAPON", "STUNNING");
                character Charlie("Charlie", 10, 1, 1, 10, emptyInventory, charliesRatBashinStick, noEquipment, noEquipment);
                Charlie.setTurn(false);
                playerParty.addMember(Charlie);
                screen = ratFight;
                firstTimeHere = true;
                break;}
            case ratFightVictory:{
                screen = kissedCharlie;
                firstTimeHere = true;
                equipment GlimbosVeryOwnRatBashinStick(charliesRatBashinStick);
                playerParty.getParty()[0].equipRightHand(GlimbosVeryOwnRatBashinStick);
                break;}
            case kissedCharlie: {
                screen = town;
                firstTimeHere = true;
                break;}
            case  didntKissCharlie: {
                screen = town;
                firstTimeHere = true;
                break;}
            case blacksmith:{
                screen = town;
                firstTimeHere = true;
                break;}
            case donationBox:{
                screen = town;
                firstTimeHere = true;
                break;}
        }
    }else if(buttonPressed == 2) {
        switch (screen) {
            case start:{
                screen = stayedHome;
                firstTimeHere = true;
                break;}
            case walkingPastGuard:{
                screen = town;
                firstTimeHere = true;
                break;}
            case talkingToGuard:{
                screen = town;
                firstTimeHere = true;
                break;}
            case town:{
                screen = donationBox;
                beenToDonationBox = true;
                firstTimeHere = true;
                break;}
            case tavern:{
                screen = town;
                firstTimeHere = true;
                break;}
            case ratFightVictory:{
                screen = didntKissCharlie;
                firstTimeHere = true;
                break;}
            case kissedCharlie: {
                screen = town;
                firstTimeHere = true;
                break;}
            case didntKissCharlie: {
                screen = town;
                firstTimeHere = true;
                break;}
            case blacksmith:{
                screen = town;
                firstTimeHere = true;
                break;}
            case donationBox:{
                screen = town;
                firstTimeHere = true;
                break;}
        }
    }else if(buttonPressed == 3) {
        switch (screen) {
            case talkingToGuard:{
                screen = town;
                firstTimeHere = true;
                break;}
            case town:{
                screen = blacksmith;
                beenToBlacksmith = true;
                firstTimeHere = true;
                break;}
            case blacksmith:{
                screen = town;
                firstTimeHere = true;
                break;}
            case donationBox:{
                screen = town;
                firstTimeHere = true;
                break;}
        }
    }else if(buttonPressed == 4) {
        switch (screen) {
            case talkingToGuard:{
                screen = town;
                firstTimeHere = true;
                break;}
            case town:{
                screen = market;
                firstTimeHere = true;
                break;}
            case blacksmith:{
                screen = town;
                firstTimeHere = true;
                break;}
            case donationBox:{
                screen = town;
                firstTimeHere = true;
                break;}
        }
    }
}

void Engine::update() {
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Engine::render() {
    glClearColor(0.219607843137f, 0.678431372549f, 0.81568627451f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);

    // Set shader to draw shapes
    shapeShader.use();


    // Render differently depending on screen
    switch (screen) {
        case start: {
            if(firstTimeHere) {
                string message0 = "Welcome to a day in the life of Glimbo. Glimbo is a goblin, "
                "you are Glimbo. One day after coming home you find you gold "
                "missing. Whoever took your precious gold obviously left in a "
                "rush after finding the gold as all the silver goblets and plates "
                "are still stored safely in the cupboard. Would you like to go into "
                "town to investigate? to investigate: select option A, to stay home select option B ";
                parseText(text, message0);
                firstTimeHere = false;
                vector<bool> options = {true, true, false, false};
                setAvailability(options);
            }
            // NOTE: This line changes the shader being used to the font shader.
            //  If you want to draw shapes again after drawing text,
            //  you'll need to call shapeShader.use() again first.
            renderModel(glimbosHouseBackground);
            renderModel(glimboRendering);
            renderText();
            renderButtons();
            break;
        }
        case stayedHome: {
            if(firstTimeHere) {
                string message1 = "Glimbo never found his gold, leaving him to die impoverished and sad";
                parseText(text, message1);
                vector<bool> options = {false, false, false, false};
                setAvailability(options);
            }
            renderModel(glimbosHouseBackground);
            renderModel(glimboRendering);
            renderText();

            break;
        }
        case walkingPastGuard: {
            if(firstTimeHere) {
                string message1 = "As you wander into the town you see a dumb looking guard. Would you like to talk "
                "to this moron? To talk to the guard select option A, to ignore them, select option B";
                parseText(text, message1);
                firstTimeHere = false;
                vector<bool> options = {true, true, false, false};
                setAvailability(options);
            }
            renderModel(townBackground);
            renderModel(glimboRendering);
            renderText();
            renderButtons();
        }
        case talkingToGuard: {
            shapeShader.use();
            if(firstTimeHere) {
                string message1 = "You ask the guard about your missing gold. The guard say's: "
                "duuurh I don't know about gold duuuum. To continue select any option.";
                parseText(text, message1);
                firstTimeHere = false;
            }
            renderModel(townBackground);
            renderModel(glimboRendering);
            renderModel(guardRendering);
            renderText();
            renderButtons();
            break;
        }
        case town: {
            if(firstTimeHere) {
                string message1 = "With that settled, you look around the town square you find "
                "yourself in. Assessing your option you realize that you can  (A) go into the "
                "tavern to perhaps find more information, B) check the town donation bin for "
                "something, (C) beg the blacksmith for equipment that may be helpful, or (D) "
                "investigate the market for more information to help on your quest ";
                parseText(text, message1);
                vector<bool> options = {!beenToTavern, !beenToDonationBox, !beenToBlacksmith, true};
                setAvailability(options);
                firstTimeHere = false;
            }
            renderModel(townBackground);
            renderModel(glimboRendering);
            if(playerParty.getParty().size() > 1) {
                renderModel(charlieRendering);
            }
            renderText();
            renderButtons();
            break;
        }
        case tavern: {
            if(firstTimeHere) {
                string message1 = "As you walk up to Pimley's Pub and the stench of stale ale "
                "and gross, unwashed patrons wash over you, find a "
                "dysfunctional staff shouting over each other about how to "
                "take care of the rats crowding the escape tunnel. The staff "
                "decides that each person will vote for who they like the "
                "least. Whoever gets the most votes has to clear out the rats. "
                "After a decisive vote Charlie walks away from the group "
                "looking absolutely dejected. In that moment Charlie curses "
                "his former friends (coworkers) and looks out to the "
                "wide world for new people. It is at this point that he lays "
                "eye's upon you. He asks you if you'd like to join him in the "
                "basement. to agree select optionA, to leave select optionB";
                parseText(text, message1);
                vector<bool> options = {true, true, false, false};
                setAvailability(options);
                firstTimeHere = false;
            }
            renderModel(tavernBackground);
            renderModel(glimboRendering);
            renderModel(charlieRendering);
            renderText();
            renderButtons();
            break;
        }
        case ratFight: {
            if(firstTimeHere) {
                firstTimeHere = false;
                vector<bool> options = {true, true, true, true};
                setAvailability(options);
            }
            renderModel(tavernBackground);
            renderModel(rat1);
            renderModel(rat2);
            renderModel(rat3);
            renderModel(rat4);
            renderModel(glimboRendering);
            renderModel(charlieRendering);
            renderCombatText(playerParty, ratParty);
            renderButtons();
            combat(playerParty, ratParty);
            if(!ratParty.everyoneIsLiving()) {
                screen = ratFightVictory;
                turn = glimbosTurn;
                playerParty.getParty()[0].setTurn(true);
                firstTimeHere = true;
            }
            if(!playerParty.everyoneIsLiving()){
                screen = lose;
                firstTimeHere = true;
            }
            break;
        }
        case ratFightVictory: {
            if(firstTimeHere) {
                string message1 = "HORAY! the rat's are dead! Great celebrations all "
                "around! As the exhilaration of successful battle rushes "
                "through the both of you your eye's lock and you must "
                "ask yourself what to do now. Will you (B) look away and leave before the moment can escalate"
                "or will you (A) stop and share a tender kiss with Charlie? ";
                parseText(text, message1);
                vector<bool> options = {true, true, false, false};
                setAvailability(options);
                firstTimeHere = false;
            }
            renderModel(tavernBackground);
            renderModel(glimboRendering);
            renderModel(charlieRendering);
            renderText();
            renderButtons();
            break;
        }
        case kissedCharlie : {
            if(firstTimeHere) {
                string message1 = "To thank you for such a wonderful moment Charlie will not only "
                "follow you till the ends of the earth, but he has also fashioned "
                "Glimbo his very own rat bashin stick. To continue, select any option";
                parseText(text, message1);
                firstTimeHere = false;
            }
            renderModel(tavernBackground);
            renderModel(glimboRendering);
            if(playerParty.getParty().size() > 1) {
                renderModel(charlieRendering);
            }
            renderText();
            renderButtons();
            if(glimboRendering[0]->getPosX() < height/3) {
                const float speed = 3.0 * deltaTime;
                for(const unique_ptr<Shape> & shape : glimboRendering) {
                    shape->moveX(speed);
                }
                for(const unique_ptr<Shape> & shape : charlieRendering) {
                    shape->moveX(-speed);
                }
            }
            break;
        }
        case didntKissCharlie : {
            if(firstTimeHere) {
                string message1 = "Charlie makes it clear that he much enjoys the company of Glimbo "
                "and will stay with him through the rest of Glimbo's journey. ";
                parseText(text, message1);
                firstTimeHere = false;
            }
            renderModel(tavernBackground);
            renderModel(glimboRendering);
            if(playerParty.getParty().size() > 1) {
                renderModel(charlieRendering);
            }
            renderText();
            renderButtons();
            break;

        }
        case blacksmith: {
            if(firstTimeHere) {
                string message1 = "You approach the kind blacksmith and ask her for solid metal sword "
                "to aid you on your journey. The blacksmith explains that while she "
                "would love to help you, she runs a business and not a charity, and that "
                "to grant the wishes of everyone that walked in would leave her destined "
                "for destitution. However, she can spare a suit of "
                "leather armor, although it may be ineffective it will be far better than the paper that goblins call skin, "
                "or any shirt a goblin could reasonably procure. Glimbo equips it and discards his old crap" ;
                equipment leatherArmor(0, 2, "Is leather armor.", "leather armor", "ARMOR", "NONE");
                playerParty.getParty()[0].equipArmor(leatherArmor);
                parseText(text, message1);
                firstTimeHere = false;
            }
            renderModel(townBackground);
            renderModel(glimboRendering);
            if(playerParty.getParty().size() > 1) {
                renderModel(charlieRendering);
            }
            renderText();
            renderButtons();
            break;
        }
        case donationBox: {
            if(firstTimeHere) {
                string message1 = "The donation box shows slim pickings. All that's in there is a cloth tunic. Upon seeing what Glimbo perceives "
                "to be fine threads and masterful weaving he discards the relative garbage that was on his chest and throws "
                "on this cloth tunic wil all haste";
                parseText(text, message1);
                firstTimeHere = false;
            }
            renderModel(townBackground);
            renderModel(glimboRendering);
            if(playerParty.getParty().size() > 1) {
                renderModel(charlieRendering);
            }
            renderText();
            renderButtons();
            break;
        }
        case market: {
            if(firstTimeHere) {
                string message1 = "There in the market you find the most evil and dastardly criminal. Martin Shkreli. His lore proceeds him"
                "as although it is common knowledge that this is not a good man before you the exact nature and procedure"
                "of his crimes remains veiled under a thick fog of garbage corporate language for Glimbo and all goblins"
                "of his time.";
                parseText(text, message1);
                firstTimeHere = false;
                vector<bool> options = {true, true, true, true};
                setAvailability(options);
                inputUsed = true;
            }
            renderCombatText(playerParty, theMarts);
            renderModel(townBackground);
            renderModel(glimboRendering);
            if(playerParty.getParty().size() > 1) {
                renderModel(charlieRendering);
            }
            renderModel(martinSkrelliRendering);
            renderModel(martinMinion1Rendering);
            renderModel(martinMinion2Rendering);
            renderText();
            renderCombatText(playerParty, theMarts);
            renderButtons();
            combat(playerParty, theMarts);
            if(!theMarts.everyoneIsLiving()) {
                screen = win;
                turn = glimbosTurn;
                playerParty.getParty()[0].setTurn(true);
                firstTimeHere = true;
            }
            if(!playerParty.everyoneIsLiving()){
                screen = lose;
                firstTimeHere = true;
            }
            break;
        }
        case lose: {
            string message = "You lose :(";
            // Display the message on the screen
            this->fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2, projection, 1, vec3{1, 1, 1});
            break;            
        }
        case forfeit: {
            if(firstTimeHere) {
                text.clear();
                string message1 = "forfeit.";
                text.push_back(message1);
                firstTimeHere = false;
                vector<bool> options = {false, false, false, false};
                setAvailability(options);
            }
            renderText();
            break;
        }
        case win: {
            string message = "You win!";
            // Display the message on the screen
            this->fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2, projection, 1, vec3{1, 1, 1});
            break;
        }
    }

    glfwSwapBuffers(window);
}

void Engine::renderButtons() {
    shapeShader.use();
    if(aIsAvailable) {
        buttons[1]->setUniforms();
        buttons[1]->draw();
        fontRenderer->renderText("Option A", buttons[1]->getPos().x - 45, buttons[1]->getPos().y - 5, projection, 0.5, vec3{1, 1, 1});
        shapeShader.use();
    }
    if(bIsAvailable) {
        buttons[2]->setUniforms();
        buttons[2]->draw();
        fontRenderer->renderText("Option B", buttons[2]->getPos().x - 45, buttons[2]->getPos().y - 5, projection, 0.5, vec3{1, 1, 1});
        shapeShader.use();

    }
    if(cIsAvailable) {
        buttons[3]->setUniforms();
        buttons[3]->draw();
        fontRenderer->renderText("Option C", buttons[3]->getPos().x - 45, buttons[3]->getPos().y - 5, projection, 0.5, vec3{1, 1, 1});
        shapeShader.use();
    }
    if(dIsAvailable) {
        buttons[4]->setUniforms();
        buttons[4]->draw();
        fontRenderer->renderText("Option D", buttons[4]->getPos().x - 45, buttons[4]->getPos().y - 5, projection, 0.5, vec3{1, 1, 1});
        shapeShader.use();
    }
}
void Engine::renderText() {
    int i;
    for(i = 0; i < text.size(); i++) {
        this->fontRenderer->renderText(text[i], 0, height - 30 * (i+1), projection, 1, vec3{1, 1, 1});
    }
}
void Engine::renderModel(vector<unique_ptr<Shape>> & model) {
    shapeShader.use();
    for(const unique_ptr<Shape> & shape : model) {
        shape->setUniforms();
        shape->draw();
    }
    //if the model is the town, put writing on all the signs
     if(screen == town || screen == talkingToGuard || screen == walkingPastGuard || screen == blacksmith || screen == donationBox) {
         this->fontRenderer->renderText(townSigns[0], tavernSignPos.x-150, tavernSignPos.y, projection, 1, vec3{1, 1, 1});
         this->fontRenderer->renderText(townSigns[1], donoBoxPos.x-100, donoBoxPos.y, projection, 1, vec3{1, 1, 1});
         this->fontRenderer->renderText(townSigns[2], blacksmithSignPos.x-150, blacksmithSignPos.y, projection, 1, vec3{1, 1, 1});
         this->fontRenderer->renderText(townSigns[3], marketSignPos.x-100, marketSignPos.y, projection, 1, vec3{1, 1, 1});
         shapeShader.use();
    }

}
void Engine::setAvailability(vector<bool> options) {
    aIsAvailable = false;
    bIsAvailable = false;
    cIsAvailable = false;
    dIsAvailable = false;
    if(options[0]) {aIsAvailable = true;}
    if(options[1]) {bIsAvailable = true;}
    if(options[2]) {cIsAvailable = true;}
    if(options[3]) {dIsAvailable = true;}
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


void Engine::combat(Party &playerParty, Party &enemies) {
    if(turn != enemyTurn){playerCombatTurn(playerParty, enemies);}
    else{
        enemyCombatTurn(playerParty, enemies);
        turn = glimbosTurn;
        playerParty.getParty()[0].setTurn(true);
    }
}
void Engine::playerCombatTurn(Party &playerParty, Party &enemies) {
    for(int i =0; i < playerParty.getParty().size(); i++) {
        if(!inputUsed) {
            if(playerParty.getParty()[i].getTurn()) {
                if(playerParty.getParty()[i].getStatusString() != "STUNNED" && playerParty.getParty()[i].getLiving()) {
                    if(fightTracker ==  fightMenue) {
                        playerParty.getParty()[i].setStatus("CHILLING");
                        if (buttonPressed == 1) {
                            inputUsed = true;
                            playerParty.getParty()[i].displayDetailedStats();
                        }if (buttonPressed == 2) {
                            inputUsed = true;
                            fightTracker = targetingMenue;
                            vector<string> enemyNames = enemies.getMembers();
                            cout << "this is a list of your enemies: " << enemies << endl;
                            cout << "Who would you like " << playerParty.getParty()[i].getName() << " to attack?" << endl;
                            cout << "Please choose your target using the buttons on screen:" << enemies << endl;
                        }else if (buttonPressed == 3) {
                            inputUsed = true;
                            playerParty.getParty()[i].setStatus("BLOCKING");
                            playerParty.getParty()[i].setTurn(false);
                            if(i < playerParty.getParty().size() - 1) {playerParty.getParty()[i+1].setTurn(true);}
                            else {turn = enemyTurn;}
                        }else if (buttonPressed == 4) {
                            inputUsed = true;
                            screen = forfeit;
                            cout << "after being stabbed in the back by who Glimbo once considered an ally he crumples. "
                                    "Not only the pain kept him from getting up but mainly the miserable realization "
                                    "that he did not have " << playerParty.getParty()[i].getName() << " as a friend. if this person could "
                                    "act so disengenously as Glimbo's friend then he would not ever know a true friend "
                                    "as he would never again be able to trust. Glimbo did not wish to live in a world where"
                                    "such a terrible thing could be true, so instead he just bled out slowly and coldly." << endl;
                            //https://www.gavilan.edu/csis/languages/stop-end.html#:~:text=C%2B%2B%20uses%20the%20exit()%20function%20to%20terminate%20the%20program%20execution.
                            exit(1);
                        }
                    }
                    else {
                        int index = -1;
                        for(int j = 0; j < enemies.getParty().size(); j++) {
                            if(enemies.getParty()[j].getLiving() && buttonPressed -1 == j) {
                                index = j;
                            }
                        }
                        if(index != -1) {
                            inputUsed = true;
                            playerParty.getParty()[i].dealDamageTo(enemies.getParty()[index]);
                            playerParty.getParty()[i].setTurn(false);
                            if(i < playerParty.getParty().size() - 1) {playerParty.getParty()[i+1].setTurn(true);}
                            else {turn = enemyTurn;}
                            fightTracker = fightMenue;
                        }
                    }
                }
                else {
                    cout << playerParty.getParty()[i].getName() << " was stunned and couldn't attack this turn!" << endl;
                    playerParty.getParty()[i].setStatus("CHILLING");
                    playerParty.getParty()[i].setTurn(false);
                    if(i < playerParty.getParty().size() - 1) {playerParty.getParty()[i+1].setTurn(true);}
                    else {turn = enemyTurn;}
                }
            }
        }
    }
}

void Engine::enemyCombatTurn(Party &playerParty, Party &enemies) {
    for( character &foe : enemies.getParty()) {
        if(foe.getStatusString() != "STUNNED" && foe.getLiving()) {
            foe.setStatus("CHILLING");
            int target = playerParty.findIndexOfFirstLivingPerson();
            if(target != -1) {
                foe.dealDamageTo(playerParty.getParty()[target]);
            }
            if(foe.getEquippedRightHand().getAttributestring() == "STUNNING" || foe.getEquippeLeftHand().getAttributestring() == "STUNNING") {
                playerParty.getParty()[target].setStatus("STUNNED");
            }
        }
        else {
            cout << foe.getName() << " was stunned or dead and couldn't attack this turn!" << endl;
            foe.setStatus("CHILLING");
        }
    }
    turn = glimbosTurn;
}

void Engine::renderCombatText(Party &playerParty, Party &enemies) {
    string menueOptions;
    string turnTracker;
    if(fightTracker == fightMenue) {
        menueOptions += "optionA: view stats, optionB: attack, optionC:block, optionD: death";
    }else {
        if(enemies.getParty().size() > 0) {menueOptions += "option A:" +enemies.getParty()[0].getName();}
        if(enemies.getParty().size() > 1) {menueOptions += " option B:" +enemies.getParty()[1].getName();}
        if(enemies.getParty().size() > 2) {menueOptions += " option C:" +enemies.getParty()[2].getName();}
        if(enemies.getParty().size() > 3) {menueOptions += " option D:" +enemies.getParty()[3].getName();}
    }
    this->fontRenderer->renderText(menueOptions, 0, 30 , projection, 1, vec3{1, 1, 1});
    if(turn == enemyTurn) { turnTracker = "enemy turn";}
    else {
        for(character &ally: playerParty.getParty()) {
            if(ally.getTurn()) {turnTracker += ally.getName() + "'s turn";}
        }
    }
    this->fontRenderer->renderText(turnTracker, width - 400, height - 30 , projection, 1, vec3{1, 1, 1});
    text.clear();
    if(screen == ratFight) {
        string message3 = "";
        string message1 = "rat fight.";
        string message2 = "Glimbo's health: " + to_string(playerParty.getParty()[0].getHealth());
        if(playerParty.getParty().size() > 1)
            message3 = "Charlie's health: " + to_string(playerParty.getParty()[1].getHealth());
        string message4 = "Leonardo's health: " + to_string(ratParty.getParty()[0].getHealth());
        string message5 = "Raphael's health: " + to_string(ratParty.getParty()[1].getHealth());
        string message6 = "Donatello's health: " + to_string(ratParty.getParty()[2].getHealth());
        string message7 = "Mikey's health: " + to_string(ratParty.getParty()[3].getHealth());
        text.push_back(message1);
        text.push_back(message2);
        text.push_back(message3);
        text.push_back(message4);
        text.push_back(message5);
        text.push_back(message6);
        text.push_back(message7);
        renderText();
    } else {
        string message3 = "";
        string message1 = "Boss fight.";
        string message2 = "Glimbo's health: " + to_string(playerParty.getParty()[0].getHealth());
        if(playerParty.getParty().size() > 1)
            message3 = "Charlie's health: " + to_string(playerParty.getParty()[1].getHealth());
        string message4 = "Martin Shkrelli's health: " + to_string(theMarts.getParty()[0].getHealth());
        string message5 = "Insurance fraud's health: " + to_string(theMarts.getParty()[1].getHealth());
        string message6 = "Securities fraud's health: " + to_string(theMarts.getParty()[2].getHealth());
        text.push_back(message1);
        text.push_back(message2);
        text.push_back(message3);
        text.push_back(message4);
        text.push_back(message5);
        text.push_back(message6);
        renderText();

    }
}
void Engine::parseText(vector<string> &result, string &s) {
    result.clear();
    string substr;
    int index = 0;
    for(int i = 0;!s.empty(); i++) {
        if(s.length() >= 67) {
            for(int j = 67; j > 0; j--) {
                substr = s.substr(j,1);
                if(substr == " ") {
                    index = j;
                    break;
                }
            }
            substr = s.substr(0, index+1);
            s = s.substr(index+1, s.length());
            result.push_back(substr);
        } else {
            result.push_back(s);
            s = "";
        }
        if(i > 100) {
            cout << "problem in string parsing" << endl;
            exit(0);
        }
    }
}
