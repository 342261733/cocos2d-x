#ifndef __JSON_MANAGER_H__
#define __JSON_MANAGER_H__

#include "JsonBox/include/JsonBox.h"

class JsonManager
{
public:
	~JsonManager();

	static JsonBox::Value userJson;
	static JsonManager* shareJsonManager();

private:
	JsonManager();
	static JsonManager* jsonManager;

	int _nCurrLevel;
	int _nStartNum;
};

#endif