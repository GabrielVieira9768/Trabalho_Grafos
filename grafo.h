#ifndef GRAFO_H
#define GRAFO_H

class Grafo {
    public:
        virtual ~Grafo() {}

        virtual bool eh_bipartido() = 0;
        virtual int n_conexo() = 0;
};

#endif