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

<<<<<<< HEAD
	struct Animacion {
		string fps;
		string delay;
	};

=======
>>>>>>> 88e1ab52d787b081368f57e24c0232b88d97f459
	struct ObjetoGeneral{
		string nombre;
		int ancho;
		int alto;
		int x;
		int y;
<<<<<<< HEAD
		Animacion animacion;
		string imagen;
	};

=======
	};

	struct Animacion {
		int fps;
		int delay;
	};
>>>>>>> 88e1ab52d787b081368f57e24c0232b88d97f459

	struct ConfigGame {
		Pantalla pantalla;
		Configuracion configuracion;
		map<string,string> imagenes;
		map<string,ObjetoGeneral> objetos;
	};

	ConfigGame configGame;
	static Parser* parInstance;


<<<<<<< HEAD
	Parser();
	virtual ~Parser();
=======
>>>>>>> 88e1ab52d787b081368f57e24c0232b88d97f459
	void Inicializar();

	static Parser* Instance(){
		if (parInstance == 0)
			parInstance = new Parser();
<<<<<<< HEAD

=======
>>>>>>> 88e1ab52d787b081368f57e24c0232b88d97f459
		return parInstance;
	}

	YAML::Node getField(std::string field, std::string subField, YAML::Node nodo);
	YAML::Node getField(string field, YAML::Node::const_iterator it);

<<<<<<< HEAD
	std::map<std::string, std::list<std::string>> const camposObjetos {
	   { "arbol", {"imagen"}},
	   { "castillo", {"imagen","ancho_base","alto_base","pixel_ref_x","pixel_ref_y" }},
	   { "soldado", {"imagen","fps","delay"}},
	   { "juana_de_arco", {"imagen","fps"}},
	   { "tierra", {"imagen"}},
	   { "agua", {"imagen"}},

	};

=======
private:
	Parser();
	~Parser();
>>>>>>> 88e1ab52d787b081368f57e24c0232b88d97f459
};


typedef Parser TheParser;
} /* namespace std */


#endif /* PARSER_H_ */
