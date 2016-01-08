//
//  main.cpp
//  Simulazione-Goodnes-of-fit
//
//  Created by Gabriele on 07/01/16.
//  Copyright © 2016 Gabriele. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

#define DISCRETA
const double n = 156;
struct row { float valore; float occorenza; };
std::vector<row> rows =
{
	{ 0.,59. },
	{ 1.,26. },
	{ 2.,24. },
	{ 3.,18. },
	{ 4.,12. },
	{ 5.,5. },
	{ 6.,4. },
	{ 7.,3. },
	{ 9.,3. },
	{ 11.,2. },
};

const double parametri_geometrica = 1;

double F_geometrica(double x, double p)
{
	return 1. - std::pow((1. - p), x + 1);
}

double p_geometrica(double x, double p)
{
	return p*std::pow((1. - p), x);
}


int main(int argc, const char * argv[])
{
	///////////////////////////////////////////////////////////
	double x_segnato = 0;

	for (const row& r : rows)
	{
		x_segnato += r.valore * r.occorenza;
	}

	x_segnato /= n;

	std::cout << "x segnato: " << x_segnato << "\n";
	///////////////////////////////////////////////////////////
	double s_2 = 0;

	for (const row& r : rows)
	{
		s_2 += r.occorenza * std::pow(r.valore - x_segnato, 2.0);
	}

	s_2 /= n - 1;

	std::cout << "s^2: " << s_2 << "\n";
	///////////////////////////////////////////////////////////
	//parametro distribuzione
	const double parametro = 0.346;
	//calcolo vettore frequenze
	std::vector< double > f;
	std::vector< double > F;
	std::vector< double > p;
#if defined( DISCRETA )
	for (const row& r : rows)
	{
		f.push_back(r.occorenza / n);
		p.push_back(p_geometrica(r.valore, parametro));
		F.push_back(p_geometrica(r.valore, parametro)*n);
	}
#else
#error non supportato
#endif
	///////////////////////////////////////////////////////////
	std::cout << "Valore\t\tOccorrenze\t\tFrequenza\t\tp(i)\t\tF(i)\n";
	for (size_t i = 0; i != rows.size(); ++i)
	{
		std::cout
			<< rows[i].valore << "\t\t"
			<< rows[i].occorenza << "\t\t"
			<< f[i] << "\t\t" << p[i] << "\t\t" << F[i] << "\t" << "\n";
	}
	///////////////////////////////////////////////////////////
	// Goodnes richiede almeno 5 osservazioni
	double occorenze_somma = 0;
	double f_somma = 0;
	double F_somma = 0;
	double p_somma = 0;
	size_t i = rows.size()-1;
	for (; i != 0; --i)
	{
		if (rows[i].occorenza < 5)
		{
			occorenze_somma += rows[i].occorenza;
			f_somma += f[i];
			F_somma += F[i];
			p_somma += p[i];
		}
		else { ++i; break; }
	}

	if (i != rows.size())
	{
		rows[i].occorenza = occorenze_somma;
		f[i] = f_somma;
		F[i] = F_somma;
		p[i] = p_somma;
		//reduce
		rows.resize(i + 1);
		f.resize(i + 1);
		F.resize(i + 1);
		p.resize(i + 1);
	}
	std::cout << "\n";
	std::cout << "Solo valori con almeno 5 osservazioni:\n";
	std::cout << "Valore\t\tFrequenza\t\tp(i)\t\tF(i)\n";
	for (size_t i = 0; i != rows.size(); ++i)
	{
		std::cout
			<< rows[i].valore << "\t\t"
			<< rows[i].occorenza << "\t\t"
			<< f[i] << "\t\t" << p[i] << "\t\t" << F[i] << "\t" << "\n";
	}
	///////////////////////////////////////////////////////////
	//calcolo varianza tra la quantità teorica e quella osservata
	// (fi-Fi)^2 / Fi
	double kquadro = 0;
	for (size_t i = 0; i != rows.size(); ++i)
	{
		kquadro += std::pow(rows[i].occorenza - F[i], 2.0) / F[i];
	}
	///////////////////////////////////////////////////////////
	std::cout << "kquadro: " << kquadro << "\n";
	std::cout << "df: " << rows.size() - 1 - parametri_geometrica << "\n";
	///////////////////////////////////////////////////////////

	return 0;
}