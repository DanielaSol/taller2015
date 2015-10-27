/*
 * ObjectFactory.h
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "GameObject.h"

namespace std {

class ObjectFactory {
public:
	static ObjectFactory* Instance() {
		if (objectInstance == 0) {
			objectInstance = new ObjectFactory ();
			return objectInstance;
		}

		return objectInstance;
	}

	/*static ObjectFactory* Instance()
		{
			if(s_pInstance == 0)
			{
				s_pInstance = new ObjectFactory();
				return s_pInstance;
			}

			return s_pInstance;
		}*/

	ObjectFactory();
	virtual ~ObjectFactory();

	GameObject* crear (string tipo, int x, int y);

private:
	static ObjectFactory* objectInstance;
};

typedef ObjectFactory TheObjectFactory ;

}
#endif /* OBJECTFACTORY_H_ */
