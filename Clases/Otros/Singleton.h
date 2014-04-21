/* 
 * File:   Singleton.h
 * Author: linuxero
 *
 * Created on March 18, 2014, 8:18 AM
 */

#ifndef SINGLETON_H
#define	SINGLETON_H

class Singleton {
	
public:
	static Singleton* Instance(); // Método que habrá que llamar para crear el objeto
	
protected:
	Singleton();
	Singleton(const Singleton& orig);
	virtual ~Singleton();
	
private:
	static Singleton* instance;
};

#endif	/* SINGLETON_H */

