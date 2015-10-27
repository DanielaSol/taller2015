/*
 * ObjectFactory.h
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "GameObject.h"

using namespace std;

class ObjectFactory {
public:

	static ObjectFactory* Instance() {
		if (objectInstance == 0) {
			objectInstance = new ObjectFactory ();
			return objectInstance;
		}

		return objectInstance;
	}


	ObjectFactory();
	virtual ~ObjectFactory();

	GameObject* crear (string tipo, int x, int y);
	GameObject* crear (string tipo, int x, int y, int cant);

private:
	static ObjectFactory* objectInstance;
};

typedef ObjectFactory TheObjectFactory ;


#endif /* OBJECTFACTORY_H_ */
