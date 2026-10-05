#include "Figura.h"

void::Figura::resetForma()
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++)
			m_formaActualEnMatriu[i][j] = 0;
}

void Figura::inicialitzaForma(TipusFigura tipus)
{
	switch (tipus)
	{
	case FIGURA_O:
		m_amplada = 2;
		m_alcada = 2;
		m_formaActualEnMatriu[0][0] = 1;
		m_formaActualEnMatriu[0][1] = 1;
		m_formaActualEnMatriu[1][0] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_color = COLOR_GROC;
		break;
	case FIGURA_I:
		m_amplada = 4;
		m_alcada = 4;
		resetForma();
		m_formaActualEnMatriu[1][0] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_formaActualEnMatriu[1][2] = 1;
		m_formaActualEnMatriu[1][3] = 1;
		m_color = COLOR_BLAUCEL;
		break;
	case FIGURA_T:
		m_amplada = 3;
		m_alcada = 3;
		resetForma();
		m_formaActualEnMatriu[0][1] = 1;
		m_formaActualEnMatriu[1][0] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_formaActualEnMatriu[1][2] = 1;
		m_color = COLOR_MAGENTA;
		break;
	case FIGURA_L:
		m_amplada = 3;
		m_alcada = 3;
		resetForma();
		m_formaActualEnMatriu[0][2] = 1;
		m_formaActualEnMatriu[1][0] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_formaActualEnMatriu[1][2] = 1;
		m_color = COLOR_TARONJA;
		break;
	case FIGURA_J:
		m_amplada = 3;
		m_alcada = 3;
		resetForma();
		m_formaActualEnMatriu[0][0] = 1;
		m_formaActualEnMatriu[1][0] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_formaActualEnMatriu[1][2] = 1;
		m_color = COLOR_BLAUFOSC;
		break;
	case FIGURA_Z:
		m_amplada = 3;
		m_alcada = 3;
		resetForma();
		m_formaActualEnMatriu[0][0] = 1;
		m_formaActualEnMatriu[0][1] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_formaActualEnMatriu[1][2] = 1;
		m_color = COLOR_VERMELL;
		break;
	case FIGURA_S:
		m_amplada = 3;
		m_alcada = 3;
		resetForma();
		m_formaActualEnMatriu[0][1] = 1;
		m_formaActualEnMatriu[0][2] = 1;
		m_formaActualEnMatriu[1][0] = 1;
		m_formaActualEnMatriu[1][1] = 1;
		m_color = COLOR_VERD;
		break;
	}
}

void Figura::inicialitza(TipusFigura tipus, int fila, int columna)
{
	m_tipus = tipus;
	m_fila = fila;
	m_columna = columna;
	m_gir = 0;
	inicialitzaForma(tipus);
}

void Figura::getformaActualEnMatriu(int mascara[MAX_ALCADA][MAX_AMPLADA]) const
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++)
			mascara[i][j] = m_formaActualEnMatriu[i][j];
}
void Figura::girarFigura(DireccioGir direccio)
{
	transposarMatriu();
	if (direccio == GIR_HORARI)
	{
		invertirColumnes();
		m_gir = (m_gir + 1) % 4;
	}
	else
	{
		invertirFiles();
		m_gir = (m_gir - 1) % 4;
	}

}


void Figura::transposarMatriu()
{
	int aux;
	for (int i = 1; i < m_alcada; i++)
		for (int j = 0; j < i; j++)
		{
			aux = m_formaActualEnMatriu[i][j];
			m_formaActualEnMatriu[i][j] = m_formaActualEnMatriu[j][i];
			m_formaActualEnMatriu[j][i] = aux;
		}
}

void Figura::invertirColumnes()
{
	int columna, col;
	if (m_amplada != 2)
	{
		if (m_amplada == 3)
		{
			columna = 0;
			col = 2;
		}
		else
		{
			columna = 1;
			col = 2;
		}
		int aux;
		for (int i = 0; i < m_alcada; i++)
		{
			aux = m_formaActualEnMatriu[i][columna];
			m_formaActualEnMatriu[i][columna] = m_formaActualEnMatriu[i][col];
			m_formaActualEnMatriu[i][col] = aux;
		}
	}
}

void Figura::invertirFiles()
{
	int fila, fil;
	if (m_alcada != 2)
	{
		if (m_alcada == 3)
		{
			fila = 0;
			fil = 2;
		}
		else
		{
			fila = 1;
			fil = 2;
		}
		int aux;
		for (int i = 0; i < m_amplada; i++)
		{
			aux = m_formaActualEnMatriu[fila][i];
			m_formaActualEnMatriu[fila][i] = m_formaActualEnMatriu[fil][i];
			m_formaActualEnMatriu[fil][i] = aux;
		}
	}

}

void Figura::dibuixa()
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_formaActualEnMatriu[i][j] != 0)
				dibuixaQuadrat(m_color, POS_X_TAULER + ((m_columna + j) * MIDA_QUADRAT),
					POS_Y_TAULER + ((m_fila - 1 + i) * MIDA_QUADRAT));
		}

}