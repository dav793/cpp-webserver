build-prod: src/webserver.cpp
	g++ -I C:/Users/gagas/Documents/ucr/seguridad/proyecto/src src/webserver.cpp src/lib/config.cpp src/lib/template-parser.cpp -o bin/webserver.cgi

build-dev: src/webserver.cpp
	g++ -I C:/Users/gagas/Documents/ucr/seguridad/proyecto/src src/webserver.cpp src/lib/config-dev.cpp src/lib/template-parser.cpp -o bin/webserver