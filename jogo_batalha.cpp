#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

class FormaDeVida
{
protected:
    string nome;
    int vida;
    int forca;

public:
    FormaDeVida()
    {
        vida = 100;
        forca = 100;
    }
    FormaDeVida(string n)
    {
        nome = n;
        vida = 100;
        forca = 100;
    }

    bool estaVivo() { return vida > 0; }
    string getNome() { return nome; }
    void setNome(string n) { nome = n; }
    int getVida() { return vida; }
    virtual void atacar(FormaDeVida &alvo)
    {
        int dano = (rand() % forca) + 1;
        alvo.receberDano(dano);
        cout << nome << " ataca " << alvo.getNome() << " causando " << dano << " de dano!\n";
    }
    void receberDano(int dano)
    {
        vida = vida - dano;
        if (vida < 0)
        {
            vida = 0;
        }
    }
};
/*
int main(void)
{
    srand(time(0)); // Initialize random seed

    cout << "Sherek enfrenta Granamir!\n";

    FormaDeVida sherek, granamir;

    sherek.setNome("Sherek");
    granamir.setNome("Granamir");

    while (sherek.estaVivo() && granamir.estaVivo())
    {
        sherek.atacar(granamir);
        if (granamir.estaVivo())
            granamir.atacar(sherek);
    }

    if (sherek.estaVivo())
    {
        cout << "Sherek venceu e absorveu o poder do dragão!\n";
    }
    else
    {
        cout << "Granamir venceu! O reino está condenado...\n";
        return 0;
    }

    return 0;
}
*/