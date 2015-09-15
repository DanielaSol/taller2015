/*
 * Logger.h
 *
 *  Created on: 15/09/2015
 *      Author: daniela
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <fstream>

namespace std {

class Logger {



public:

	ofstream file;

	Logger();

	~Logger();

	void write(char * message) ;
};

} /* namespace std */
#endif /* LOGGER_H_ */
