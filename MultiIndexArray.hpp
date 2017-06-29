#ifndef MULTIINDEXARRAY_HPP_INCLUDED
#define MULTIINDEXARRAY_HPP_INCLUDED

#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>
#include <functional>



template<typename T>
class MultiIndexArray{
private:
    /* Az aktív indexOrder sorszáma */
    size_t activeIndexOrderNumber;
    /* Az adatokat tároló vektor */
    std::unique_ptr<std::vector<T>> dataVector;
    /* Az indexelőtömböket tároló vektor */
    std::unique_ptr<std::vector<std::vector<size_t>>> indexOrderVector;
public:
    /* Konstruktorok */
    MultiIndexArray();
    MultiIndexArray(std::vector<T>& inputData);
    MultiIndexArray(MultiIndexArray const& other);
    MultiIndexArray(MultiIndexArray && other);

    /* Destruktor jó az eredeti */
    ~MultiIndexArray() = default;

    /* Másoló és mozgató op= */
    MultiIndexArray& operator=(MultiIndexArray const& other);
    MultiIndexArray& operator=(MultiIndexArray && other);

    /* Specifikáció függvényei */
    void add(T element);                            //elem hozzáadása
    void remove(T element);                         //elem megkeresése és kivétele
    void removeAt(size_t which);                    //elem lekérése adott indexen
    void addNewIndexOrder();                        //új indexelőtömb hozzáadása
    void removeIndexOrder(size_t which);               //adott indexelőtömb törlése
    void setActiveIndexOrder(size_t which);            //aktív indexelőtömb kiválasztása
    void sortData(std::function<bool(T,T)> cmp);    //rendezőfüggvény, egy predikátumot vár

    /* at objektumok eléréséhez, op[] objektumok módosításához */
    T const& at(size_t i) const;
    T& operator[](size_t i);

    /* "getterek" */
    int size(){return dataVector->size();}
    int indexOrderSize(){return indexOrderVector->size();}
};



/* Nullparaméteres konstruktor, inicializálja az adattagokat üres vektorokkal */
template <typename T>
MultiIndexArray<T>::MultiIndexArray(){
    dataVector = std::make_unique<std::vector<T>>(std::vector<T>{});
    indexOrderVector = std::make_unique<std::vector<std::vector<size_t>>>(std::vector<std::vector<size_t>>{});
    indexOrderVector->push_back(std::vector<size_t>{});
    activeIndexOrderNumber = 0;
}

/* Konstruktor std::vectorból, inicializálja az adattagokat üres vektorokkal,
 * majd a dataVectorba bemásolja az inputData-ban lévő objektumokat.
 * Ezen kívül létrehoz egy indexelőtömböt, amely a fizikai tárolás szerint van sorban */
template <typename T>
MultiIndexArray<T>::MultiIndexArray(std::vector<T>& inputData){
    dataVector = std::make_unique<std::vector<T>>(std::vector<T>{});
    indexOrderVector = std::make_unique<std::vector<std::vector<size_t>>>(std::vector<std::vector<size_t>>{});
    indexOrderVector->push_back(std::vector<size_t>{});
    for(unsigned int i = 0; i < inputData.size(); ++i){
        dataVector->push_back(inputData.at(i));
        indexOrderVector->at(0).push_back(i);
    }
    activeIndexOrderNumber = 0;
}

/* Másoló konstruktor, létrehozza üresen a this vektorait, majd azokat feltölti az other adataival
 * Először az adatokat másolja át a dataVectorba, majd utána az összes indexelőtömböt */
template <typename T>
MultiIndexArray<T>::MultiIndexArray(MultiIndexArray const& other){
    dataVector = std::make_unique<std::vector<T>>(std::vector<T>{});
    indexOrderVector = std::make_unique<std::vector<std::vector<size_t>>>(std::vector<std::vector<size_t>>{});
     /* Bemásoljuk az adatokat az othertől az új dataVectorba */
    for(unsigned int i = 0; i < other.dataVector->size(); ++i){
        dataVector->push_back(other.dataVector->at(i));
    }
    /* Lemásoljuk az indexelő tömböket */
    for(unsigned int i = 0; i < other.indexOrderVector->size(); ++i){
        indexOrderVector->push_back(std::vector<size_t>{});
        for(unsigned int j = 0; j < other.dataVector->size(); ++j){
            indexOrderVector->at(i).push_back(other.indexOrderVector->at(i).at(j));
        }
    }
    activeIndexOrderNumber = other.activeIndexOrderNumber;
}

/* Mozgató konstruktor, először ellopjuk a unique_ptr és move segítségével a vectorokat */
template <typename T>
MultiIndexArray<T>::MultiIndexArray(MultiIndexArray && other){
    dataVector = std::unique_ptr<std::vector<T>>(std::move(other.dataVector));
    indexOrderVector = std::unique_ptr<std::vector<std::vector<size_t>>>(std::move(other.indexOrderVector));
    activeIndexOrderNumber = other.activeIndexOrderNumber;
    other.activeIndexOrderNumber = 0;
    /* std::move miatt nem kell nullptr-re állítani*/
}

/* Sima Op= */
template <typename T>
MultiIndexArray<T>& MultiIndexArray<T>::operator=(MultiIndexArray const& other){
    /* Önértékadás vizsgálata */
    if(this != &other){
        /* Kitöröljük az eddigi adatokat a vektorokból */
        dataVector.reset();
        indexOrderVector.reset();
        /* Újakra mutatunk */
        dataVector = std::make_unique<std::vector<T>>(std::vector<T>{});
        indexOrderVector = std::make_unique<std::vector<std::vector<size_t>>>(std::vector<std::vector<size_t>>{});
        /* Bemásoljuk az adatokat az othertől az új dataVectorba */
        for(unsigned int i = 0; i < other.dataVector->size(); ++i){
            dataVector->push_back(other.dataVector->at(i));
        }
        /* Lemásoljuk az indexelő tömböket */
        for(unsigned int i = 0; i < other.indexOrderVector->size(); ++i){
            indexOrderVector->push_back(std::vector<size_t>{});
            for(unsigned int j = 0; j < other.dataVector->size(); ++j){
                indexOrderVector->at(i).push_back(other.indexOrderVector->at(i).at(j));
            }
        }
        activeIndexOrderNumber = other.activeIndexOrderNumber;
    }
    return (*this);
}

/* Mozgato Op= */
template <typename T>
MultiIndexArray<T>& MultiIndexArray<T>::operator=(MultiIndexArray && other){
    /* Önértékadás vizsgálata */
    if(this != &other){
        /* Kitöröljük az eddigi adatokat a vektorokból */
        dataVector.reset();
        indexOrderVector.reset();
        /* Újakra mutatunk, lopunk */
        dataVector = std::unique_ptr<std::vector<T>>(std::move(other.dataVector));
        indexOrderVector = std::unique_ptr<std::vector<std::vector<size_t>>>(std::move(other.indexOrderVector));
        activeIndexOrderNumber = other.activeIndexOrderNumber;
        other.activeIndexOrderNumber = 0;
    }
    return (*this);
}

/* T típus elem hozzáadása a dataVectorhoz
 * Emellett minden indexelő tömb végére adunk egy elemet
 * ami az új elem indexét tárolja */
template <typename T>
void MultiIndexArray<T>::add(T element){
    dataVector->push_back(element);
    for(auto& ixo : *indexOrderVector){
        ixo.push_back(dataVector->size()-1);
    }
}

/* A paraméterben kapott elemet keresi meg, és törli ki a dataVectorból,
 * ha nem találja meg, akkor nem csinál semmit */
template <typename T>
void MultiIndexArray<T>::remove(T element){
    unsigned int which = 0;         //benne számoljuk az eltolást
    for(auto stored : *dataVector){
        if(stored == element){      //ha megvan, megállunk
            break;
        }
        ++which;    //egyébként növeljük az eltolást
    }
    /* ha nem találtuk meg, akkor which megegyezik dataVector->size()-zal */
    if(which != dataVector->size()){
        /* Kitöröljük a megtalált elemet */
        dataVector->erase(dataVector->begin()+which);
        /* Kitöröljük az indexekből is a rá "hivatkozót" */
        for(unsigned int i = 0; i < indexOrderVector->size(); ++i){
            size_t atWhere = 0;
            /* Megkeressük minden indexelő tömbben a törlendő elemet */
            for(unsigned int j = 0; j < dataVector->size()+1; ++j){
                if(which == indexOrderVector->at(i).at(j)){//megtaláljuk, eltároljuk
                    atWhere = j;
                    break;  //nem megyünk tovább a ciklussal
                }
            }
            indexOrderVector->at(i).erase(indexOrderVector->at(i).begin()+atWhere); //kitöröljük
            for(unsigned int j = 0; j < dataVector->size(); ++j){
                if(indexOrderVector->at(i).at(j) > which){
                    --indexOrderVector->at(i)[j];   //csökkentjük a többit
                }
            }
        }
    }
}

template <typename T>
void MultiIndexArray<T>::removeAt(size_t which){
    if(which < dataVector->size() && which >= 0){
        /* Kitöröljük az adott helyről az elemet */
        dataVector->erase(dataVector->begin()+which);
        for(unsigned int i = 0; i < indexOrderVector->size(); ++i){
            size_t atWhere = 0;
            /* Megkeressük minden indexelő tömbben a törlendő elemet */
            for(unsigned int j = 0; j < dataVector->size()+1; ++j){
                if(which == indexOrderVector->at(i).at(j)){//megtaláljuk, eltároljuk
                    atWhere = j;
                    break;  //nem megyünk tovább a ciklussal
                }
            }
            indexOrderVector->at(i).erase(indexOrderVector->at(i).begin()+atWhere); //kitöröljük
            for(unsigned int j = 0; j < dataVector->size(); ++j){
                if(indexOrderVector->at(i).at(j) > which){
                    --indexOrderVector->at(i)[j];   //csökkentjük a többit
                }
            }
        }
    }
}

/* Hozzáad egy új indexelő tömböt az objektumhoz.
 * Létrehozáskor a fizikai indexeléssel egyenértékű */
template <typename T>
void MultiIndexArray<T>::addNewIndexOrder(){
    std::vector<size_t> newIndexOrder = std::vector<size_t>();
    for(unsigned int i = 0; i < dataVector->size(); ++i){
        newIndexOrder.push_back(i);
    }
    indexOrderVector->push_back(newIndexOrder);
}

/* Eltávolítja a megadott sorszámú indexelő tömböt, kivéve
 * ha az a fizikai (azaz a 0 sorszámú) */
template <typename T>
void MultiIndexArray<T>::removeIndexOrder(size_t which){
    if(which != 0){
        indexOrderVector->erase(indexOrderVector->begin()+which);
        if( activeIndexOrderNumber > which){
            --activeIndexOrderNumber;   // a föléesőt csökkentjük
        } else if(activeIndexOrderNumber == which){
            activeIndexOrderNumber = 0; // ha a jelenlegit töröltük, akkor fizikaira váltunk
        }
    } else{
        throw std::invalid_argument("A fizikai indexek nem torolhetok");
    }
}

/* Kiválasztunk egy aktív indexelő tömböt */
template <typename T>
void MultiIndexArray<T>::setActiveIndexOrder(size_t which){
    if(which < 0 || which > indexOrderVector->size()){
        throw std::domain_error("Out of range indexeles, ez az indexelotomb, nem letezik");
    }
    activeIndexOrderNumber = which;
}

/* Rendező függvény
 * Először létrehoz egy std::pair<T*, size_t> ből álló vektort, amit majd rendezni fogunk.
 * Létrehozunk egy olyan függvényobjektumot(*), amiben egy három bemeneti paraméterű lambda kifejezés
 * első két tagja std:pair, amit az std::sort fog beletenni, a harmadik pedig rögzítetten a kapott cmp predikátum.
 * Ezáltal a std::sort-ba eljut a predikátum, és ez alapján tud dönteni a T* pointereken keresztül, hogy miként rendezze sorba az objektumokat.
 * Végül a rendezett std::pair tömb adataival felülírjuk az eddigi indexeket */
template <typename T>
void MultiIndexArray<T>::sortData(std::function<bool(T,T)> cmp){
    if(activeIndexOrderNumber == 0){
        throw std::invalid_argument("A fizikai indexek nem rendezhetoek.");
    }
    std::vector<std::pair<T*, size_t>> result = std::vector<std::pair<T*, size_t>>{};
    for(unsigned int i = 0; i < dataVector->size(); ++i){
        result.push_back(std::pair<T*, size_t> {&(dataVector->at(i)), i});
    }
//(*)
    auto parametrizedCmp = std::bind([](std::pair<T*, size_t> a, std::pair<T*, size_t> b, std::function<bool(T,T)> compare){ return compare(*(a.first),*(b.first));},
                                    std::placeholders::_1, std::placeholders::_2, cmp);
    std::sort(result.begin(), result.end(), parametrizedCmp);
    for(unsigned int i = 0; i < result.size(); ++i){
        indexOrderVector->at(activeIndexOrderNumber)[i] = result.at(i).second;
    }
}

/* Objektumokhoz való hozzáférés konstans változata */
template <typename T>
T const& MultiIndexArray<T>::at(size_t i) const{
    if(i > dataVector->size() || i < 0)
        throw std::domain_error("Out of range indexeles");
    return dataVector->at((*indexOrderVector)[activeIndexOrderNumber][i]);
}

/* Objektumokhoz való hozzáférés változtató szándék esetén */
template <typename T>
T& MultiIndexArray<T>::operator[](size_t i){
    if(i > dataVector->size() || i < 0)
        throw std::domain_error("Out of range indexeles");
    return (*dataVector)[(*indexOrderVector)[activeIndexOrderNumber][i]];
}


#endif // MULTIINDEXARRAY_HPP_INCLUDED
