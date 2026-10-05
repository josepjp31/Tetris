#include "Joc.h"
#include <fstream>
using namespace std;

bool Joc::generarFigura()
{
	TipusFigura tipus = TipusFigura((rand() % N_TIPUS_FIGURES) + 1);
	int columnaMax = N_COL_TAULER - 2;
	if (tipus == FIGURA_O)
		columnaMax = N_COL_TAULER - 1;
	else
		if (tipus == FIGURA_I)
			columnaMax = N_COL_TAULER - 3;
	int col = (rand() % columnaMax) + 1;
	int nGir = (rand() % 4);
	m_figuraActual.inicialitza(tipus, 1, col);
	for (int i = 0; i < nGir; i++)
		m_figuraActual.girarFigura(GIR_HORARI);
	bool hayLimite = m_tauler.comprovarLimits(m_figuraActual);
	return hayLimite;
}

void Joc::generarFigura(InfoFigura figura)
{
	m_figuraActual.inicialitza(figura.tipus, figura.fila, figura.columna);
	for (int i = 0; i < figura.gir; i++)
		m_figuraActual.girarFigura(GIR_HORARI);
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int tipus, fila, columna, gir;
		fitxer >> tipus >> fila >> columna >> gir;
		m_figuraActual.inicialitza(TipusFigura(tipus), fila, columna);
		for (int i = 0; i < gir; i++)
			m_figuraActual.girarFigura(GIR_HORARI);

		ColorFigura taulerInicial[MAX_FILA][MAX_COL];
		int color;
		for (int i = 0; i < MAX_FILA; i++)
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> color;
				taulerInicial[i][j] = ColorFigura(color);
			}
		m_tauler.inicialitza(taulerInicial);
		fitxer.close();
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
	m_figuraActual.girarFigura(direccio);
	bool hayLimite = m_tauler.comprovarLimits(m_figuraActual);
	if (hayLimite)
	{
		if (direccio == GIR_HORARI)
			direccio = GIR_ANTI_HORARI;
		else
			direccio = GIR_HORARI;
		m_figuraActual.girarFigura(direccio);
	}
	return !hayLimite;
}

bool Joc::mouFigura(int dirX)
{
	m_figuraActual.moureLateralment(dirX);
	bool hayLimite = m_tauler.comprovarLimits(m_figuraActual);
	if (hayLimite)
		m_figuraActual.moureLateralment(-dirX);
	return !hayLimite;
}

int Joc::baixaFigura()
{
	int nFiles = -1;
	m_figuraActual.baixarFigura();
	if (m_tauler.comprovarLimits(m_figuraActual))
	{
		nFiles = 0;
		m_figuraActual.pujarFigura();
		nFiles = m_tauler.colocaFigura(m_figuraActual);
	}
	return nFiles;
}

int Joc::colocaFigura()
{
	int nFiles;
	do
	{
		nFiles = baixaFigura();
	} while (nFiles == -1);
	return nFiles;
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		if (m_figuraActual.getTipus() != NO_FIGURA)
			m_tauler.dibuixaFigura(m_figuraActual);
		ColorFigura tauler[MAX_FILA][MAX_COL];
		m_tauler.getValorsTauler(tauler);
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << int(tauler[i][j]) << " ";
			}
			fitxer << endl;
		}

		fitxer.close();
	}
}

void Joc::dibuixa()
{
	m_tauler.dibuixa();
	m_figuraActual.dibuixa();
}