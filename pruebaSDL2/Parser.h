/*
 * Parser.h
 *
 *  Created on: 16/09/2015
 *      Author: daniela
 */

#ifndef PARSER_H_
#define PARSER_H_

#define FILE_YAML_DEFAULT "../Files/configDefault.yaml"
#define FILE_YAML "../Files/config.yaml"


namespace std {

class Parser {
public:
	Parser();
	virtual ~Parser();
};

} /* namespace std */
#endif /* PARSER_H_ */
