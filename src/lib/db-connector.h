#ifndef _DB_CONNECTOR_H
#define _DB_CONNECTOR_H

class Connector_DB{
    private:
        //Cambiar
        const char * server = "localhost";
        const char * user = "dbuser";
        const char * password = "comprayventa";
        const char * database = "comprayventa";

        MYSQL * con;
        MYSQL_RES * res;
        
    public:
        Connector_DB();
        ~Connector_DB();
        MYSQL* connect();
        MYSQL_RES* query(char const*);
        void clean_result();
};

#endif // DB_CONNECTOR_H