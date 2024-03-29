#include "header2.h"
#include "header1.h"
using namespace std;

// default constructor
circuit::circuit()
{
  conntype = "empty";
  setimpedance();
  name = "circuit";
};

// two sub circuit constructor
circuit::circuit(circuit* sub_circuit_1,circuit* sub_circuit_2, string ctype)
{
  sub_circuit.push_back(sub_circuit_1);
  sub_circuit.push_back(sub_circuit_2);
  conntype = ctype;
  name = "circuit";
  setimpedance();
};

// one sub-circuit constructor
circuit::circuit(circuit* sub_circuit_1)
{
  sub_circuit.push_back(sub_circuit_1);
  conntype = "single";
  name = "circuit";
  setimpedance();
};

circuit::circuit(component* newcomponent)
{
  conntype = "component";
  name == "circuit";
  base_component = newcomponent;
  setimpedance();
};

circuit::circuit(int comonent_type)
{
  conntype = "component";
  name == "circuit";
  switch(comonent_type)
  {
    case(1):
    {
        cout<<"Input the resistance"<<endl;
        double  value;
        value=cinvalue();
        base_component = new resistor(value);
        break;
    };
    case(2):
    {
        cout<<"input the capacity"<<endl;
        double  value;
        value=cinvalue();
        base_component = new capacitor(value);
        break;
    };
    case(3):
    {
        cout<<"input the inductance"<<endl;
        double  value;
        value=cinvalue();
        base_component = new inductor(value);
        break;
    } ;
    default:
    {

    };
  };
  setimpedance();
}

void circuit::setimpedance()
{
    if(conntype=="series")
    {
        sub_circuit[0]->setf(frequency);
        sub_circuit[1]->setf(frequency);
        impedance = sub_circuit[0]->getimpedance()+sub_circuit[1]->getimpedance();
    }
    else if(conntype=="parallel")
    {
        sub_circuit[0]->setf(frequency);
        sub_circuit[1]->setf(frequency);
        impedance = complex<double>(1.0,0.0)/(complex<double>(1.0,0.0)/(sub_circuit[0]->getimpedance()+complex<double>(e,e))+complex<double>(1.0,0.0)/(sub_circuit[1]->getimpedance()+complex<double>(e,e))+complex<double>(e,e));
        if (abs(impedance.real()) <THRESHOLD) impedance.real(0.0);
        if (abs(impedance.imag()) < THRESHOLD) impedance.imag(0.0);
    }
    else if(conntype=="empty")
    {
        impedance = complex<double>(1/e,1/e);
    }
    else if(conntype=="single")
    {
        sub_circuit[0]->setf(frequency);
        impedance = sub_circuit[0]->getimpedance();
    }
    else if(conntype=="component")
    {
        base_component ->setf(frequency);
        impedance = base_component->getimpedance();
    }
};

//set the frequency of the circuit and update the impedance accordingly
void circuit::setf(double f)
{
    frequency=f;
    setimpedance();
};

void circuit::setf()
{
    cout << "Enter the frequency(Hz):"<<endl;
    cin >> frequency;
    setimpedance();
}

void circuit::info()
{
    setf();
    vector<bool> branch;
    branch.clear();
    int level=0;
    cout << "\n------Information of this circuit:-----"<<endl;
    cout << "impedance = " << impedance << ", frequency ="<< frequency <<" Hz."<<endl;
    if(conntype == "component")
    {
        cout << "circuit type is \" "<< conntype <<"\": " <<base_component->getname()<< endl;
        base_component -> info();
    }
    else
    {
        cout << "circuit type is \" "<< conntype <<"\""<< endl;
    }
    cout << "The magnitude is "<<getmagnitude()<<" and thePhase shift is: "<<getphase() <<endl;
    plot(branch,level);
};

void circuit::setvalue(double value){};

double circuit::getvalue(){};

void circuit::delsubcircuit()
{
    cout << "the current circuit is \" " << conntype <<"\" type" <<endl;
    // type 1
    if(conntype=="series" or conntype=="parallel")
    {
        int todelete = 0;
        cout << "enter which subcitcuit you want delete (1 or 2), if you want to stop deleting, input 0 : " <<endl;
        cin >> todelete;
        cout << todelete <<endl;
        if (todelete == 0)
        {
            cout << "Nothing is done." <<endl;
        }
        else if (todelete == 1)
        {
            cout << "subcircuit 1 is deleted, and this circuit is now \"single\" type" << endl;
            sub_circuit[0] = move(sub_circuit[1]);
            conntype = "single";
        }
        else if(todelete == 2)
        {
            cout << "subcircuit 2 is deleted" << endl;
            sub_circuit.erase(sub_circuit.begin()+1);
            conntype = "single";
            cout << "subcircuit 1 is deleted, and this circuit is now \"single\" type" << endl;
        }
        else
        {
            cout << "wrong input" <<endl;
        }
    }
    else if(conntype=="empty")
    {
        cout << "You can not delete subcircuit if it does not exist." <<endl;
    }
    else if(conntype=="single")
    {
        cout << "Delete or keep the only subcitcuit (1:deleting, 0: keeping): " << endl;
        int action = 1;
        cin >> action;
        if (action == 1)
        {
            cout << "you deleted the only subcircuit, now the type of this circuit is empty" << endl;
            sub_circuit.erase(sub_circuit.begin());
            conntype = "empty";
        }
        else
        {
            cout << "Thank you for keeping me, said by the subcircuit." << endl;
        }
    }
};

void circuit::setlabel(int inlabel)
{
    label = inlabel;
}

string circuit::getconntype()
{
    return conntype;
};

component* circuit::getcomponent()
{
    return base_component;
}

string circuit::get_component_name()
{
    if(conntype == "component")
    {
        return base_component->getname();
    }
    else
    {
        return "It's not a component circuit.";
    }
};

void circuit::format(vector<bool>& branch,int& level)
{
    for(int i=0;i<level;i++)
    {
        if(branch[i])
        {
            cout<<"| ";
        }
        else
        {
            cout<<"  ";
        }
    }
}

void circuit::branchtype(vector<bool>& branch,int& level,bool type)
{
    if(branch.size()<level+1)
    {
        branch.push_back(type);
    }
    else
    {
        branch[level]=type;
    }
}

void circuit::plot(vector<bool>& branch,int& level)
{
    if(conntype != "component")
    {
        if(conntype=="series" )
        {
            cout << "S" <<label<<endl;
            format(branch,level);
            cout<< "|-";
            branchtype(branch,level,1);
            level = level +1;// go to the next level
            sub_circuit[0]->plot(branch,level);
            format(branch,level);
            cout<< "`-";
            branchtype(branch,level,0);
            level = level+1;
            sub_circuit[1]->plot(branch,level);
            level = level - 1;
        }
        else if(conntype=="parallel")
        {
            cout<< "P" <<label<<endl;

            format(branch,level);
            cout<< "|-";
            branchtype(branch,level,1);
            level = level+1;
            sub_circuit[0]->plot(branch,level);
            format(branch,level);
            cout<< "`-";
            branchtype(branch,level,0);
            level = level+1;
            sub_circuit[1]->plot(branch,level);
            level = level - 1;

      }
      else if(conntype=="empty")
      {
            cout << "E"<<label<<endl;
            level = level -1;
      }
      else if(conntype=="single")
      {
            cout<< "O" <<label<< endl;
            format(branch,level);
            cout<< "`-";
            branchtype(branch,level,0);
            level = level+1;
            sub_circuit[0]->plot(branch,level);
            level = level -1;
      }
    }
    else
    {
        if(base_component->getname()=="resistor"){
        cout << "R"<<label<<"\n";
        level = level -1;
        }
        else if(base_component->getname() == "capacitor")
        {
            cout << "C"<<label<<"\n";
            level = level -1;
        }
        else if(base_component->getname() == "inductor")
        {
            cout << "L"<<label<<"\n";
            level = level -1;
        }
    }
}
