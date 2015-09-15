/*
 * Logger.cpp
 *
 *  Created on: 15/09/2015
 *      Author: daniela
 */

#include "Logger.h"
#include <iostream>
#include <fstream>

using namespace std;

Logger::Logger() {
	file.open("log.txt");

}

Logger::~Logger() {
	file.close();
}


void Logger::write(char * message) {
    time_t tim;
    time(&tim);

    file << message << " - " << ctime(&tim);



}




