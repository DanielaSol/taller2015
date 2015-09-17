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

namespace std {

class Parser {
public:
	Parser();
	virtual ~Parser();
	YAML::Node getField(std::string field, YAML::Node nodo);
	YAML::Node getField(string field, YAML::Node::const_iterator it);
};

} /* namespace std */
#endif /* PARSER_H_ */
