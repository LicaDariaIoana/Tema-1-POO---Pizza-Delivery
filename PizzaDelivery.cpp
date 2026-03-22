/*
Problema: Un program pentru managerul unui magazin de pizza delivery, in care poate sa vada cu usurinta date importante;

Date de intrare: ca date de intrare avem detalii despre pizza, clienti, angajati si comenzile plasate:

    -nume pizza, topinguri, blat, sos;
    -nume clienti, adresa lor, nr lor de telefon;
    -numele angajatilor, pozitia lor, orele lucrate saptamana aceasta, salariul lor pe ora, ora la care incep/ termina in ziua aceasta;
    -comenzile din acea zi, fiecare comanda fiind compusa din: clientul, pizzele comandate, curierul care livreaza, ora la care e plasata
     comanda respectiv ora la care ar trebui livrata;

Operatii posibile: Presupusul manager care foloseste acest program poate sa verifice:

     -ce pizze sunt disponibile in acea zi;
     -informatiile tuturor clientilor/ angajatilor din sistem;
     -comenzile plasate in acea zi;
     -cat trebuie platiti angajatii in acea zi;
     -daca exista cel putin un angajat care sa livreze comenzile in orice minut al programului stabilit(11-23.30);
     -daca comenzile plasate se pot livra sau nu;
     -daca nu se pot livra se afiseaza de ce nu ( din cauza nr de telefon fiind gresitintrodus/ livrarea a fost introdus in afara programului/ nu exista curier pentru cand trebuie livrata comanda);

*/

#include <string>
#include<fstream>
#include <vector>
#include <iostream>

class info_pizza{
private:
    std::string nume, topinguri, blat, sos;

public:
// constructorii, 1 deafault, 2 de initializare/ cu parametri, 3 de copiere, 4 destructor;
info_pizza(): nume(""), topinguri(""), blat(""), sos(""){}
info_pizza(const std::string& n, const std::string& t, const std::string& b, const std::string& s):nume(n), topinguri(t), blat(b), sos(s){}
info_pizza(const info_pizza& inca_una): nume(inca_una.nume), topinguri(inca_una.topinguri), blat(inca_una.blat), sos(inca_una.sos) {} // constructor de copiere, pt inca o pizza
~info_pizza(){}

//geteri:
std::string getNume() const{return nume;}
std::string getTopinguri() const{return topinguri;}
std::string getBlat() const{return blat;}
std::string getSos() const{return sos;}

//functie pt citire(>>) pentru info pizza
friend std::istream& operator>>(std::istream& citire_pizza, info_pizza& p){
    citire_pizza>>p.nume>>p.topinguri>>p.blat>>p.sos;
    return citire_pizza;}

// functia pt afisare(<<) pentru info pizaa
friend std::ostream& operator<<(std::ostream& afisare_pizza, const info_pizza& p){
    afisare_pizza<< "Tipul de pizza: "<<p.nume<<", topinguri: "<<p.topinguri<<", blat: "<<p.blat<<", sos: "<<p.sos<<";"<<std::endl;
    return afisare_pizza;}

//functia pt =
info_pizza& operator=(const info_pizza& p) {
    if (this != &p) {
        nume = p.nume;
        topinguri = p.topinguri;
        blat = p.blat;
        sos = p.sos;}
    return *this;}
};

class info_clienti{
private:
    std::string nume_client, adresa, nr_telefon;
public:
// constructorii:
    info_clienti(): nume_client(""), adresa(""), nr_telefon(""){}
    info_clienti(const std::string& n, const std::string& a, const std::string& t): nume_client(n), adresa(a), nr_telefon(t){}
    info_clienti(const info_clienti& inca_unul): nume_client(inca_unul.nume_client), adresa(inca_unul.adresa), nr_telefon(inca_unul.nr_telefon){}
    ~info_clienti(){}

//getari:
std::string getNume_client() const{ return nume_client;}
std::string getAdresa() const{ return adresa;}
std::string getNr_telefon() const{ return nr_telefon;}

//functia >> pt citire clienti:
friend std::istream& operator>>(std::istream& citire_clienti, info_clienti& c){
citire_clienti>>c.nume_client>>c.adresa>>c.nr_telefon;
return citire_clienti;
}

//functia << pt clientii
friend std::ostream& operator<<(std::ostream& afisare_clienti, const info_clienti& c){
    afisare_clienti<< "Clientul: "<<c.nume_client<<", aflat la adresa: "<<c.adresa<<", cu nr de telefon: "<<c.nr_telefon<<"."<<std::endl;
    return afisare_clienti;}

//functia =
info_clienti& operator= (const info_clienti& c){
    if (this != &c){
        nume_client = c.nume_client;
        adresa = c.adresa;
        nr_telefon = c.nr_telefon;}
    return *this;}

// functie validare telefon:
bool nr_tel_valid() const{
    if (nr_telefon.size() != 10){ return false;}
    if (nr_telefon[0] != '0' || nr_telefon[1] != '7'){return false;}
    return true;}
};

class angajati{
private:
    std::string nume, pozitie;
    float ore_lucrate, salariu, ora_start,ora_final;

public:
// constructorii:
    angajati(): nume("") ,pozitie(""), ore_lucrate(0), salariu(0), ora_start(0), ora_final(0){}
    angajati(const std::string& n, const std::string& poz, float o, float s, float os, float of): nume(n),pozitie(poz), ore_lucrate(o), salariu(s), ora_start(os), ora_final(of){}
    angajati(const angajati& inca_unul): nume(inca_unul.nume), pozitie(inca_unul.pozitie), ore_lucrate(inca_unul.ore_lucrate), salariu(inca_unul.salariu), ora_start(inca_unul.ora_start), ora_final(inca_unul.ora_final){}
    ~angajati(){}

//geteri:
const std::string getNume() const{ return nume;}
const std::string getPozitie() const{ return pozitie;}
float getOre_lucrate() const{ return ore_lucrate;}
float getSalariu() const{ return salariu;}
float getOra_start() const { return ora_start; }
float getOra_final() const { return ora_final; }

// functie citire(>>) pt angajati:
friend std::istream& operator>>(std::istream& citire_angajat, angajati& a){
citire_angajat>>a.nume>>a.pozitie>>a.ore_lucrate>>a.salariu>>a.ora_start>>a.ora_final;
return citire_angajat;
}

//functia << pt angajati:
friend std::ostream& operator<<(std::ostream& afisare_angajati, const angajati &a){
    afisare_angajati<<"Informatii despre angajat: nume: "<<a.nume<<", pozitie curenta: "<<a.pozitie<<", ore lucrate saptamana asta: "<<a.ore_lucrate<<", program: "<<a.ora_start<<" - "<<a.ora_final<<", salariu(pe ora): "<<a.salariu<<".\n";
    return afisare_angajati;}

//functia =
angajati& operator= (const angajati& a){
    if (this != &a){
        nume = a.nume;
        pozitie = a.pozitie;
        ore_lucrate = a.ore_lucrate;
        salariu = a.salariu;
        ora_start = a.ora_start;
        ora_final = a.ora_final;}
    return *this;}

// functie datoarie salariat
float castig_salariat() const{return ore_lucrate*salariu;}
};

class comanda{
private:
    info_clienti client_comanda;
    int cate;
    std::vector<std::string> pc; // pc = pizza comandata
    std::string curier_comanda;
    float ora_plasare, ora_livrare; // ora plasarii, livrarii comenzi, tre sa fie intre 11 si 23.30

public:
// constructorii:
    comanda(): client_comanda(),cate(0), pc(), curier_comanda(), ora_plasare(0), ora_livrare(0){}
    comanda(const info_clienti& c, int cat, const std::vector<std::string>& p, const std::string& cc, float op, float ol): client_comanda(c), cate(cat), pc(p), curier_comanda(cc), ora_plasare(op), ora_livrare(ol){}
    comanda(const comanda& inca_una): client_comanda(inca_una.client_comanda), cate(inca_una.cate), pc(inca_una.pc), curier_comanda(inca_una.curier_comanda), ora_plasare(inca_una.ora_plasare), ora_livrare(inca_una.ora_livrare){}
    ~comanda(){}

//getari:
info_clienti getClient_comanda() const{ return client_comanda;}
int getCate() const{ return cate;}
const std::vector<std::string> getPizza_comandata() const{ return pc;}
const std::string getCurier_comanda() const{ return curier_comanda;}
float getOra_plasare()const{ return ora_plasare;}
float getOra_livrare() const { return ora_livrare;}

//functia >> pt citire comenzi
friend std::istream& operator>>(std::istream& citire_comanda, comanda& c){
citire_comanda>> c.client_comanda>>c.cate;
for(int i=0; i<c.cate; i++){ std::string p; citire_comanda>>p; c.pc.push_back(p);}
citire_comanda>>c.curier_comanda>>c.ora_plasare>>c.ora_livrare;
return citire_comanda;
}

//functia << pt comanda plasata:
friend std::ostream& operator<<(std::ostream& afisare_comanda, const comanda& c){
    afisare_comanda<<c.client_comanda<<"Comanda contine "<<c.cate<<" pizza:\n";
    for ( int i=0; i< c.cate; i++){afisare_comanda<<i+1<<". "<<c.pc[i]<<" ";}
    afisare_comanda<<"\nLivrat de: "<<c.curier_comanda<<" "<< "ora plasare: " << c.ora_plasare<< ", ora livrare: " << c.ora_livrare<<"\n\n";
    return afisare_comanda;}

//functia =
comanda& operator= (const comanda& c){
    if (this != &c){
        client_comanda = c.client_comanda;
        cate = c.cate;
        pc=c.pc;
        curier_comanda = c.curier_comanda;
        ora_plasare = c.ora_plasare;
        ora_livrare = c.ora_livrare;}
    return *this;}

// functie timp livrare:
float timp_livrare() const{
float durata;
durata = ora_livrare+ora_plasare;
while(durata>1){ durata=durata-1;}
while(durata>=0.6){ durata=durata-0.6;}
return durata;}

//functie validare timp:
bool timp_valid() const{
    if (ora_plasare < 11 || ora_plasare > 23.3){return false;}
	return true;}
};

//functia exista destuli curieri?
void avem_curieri(std::vector<std::vector<float>> program) {
    if (program.empty()){ std::cout<<"Nu exista niciun curier azi!\n"; return;}

    // trebuie sortat in functie de stanga:
    for ( int i=0; i<program.size() -1; i++){
        for(int j=0; j<program.size()-i-1; j++){
            if(program[j][0] > program[j+1][0] ){
                std::vector<float> aux = program[j];
                program[j]=program[j+1];
                program[j+1]=aux;}}}

    float max_ora=program[0][1];
    bool avem_curier = true;

    if(program[0][0] > 11){ avem_curier = false;
        std::cout<<"Nu avem niciun curier intre orele: 11 - "<<program[0][0]<<" ";}

    for ( int i=1; i< program.size(); i++){
        if(max_ora<program[i][1]){max_ora=program[i][1];}
        if (program[i][0] > max_ora ){
            if(avem_curier == true){ std::cout<<" Nu avem niciun curier intre orele:  ";}
            avem_curier = false;
            std::cout<<program[i-1][1]<<" - "<<program[i][0]<<" ";}}

    if(max_ora<23.30){
        if(avem_curier == true){std::cout<<"Nu avem niciun curier intre orele: "; avem_curier = false;}
        std::cout<<max_ora<<" - 23.30 ";}
    if( avem_curier == true ){ std::cout<<"Avem destui curieri azi!\n";}
}

//functia daca se pot sau nu executa comenzile:
void da_nu_livrari(const std::vector<comanda>& comenzi, const std::vector<std::vector<float>>& program){
    for ( int i=0; i<comenzi.size(); i++ ){

        // verificam (cu metoda din comenzi) daca timpul valid (intre 11 si 23.30)
        if ( comenzi[i].timp_valid() == false)
                {std::cout<<"Comanda clientului "<<comenzi[i].getClient_comanda().getNume_client()<<" nu se poate livra, caci a fost plasata in afara programului.\n";
                 continue;}

        //verificam daca nr de telofon este valid
        if(comenzi[i].getClient_comanda().nr_tel_valid() == false )
            {std::cout<<"Nr de telefon al clientului "<<comenzi[i].getClient_comanda().getNume_client()<<" este invalid.\n";
             continue;}

        //verificam daca exista curier care lucreaza in acel interval
        bool se_poate_livra = false;
        for(int  j=0; j<program.size(); j++){
            if(comenzi[i].getOra_plasare() >= program[j][0] && comenzi[i].getOra_livrare() <= program[j][1])
                {se_poate_livra = true; break;}}

        //mesajul final, daca a trecut de retul validarilor:
        if( se_poate_livra ){ std::cout<<"Comanda clientului "<<comenzi[i].getClient_comanda().getNume_client()<<" se poate livra. Durata livrarii este de: "<<comenzi[i].timp_livrare()<<".\n";}
        else std::cout<<"Comanda clientului "<<comenzi[i].getClient_comanda().getNume_client()<<" nu se poate livra, caci nu exsista curieri disponibili.\n";
    }
}

int main(){
std::ifstream fin("date_intrare.txt");
int i,x;

//citire pizza
int nr_pizza;
fin>>nr_pizza;
std::vector<info_pizza> pizza(nr_pizza);
for( i=0; i<nr_pizza; i++){ fin>>pizza[i];}

//citire clienti
int nr_clienti;
fin>>nr_clienti;
std::vector<info_clienti> clienti(nr_clienti);
for(i=0; i<nr_clienti; i++){fin>>clienti[i];}

//citire angajati:
int nr_angajati;
fin>>nr_angajati;
std::vector<angajati> angajatii(nr_angajati);
std::vector<std::vector<float>> program;
for(i=0; i<nr_angajati; i++){
    fin>>angajatii[i];
    program.push_back({angajatii[i].getOra_start(), angajatii[i].getOra_final()});}

//citire comenzi:
int nr_comenzi;
fin>>nr_comenzi;
std::vector<comanda> comenzi(nr_comenzi);
for(i=0; i<nr_comenzi; i++){fin>>comenzi[i];}

do{

std::cout<<"Buna ziua!\n Alegeti ce informatii doriti sa vedeti\n1. Pizza disponibila\n2.Informatii clienti\n";
std::cout<<"3.Informatii angajatii\n4.Informatii comenzi\n5.Daca avem destui curieri programati sa lucreze\n6.Daca se pot excuta toate livrarile\n";
std::cout<<"7.Cat trebuie platit fiecare angajat ziua acesata\nDaca doriti sa inchideti, apasati 0.\n\n";

std::cin>>x;
    switch(x) {
    case 0:
        std::cout<<"Zi buna!";
        break;
    case 1:
        std::cout<<"Pizza disponibila in aceasta zi:\n";
        for(i=0; i<nr_pizza; i++){ std::cout<<pizza[i];}
        break;
    case 2:
        std::cout<<"Informatii clienti:\n";
        for(i=0; i<nr_clienti; i++){ std::cout<<clienti[i];}
        break;
    case 3:
        std::cout<<"Informatii angajatii:\n";
        for(i=0; i<nr_angajati; i++){ std::cout<<angajatii[i];}
        break;
    case 4:
        std::cout<<"Comenzile plasate azi:\n\n";
        for(i=0; i<nr_comenzi; i++){ std::cout<<comenzi[i];}
        break;
    case 5:
        avem_curieri(program);
        break;
    case 6:
        std::cout<<"Se verifică eligibilitatea comenzilor pentru livrare:\n";
        da_nu_livrari(comenzi, program);
        break;
    case 7:
        std::cout<<"Detalii plata angajati:\n";
        for(i=0; i<angajatii.size(); i++){ std::cout<<"Angajatul: "<<angajatii[i].getNume()<<" trebuie sa incaseze "<<angajatii[i].castig_salariat()<<" de lei;\n";}
        break;
    default:
        std::cout <<x<<" nu este o optinue, va rog alegeti una dintre obtiunile prezentate mai jos1.";
        break;}

std::cout<<"\n\n\n";
}while(x != 0);

fin.close();
return 0;}
