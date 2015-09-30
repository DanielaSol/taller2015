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
	struct Protagonista {
		string tipo;
		int x;
		int y;
	};

	struct Entidad {
		int x;
		int y;
		string tipo;
	};

	struct Escenario {
		string nombre;
		int size_x;
		int size_y;
		std::vector<Entidad> entidades;
	};


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

	struct Animacion {
		int fps;
		int delay;
	};

	struct ObjetoGeneral{
		string nombre;
		int ancho;
		int alto;
		int x;
		int y;
		int pixelrefx;
		int pixelrefy;

		Animacion animacion;
		string imagen;
	};

	struct ConfigGame {
		Pantalla pantalla;
		Configuracion configuracion;
		map<string,string> imagenes;
		map<string,ObjetoGeneral> objetos;
		Escenario escenario;
		Protagonista protagonista;

	};

	ConfigGame configGame;
	static Parser* parInstance;


	void Inicializar(YAML::Node);
	void reset();

	static Parser* Instance(){
		if (parInstance == 0)
			parInstance = new Parser();


		return parInstance;
	}

	YAML::Node getField(std::string field, std::string subField, YAML::Node nodo);
	YAML::Node getField(string field, YAML::Node::const_iterator it);
	void setField(std::string field, std::string subField,  YAML::Node nodo, int& aSetear);
	void setField( std::string field, std::string subField,  YAML::Node nodo, string& aSetear);
	void setField(std::string field, YAML::Node::const_iterator it, string& aSetear);
	void setField(string field, YAML::Node::const_iterator it, int& aSetear);

	 std::map<std::string, std::list<std::string>> const camposObjetos {
	       { "arbol", {"imagen",  "ancho", "alto", "pixel_ref_x","pixel_ref_y" }},
	       { "castillo", {"imagen", "ancho", "alto", "pixel_ref_x","pixel_ref_y" }},
	       { "soldado", {"imagen","delay", "fps", "ancho", "alto", "pixel_ref_x","pixel_ref_y" }},
	       { "juana_de_arco", {"imagen", "ancho", "fps", "delay", "alto", "pixel_ref_x","pixel_ref_y" }},
	       { "tierra", {"imagen",  "ancho", "alto", "pixel_ref_x","pixel_ref_y" }},
	       { "agua", {"imagen",  "ancho", "alto", "pixel_ref_x","pixel_ref_y" }},
	       { "molino", {"imagen",  "ancho", "alto", "pixel_ref_x","pixel_ref_y" }}

	    };


//private:
	Parser();
	~Parser();

};


typedef Parser TheParser;
} /* namespace std */


#endif /* PARSER_H_ */
