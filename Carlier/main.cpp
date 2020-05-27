#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <string>

class rpqItem{

public:
	int r;
	int p;
	int q;
	int ordinalNumber;

	rpqItem(int r, int p, int q, int oN) {
		this->r = r;
		this->p = p;
		this->q = q;
		ordinalNumber = oN;
	}

	void rpqItem::printRPQ(){
	    std::cout << r << " " << p << " " << q << ": " << ordinalNumber << std::endl;	
    }

};

bool czyDostepne(rpqItem& rpq, int time) {
	return (rpq.r <= time);
}

std::vector<rpqItem> schragePodzial(std::vector<rpqItem> &rpqVector){
    
    std::vector<rpqItem> wykonane;

	int time = 0;
	int maxQIndex = 0;

	int tnext = 999999999;
	bool dostepne = false;

    //ALGORYTM
	while (!rpqVector.empty()){

		dostepne = false;
		rpqItem maxQ(-1, -1, -1, 0);
		rpqItem minR(9999999, 0, 0, 0);

		for (int i = 0; i < rpqVector.size(); ++i) {
			if (czyDostepne(rpqVector[i], time)) {

				if (rpqVector[i].q > maxQ.q) {
					maxQ = rpqVector[i];
					maxQIndex = i;
				}

				if(tnext >= rpqVector[i].r){
					tnext = rpqVector[i].r;
				}
			}
			else if (rpqVector[i].r < minR.r) {
				minR = rpqVector[i];
			}

		}

		if (maxQ.ordinalNumber != 0) {

			if(tnext < (time + maxQ.p)){
				maxQ.p = maxQ.p - (tnext - time);
				time = tnext;
			}else{
				time = time + maxQ.p;

				wykonane.push_back(maxQ);
				rpqVector.erase(rpqVector.begin() + maxQIndex);
			}
		}
		else {
			time = tnext;
		}
	}

    return wykonane;
}

std::vector<rpqItem> schrageBezPodzialu(std::vector<rpqItem> &rpqVector){

    std::vector<rpqItem> wykonane;

	int time = 0;
	int maxQIndex = 0;
    
    while (!rpqVector.empty()){
		rpqItem maxQ(-1, -1, -1, 0);
		rpqItem minR(9999999, 0, 0, 0);

		for (int i = 0; i < rpqVector.size(); ++i) {
			if (czyDostepne(rpqVector[i], time)) {
				if (rpqVector[i].q > maxQ.q) {
					maxQ = rpqVector[i];
					maxQIndex = i;
				}
			}
			else if (rpqVector[i].r < minR.r) {
				minR = rpqVector[i];
			}
		}

		if (maxQ.ordinalNumber != 0) {
			wykonane.push_back(maxQ);
			rpqVector.erase(rpqVector.begin() + maxQIndex);

			time = time + maxQ.p;
		}
		else {
			time = time + minR.r;
		}
	}
    return wykonane;
}

int wyznaczB(int cmax, std::vector<rpqItem> &rpqVector){
    int B = 0;
        
    for (int i = rpqVector.size() - 1; i > 0; i--) {
        if (cmax == (obliczC(rpqVector, i) + rpqVector[i].q)) {
            B = i;
            return B;
        }
    }
    return B;
}

int wyznaczA(int B, int cmax, std::vector<rpqItem> &rpqVector){
    int A, tmp = 0;
        for (A = 0; A < B; A++) {
            tmp = 0;
            for (int j = A; j <=B; j++) { 
                tmp += rpqVector[j].p;
            }
            if (cmax == (tmp + rpqVector[A].r + rpqVector[B].q)) {
                return A;
            }
        }
    return A;
}

int wyznaczRefC(int A, int B, std::vector<rpqItem> rpqVector) {
        int C = -1;
        for (int i = B; i >= A; i--) {
            if (rpqVector[i].q < rpqVector[B].q) {
                return i;
            }
        }
        return C;
    }

int obliczC(std::vector<rpqItem> rpqVector, int index){

    int m = 0;
	int c = 0;
	int wynik;

	for (unsigned int i = 0; i < index; ++i) {

		m = std::max(rpqVector[i].r, m) + rpqVector[i].p;
		c = std::max(m + rpqVector[i].q, c);
	}

	wynik = c;

	return c;
}

std::vector<rpqItem> carlier(std::vector<rpqItem> &rpqVector){
    int LB;
    int U;
    int UB=0;
    
    int tmpr = 99999999;
    int tmpq = 99999999;
    int tmpp = 0;

    int tmpA, tmpB, tmpC;

    std::vector<rpqItem> tmp;

    tmp = schrageBezPodzialu(rpqVector);
    U = czasDzialania(tmp);

    if(U < UB)
        return tmp;

    tmpB = wyznaczB(U, tmp);
    tmpA = wyznaczA(tmpB, U, tmp);
    tmpC = wyznaczRefC(tmpA, tmpB, tmp);

    if(tmpC == 0)
        return tmp;

    for (int i = tmpC+1; i =< tmpB; i++)
    {
        if(tmpr > tmp[i].r)
            tmpr = tmp[i].r;

        if(tmpq > tmp[i].q)
            tmpr = tmp[i].q;

        tmpp += tmp[i].p;
    }
    

    LB = czasDzialania(schragePodzial(rpqVector));
}


int czasDzialania(const std::vector<rpqItem> &rpqVector) {

	int m = 0;
	int c = 0;
	int wynik;

	for (unsigned int i = 0; i < rpqVector.size(); ++i) {

		m = std::max(rpqVector[i].r, m) + rpqVector[i].p;
		c = std::max(m + rpqVector[i].q, c);
	}

	wynik = c;

	std::cout   << "Dlugosc dzialania algorytmu (Cmax) wynosi: " << wynik << std::endl;

	return c;
}



void inicjalizujVector(std::vector<rpqItem> &rpqVector, std::string name){

    int numberOfElements = 0;
    int r, p, q;


	std::fstream plik;
	plik.open(name, std::ios::in | std::ios::out);

		if (plik.good() == true) {
			plik >> numberOfElements;

			for (int i = 0; i < numberOfElements; ++i) {
				plik >> r;
				plik >> p;
				plik >> q;

				rpqVector.push_back(rpqItem(r, p, q, i + 1));
			}

			plik.close();
		}
		else {
			std::cout << "FILE DID NOT OPEN";
		}
}

void showPermutation(std::vector<rpqItem> &rpqVector){
    std::cout << std::endl << "Kolejka procesow: ";
	for (int i = 0; i < rpqVector.size(); ++i) {
		std::cout << rpqVector[i].ordinalNumber << " ";
	}
	std::cout << std::endl;
}

int main() {

	// WCZYTYWANIE DANYCH
	std::vector<rpqItem> rpqVector;
    
	double czasTrwaniaOstateczny = 0;

	
	// ITERATOR PO NAZWACH PLIKOW
	for (auto iteratorPlik = 1; iteratorPlik <= 9; iteratorPlik++)
	{

		std::stringstream ss;
		ss << "data" << iteratorPlik << ".txt";
		std::string name = ss.str();

		std::cout << "Nazwa pliku: " << name << std::endl;

		inicjalizujVector(rpqVector, name);
		std::vector<rpqItem> wykonane;

        double czasTrwania = 0;
		//CZAS START
		auto start = std::chrono::high_resolution_clock::now();

        // MIEJSCE NA ALGORYTM **************************************
		wykonane = schragePodzial(rpqVector);

        // KONIEC MIEJSCA NA ALGORYTM *******************************

		//CZAS STOP
		auto stop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

		czasTrwania = time_span.count();
		czasTrwaniaOstateczny += czasTrwania;

        std::cout  << "Czas trwania algorytmu:" << czasTrwania << std::endl << std::endl;
        //czasDzialaniaOstateczny += czasDzialania(wykonane);
	}

	std::cout << "Czas dzialania algorytmu dla wszystkich zestawow danych: " << czasTrwaniaOstateczny << "s" << std::endl;

	std::getchar();
	return 0;
}
