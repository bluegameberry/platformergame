#include <player.h>



glm::vec2 Player::velocity(platform::Input &input)
{
    // may need to use acceleration instead?
    // or function takes velocity and acceleration?
    // differential equation solver takes the platform::input and accelerations
    //    returns position


    return forcingDirection;
}

void Player::spawn()
{
    isIdle = true;
    hp = max_hp;

    isMoving = false;
    isInAir = false;
    isRolling = false;
    isAttacking = false;
    isDead = false;
}

void Player::update(float deltaTime, platform::Input &input)
{
    // movement based on inputs
    forcingDirection = glm::vec2(0, 0);
    if (input.isButtonHeld(platform::Button::Right))
    {
        forcingDirection += glm::vec2(1, 0);
    }
    if (input.isButtonHeld(platform::Button::Left))
    {
        forcingDirection += glm::vec2(-1, 0);
    }
    if (input.isButtonHeld(platform::Button::Up))
    {
        forcingDirection += glm::vec2(0, 1);
    }
    if (input.isButtonHeld(platform::Button::Down))
    {
        forcingDirection += glm::vec2(0, -1);
    }

    // waiter waiter more hard to read code please
    isMoving = forcingDirection == glm::vec2(0, 0) ? false : true;
    isIdle = !isMoving;
    
    
    // damage


    // update sprite
    spriteCycle -= deltaTime;
    if (spriteCycle <= 0)
    {
        spriteCycle = spriteCycleTime;
        if (spriteIndex == spriteIndices.end())
        {
            spriteIndex = spriteIndices.begin();
        }
        ++spriteIndex;

    }
    
}

void Player::render(
    gl2d::Renderer2D &renderer,
    glm::vec2 position,
    float size,
    gl2d::Texture &spriteSheet,
    gl2d::TextureAtlasPadding &spriteAtlas
)
{
    unsigned int spriteY, spriteX = 0;
    if (isIdle || isHit || isDead)
    {
        spriteY = *spriteIndex % 4;
        spriteX = isIdle ? 0 : isHit ? 6 : isDead ? 7 : 0; // trust me
                
    }
    else if (isMoving)
    {
        spriteX = *spriteIndex / 8 ? 3 : 2;
        spriteY = *spriteIndex % 8;
    }
    else if (isRolling)
    {
        spriteX = 5;
        spriteY = *spriteIndex % 8;
    }

    renderer.renderRectangle(
		{position - glm::vec2{size/2, size/2}, size, size},
        spriteSheet,
        Colors_White,
        {},
        glm::degrees(toRadians(facingDirection)) - 90,
        spriteAtlas.get(spriteY, spriteX)
	);
}








// my convention
glm::vec2 toVec2(float angle)
{
    return {cosf(angle), -sinf(angle)};
}

float toRadians(glm::vec2 direction)
{
    return atan2(direction.x, -direction.y);
}