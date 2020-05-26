#include "rpqItem.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <string>

int czasDzialania(const std::vector<rpqItem> &rpqVector) {

	int m = 0;
	int c = 0;
	int wynik;

	for (unsigned int i = 0; i < rpqVector.size(); ++i) {

		m = std::max(rpqVector[i].r, m) + rpqVector[i].p;
		c = std::max(m + rpqVector[i].q, c);
	}

	wynik = c;

	std::cout   << "Dlugosc dzialania algorytmu wynosi: " << wynik << std::endl;

	return c;
}


bool czyDostepne(rpqItem& rpq, int time) {
	return (rpq.r <= time);
}

int main() {

	// WCZYTYWANIE DANYCH

	int numberOfElements = 0;
	std::vector<rpqItem> rpqVector;

	int r, p, q;

	double czasTrwaniaOstateczny = 0;
	int czasDzialaniaOstateczny = 0;

	
	// ITERATOR PO NAZWACH PLIKOW
	for (auto iteratorPlik = 1; iteratorPlik <= 9; iteratorPlik++)
	{

		std::stringstream ss;
		ss << "data" << iteratorPlik << ".txt";
		std::string name = ss.str();

		std::cout << "Nazwa pliku: " << name << std::endl;

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



		std::vector<rpqItem> wykonane;

		int time = 0;
		int maxQIndex = 0;
		double czasTrwania = 0;

		//Z podzialem
		int tnext = 999999999;
		bool dostepne = false;

		//CZAS START
		auto start = std::chrono::high_resolution_clock::now();


		//ALGORYTM
		while (!rpqVector.empty())
		{
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

		//CZAS STOP
		auto stop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

		czasTrwania = time_span.count();
		czasTrwaniaOstateczny += czasTrwania;

		// OBLICZANIE WYNIKU


		//for (int i = 0; i < wykonane.size() ; ++i) {
		//	wykonane[i].printRPQ();
		//}


		std::cout << std::endl << "Kolejka procesow: ";
		for (int i = 0; i < wykonane.size(); ++i) {

			std::cout << wykonane[i].ordinalNumber << " ";
		}
		std::cout << std::endl;

		czasDzialaniaOstateczny += czasDzialania(wykonane);

		std::cout  << "Czas trwania algorytmu:" << czasTrwania << std::endl << std::endl;

	}

	std::cout << "Czas dzialania algorytmu dla wszystkich zestawow danych: " << czasTrwaniaOstateczny << "s" << std::endl;

	std::cout << "Laczny czas kolejki dla wszystkich zestawow danych: " << czasDzialaniaOstateczny << std::endl;

	std::getchar();
	return 0;
}
