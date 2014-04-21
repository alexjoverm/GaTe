/******************************************/
/*              ANIMABLE.HPP             */
/******************************************/

#ifndef ANIMABLE_H

#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include <vector>

class Animable
{
public:
    //initANim, tilesAnim, reverse
    Animable(SpriteSheet* spriteSheet);
    ~Animable();
    
    void AddAnimation(Animation* animation);
    void AddAnimation(std::vector<Animation*> *animations);
    Animation* GetAnimation(std::string nombre) const;
    void SetCurrentAnimation(std::string nombre, SpriteSheet* sp);
    Animation* GetCurrentAnimation() const;
    AnimatedSprite* GetAnimatedSprite() const { return m_animatedSprite; }
    void SetWidthTile(int widthTile) { m_spriteSheet->SetWidthTile(widthTile); }
    void SetHeightTile(int heightTile) { m_spriteSheet->SetHeightTile(heightTile); }
    void SetSizeTile(int widthTile, int heightTile) { m_spriteSheet->SetWidthTile(widthTile); m_spriteSheet->SetHeightTile(heightTile); }
    int GetWidthTile() const{ return m_spriteSheet->GetSizeTile().GetX(); }
    int GetHeightTile() const{ return m_spriteSheet->GetSizeTile().GetY(); }
    void PlayAnimation();
    void StopAnimation();
    bool InitAnim();
    
private:
    SpriteSheet* m_spriteSheet;                                         //Spritesheet de la animacion   
    std::vector<Animation*> *m_animaciones;
    AnimatedSprite* m_animatedSprite;
    bool m_initAnim;
};

#endif	/* ANIMABLE_HPP */