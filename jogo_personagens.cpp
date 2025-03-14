#include <iostream>
#include <string>
#include <clocale>
#include <cmath> // Include cmath for floor function

// Define dice constants
const int d10 = 10;
const int d6 = 6;
const int d20 = 20;

#define coin 2
#define d4 4
#define d6 6
#define d8 8
#define d10 10
#define d12 12
#define d20 20
#define d100 100

// Function to roll a dice
int roll_dice (int dice_num)
{
    switch (dice_num)
    {
    case 2:
        srand(time(0));
        dice_num = rand() % coin+1;        
        break;
        
    case 4:
        srand(time(0));
        dice_num = rand() % d4+1;        
        break;

    case 6:
        srand(time(0));
        dice_num = rand() % d6+1;        
        break;

    case 8:
        srand(time(0));
        dice_num = rand() % d8+1;        
        break;
        
    case 10:
        srand(time(0));
        dice_num = rand() % d10+1;        
        break;
        
    case 12:
        srand(time(0));
        dice_num = rand() % d12+1;        
        break;

    case 20:
        srand(time(0));
        dice_num = rand() % d20+1;       
        break;
        
    case 100:
        srand(time(0));
        dice_num = rand() % d100+1;        
        break;

        
    default:
        break;
    }
    return dice_num;
}

using namespace std;

// Classe base
class FormaDeVida {
  protected:
    string nome;
    float vida;   // Valores de 0 a 100.
    float forca;  // Valores de 0 a 100.
    
  public:
    FormaDeVida() : vida(100), forca(100) { }
    FormaDeVida(string n) : nome(n), vida(100), forca(100) { }
    
    void setNome(string n) { nome = n; }
    string getNome() { return nome; }
    
    void setVida(int v) { if(v >= 0 && v <= 100) vida = v; else if(v > 100) vida = 100; }
    int getVida() { return vida; }
    
    void setForca(int f) { if(f >= 0 && f <= 100) forca = f; }
    int getForca() { return forca; }

    string ataque(FormaDeVida alvo){
      cout << getNome() << " ataca com força " << roll_dice(d20) << "!\n";
    }
};

// Classe para personagens humanos com diálogo
class SerHumano : public FormaDeVida {
  public:
    SerHumano() : FormaDeVida() { }
    SerHumano(string n) : FormaDeVida(n) { }
    
    void fale(string s) {
        cout << getNome() << " diz: " << s << "\n";
    }
    
    virtual string responda(string s) {
        if (s == "Olá!") return "Tudo bem?";
        else if (s == "Tudo bem?") return "Sim, e você?";
        else if (s == "Sim, e você?") return "Estou ótimo!";
        else if (s == "Até logo!") return "Até!";
        else if (s == "Tchau!") return "Tchau!";
        else return "Não sei dizer.";
    }
    
    // Conversa interativa entre personagens usando template.
    template <class ClasseTemplate>
    void converse(ClasseTemplate pessoa, string s) {
        string respostaPessoa;
        string minhaResposta = s;
        while (true) {
            this->fale(minhaResposta);
            respostaPessoa = pessoa.responda(minhaResposta);
            pessoa.fale(respostaPessoa);
            minhaResposta = this->responda(respostaPessoa);
            if (respostaPessoa == "Não sei dizer." || minhaResposta == "Não sei dizer.")
                break;
        }
    }
};

class Mago : public SerHumano {
  protected:
    int magia;
    
  public:
    Mago() : SerHumano(), magia(100) { }
    Mago(string n) : SerHumano(n), magia(100) { }
    
    void setMagia(int m) { if(m >= 0 && m <= 100) magia = m; }
    int getMagia() { return magia; }

    void aplicaMagia(int acao, FormaDeVida &alvo){    
      switch (acao)
      {
      case 1: // Cura 
        alvo.setVida(floor(alvo.getVida() + roll_dice(d10)));
        /* code */
        break;

      case 2: // Aumento de Forca
        alvo.setForca(floor(alvo.getForca() + roll_dice(d6)));
        /* code */
        break;

      default:
        /* a magia falhou */
        cout << "A magia falhou";
        break;
      }
    }
};

class Bruxa : public SerHumano {
  protected:
    int magia;
    
  public:
    Bruxa() : SerHumano(), magia(100) { }
    Bruxa(string n) : SerHumano(n), magia(100) { }
    
    void setMagia(int m) { if(m >= 0 && m <= 100) magia = m; }
    int getMagia() { return magia; }
};

class Cavaleiro : public SerHumano {
  protected:
    int coragem;
    int armadura;
    
  public:
    Cavaleiro() : SerHumano(), coragem(100), armadura(100) { }
    Cavaleiro(string n) : SerHumano(n), coragem(100), armadura(100) { }
    
    void setCoragem(int c) { if(c >= 0 && c <= 100) coragem = c; }
    int getCoragem() { return coragem; }
    
    void setArmadura(int a) { if(a >= 0 && a <= 100) armadura = a; }
    int getArmadura() { return armadura; }
    
    virtual string responda(string s) {
        if (s == "Olá!") return "Como vai, nobre amigo?";
        else if (s == "Tudo bem?") return "Sim, e como está Vossa senhoria?";
        else if (s == "Sim, e você?") return "Estou passando muito bem!";
        else if (s == "Até logo!") return "Até a próxima!";
        else if (s == "Tchau!") return "Até logo!";
        else return "Não sei dizer.";
    }

    void defender(){
        cout << getNome() << " se defende com sua armadura!\n";
    }
};

class Princesa : public SerHumano {
  protected:
    int inteligencia, beleza, dinheiro;
    
  public:
    Princesa() : SerHumano() { }
    Princesa(string n) : SerHumano(n) { }
    
    void setInteligencia(int i) { if(i >= 0 && i <= 100) inteligencia = i; }
    int getInteligencia() { return inteligencia; }
    
    void setBeleza(int b) { if(b >= 0 && b <= 100) beleza = b; }
    int getBeleza() { return beleza; }
    
    void setDinheiro(int d) { if(d >= 0 && d <= 100) dinheiro = d; }
    int getDinheiro() { return dinheiro; }
};

class Aldeao : public SerHumano {
  protected:
    int lealdade, honestidade;
    
  public:
    Aldeao() : SerHumano() { }
    Aldeao(string n) : SerHumano(n) { }
    
    void setLealdade(int l) { if(l >= 0 && l <= 100) lealdade = l; }
    int getLealdade() { return lealdade; }
    
    void setHonestidade(int h) { if(h >= 0 && h <= 100) honestidade = h; }
    int getHonestidade() { return honestidade; }
    
    string responda(string s) {
        if (s == "Olá!") return "To de boa, e você?";
        else if (s == "Tudo bem?") return "Não é da sua conta!";
        else if (s == "Sim, e você?") return "Então, larga mão!";
        else if (s == "Até logo!") return "Se cuida!";
        else if (s == "Tchau!") return "Tô nem aí!";
        else return "Não sei dizer.";
    }
};

class Monstro : public FormaDeVida {
  protected:
    int simpatia;
    
  public:
    Monstro() : FormaDeVida() { }
    Monstro(string n) : FormaDeVida(n) { }
    
    void setSimpatia(int s) { if(s >= 0 && s <= 100) simpatia = s; }
    int getSimpatia() { return simpatia; }
};

class Dragao : public Monstro {
  protected:
    int fogo;
    
  public:
    Dragao() : Monstro() { }
    Dragao(string n) : Monstro(n) { }
    
    void setFogo(int f) { if(f >= 0 && f <= 100) fogo = f; }
    int getFogo() { return fogo; }

    int ataque(int dano, FormaDeVida &alvo){
    alvo.setVida(alvo.getVida() - dano);
    return alvo.getVida();
    }
};