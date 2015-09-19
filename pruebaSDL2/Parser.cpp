/*
 * Parser.h
 *
 *  Created on: 16/09/2015
 *      Author: daniela
 */

#include "Parser.h"
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"
#include "Logger.h"


namespace std {

YAML::Node Trees;
Parser* Parser::parInstance = 0;

Parser::Parser() {
	std::ifstream fileYaml( FILE_YAML );

	if (fileYaml){

		Trees=YAML::LoadFile(FILE_YAML);
		Inicializar();



		/*YAML::Node prueba = getField("pantalla" , Trees);

		cout << prueba << endl;
		for (YAML::Node::const_iterator it = Trees["tipos"].begin();it !=Trees["tipos"].end(); it++){
			string name = "nombre";

			//cout << getField(name,it)<< endl;
		}


		//if(!Trees["pantalla"])
		// LOG("No existe el campo pantalla en el archivo de configuración, se cargará un valor por defecto \n");

		//const YAML::Node& tree = Trees["pantalla"];
		//std::cout << YAML::Dump(tree) << std::endl;*/

		}
	else
		LOG ("No puede abrirse el archivo "FILE_YAML" se cargará el archivo de configuración por defecto");



}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}


YAML::Node Parser::getField(string field , string subField, YAML::Node nodo){

	YAML::Node result;
	if (subField.empty())
		result = Trees[field];
	else
		result = Trees[field][subField];

	if (result== NULL) {
		LOG ("Se intentó acceder al campo inexistente "+field);
		return Trees; //acá deberia buscar un valor por defecto
	}
	else
		return result;

}

YAML::Node Parser::getField(string field, YAML::Node::const_iterator it){

	return (*it)[field];
}

void Parser::Inicializar(){
	configGame.pantalla.alto= getField("pantalla" ,"alto", Trees).as<int>();
	configGame.pantalla.ancho=getField("pantalla" ,"ancho", Trees).as<int>();
	configGame.configuracion.vel_personaje=getField("configuracion", "vel_personaje", Trees).as<int>();
	configGame.configuracion.margen_scroll=getField("configuracion", "margen_scroll", Trees).as<int>();

}

} /* namespace std */




