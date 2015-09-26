/*
 * Logger.cpp
 *
 *  Created on: 15/09/2015
 *      Author: daniela
 */

#include "Logger.h"
#include <fstream>
#include "time.h"

using namespace std;

Logger::Logger() {
	file=fopen("log.txt","w+");
}

Logger::~Logger() {
	fclose(file);
}

FILE *Logger::file;


void Logger::write(string message) {
	  time_t rawtime;
	  struct tm * timeinfo;

	  time ( &rawtime );
	  timeinfo = localtime ( &rawtime );

	  string salida = message + " - " + asctime (timeinfo);
	  fputs(salida.c_str(),file);

}




