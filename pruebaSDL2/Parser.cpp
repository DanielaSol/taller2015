#include "Parser.h"
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"
#include "Logger.h"


namespace std {

Parser::Parser() {
	 std::ifstream fileYaml( FILE_YAML );

	    if (fileYaml){

	        YAML::Node Trees=YAML::LoadFile(FILE_YAML);

	        std::cout << YAML::Dump(Trees) << std::endl;
	        if(!Trees["pantalla"])
	        {
	          std::cerr << "Required tree not found." << std::endl;
	          exit(1);
	        }
	        const YAML::Node& tree = Trees["pantalla"];
	        std::cout << YAML::Dump(tree) << std::endl;



		    }
	    else
		cout << "(llamar log)";



}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */



