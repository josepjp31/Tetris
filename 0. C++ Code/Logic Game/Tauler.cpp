#include "Tauler.h"
#include "GraphicManager.h"
#include "InfoJoc.h"
#include <iostream>
using namespace std;

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        m_tauler[i][0] = NO_COLOR;
        m_tauler[i][1] = NO_COLOR;
        m_tauler[i][MAX_COL + 2] = NO_COLOR;
        m_tauler[i][MAX_COL + 3] = NO_COLOR;
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j + 2] = COLOR_NEGRE;
    }
    for (int j = 0; j < MAX_COL + 4; j++)
    {
        m_tauler[MAX_FILA][j] = NO_COLOR;
        m_tauler[MAX_FILA + 1][j] = NO_COLOR;
    }
    for (int i = 0; i < MAX_FILA; i++)
        m_nCaselleslliures[i] = MAX_COL;
}

void Tauler::inicialitza(ColorFigura taulerInicial[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
        m_nCaselleslliures[i] = MAX_COL;
    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j + 2] = taulerInicial[i][j];
            if (taulerInicial[i][j] != COLOR_NEGRE)
                m_nCaselleslliures[i]--;
        }
}

bool Tauler::comprovarLimits(const Figura& figura)
{
    bool hayLimite = false;
    int formaMatriu[MAX_ALCADA][MAX_AMPLADA];

    int filaMatriu = 0;
    int filaTauler = figura.getFila() - 1;
    figura.getformaActualEnMatriu(formaMatriu);
    do
    {
        int colTauler = figura.getColumna() + 1;
        int colMatriu = 0;
        do
        {
            if ((formaMatriu[filaMatriu][colMatriu] * m_tauler[filaTauler][colTauler]) != 0)
            {
                hayLimite = true;
            }
            colMatriu++;
            colTauler++;
        } while ((!hayLimite) && (colMatriu < figura.getAmplada()));

        filaMatriu++;
        filaTauler++;
    } while ((!hayLimite) && (filaMatriu < figura.getAlcada()));

    return hayLimite;

}

int Tauler::colocaFigura(const Figura& figura)
{
    int formaMatriu[MAX_ALCADA][MAX_AMPLADA];
    int numFilesFetes = 0;

    ColorFigura color = figura.getColor();
    figura.getformaActualEnMatriu(formaMatriu);
    int filaTauler = figura.getFila() - 1;
    for (int filaMatriu = 0; filaMatriu < figura.getAlcada(); filaMatriu++)
    {
        int colTauler = figura.getColumna() + 1;
        for (int colMatriu = 0; colMatriu < figura.getAmplada(); colMatriu++)
        {
            if (formaMatriu[filaMatriu][colMatriu] > 0)
            {
                m_tauler[filaTauler][colTauler] = color;
                m_nCaselleslliures[filaTauler]--;
                if (m_nCaselleslliures[filaTauler] == 0)
                {
                    numFilesFetes++;
                    baixaFila(filaTauler);
                }
            }
            colTauler++;
        }
        filaTauler++;
    }
    return numFilesFetes;
}


void Tauler::dibuixaFigura(const Figura& figura)
{
    int formaMatriu[MAX_ALCADA][MAX_AMPLADA];

    ColorFigura color = figura.getColor();
    figura.getformaActualEnMatriu(formaMatriu);
    int filaTauler = figura.getFila() - 1;
    for (int filaMatriu = 0; filaMatriu < figura.getAlcada(); filaMatriu++)
    {
        int colTauler = figura.getColumna() + 1;
        for (int colMatriu = 0; colMatriu < figura.getAmplada(); colMatriu++)
        {
            if (formaMatriu[filaMatriu][colMatriu] > 0)
            {
                m_tauler[filaTauler][colTauler] = color;
            }
            colTauler++;
        }
        filaTauler++;
    }
}

void Tauler::baixaFila(int fila)
{
    if (fila > 0)
    {
        for (int i = fila; i > 0; i--)
        {
            for (int j = 0; j < MAX_COL; j++)
            {
                m_tauler[i][j + 2] = m_tauler[i - 1][j + 2];
            }
            m_nCaselleslliures[i] = m_nCaselleslliures[i - 1];
        }
    }
    for (int i = 0; i < MAX_COL; i++)
        m_tauler[0][i + 2] = COLOR_NEGRE;
    m_nCaselleslliures[0] = MAX_COL;
}

void Tauler::getValorsTauler(ColorFigura tauler[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            tauler[i][j] = m_tauler[i][j + 2];
    }
}

void Tauler::dibuixa()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            if (m_tauler[i][j + 2] != COLOR_NEGRE)
                dibuixaQuadrat(m_tauler[i][j + 2], POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + (i * MIDA_QUADRAT));
        }

}