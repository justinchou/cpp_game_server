#include <iostream>
#include <string>
#include <map>
using namespace std;

class Persion{
public:
    Persion(string name){this->name = name;}
public:
    string name;
};

class PL
{
public:
    void add(int,string);
    void DisplayPersion();
private:
    map<int,Persion*> persion;
};


void Display(map<int,string> &m)
{
    map<int,string>::iterator te = m.begin();
    while(te != m.end())
    {
        cout<<(*te).first<<"\t"<<(*te).second<<endl;
        te++;
    }
}

//template<typename MapType,typename KeyType, typename ValueType>
//typename MapType::iterator save(MapType &curMap, const KeyType &key, const ValueType &value)
//{
//    typename MapType::iterator ite = curMap.lower_bound(key);
//    if(ite != curMap.end())// && !curMap.comp(key, ite->first))
//    {
//        ite->second = value;
//        return ite;
//    }
//    return NULL;
//    } else {
//        pair<KeyType, ValueType> temp(key, value);
//        return curMap.insert(ite, temp);
//    }
//}

int main()
{
    map<int,string> mymap;
    pair<int,string> s1(1,"aa");
    pair<int,string> s2(2,"bb");
    pair<int,string> s3(3,"cc");
    pair<int,string> s4(4,"dd");
    pair<int,string> s5(1,"ee");
    mymap.insert(s1);
    mymap.insert(s2);
    mymap.insert(s3);
    mymap.insert(s4);
    mymap.insert(s5);

//    save(mymap,2,"ff");

    mymap[2] = "ff";
    mymap[3] = "ff";

    cout<<"new:"<<endl;
    Display(mymap);

    cout<<"copy:"<<endl;
    map<int,string>mymap2(mymap);
    Display(mymap2);

//    cout<<"copy2:"<<endl;
//    int *first = new int(2);
//    int *last = new int(4);
//    map<int,string>mymap3(first,last,mymap);
//    Display(mymap3);
    PL *pl = new PL();
    pl->add(133,"xiaoming");
    pl->add(22368,"xiaoli");
    pl->add(32,"xiaogang");
    pl->add(44456,"xiaowei");
    pl->DisplayPersion();
    return 0;
}

void PL::add(int i,string name)
{
    Persion *tmp1 = new Persion(name);
    pair<int,Persion*> tmp2(i,tmp1);
    this->persion.insert(tmp2);
}
void PL::DisplayPersion()
{
    map<int,Persion*> &m = this->persion;
    map<int,Persion*>::iterator te = m.begin();
    while(te != m.end())
    {
        cout<<(*te).first<<"\t"<<(*te).second<<"\t"<<(*te).second->name<<endl;
        te++;
    }
}

