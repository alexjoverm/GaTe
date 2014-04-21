
#include "ResourceHolder.hpp"


template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder(){
	mResourceMap = new std::map<Identifier, std::unique_ptr<Resource> >();
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder(const ResourceHolder& orig){
	
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder(){
	delete mResourceMap;
}





template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	// Crear y Cargar el recurso
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Fallo al cargar " + filename);

	// Se se ha podido cargar, lo metemos en el mapa
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Crear y Cargar el recurso
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Fallo al cargar " + filename);

	// Se se ha podido cargar, lo metemos en el mapa
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap->find(id);  //auto es una variable dinamica
	assert(found != mResourceMap->end()); //Comprobamos que es correcto

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap->find(id);
	assert(found != mResourceMap->end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource) 
{
	// Metemos en el mapa y comprobamos que se ha hecho
	auto inserted = mResourceMap->insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}
