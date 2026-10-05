#include <stdlib.h>
#include "InfoJoc.h"


class NodeMoviment
{
public:
    NodeMoviment() { m_next = nullptr; };
    ~NodeMoviment() {};
    NodeMoviment(const TipusMoviment& valor) { m_moviment = valor; m_next = nullptr; }

    NodeMoviment* getNext() { return m_next; }
    TipusMoviment getValor() { return m_moviment; }

    void setNext(NodeMoviment* next) { m_next = next; }
    void setValor(const TipusMoviment& valor) { m_moviment = valor; }
private:
    TipusMoviment m_moviment;
    NodeMoviment* m_next;
};
