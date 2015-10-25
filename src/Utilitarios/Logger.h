/*
 * Logger.h
 *
 *  Created on: 15/09/2015
 *      Author: daniela
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <fstream>

#define LOG(message)   Logger::write(message)
#define logfile Logger::file



namespace std {

class Logger {


public:

	static FILE *file;

	Logger();

	~Logger();

	static void write(std::string message) ;

};

} /* namespace std */
#endif /* LOGGER_H_ */
