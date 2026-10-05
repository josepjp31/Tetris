#include "NodeMoviment.h"

class LlistaMoviments
{
public:
	LlistaMoviments() { m_primer = nullptr; }
	~LlistaMoviments();
	LlistaMoviments(const LlistaMoviments& llistaMoviments);

	LlistaMoviments& operator=(const LlistaMoviments& llistaMoviments);
	NodeMoviment* insereix(const TipusMoviment& pt);
	void elimina();
	bool esBuida() const { return m_primer == nullptr; }

	int getnElements() const;
	TipusMoviment getPrimer() const { return m_primer->getValor(); }
private:
	NodeMoviment* m_primer;
	NodeMoviment* m_ultim;
};
