#ifndef SPRITEPARTICLESYSTEM_H
#define	SPRITEPARTICLESYSTEM_H

/***********************************************/
/******** SPRITEPARTICLESYSTEM.H - GaTE ********/
/***********************************************/

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

//Tipos de sistemas de particulas por defecto
namespace SystemParticleType
{
    enum systemParticleType
    {
        EMBER1,
        EXPLOSION1,
        EXPLOSION2
    };
}

//Tipos de particulas por defecto (solo cambian el sprite))
namespace ParticleType
{
    enum particleType
    {
        EMBER,
        SMOKE
    };
}

struct SpriteParticle
{
    sf::Vector2f velocity;
    sf::Time lifeTime;
    sf::Sprite sprite;
};

typedef std::vector<SpriteParticle*>::const_iterator SpriteParticleIterator;
    
class SpriteParticleSystem : public sf::Drawable, public sf::Transformable
{
    public:
        SpriteParticleSystem();
        SpriteParticleSystem(unsigned int particles, sf::Sprite sprite);
        SpriteParticleSystem(unsigned int particles, sf::Sprite sprite, sf::Color colorInit, sf::Color colorEnd);
        ~SpriteParticleSystem();
        
        void update(sf::Time elapsedTime);
        void addParticles(int particles);
        void removeParticles(int particles);
        
        void setNumParticles(unsigned int particles);
        void setTypeParticle(unsigned char typeParticle);
        void setTypeSystem(unsigned char typeSystem);
        void setEmitter(sf::Vector2f position);
        void setScale(float x, float y);
        void setGravity(float x, float y);
        void setParticleSpeed(float speed);
        void setDissolve(bool flag);
        void setGrow(bool flag);
        void setUniformScale(bool flag);
        void setRotate(bool flag);
        void setColor(sf::Color color);
        void setColor(sf::Color colorInit, sf::Color colorEnd);
        void setLifeTime(float lifeTime);
        void setSprite(sf::Sprite sprite);
        void setGrowScale(float initVal, float endVal);
        void setParticleRotation(float rotation);
        
        
        float getParticleRotation();
        unsigned char getTypeParticle();
        unsigned char getTypeSystem();
        unsigned int getNumParticles();
        float getParticleSpeed();
        bool getDissolve();
        bool getGrow();
        bool getTwoColors();
        bool getUniformScale();
        bool getRotate();
        sf::Time getLifeTime();
        sf::Vector2f getEmitter();
        sf::Vector2f getGravity();
        sf::Vector2f getVelocity();
        sf::Vector2f getScale();
        sf::Vector2f getGrowScale();
        sf::Sprite getSprite();
        sf::Color getColorInit();
        sf::Color getColorEnd();
         /**
          * Devuelve una cadena a partir de cualquier tipo de dato
          * @param objeto
          * @return 
          */
         template <class T>
        std::string getString(T objeto)
        {
            std::ostringstream oss;
            oss << objeto;
            return oss.str();
        }
        
        static sf::Color randomColor();
        static sf::Color randomColor(sf::Color val1, sf::Color val2, sf::Time lifeTime);
        static sf::Vector2f randomVector2f(float from, float to, sf::Time lifeTime);
        
        /**
         * Funcion que genera una interpolacion lineal suave entre dos valores
         * @param start Valor de inicio
         * @param end Valor de final
         * @param percent Tiempo entre los dos valores
         * @return Devuelve un valor float correspondiente al valor interpolado en un determinado momento de tiempo
         */
        static float lerp(float start, float end, float percent)
        {
            return (start + ((-std::cos(3.14f * percent)/2) + 0.5) *(end - start));
        }
        
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void resetParticle(std::size_t index);
        
        float m_particleSpeed;
        float m_particleRotate;
        float m_rotate;
        bool m_grow;
        bool m_dissolve;
        bool m_twoColors;
        bool m_uniformScale;
        bool m_rotateParticle;
        unsigned char m_particleType;
        unsigned char m_systemType;
        unsigned int m_numParticles;
        sf::Time m_lifeTime;
        sf::Vector2f m_emitter;
        sf::Vector2f m_gravity;
        sf::Vector2f m_scale;
        sf::Vector2f m_growScale;
        sf::Sprite m_sprite;
        sf::Color m_color;
        sf::Color m_colorInit;
        sf::Color m_colorEnd;
        std::vector<SpriteParticle*> m_particles;
};

#endif	/* SPRITEPARTICLESYSTEM_H */

