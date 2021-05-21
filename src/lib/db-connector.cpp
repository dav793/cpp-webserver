#include <mysql/mysql.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "db-connector.h"

Connector_DB::Connector_DB(){
    this->connect();
}

Connector_DB::~Connector_DB(){
    mysql_close(this->con);
}

MYSQL* Connector_DB::connect(){
    this->con = mysql_init(NULL); // mysql instance
    
    //connect database
    if(!mysql_real_connect(this->con, this->server, this->user, this->password, this->database, 0, NULL, 0)){
        cout << "Connection Error: " << mysql_error(this->con) << std::endl;
        exit(1); 
    }
    
    return con; 
}

MYSQL_RES* Connector_DB::query(char const* sql_query){

    if(mysql_query(this->con, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(this->con) << std::endl;
        exit(1);
    }

    return mysql_use_result(this->con);
}

void Connector_DB::clean_result(){
    mysql_free_result(this->res);
}