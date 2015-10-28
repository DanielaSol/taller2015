/*
 * Barra.h
 *
 *  La clase barra se encarga de manejar la barra de estado y reflejar los recursos
 *  	que posee el usuario.
 */

#ifndef BARRA_H_
#define BARRA_H_

#include <string>
#include <map>


using namespace std;

class Barra {
public:
	Barra();
	virtual ~Barra();
	void setRecurso(string,int);




};


#endif /* BARRA_H_ */
