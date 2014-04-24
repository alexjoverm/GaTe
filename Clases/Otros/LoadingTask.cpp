/* 
 * File:   LoadingTask.cpp
 * Author: alejandrojovermorales
 * 
 * Created on April 24, 2014, 11:57 AM
 */

#include "LoadingTask.h"
#include <SFML/System/Lock.hpp>
#include "../States/WorldState.h"

LoadingTask::LoadingTask(): mThread(&LoadingTask::RunTask, this), mFinished(false), loading(false)
{
}

LoadingTask::~LoadingTask() {
}

void LoadingTask::Execute()
{
	mFinished = false;
	mElapsedTime.restart();
	mThread.launch();
}

bool LoadingTask::IsFinished()
{
	sf::Lock lock(mMutex);
	return mFinished;
}

float LoadingTask::GetCompletion()
{
	sf::Lock lock(mMutex); 
	return mElapsedTime.getElapsedTime().asSeconds();  // Ahora mismo es fake
}

void LoadingTask::RunTask()
{
	bool ended = false;
	while (!ended)
	{
		sf::Lock lock(mMutex);
        if(!loading){
            WorldState::Instance()->LoadResources();
            loading=true;
        }
		if (mElapsedTime.getElapsedTime().asSeconds() >= 10.f && loading)
			ended = true;
	}

	{ 
		sf::Lock lock(mMutex);
		mFinished = true;
	}	
}

