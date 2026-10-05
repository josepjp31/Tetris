#include "NodeFigura.h"

class LlistaFigures
{
public:
	LlistaFigures() { m_primer = nullptr; }
	~LlistaFigures();
	LlistaFigures(const LlistaFigures& l);
	LlistaFigures& operator=(const LlistaFigures& l);
	NodeFigura* insereix(const InfoFigura& pt);
	void elimina();
	int getnElements() const;
	InfoFigura getPrimer() const { return m_primer->getValor(); }
	bool esBuida() const { return m_primer == nullptr; }

private:
	NodeFigura* m_primer;
	NodeFigura* m_ultim;
};
