#include "JsonManager.h"

JsonManager* JsonManager::jsonManager = NULL;

JsonManager::JsonManager()
{

}

JsonManager::~JsonManager()
{

}

JsonManager* JsonManager::shareJsonManager()
{
	if (NULL == jsonManager)
	{
		jsonManager = new JsonManager();
	}

	return jsonManager;
}