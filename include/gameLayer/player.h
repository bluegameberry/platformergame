#include <gl2d/gl2d.h>
#include "platformInput.h"

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
    
    unsigned int iframes = 9;

    void spawn();

    void update(float deltaTime, platform::Input &input);

    void kill();

    void render(gl2d::Renderer2D &renderer, gl2d::Texture &spriteSheet, gl2d::TextureAtlasPadding &spriteAtlas);
};


