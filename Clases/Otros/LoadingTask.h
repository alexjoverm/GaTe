/* 
 * File:   LoadingTask.h
 * Author: alejandrojovermorales
 *
 * Created on April 24, 2014, 11:57 AM
 */

#ifndef LOADINGTASK_H
#define	LOADINGTASK_H
#include <SFML/System.hpp>

class LoadingTask {
public:
    LoadingTask();
    virtual ~LoadingTask();
    
    void			Execute();
    bool			IsFinished();
    float			GetCompletion();

private:
    void			RunTask();

private:
    sf::Thread		mThread;
    bool			mFinished;
    sf::Clock       mElapsedTime;
    sf::Mutex		mMutex;
    
    bool            loading;
};

#endif	/* LOADINGTASK_H */

