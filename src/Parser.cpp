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
#include "yaml-cpp/exceptions.h"
#include <map>


namespace std {

YAML::Node Trees;
YAML::Node DefaultTrees;
Parser* Parser::parInstance = 0;

Parser::Parser() {

	try{
		Trees=YAML::LoadFile(FILE_YAML);
	}
	catch (YAML::ParserException& e){
		 LOG("NO PUEDE ABRIRSE EL ARCHIVO " FILE_YAML ", SE CARGARÁ EL ARCHIVO DE CONFIGURACIÓN POR DEFECTO");
		 try{
		 		Trees=YAML::LoadFile(FILE_YAML_DEFAULT);
		 	}
		 	catch (YAML::BadFile& e){
		 		LOG("NO PUDO ABRIRSE EL ARCHIVO " FILE_YAML_DEFAULT " EL PROGRAMA SE INTERRUMPIRÁ");
		 		exit (1); //acá debería hacer un exit lindo
		 	}
	}

	Inicializar(Trees);

}

Parser::~Parser() {

}


YAML::Node Parser::getField(string field , string subField, YAML::Node nodo){

	YAML::Node result;
	if (subField.empty())
		result = nodo[field];
	else
		result = nodo[field][subField];

	if (result== NULL) {
		LOG ("SE INTENTÓ ACCEDER AL CAMPO INEXISTENTE "+field);
		//return nodo; //acá deberia buscar un valor por defecto
		/*if (subField.empty())
				result = DefaultTrees[field];
			else
				result = DefaultTrees[field][subField];
		return result;*/
		throw 0;

	}
	else
		return result;

}


YAML::Node Parser::getField(string field, YAML::Node::const_iterator it){
	YAML::Node result;
	result = (*it)[field];
	if (result== NULL) {
		LOG ("SE INTENTÓ ACCEDER AL CAMPO INEXISTENTE "+field);
		throw 0;
		//return result; //acá deberia buscar un valor por defecto, tengo que agarrar la lista de este iterador en el defaulTrees
		//return result;


	}
	else
		return result;


}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Parser::setField( std::string field, std::string subField,  YAML::Node nodo, int& aSetear){

/*	try{
		aSetear=getField(field ,subField, nodo).as<int>();
	}
	catch (YAML::TypedBadConversion<int>& e){
		LOG ("ERROR DE TIPO EN CAMPO " + field + " " + subField + ", SE CARGARÁ VALOR POR DEFECTO PARA EL MISMO");
		aSetear=getField(field ,subField, DefaultTrees).as<int>();
	}*/

	aSetear=getField(field ,subField, nodo).as<int>();


}

void Parser::setField(std::string field, std::string subField, YAML::Node nodo, string& aSetear){

/*	try{
		aSetear=getField(field ,subField, nodo).as<string>();
	}
	catch (YAML::TypedBadConversion<string>& e){
		LOG ("ERROR DE TIPO EN CAMPO " + field + " " + subField + ", SE CARGARÁ VALOR POR DEFECTO PARA EL MISMO");
		aSetear=getField(field ,subField, DefaultTrees).as<string>();
	}*/

	aSetear=getField(field ,subField, nodo).as<string>();

}


void Parser::setField(string field, YAML::Node::const_iterator it, string& aSetear){

	/*try{
		aSetear=getField(categoria, field, it).as<string>();
    	}
	catch (YAML::TypedBadConversion<string>& e){
		LOG ("ERROR DE TIPO EN CAMPO " + field +", SE CARGARÁ VALOR POR DEFECTO PARA EL MISMO");
		cout << (*it);
		}*/

	aSetear=getField(field, it).as<string>();


}


void Parser::setField(string field, YAML::Node::const_iterator it, int& aSetear){

/*	try{
		aSetear=getField(field, it).as<int>();
	}
	catch (YAML::TypedBadConversion<int>& e){
		LOG ("ERROR DE TIPO EN CAMPO " + field +", SE CARGARÁ VALOR POR DEFECTO PARA EL MISMO");
		if (field == "x" ){
			srand (time(NULL));
			aSetear = rand() % configGame.escenario.size_x + 1;
		}
		else if (field == "y"){
			srand (time(NULL));
			aSetear = rand() % configGame.escenario.size_y + 1;
		}
		else
			aSetear=getField(field , "", DefaultTrees).as<int>();
	}


	*/

	aSetear=getField(field, it).as<int>();


}

//////////////////////////////////////////////////////////////////////////////////////////////////




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


void Parser::Inicializar(YAML::Node Arbol){
	bool huboErrores = false;

	try{
		setField("pantalla" ,"alto", Arbol,configGame.pantalla.alto);
		setField("pantalla" ,"ancho", Arbol,configGame.pantalla.ancho);
		setField("configuracion" ,"vel_personaje", Arbol,configGame.configuracion.vel_personaje);
		setField("configuracion" ,"margen_scroll", Trees,configGame.configuracion.margen_scroll);

		YAML::Node tiposDeObjetos= getField("tipos","", Trees);

		map<string,ObjetoGeneral> listaDeObjetos;

		for (YAML::Node::const_iterator it = tiposDeObjetos.begin();it !=tiposDeObjetos.end(); it++){
			ObjetoGeneral unObjeto;

			setField("nombre",it,unObjeto.nombre);

			std::list<std::string> listaCampos;

			try{
				listaCampos = (camposObjetos.at(unObjeto.nombre));
			}
			catch(std::out_of_range& e){
				LOG ("SE INTENTÓ CARGAR UN OBJETO INVÁLIDO "+unObjeto.nombre);
				break; // no cargo el elemento
			}

			if (campoValido("imagen",listaCampos))
				setField("imagen",it,unObjeto.imagen);
			if (campoValido("alto",listaCampos))
				setField("alto",it,unObjeto.alto);
			if (campoValido("ancho",listaCampos))
				setField("ancho",it,unObjeto.ancho);
			if (campoValido("delay",listaCampos))
				setField("delay",it,unObjeto.animacion.delay);
			if (campoValido("fps",listaCampos))
				setField("fps",it,unObjeto.animacion.fps);
			if (campoValido("pixel_ref_x",listaCampos))
				setField("pixel_ref_x",it,unObjeto.pixelrefx);
			if (campoValido("pixel_ref_y",listaCampos))
				setField("pixel_ref_y",it,unObjeto.pixelrefx);

			listaDeObjetos.insert(std::pair<string,ObjetoGeneral>(unObjeto.nombre,unObjeto));
		}

		configGame.objetos=listaDeObjetos;

		setField("escenario" ,"nombre", Trees,configGame.escenario.nombre);
		setField("escenario" ,"size_x", Trees,configGame.escenario.size_x);
		setField("escenario" ,"size_y", Trees,configGame.escenario.size_y);

		std::vector<Entidad> listaDeEntidades;

		YAML::Node entidades= getField("escenario","entidades", Trees);
		for (YAML::Node::const_iterator it = entidades.begin();it !=entidades.end(); it++){
			Entidad unaEntidad;

			setField("tipo",it,unaEntidad.tipo);
			try{
				(camposObjetos.at(unaEntidad.tipo));
			}
			catch(std::out_of_range& e){
				LOG ("SE INTENTÓ CARGAR UN OBJETO INVÁLIDO "+unaEntidad.tipo);
				break; // no cargo el elemento
			}

			setField("x",it,unaEntidad.x);
			setField("y",it,unaEntidad.y);

			listaDeEntidades.push_back(unaEntidad);
		}

		configGame.escenario.entidades=listaDeEntidades;

		setField("protagonista" ,"tipo", Trees,configGame.protagonista.tipo);
		setField("protagonista" ,"x", Trees,configGame.protagonista.x);
		setField("protagonista" ,"y", Trees,configGame.protagonista.y);

	}
	catch (YAML::TypedBadConversion<int>& e){
		LOG("Hubo un error de conversión, se cargará el archivo YAML por defecto");
		huboErrores = true;
	}

	catch (int e){
		huboErrores = true;
	}


	if (huboErrores){
		cout << "hay que agarrar todo el árbol por defecto"<< endl;
		Trees=YAML::LoadFile(FILE_YAML_DEFAULT);
		Inicializar(Trees);
	}
}

} /* namespace std */
