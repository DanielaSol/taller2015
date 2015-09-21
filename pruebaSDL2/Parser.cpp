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

	}
	else
		LOG("No puede abrirse el archivo " FILE_YAML " se cargará el archivo de configuración por defecto");

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
	YAML::Node result;
	result = (*it)[field];
	if (result== NULL) {
		LOG ("Se intentó acceder al campo inexistente "+field);
		return Trees; //acá deberia buscar un valor por defecto
	}
	else
		return result;

}

bool campoValido (string field,list<string> listaCampos ){

	bool encontrado = false;
	for (list<string>::iterator it = listaCampos.begin();it !=listaCampos.end(); it++){
		if ((*it)==field){
			encontrado = true;
			break;
		}
	}

	return encontrado;

}

void Parser::Inicializar(){
	configGame.pantalla.alto= getField("pantalla" ,"alto", Trees).as<int>();
	configGame.pantalla.ancho=getField("pantalla" ,"ancho", Trees).as<int>();
	configGame.configuracion.vel_personaje=getField("configuracion", "vel_personaje", Trees).as<int>();
	configGame.configuracion.margen_scroll=getField("configuracion", "margen_scroll", Trees).as<int>();

	YAML::Node tiposDeObjetos= getField("tipos","", Trees);

	for (YAML::Node::const_iterator it = tiposDeObjetos.begin();it !=tiposDeObjetos.end(); it++){
		ObjetoGeneral unObjeto;
		unObjeto.nombre=getField("nombre",it).as<string>();

		std::list<std::string> listaCampos;
		cout << unObjeto.nombre << endl;
		try{
			listaCampos = (camposObjetos.at(unObjeto.nombre));
		}
		catch(int e){
			LOG ("Se intentó cargar un objeto inválido");
			break; // no cargo el elemento
		}


		if (campoValido("imagen",listaCampos))
			unObjeto.imagen=getField("imagen",it).as<string>();
		if (campoValido("alto",listaCampos))
			unObjeto.alto=getField("alto",it).as<int>();
		if (campoValido("ancho",listaCampos))
			unObjeto.ancho=getField("ancho",it).as<int>();
		if (campoValido("delay",listaCampos))
			unObjeto.animacion.delay=getField("delay",it).as<int>();
		if (campoValido("fps",listaCampos))
			unObjeto.animacion.fps=getField("fps",it).as<int>();
	}

}



} /* namespace std */






