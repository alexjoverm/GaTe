/***********************************************/
/******* SPRITEPARTICLESYSTEM.CPP - GaTE *******/
/***********************************************/
#include "SpriteParticleSystem.h"

/**
 * Crea un sistema de particulas basico
 */
SpriteParticleSystem::SpriteParticleSystem():
m_emitter(200.0f, 200.0f)
,m_lifeTime(sf::seconds(0.8f))
,m_particleSpeed(1.0f)
,m_gravity(0, 100)
,m_dissolve(true)
,m_scale(1.0, 1.0)
,m_grow(false)
,m_color(sf::Color::White)
,m_systemType(SystemParticleType::EMBER1)
,m_particleType(ParticleType::EMBER)
,m_numParticles(1000)
,m_uniformScale(false)
,m_growScale(0.0f, 1.0f)
,m_rotateParticle(true)
,m_particleRotate(3.14f)
{
    SpriteParticle* particle;
    
    sf::Texture* texture;
    texture = new sf::Texture;
    if(!texture->loadFromFile("Recursos/ember01.png"))
    {
        std::cout << "particle.png is not in Recursos folder ..."<<std::endl;
        exit(0);
    }
    
    for(int i = 0; i < m_numParticles; i++)
    {
        
        m_sprite.setTexture(*texture);
        particle = new SpriteParticle();
        particle->sprite = m_sprite;
        particle->sprite.setColor(m_color);
        particle->sprite.setScale(m_scale);
        m_particles.push_back(particle);
    }
    m_numParticles = m_particles.size();
}

/**
 * Destructor de SpriteParticleSystem
 */
SpriteParticleSystem::~SpriteParticleSystem()
{
    for( SpriteParticleIterator it = m_particles.begin(); it != m_particles.end(); it++ )
    {
        delete *it;
    }
}

/**
 * Añade particulas al sistema
 * @param particles Numero de particulas a añadir al sistema
 */
void SpriteParticleSystem::addParticles(int particles)
{
    float angle;
    SpriteParticle* particle;
    
    for(int i = 0; i < particles; i++)
    {
        particle = new SpriteParticle();
        particle->sprite.setPosition(m_emitter);
        angle = (std::rand() % 360) * 3.14f / 180.0f;
        particle->sprite = m_sprite;
    }
    
    //Si hay gravidad, esta afecta a la velocidad ...
    if(m_gravity.x != 0 && m_gravity.y != 0)
    {
        particle->velocity.x = m_gravity.x * static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/cos(angle))) * m_particleSpeed;
        particle->velocity.y = m_gravity.y * static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/sin(angle))) * m_particleSpeed;
    }
    else
    {
        particle->velocity.x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/cos(angle))) * m_particleSpeed;
        particle->velocity.y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/sin(angle))) * m_particleSpeed;
    }
    
    //Inicializamos el tiempo de vida de la particula
    particle->lifeTime = m_lifeTime;
    
    //Si el sistema admite dos colores, el color de la partcula sera el incial ...
    if(m_twoColors) particle->sprite.setColor(m_colorInit);
    else particle->sprite.setColor(m_color);
    
    //La particula se genera en la posicion del emiiter
    particle->sprite.setPosition(m_emitter);
    
    //Añadimos las particulas al vector de particulas y aumentamos el numero de particulas
    m_particles.push_back(particle);
    m_numParticles = m_particles.size();
}

/**
 * Elimina particulas del sistema
 * @param particles Numero de partciulas a eliminar del sistema
 */
void SpriteParticleSystem::removeParticles(int particles)
{
     if(m_particles.size()>20)
    {
        m_particles.erase(m_particles.begin(), m_particles.begin()+particles);
        m_numParticles = m_particles.size();
    }
    else
    {
        m_particles.clear();
        m_numParticles = m_particles.size();
    }
}

/**
 * Actualiza las particulas
 * @param elapsedTime Tiempo desde el último frame
 */
void SpriteParticleSystem::update(sf::Time elapsedTime)
{
    //Calculamos el número de particulas a mostrar
    while(m_particles.size() != m_numParticles)
    {
        float particles = m_particles.size() - m_numParticles;
        
        if(m_particles.size() > m_numParticles)
        {
            this->removeParticles(particles);
        }
        else this->addParticles(particles);
    }
    
    //Recorremos todas las particulas ...
    for(SpriteParticleIterator it = m_particles.begin(); it != m_particles.end(); it++)
    {   
        //Disminuimos el tiempo de vida de la particula
        (*it)->lifeTime -= elapsedTime;
        
        //Si la particula muere, generamos una nueva
        if((*it)->lifeTime <= sf::Time::Zero)
        {
            resetParticle(std::distance<std::vector<SpriteParticle*>::const_iterator>(m_particles.begin(), it));       
        }
        
        //Controlamos el cambio de color
        if(m_twoColors)
        {
                m_color = randomColor(m_colorInit, m_colorEnd, (*it)->lifeTime);
                (*it)->sprite.setColor(m_color);
        }
        if(m_dissolve)
        {
            //Actualizamos el alpha (transparencia) de la particula de acuerdo a su tiempo de vida
            (*it)->sprite.setColor(sf::Color((*it)->sprite.getColor().r, (*it)->sprite.getColor().g, (*it)->sprite.getColor().b, static_cast<sf::Uint8>(m_lifeTime.asSeconds() * 255)));
        }

        //Actualizamos la velocidad de las particulas
        if(m_rotateParticle)
        {
            m_rotate = ((std::rand() % 360) * m_particleRotate / 180.f) * (*it)->lifeTime.asSeconds();
            (*it)->sprite.setRotation(m_rotate);
        }
        
        (*it)->velocity.x += m_gravity.x * elapsedTime.asSeconds();
        (*it)->velocity.y += m_gravity.y * elapsedTime.asSeconds();
        
        //Actualizamos el tamaño de las particulas
        if(m_grow)
        {
            m_scale = randomVector2f(m_growScale.x, m_growScale.y, (*it)->lifeTime);
            (*it)->sprite.setScale(m_scale);
        }
        else
        {
            if(m_uniformScale)
            {
                m_scale = randomVector2f(m_scale.x, m_scale.y, (*it)->lifeTime);
                (*it)->sprite.setScale(m_scale);
            }
            else
            {
                (*it)->sprite.setScale(m_scale.x, m_scale.y);
            }
        }
        
        //Actualizamos la posicion del sprite correspondiente
        float getPosX = (*it)->sprite.getPosition().x;
        float getPosY = (*it)->sprite.getPosition().y;
        float posX = getPosX += (*it)->velocity.x * elapsedTime.asSeconds() * m_particleSpeed;
        float posY = getPosY += (*it)->velocity.y * elapsedTime.asSeconds() * m_particleSpeed;
        (*it)->sprite.setPosition(posX, posY);
    }
}

/**
 * Dibujamos el sistema de particulas
 * @param target Donde dibujamos las particulas
 * @param states Estado (no aplicable)
 */
void SpriteParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(SpriteParticleIterator it = m_particles.begin(); it != m_particles.end(); it++)
    {
        target.draw((*it)->sprite);
    }
}

/**
 * Resetea las particulas cuando mueren
 * @param index Indice de la particula dentro del vector de particulas
 */
void SpriteParticleSystem::resetParticle(std::size_t index)
{   
    //FIjamos el sprite inicial de la particula
    m_particles[index]->sprite = m_sprite;
    
    //Dependiendo de la opcion de color el sprite tomara un color u otro
    if(m_twoColors) m_particles[index]->sprite.setColor(m_colorInit);
    else m_particles[index]->sprite.setColor(m_color);
    
    //Dependiendo del tipo de sistema de particulas las particulas se comportaran de una forma u otra
    switch(m_systemType)
    {
        case SystemParticleType::EMBER1:
        {
            float angle = (std::rand() % 360) * 3.14f / 180.f;
            float speed = ((std::rand() % 50) + 50.0f) * m_particleSpeed;
            m_particles[index]->velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
            m_particles[index]->lifeTime = sf::milliseconds((std::rand() % 2000) + 1000);
            m_particles[index]->sprite.setPosition(m_emitter);
            break;
        }
        case SystemParticleType::EXPLOSION1:
        {
            float angle = (std::rand() % 360) * 3.14f / 180.f;
            float speed = ((std::rand() % 50) + 50.0f) * m_particleSpeed;
            m_particles[index]->velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
            m_particles[index]->lifeTime = m_lifeTime;
            m_particles[index]->sprite.setPosition(m_emitter);
            break;
        }
        case SystemParticleType::EXPLOSION2:
        {
            float angle = (std::rand() % 360) * 3.14f / 180.f;
            float speed = ((std::rand() % 50) + 50.0f) * m_particleSpeed;
            m_particles[index]->velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
            m_particles[index]->lifeTime = m_lifeTime;
            m_particles[index]->sprite.setPosition(m_emitter);
            break;
        }
    }
}

/**
 * Fijamos el numero de particulas de nuestro sistema
 * @param particles Numero de particulas del sistema
 */
void SpriteParticleSystem::setNumParticles(unsigned int particles)
{
    m_numParticles = particles;
}

/**
 * Fijamos la posicion del Emitter de nuestro sistema
 * @param position Posicion del sitema de particulas
 */
void SpriteParticleSystem::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

/**
 * Fijamos la velocidad de las particulas del sistema
 * @param speed Velocidad inicial de las partículas del sistema
 */
void SpriteParticleSystem::setParticleSpeed(float speed)
{
    m_particleSpeed = speed;
}

/**
 * Fijamos la gravedad que afecta al sistema
 * @param x Gravedad en el eje X
 * @param y Gravedad en el eje Y (80 aproximadamente 9.8 en la vida real)
 */
void SpriteParticleSystem::setGravity(float x, float y)
{
    m_gravity.x = x;
    m_gravity.y = y;
}

/**
 * Fijamos el tiempo de vida de las particulas del sistema
 * @param lifeTime Tiempo de vida de las particulas
 */
void SpriteParticleSystem::setLifeTime(float lifeTime)
{
    m_lifeTime = sf::seconds(lifeTime);
}

/**
 * Fijamos si las particulas se disuelven o no al morir
 * @param flag Verdadero o falso
 */
void SpriteParticleSystem::setDissolve(bool flag)
{
    m_dissolve = flag;
}

/**
 * Fijamos si las particulas cambian de tamaño con el tiepmo
 * @param flag Verdaero o falso
 */
void SpriteParticleSystem::setGrow(bool flag)
{
    m_grow = flag;
    
    //Si no cambian de tamaño, reseteamos la escala de las particulas
    if(!flag)
    {
        m_scale.x = 1.0f;
        m_scale.y = 1.0f;
    }
}

/**
 * Fijamos si las particulas se escalan uniformemente
 * @param flag Verdadero o falso
 */
void SpriteParticleSystem::setUniformScale(bool flag)
{
    m_uniformScale = flag;
    
    //Si se escalan uniformente ambos valores de escala son los mismos
    if(flag)
    {
        m_scale.x = m_scale.y;
    }
}

/**
 * Fijamos si las particulas rotan o no
 * @param flag Verdadero o falso
 */
void SpriteParticleSystem::setRotate(bool flag)
{
    m_rotateParticle = flag;
    
    if(!flag) m_particleRotate = 0;
}

/**
 * Fija la cantidad de rotacion que se les aplica a las particulas si la opcion de rotacion de las particulas esta activada
 * @param rotation
 */
void SpriteParticleSystem::setParticleRotation(float rotation)
{
    if(getRotate())
    {
        m_particleRotate = rotation;
    }
    else m_particleRotate = 0;
}

/**
 * Fijamos un color individual para todas las particulas del sistema
 * @param color Color de las particulas
 */
void SpriteParticleSystem::setColor(sf::Color color)
{
    m_color = color;
    m_twoColors = false;
}

/**
 * Fijamos un degradado de color para las particulas segun su tiempo de vida
 * @param colorInit Color incial de las particulas (cuando se generan)
 * @param colorEnd Color final de las particulas (cuando mueren)
 */
void SpriteParticleSystem::setColor(sf::Color colorInit, sf::Color colorEnd)
{
    m_colorInit = colorInit;
    m_colorEnd = colorEnd;
    m_twoColors = true;
}

/**
 * Fijamos la escala de las particulas. Si el escalado uniforme esta activado solo se tendra en cuenta el valor de X
 * @param x Escalado en el eje X (1.0 = no escalado)
 * @param y Escalado en el eje Y (1.0 = no escalado)
 */
void SpriteParticleSystem::setScale(float x, float y)
{
    //Si tenemos activado el escalado uniforme ambos valores tomaran el valor de la escala X
    if(!getUniformScale())
    {
        m_scale.x = x;
        m_scale.y = y;
    }
    else
    {
        m_scale.x = x;
        m_scale.y = x;
    }
}

/**
 * Si la opcion de Grow (crecimiento) esta activada, fijamos el tamaño inicial y final de la particula a lo largo de su tiempo de vida
 * @param x Tamaño de las particulas cuando nacen
 * @param y Tamaño de las particulas cuando mueren
 */
void SpriteParticleSystem::setGrowScale(float x, float y)
{
    m_growScale.x = x;
    m_growScale.y = y;
}

/**
 * Fijamos el sprite que mostraran las particulas
 * @param sprite Sprite de las particulas
 */
void SpriteParticleSystem::setSprite(sf::Sprite sprite)
{
    m_sprite = sprite;
}

/**
 * Devuelve el numero de particulas del sistema
 * @return Numero de particulas del sistema
 */
unsigned int SpriteParticleSystem::getNumParticles()
{
    return m_particles.size();
}

/**
 * Devuelve la posicion del sistema de particulas
 * @return  Posicion del emitter
 */
sf::Vector2f SpriteParticleSystem::getEmitter()
{
    return m_emitter;
}

/**
 * Devuelve la gravedad que afecta al sistema
 * @return Gravedad que afecta al sistema
 */
sf::Vector2f SpriteParticleSystem::getGravity()
{
    return m_gravity;
}

/**
 * Devuelve la escala de las particulas del sistema
 * @return Escala de las particulas
 */
sf::Vector2f SpriteParticleSystem::getScale()
{
    return m_scale;
}

/**
 * Devuelve la velocidad inicial de las particulas del sistema
 * @return Velocidad inicial de las particulas
 */
float SpriteParticleSystem::getParticleSpeed()
{
    return m_particleSpeed;
}

/**
 * Devuelve la cantidad de rotacion que se le aplica a las particulas si la caracteristica de rotacion esta activada
 * @return Rotacion de las particulas
 */
float SpriteParticleSystem::getParticleRotation()
{
    return m_particleRotate;
}

/**
 * Devuelve true si la caracteristica de Disolucion esta activada
 * @return Activada o desactivada
 */
bool SpriteParticleSystem::getDissolve()
{
    return m_dissolve;
}

/**
 * Devuelve true si la caracteristia ce Crecimiento esta activada
 * @return Activada o desactivada
 */
bool SpriteParticleSystem::getGrow()
{
    return m_grow;
}

/**
 * Devuelve true si la caracteristia de cambio de color dependiendo de la vida de las particulas esta activada
 * @return Activada o desactivada
 */
bool SpriteParticleSystem::getTwoColors()
{
    return m_twoColors;
}

/**
 * Devuelve true si la caracteristica de escalado uniforme esta activada
 * @return Activado o desactivado
 */
bool SpriteParticleSystem::getUniformScale()
{
    return m_uniformScale;
}

/**
 * Devuelve true si la caracteristica de rotacion de las particulas esta activada
 * @return Activado o desactivado
 */
bool SpriteParticleSystem::getRotate()
{
    return m_rotateParticle;
}

/**
 * Devuelve la velocidad de las particulas del sistema (dependiendo de todas las fuerzas que la afectan en un determinado momento y de su tiempo de vida)
 * @return Velocidad de las particulas
 */
sf::Vector2f SpriteParticleSystem::getVelocity()
{
    return m_particles[0]->velocity;
}

/**
 * Devuelve los tamaños inicial y final fijados cuando se activa la opcion de crecimiento
 * @return Tamaño inicial y final de las particulas
 */
sf::Vector2f SpriteParticleSystem::getGrowScale()
{
    return m_growScale;
}

/**
 * Devuelve el tiempo de vida de las particulas
 * @return Tiempo de vida de las particulas
 */
sf::Time SpriteParticleSystem::getLifeTime()
{
    return m_lifeTime;
}

/**
 * Devuelve el sprite de las particulas
 * @return  Sprite de las particulas
 */
sf::Sprite SpriteParticleSystem::getSprite()
{
    return m_sprite;
}

/**
 * Devuelve un color aleatorio
 * @return Color aleatorio
 */
sf::Color SpriteParticleSystem::randomColor()
{
    sf::Color color;
    color.r = std::rand() % 255;
    color.g = std::rand() % 255;
    color.b = std::rand() % 255;
    return color;
}

/**
 * Devuelve un color entre dos colores que varia a lo largo el tiempo
 * @param color1 Color inicial
 * @param color2 Color final
 * @param lifeTime Tiempo de interpolacion
 * @return 
 */
sf::Color SpriteParticleSystem::randomColor(sf::Color color1, sf::Color color2, sf::Time lifeTime)
{
    sf::Color color;
    sf::Vector3f vec1(color1.r, color1.g, color1.b);
    sf::Vector3f vec2(color2.r, color2.g, color2.b);
    
    float rlerp;
    float glerp;
    float blerp;
    rlerp = lerp(vec1.x, vec2.x, lifeTime.asSeconds());
    glerp = lerp(vec1.y, vec2.y, lifeTime.asSeconds());
    blerp = lerp(vec1.z, vec2.z, lifeTime.asSeconds());

    color.r = static_cast<sf::Uint8>(rlerp);
    color.g = static_cast<sf::Uint8>(glerp);
    color.b = static_cast<sf::Uint8>(blerp);
    
    return color;
}

/**
 * Devuelve un vector cuyos valores varian a lo largo del tiempo
 * @param from Valor inicial
 * @param to Valor final
 * @param lifeTime Tiempo de interpolacion
 * @return 
 */
sf::Vector2f SpriteParticleSystem::randomVector2f(float from, float to, sf::Time lifeTime)
{
    sf::Vector2f vec;
    
    float myLerp = lerp(from, to, lifeTime.asSeconds());
    
    vec.x = myLerp;
    vec.y = myLerp;
    
    return vec;
}

/**
 * Fija el tipo de particula a usar
 * @param typeParticle ParticleType::EMBER o ParticleType::SMOKE
 */
void SpriteParticleSystem::setTypeParticle(unsigned char typeParticle)
{
    switch(typeParticle)
    {
        case ParticleType::EMBER:
        {
            sf::Texture *texture = new sf::Texture();
            texture->loadFromFile("Recursos/ember01.png");
            sf::Sprite sprite1;
            sprite1.setTexture(*texture);
            this->setSprite(sprite1);
            m_particleType = ParticleType::EMBER;
            break;
        }
        case ParticleType::SMOKE:
        {
            sf::Texture *texture = new sf::Texture();
            texture->loadFromFile("Recursos/smoke01.png");
            sf::Sprite sprite;
            sprite.setTexture(*texture);
            this->setSprite(sprite);
            m_particleType = ParticleType::SMOKE;
            break;
        }
    }
}

/**
 * Fija el comportamiento de las particulas
 * @param typeSystem SystemParticleType::EMBER1 o SystemParticleType::EXPLOSION1 o SystemParticleType::EXPLOSION2
 */
void SpriteParticleSystem::setTypeSystem(unsigned char typeSystem)
{
    switch(typeSystem)
    {
        case SystemParticleType::EMBER1:
        {
            this->setNumParticles(500);
            this->setParticleSpeed(1.45);
            this->setGrow(true);
            this->setGravity(0.0f, 0.0f);
            this->setUniformScale(false);
            this->setDissolve(true);
            this->setGrowScale(0.3f, 1.0f);
            this->setTypeParticle(1);
            this->setLifeTime(1.0f);
            m_systemType = SystemParticleType::EMBER1;
            this->setTypeParticle(ParticleType::EMBER);
            break;
        }
        case SystemParticleType::EXPLOSION1:
        {
            this->setNumParticles(500);
            this->setParticleSpeed(1.0f);
            this->setGrow(true);
            this->setGravity(0.0f, 100.0f);
            this->setUniformScale(false);
            this->setDissolve(true);
            this->setGrowScale(0.0f, 0.5f);
            this->setTypeParticle(0);
            this->setLifeTime(0.8f);
            m_systemType = SystemParticleType::EXPLOSION1;
            break;
        }
        case SystemParticleType::EXPLOSION2:
        {
            this->setNumParticles(500);
            this->setParticleSpeed(1.3f);
            this->setGrow(true);
            this->setGravity(0.0f, 0.0f);
            this->setUniformScale(false);
            this->setDissolve(true);
            this->setGrowScale(1.0f, 0.5f);
            this->setTypeParticle(0);
            this->setLifeTime(1.0f);
            m_systemType = SystemParticleType::EXPLOSION2;
            break;
        }
    }
}

/**
 * Devuelve el tipo de particula fijada
 * @return  Tipo de particula
 */
unsigned char SpriteParticleSystem::getTypeParticle()
{
    switch(m_particleType)
    {
        case ParticleType::EMBER:
        {
            return ParticleType::EMBER;
            break;
        }
        case ParticleType::SMOKE:
        {
            return ParticleType::SMOKE;
            break;
        }
        default:
        {
            return ParticleType::EMBER;
        }
    }
}

/**
 * Devuelve el tipo de sistema fijado
 * @return Tipo de sistema
 */
unsigned char SpriteParticleSystem::getTypeSystem()
{
    switch(m_systemType)
    {
        case SystemParticleType::EMBER1: 
        {
           return SystemParticleType::EMBER1;
           break;
        }
        case SystemParticleType::EXPLOSION1:
        {
            return SystemParticleType::EXPLOSION1;
            break;
        }
        case SystemParticleType::EXPLOSION2:
        {
            return SystemParticleType::EXPLOSION2;
            break;
        }
        default:
        {
           return SystemParticleType::EMBER1;
        }
    }
}

/**
 * Devuelve el color de la particula. El inicial si la opcion de dos colores esta activada.
 * @return Color inicial
 */
sf::Color SpriteParticleSystem::getColorInit()
{
    if(getTwoColors())
    {
        return m_colorInit;
    }
    else return m_color;
}

/**
 * Devuelve el color de la particula. El final si la opcion de dos colores esta activada
 * @return Color final
 */
sf::Color SpriteParticleSystem::getColorEnd()
{
    if(getTwoColors())
    {
        return m_colorEnd;
    }
    else return m_color;
}