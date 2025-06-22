#include <gl2d/gl2d.h>
#include "platformInput.h"
#include <vector>
#include <cmath>

struct Player
{
    const unsigned int max_hp = 64;
    unsigned int hp = max_hp;

    unsigned int atk = 1;

    bool isIdle;
    bool isMoving;
    bool isInAir;
    bool isRolling;
    bool isAttacking;
    bool isHit;
    bool isDead;
    
    const unsigned int iframes = 9;

    float spriteCycleTime = 30.f/60.f;
    float spriteCycle = spriteCycleTime;

    const std::vector<unsigned int> spriteIndices = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::vector<unsigned int>::const_iterator spriteIndex = spriteIndices.begin();

    glm::vec2 facingDirection = {1, 0};
    glm::vec2 forcingDirection = {0, 0};

    glm::vec2 velocity(platform::Input &input);

    void spawn();

    void update(float deltaTime, platform::Input &input);

    void kill();

    void render(
        gl2d::Renderer2D &renderer,
        glm::vec2 position,
        float size,
        gl2d::Texture &spriteSheet,
        gl2d::TextureAtlasPadding &spriteAtlas
    );

};

// my convention
glm::vec2 toVec2(float angle);
float toRadians(glm::vec2 direction);
