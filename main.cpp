#include <iostream>
#include <string>
#include <sstream>

using namespace std;



class Pet {
    
public:
    
    static const int MAX_PETS = 10*1000*1000;
    Pet ();
    int getLimb();
    long getID() const { return myID;}
    long getRandomID();
    int RandomnumLimbs();
    static string search(long id, Pet **petsArray, long size, long start, long end);
    string toString();
    
    
private:
    
    long myID;
    string name;
    static int population;
    int numLimbs = 4;
    string makeFunName();
    
};

static bool comparePetsbyID(const Pet *pet1, const Pet *pet2);
                           
int main() {

    int id;
    Pet **pets;
    
    pets = new Pet*[Pet::MAX_PETS];
    for(int i = 0; i<Pet::MAX_PETS; i++){
        pets[i] = new Pet();
    }
    
    sort(pets, pets+Pet::MAX_PETS, comparePetsbyID);
    
    while(true){
        cout << "Enter id: \n";
        cin >> id;
        if(id<0)
            break;
        string name = Pet::search(id, pets, Pet::MAX_PETS, 0, Pet::MAX_PETS-1);
        cout << name;
    }
    
    for(int i = 0; i<Pet::MAX_PETS; i++){
        delete pets[i];
    }
    
    delete[] pets;
}

Pet::Pet()
{
    this->myID = getRandomID();
    this->name = makeFunName();
    this->numLimbs = RandomnumLimbs();
    
}

bool comparePetsbyID(const Pet *pet1, const Pet *pet2){
    
    return (pet1->getID() < pet2->getID());
    
}

string Pet::toString()
{
    ostringstream cnvrt;
    cnvrt << "ID: " << myID << "| Name: " << name << "| Number of Limbs: " << numLimbs << endl;
    return cnvrt.str();
}

string Pet::search(long id, Pet **petsArray, long size, long start, long end)
{
    long midpt = (start + end)/2;
    
    if(petsArray[midpt]->getID() == id)
    {
        return petsArray[midpt]->toString();
    }
    
    if (start == end)
        return "ID does not exist\n\n";
    
    if(start < 0 || end >= size)
        return "Invalid";
    
    if(petsArray[midpt]->getID() > id)
    {
        return search(id, petsArray, size, start, midpt-1);
    }
    else if(petsArray[midpt]->getID() < id)
    {
        return search(id, petsArray, size, midpt+1, end);
    }
 
    return "";
    
}

long Pet::getRandomID()
{
    return arc4random_uniform(10* MAX_PETS);
}

int Pet::getLimb()
{
    return numLimbs;
}

int Pet::RandomnumLimbs()
{
    return arc4random_uniform(15);
}

string Pet::makeFunName()
{
    const int MAX_NAME_LEN = 10;
    const int MIN_NAME_LEN = 5;
    
    string vowels("aeiou");
    string consonants("bcdfghjklmnpqrstvwxz");
    enum CharType {vowel, consonant};
    static CharType prevCharType = consonant;
    
    ostringstream nameStream;
    
    
    int nameLen = arc4random() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;
    
    for (int i=0; i < nameLen; i++)
    {
       
        if (prevCharType == vowel) {
            nameStream << consonants[arc4random() % consonants.length()];
            prevCharType = consonant;
        }
        else {
            nameStream << vowels[arc4random() % vowels.length()];
            prevCharType = vowel;
        }
}


string name = nameStream.str();
name[0] = toupper(name[0]);

return name;

}

//Sample Output
//Enter id:
//3
//ID: 3| Name: Wapuzal| Number of Limbs: 3
//Enter id:
//-1
//Program ended with exit code: 0
