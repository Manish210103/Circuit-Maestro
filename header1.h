#include<iostream>
#include<math.h>
#include<string>
#include<complex>
#include <vector>
#include "header2.h"
#include "header.h"
//#include "circuit.h"
using namespace std;

#ifndef interface_h
#define interface_h

double cinvalue();//get postive double value
void construct_circuit(vector<component*>& , vector<circuit*>& );//construct circuit
void instruction_of_circuit_construction();
void components_modify(vector<component*>& );//
void get_information_components(vector<component*> );
void get_information_circuits(vector<circuit*> circuits_container);
void get_information(vector<component*>, vector<circuit*>);
void create_component(vector<component*>&);
void component_circuit_construct(vector<component*>& , vector<circuit*>&);
int get_number(int , int );
bool yes_or_no(string);
void circuit_modify(vector<component*>& , vector<circuit*>& );
void interface();


#endif // HEADER1_H_INCLUDED
