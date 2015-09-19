/*
 * Parser.h
 *
 *  Created on: 16/09/2015
 *      Author: daniela
 */

#ifndef PARSER_H_
#define PARSER_H_

#define FILE_YAML_DEFAULT "files/configDefault.yaml"
#define FILE_YAML "files/config.yaml"

#include "yaml-cpp/yaml.h"
#include <string>
#include <map>

namespace std {

class Parser {
public:

	struct Pantalla {
		int ancho;
		int alto;
	};

	struct Configuracion {
		int vel_personaje;
		int margen_scroll;
	};

	struct Imagenes {
		string nombre;
		string imagen;
	};

	struct ObjetoGeneral{
		string nombre;
		int ancho;
		int alto;
		int x;
		int y;
	};

	struct Animacion {
		int fps;
		int delay;
	};

	struct ConfigGame {
		Pantalla pantalla;
		Configuracion configuracion;
		map<string,string> Imagenes;
		map<string,ObjetoGeneral> Objetos;
	};

	ConfigGame configGame;
	static Parser* parInstance;


	Parser();
	virtual ~Parser();
	void Inicializar();

	static Parser* Instance(){
		if (parInstance == 0)
			parInstance = new Parser();

		return parInstance;
	}

	YAML::Node getField(std::string field, std::string subField, YAML::Node nodo);
	YAML::Node getField(string field, YAML::Node::const_iterator it);

};


typedef Parser TheParser;
} /* namespace std */


#endif /* PARSER_H_ */
