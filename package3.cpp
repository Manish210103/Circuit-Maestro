#include "header1.h"
#include<fstream>
#include <stdlib.h>


void interface()
{
  cin.clear();
  circuit* usercircuit;
  vector<circuit*> circuits_container;
  vector<component*> components_container;
  bool running=true;
  do
    {
    int choice=0;
    cout << "\n==============Menu================"<<endl;
    cout << "1. Components Creation\n";
    cout << "2. Circuit Creation\n";
    cout << "3. List of components\n";
    cout << "4. Circuits Information\n";
    cout << "5. List all circuits\n";
    cout << "6. Circuit and Component Deletion\n";
    cout << "7. Exit\n";
    cout << "==================================="<<endl;
    cout << "Enter your choice : ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            create_component(components_container);
            break;
        }

        case 2:
        {
            construct_circuit(components_container, circuits_container);
            break;
        }

        case 3:
        {
            get_information_components(components_container);
            break;
        }

        case 4:
        {
            get_information_circuits(circuits_container);
            break;
        }

        case 5:
        {

            cout<<"\nCircuits Stored :\n"<<endl;
            vector<string>v;
            ifstream file;
            file.open("circuit.txt",ios::in);
            if(file.eof())
                cout<<"File is empty";
            else
            {
                string line;
                while(file)
                {
                    getline(file,line);
                    v.push_back(line);
                }
                for(int i=0;i<v.size();i++)
                    cout<<v[i]<<endl;
                break;
            }
        }

        case 6:
        {
            if(yes_or_no("Do you want to delete all data : "))
            {
                circuits_container.clear();
                components_container.clear();
            }
            else
            {
            cout << "Data is not deleted " << endl;
            }
            ofstream file;
            file.open("circuit.txt",ios::trunc);
            file.close();
            break;
        }

        case 7:
        {
            if(yes_or_no("Do you want to Exit ?"))running = false;
            break;
        }
        default: cout<<"Wrong input."<<endl;
    }
    }while(running);
}

void create_component(vector<component*>& components_container)
{
  bool repeat(true);
  do
  {
    int component_choice=0;
    double value;
    cout<< "\n==================================="<<endl;
    cout << "Input the type of components you want to add:\n\n";
    cout << "1. resistor\n";
    cout << "2. capacitor\n";
    cout << "3. inductor\n";
    cout<< "==================================="<<endl;
    cout << "Your choice : ";
    cin >> component_choice;
    switch(component_choice)
    {
      case 1:
        {
            cout << "\ninput the resistance in Omega:";
            value=cinvalue();
            components_container.push_back(new resistor(value));
            cout << "You just created an resistor,";
            cout << " stored in component_container["<< components_container.size()-1<<"] component" <<endl;
            break;
        }
      case 2:
        {
            cout << "\ninput the capacity:";
            value=cinvalue();
            components_container.push_back(new capacitor(value));
            cout << "You just created an capacitor, ";
            cout << "stored in component_container["<< components_container.size()-1<<"] component" <<endl;
            break;
        }
      case 3:
        {
            cout << "\ninput the inductance:";
            value=cinvalue();
            components_container.push_back(new inductor(value));
            cout << "You just created an inductor, ";
            cout << "stored in component_container["<< components_container.size()-1<<"] component" <<endl;
            break;
        }
        default:{cout << "\nWrong input" << endl;};
    }
    char input;
    do
    {
      cout <<"\nDo you want to continue creating components? y/n"<<endl;
      cin >> input;
    }while(input != 'y' && input!='n');

    repeat = (input=='y');
  }while(repeat);
}

void construct_circuit(vector<component*>& components_container, vector<circuit*>& circuits_container)
{
    bool repeat(true);
    do
    {

        cout << "\nYou are going to construct a circuit"<<endl;
        char input;
        do
        {//creat circuits
        if(circuits_container.size()==0)
        {
            cout << "There is not any circuit constructed, at least one \"component\" circuit is required. "<<endl;
            component_circuit_construct(components_container,  circuits_container);
            break;
        }
        else
        {
            int type_of_circuit;
            do
            {
                cout << "What type of circuit you want to construct?"<<endl;
                cout << "\n1: parallel\n2: series\n3: Single\n4: Create circuit\n5: Empty\n" << endl;
                cin >> type_of_circuit;
            }while(type_of_circuit!=1 && type_of_circuit!=2 &&type_of_circuit!=3 &&type_of_circuit!=4 &&type_of_circuit!=5);

            switch(type_of_circuit)
            {
              case(1):
              {
                    cout << "choose two existing circuit from circuits_container to connect them in parallel"<<endl;
                    get_information_circuits(circuits_container);
                    cout << "Choose two circuits as subcircuits connected in parallel:"<<endl;
                    int subc1,subc2;
                    do
                    {
                        cout << "1st one (0~"<<circuits_container.size()-1 <<") : ";
                        cin >> subc1;
                    }while(subc1>=circuits_container.size());
                    do
                    {
                        cout << "2nt one (0~"<<circuits_container.size()-1 <<") : ";
                        cin >> subc2;
                    }while(subc2>=circuits_container.size());
                    circuits_container.push_back(new circuit(circuits_container[subc1],circuits_container[subc2],"parallel"));
                    cout << "\nA parallel-circuit is created and stored at" << "circuits_container[" <<circuits_container.size()-1<<"]"<<endl;
                    break;
              };
              case(2):
              {
                    cout << "\nchoose two existing circuit from circuits_container to connect them in series"<<endl;
                    get_information_circuits(circuits_container);
                    cout << "Choose two circuits as subcircuits connected in series:"<<endl;
                    int subc1,subc2;
                    do
                    {
                        cout << "1st one (0~"<<circuits_container.size()-1 <<"): ";
                        cin >> subc1;
                    }while(subc1>=circuits_container.size());
                    do
                    {
                        cout << "2st one (0~"<<circuits_container.size()-1 <<"): ";
                        cin >> subc2;
                    }while(subc2>=circuits_container.size());
                    cout << "2nd one (0~"<<circuits_container.size()-1 <<"): ";
                    circuits_container.push_back(new circuit(circuits_container[subc1],circuits_container[subc2],"series"));
                    cout << "\nA series-circuit is created and stored at" << "circuits_container[" <<circuits_container.size()-1<<"]"<<endl;
                    break;
                };
                case(3):
                {
                    cout << "\nYou are going to create a single circuit: " <<endl;
                    get_information_circuits(circuits_container);
                    int subc1;
                    do
                    {
                        cout << "Choose an existing circuit as the only subcircuit(0~"<<circuits_container.size()-1 <<"): ";
                        cin >> subc1;
                    }while(subc1>=circuits_container.size());
                    circuits_container.push_back(new circuit(circuits_container[subc1]));
                    cout << "\nA single-circuit is created and stored at circuits_container["<<circuits_container.size()<<"]"<<endl;
                    break;
                };
                case(4):
                {
                    component_circuit_construct(components_container,  circuits_container);
                    break;
                }
                case(5):
                {
                    circuits_container.push_back(new circuit());
                    cout << "\nA empty-circuit is created and stored at circuits_container["<<circuits_container.size()<<"]"<<endl;
                };
                default:
                {

                };
            }
          }
          cout <<"\nDo you want to continue consturcting circuit? y/n"<<endl;
          cin >> input;
        }while(input != 'y' && input!='n');
    circuits_container[circuits_container.size()-1]->setlabel(circuits_container.size()-1);
    repeat = (input=='y');
    }while(repeat);
}

void component_circuit_construct(vector<component*>& components_container, vector<circuit*>& circuits_container)
{

    ofstream file;
    int first_circuit;
    file.open("circuit.txt",ios::app);
    int choice=1;
    do
    {
        cout << "\n1: choose one from components container\n2: create a new component "<<endl;
        cin>>choice;
    }while(choice!=1 && choice!=2);
    switch(choice)
    {
        case(1):
        {
            if(components_container.size()==0){
            cout<<"\nNo components in component container, you need to create a new one."<<endl;
            }
            else
            {
                get_information_components(components_container);
                cout << "Choose one:";
                circuits_container.push_back(new circuit(components_container[get_number(0, components_container.size()-1)]));
                break;
            }
        }
        case(2):
        {
            do
            {
                cout<<"\nInput the type of first component circuit (1: resistor; 2: capacitor; 3: inductor):" <<endl;
                cin >> first_circuit;
            }while((first_circuit!=1 && first_circuit !=2)&& first_circuit!=3);
            circuits_container.push_back(new circuit(first_circuit));
            break;
        };
        default:
        {

        }
    }
    file.write((char*)&circuits_container,sizeof(circuit));
    cout << "A component-circuit is created and stored at circuits_container["<<circuits_container.size()<<"]"<<endl;
    file.close();
}

void get_information_circuits(vector<circuit*> circuits_container)
{
    if(circuits_container.size()==0)
    {
        cout<<"There are no circuits"<<endl;
    }
    else
    {
        cout << "There are "<< circuits_container.size() << " circuits"<<endl;\
        bool input = yes_or_no("Do you want to get the information for any one of the stored circuits?");
        if(input)
        {
            cout << "Which one's information do you want to get? input 0~"<< circuits_container.size()-1<<endl;
            int circuit_label=0;
            do
            {
                cin >> circuit_label;
                if(circuit_label==-1)break;
                if( circuit_label < circuits_container.size() && circuit_label>=0)
                {
                    circuits_container[circuit_label]->info();
                }
                else
                {
                    cout<<"No such a circuit."<<endl;
                }
                cout<<"Input -1 to exist, input 0~"<< circuits_container.size()-1<<" to show another ones' infomation"<< endl;
            }while(true);
        }
    }
}

void get_information_components(vector<component*> components_container)
{
    if(components_container.size()==0)
    {
        cout<<"There are no components"<<endl;
    }
    else
    {
        cout << "Here are "<< components_container.size() << " components: type(value)"<<endl;
        for(int i=0;i<components_container.size();i++)
        {
            cout<< i <<": " << components_container[i] ->getname()<<"("<<components_container[i] ->getvalue()<<"); ";
        }
    }
}

int get_number(int lowerbound, int upperbound)
{
    int innumber;
    cout<<" "<<lowerbound<<"~"<<upperbound<<":"<< endl;
    do
    {
        cin >> innumber;
    }while(innumber>lowerbound && innumber<lowerbound);
    return innumber;
};



bool yes_or_no(string sentence)
{
  char userinput;
  do
  {
    cout << sentence << " (y/n):";
    cin>>userinput;
  }while(userinput!='y' && userinput!='n');
  return userinput == 'y';
}

double cinvalue()
{
  double value=1;
  cin>>value;
  try
  {
        if(value<0)
        {
            throw "entered value is negative";
        }
  }
  catch(const string s1)
  {
      cout<<s1;
      cout<<"\nRe-enter the value : ";
      cinvalue();
  }
  return value;
}

