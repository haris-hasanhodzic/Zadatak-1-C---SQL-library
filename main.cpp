/* 
 * File:   main.cpp
 * Author: Haris
 *
 * Created on October 5, 2013, 3:31 PM
 */

#include <iostream>
#include <string.h>
#include "address.h"
#include "data.h"
#include "network.h"
#include "database.h"

using namespace std;

int main(int argc, char** argv) {

    addrInNetwork::data input;
    addrInNetwork::address ip;
    addrInNetwork::network net;
    
    if(argc>4 || argc<3){
        cerr<<"Pogresan broj argumenata!\n";
        cerr<<"Primjeri poziva aplikacije:\n";
        cerr<<"./aplikacija --database test.db 10.0.0.0\n";
        cerr<<"./aplikacija mreze.txt 10.0.0.0\n";
        return -1;
    }

    if(strcmp(argv[1],"--database")==0)
    {   
        addrInNetwork::database d(argv[2]);
        if (!ip.set_addr(argv[3]))
        {
            cerr<<"Pogresna IP adresa";
            return -1;
        }        
              
        if (sqlite3_prepare( d.db, "SELECT network FROM NETWORKS WHERE ? BETWEEN NETFROM(network) AND NETTO(network);", -1, &d.stmt, NULL )!=SQLITE_OK)
        {
            std::cerr<<sqlite3_errmsg(d.db);
            return false;
        }
        sqlite3_bind_int(d.stmt, 1, ip.addr());
        
        while (sqlite3_step( d.stmt )==SQLITE_ROW)
        {
                cout<<sqlite3_column_text( d.stmt, 0 )<<"\n";
        }
        sqlite3_finalize(d.stmt);      
        
    }
    else
    {
        if (!input.source(argv[1]))
            return -1;
        if (!ip.set_addr(argv[2]))
        {
            cerr<<"Pogresna IP adresa";
            return -1;
        }
        char c_name[18];
        string name;

        while((name=input.read())!="")
        {
            strcpy(c_name, name.c_str());
            if (!net.set(c_name))
            {
                cerr<<"Pogresna mrezna adresa";
                continue;
            }
            if (net.has_addres(ip))
                cout<<name<<"\n"; 
        }
    }

    return 0;
}