#include <stdlib.h>
#include "InfoJoc.h"


class NodeFigura
{
public:
    NodeFigura() { m_next = nullptr; };
    ~NodeFigura() {};
    NodeFigura(const InfoFigura& valor) { m_figura = valor; m_next = nullptr; }

    NodeFigura* getNext() { return m_next; }
    InfoFigura getValor() { return m_figura; }

    void setNext(NodeFigura* next) { m_next = next; }
    void setValor(const InfoFigura& valor) { m_figura = valor; }
private:
    InfoFigura m_figura;
    NodeFigura* m_next;
};