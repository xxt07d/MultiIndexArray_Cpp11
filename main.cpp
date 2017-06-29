#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "MultiIndexArray.hpp"

/* A projekt code:blocks-ban készült */
/* c++14ben írt egyszerre többféleképpen indexelhetõ tömb */
/* Itt kb std::cout = komment */

int main()
{
    std::cout << "Letrehozunk egy ures MultiIndexArray<double>-t" << std::endl;
    MultiIndexArray<double> ures = MultiIndexArray<double>{};
    std::cout << "\tMegnezzuk, hogy tenyleg ures-e. ures.size(): " << ures.size() << std::endl;
    ures.add(197.1546);
    std::cout << "\tHozzaadunk egy erteket: 197.1546" << std::endl;
    std::cout << "\tures.at(0): " << ures.at(0);
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Teszt int adatok: 9 5 7 3 1 2 4" << std::endl;
    std::vector<int> teszt = {9, 5, 7, 3, 1, 2, 4};
    std::cout << "\tLetrehozunk az adatokbol egy MultiIndexArrayt, amire egy unique_pointer mutat" << std::endl;
    std::unique_ptr<MultiIndexArray<int>> MIA1 = std::make_unique<MultiIndexArray<int>>(MultiIndexArray<int>{teszt});
    std::cout << "\tKiiratjuk az elemeit: ";
    for(int i = 0; i < MIA1->size(); ++i){
        std::cout << MIA1->at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Adunk hozza uj indexelesi sorrendet " << "MIA1->addNewIndexOrder();" << std::endl;
    MIA1->addNewIndexOrder();
    std::cout << "Felvettuk es most aktivnak allitunk egy uj IndexOrder-t" << std::endl;
    MIA1->setActiveIndexOrder(1);
    std::cout << "\tEnnyi IndexOrder volt elotte: " << MIA1->indexOrderSize() << std::endl;
    std::cout << "\tEnnyi IndexOrder lett utana: " << MIA1->indexOrderSize();
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Rendezzuk az uj IndexOrder (std::greater)" << std::endl;
    MIA1->sortData(std::greater<int>{});
    std::cout << "\tKiiratjuk rendezve" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<MIA1->size(); ++i){
        std::cout << MIA1->at(i) << ' ';
    }
    std::cout << std::endl << "\tEs rendezetlenul, a regi indextombbel " << std::endl;
    std::cout << "\t\t";
    MIA1->setActiveIndexOrder(0);
    for(int i = 0; i<MIA1->size(); ++i){
        std::cout << MIA1->at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Megnezzuk, hogy elso indexben is jol tortenik-e minden(elem hozzadasa, MIA masolasa)" << std::endl;
    MIA1->setActiveIndexOrder(1);
    std::cout << "\tHozzaadunk egy erteket: 13" << std::endl;
    MIA1->add(13);
    std::cout << "\tkiiratjuk megint" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<MIA1->size(); ++i){
        std::cout << MIA1->at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Letrehozunk mozgato konstruktorral egy uj MIA-t" << std::endl;
    MultiIndexArray<int> movedMIA = std::move(*MIA1);
    std::cout << "\tHa ugyanaz a kiiras mint az elobb, akkor minden rendben" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<movedMIA.size(); ++i)
        std::cout << movedMIA.at(i) << ' ';
    movedMIA.setActiveIndexOrder(0);
    std::cout << std::endl;
    std::cout << "\tKiiratjuk a nulladik(fizikai) index szerint" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<movedMIA.size(); ++i){
        std::cout << movedMIA.at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Letrehozunk operator=-vel egy ures MIA-bol egy masikat" << std::endl;
    MultiIndexArray<int> optesztMIA = MultiIndexArray<int>{};
    std::cout << "\tLemasoljuk az elozo objektumot, es beletesszuk a 8462-t" << std::endl;
    optesztMIA = movedMIA;
    optesztMIA.add(8462);
    std::cout << "\tMegnezzuk, hogy ott van-e a tobbi kozott" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Toroljunk a fizikai index szerint!" << std::endl;
    std::cout << "Kiiratjuk eloszor a 0-as IndexOrderben az elemeket" << std::endl;
    std::cout << '\t';
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl;
    std::cout << "Kiiratas torles utan (6. indexû elem) (removeAt)" << std::endl;
    optesztMIA.removeAt(6);
    std::cout << '\t';
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl << "Kiiratas torles utan (9-es elem) (remove)" << std::endl;
    optesztMIA.remove(9);
    std::cout << '\t';
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl << "Megnezzuk, hogy az eredeti, amirol masoltunk valtozott-e" << std::endl;
    std::cout << '\t';
    for(int i = 0; i<movedMIA.size(); ++i){
        std::cout << movedMIA.at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Toroljunk az 1-es IndexOrderrel!" << std::endl;
    optesztMIA.setActiveIndexOrder(1);
    std::cout << "Kiiratjuk eloszor az 1-es IndexOrderben az elemeket" << std::endl;
    std::cout << '\t';
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl;
    std::cout << "Kiiratas torles utan (2. indexû elem) (removeAt)" << std::endl;
    optesztMIA.removeAt(2);
    std::cout << '\t';
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl << "Kiiratas torles utan (8462-es elem) (remove)" << std::endl;
    optesztMIA.remove(8462);
    std::cout << '\t';
    for(int i = 0; i<optesztMIA.size(); ++i){
        std::cout << optesztMIA.at(i) << ' ';
    }
    std::cout << std::endl << "Megnezzuk, hogy az eredetit, amirol masoltunk valtozott-e" << std::endl;
    std::cout << '\t';
    for(int i = 0; i<movedMIA.size(); ++i){
        std::cout << movedMIA.at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Letrehozok egy std::string vektort az alabbi szavakbol:" << std::endl;
    std::cout << "\talma fa tizennegyedik hetes barack kifli tea" << std::endl;
    std::vector<std::string> szavak = std::vector<std::string>{"alma", "fa", "tizennegyedik", "hetes", "barack", "kifli", "tea"};
    std::cout << "\tLetrehozok egy uj MIA-t belole" << std::endl;
    auto sztringMIA = MultiIndexArray<std::string>(szavak);
    std::cout << "\tKiiratom:" << std::endl;
    std::cout << "\t\t";
    for(unsigned int i = 0; i<szavak.size(); ++i){
        std::cout << szavak.at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Adok hozza uj indextombot" << std::endl;
    sztringMIA.addNewIndexOrder();
    std::cout << "Adok hozza meg egy uj indextombot" << std::endl;
    sztringMIA.addNewIndexOrder();
    std::cout << "Az elsot novekvo sorrendbe, a masodikat csokkeno sorrendbe rendezem" << std::endl;
    sztringMIA.setActiveIndexOrder(1);
    sztringMIA.sortData([](auto a, auto b){ return a < b;});
    sztringMIA.setActiveIndexOrder(2);
    sztringMIA.sortData([](auto a, auto b){ return a > b;});
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Letrehozok copy konstruktorral egy masik MIA-t, es ott kiiratom mindharom nezet szerint" << std::endl;
    auto copySztringMIA = sztringMIA;
    copySztringMIA.setActiveIndexOrder(0);
    std::cout << "\tFizikai" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<copySztringMIA.size(); ++i){
        std::cout << copySztringMIA.at(i) << ' ';
    }
    std::cout << std::endl;


    copySztringMIA.setActiveIndexOrder(1);
    std::cout << "\tNovekvo" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<copySztringMIA.size(); ++i){
        std::cout << copySztringMIA.at(i) << ' ';
    }
    std::cout << std::endl;


    copySztringMIA.setActiveIndexOrder(2);
    std::cout << "\tCsokkeno" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<copySztringMIA.size(); ++i){
        std::cout << copySztringMIA.at(i) << ' ';
    }
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Hozzaadom a KENYER szot ehhez a MIA-hoz" << std::endl;
    copySztringMIA.add("KENYER");
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "Az eredeti sztring MIA-t felulirom a KENYER-et tartalmazoval es kiiratom mindharom nezet szerint" << std::endl;
    std::cout << "Ilyenkor mindegyik IndexOrder szerinti utolso elem a KENYER lesz" << std::endl;
    sztringMIA = std::move(copySztringMIA);
    sztringMIA.setActiveIndexOrder(0);
    std::cout << "\tFizikai" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<sztringMIA.size(); ++i){
        std::cout << sztringMIA.at(i) << ' ';
    }
    std::cout << std::endl;


    sztringMIA.setActiveIndexOrder(1);
    std::cout << "\tNovekvo" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<sztringMIA.size(); ++i){
        std::cout << sztringMIA.at(i) << ' ';
    }
    std::cout << std::endl;


    sztringMIA.setActiveIndexOrder(2);
    std::cout << "\tCsokkeno" << std::endl;
    std::cout << "\t\t";
    for(int i = 0; i<sztringMIA.size(); ++i){
        std::cout << sztringMIA.at(i) << ' ';
    }
    return 0;
}
