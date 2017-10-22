#ifndef LEVEL_H
#define LEVEL_H


class Level
{
public:
    Level();
    ~Level();
public:
    int levelAtual();
    void passouLevel();
    void reiniciarLevel();
    int retornaDELAY();
private:
    int numeroLevel;
    int DELAY;
    static const int inicialDELAY = 10;
};

#endif // LEVEL_H
