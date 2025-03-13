#include <iostream>
#include <string>
#include <clocale>
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
    
    void setVida(int v) { if(v >= 0 && v <= 100) vida = v; }
    int getVida() { return vida; }
    
    void setForca(int f) { if(f >= 0 && f <= 100) forca = f; }
    int getForca() { return forca; }

    string ataque(float multiplicador ){
      cout << getNome() << " ataca com força " << 10 * multiplicador << "!\n";
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
        alvo.vida = alvo.vida * 1.1;
        /* code */
        break;

      case 2: // Aumento de Forca
        alvo.forca = alvo.forca * 1.1;
        /* code */
        break;

      case 3: // Remove Vida
        alvo.vida = alvo.vida * 0.9;
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
};

int main(void) {
    // Define a localidade para pt_BR com codificação UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Introdução com ASCII Art
    cout << "Bem-vindo ao RPG Interativo!\n\n";
    cout << R"EOF(
     |-----|   Castelo
    /       \
   |  [] []  |
    \   ^   /
     |-----|
    )EOF" << "\n\n";
    
    // Criação dos personagens
    Mago gandalf("Gandalf");
    Cavaleiro shereik("Shereik");
    Princesa fiona("Fiona");
    Dragao granamir("Granamir");
    Bruxa do71("Do71");
    Aldeao tiago("Tiago");
    Monstro ogro("Ogro");
    
    int escolha;
    cout << "Você é o Cavaleiro " << shereik.getNome() << " e deve decidir seu caminho:\n";
    cout << "1. Seguir para a Montanha em busca do Dragão.\n";
    cout << "2. Ir ao Castelo enfrentar diretamente a Bruxa.\n";
    cout << "Escolha (1 ou 2): ";
    cin >> escolha;
    
    if (escolha == 1) {
        cout << "\nVocê decide seguir para a Montanha.\n";
        // ASCII art da montanha
        cout << R"EOF(
         /\
        /  \
       /____\
      Montanha
        )EOF" << "\n\n";
        
        cout << "No alto da montanha, você encontra o Dragão " << granamir.getNome() << ".\n";
        cout << "Ele desafia você para um confronto!\n";
        
        int acao;
        cout << "\nEscolha sua ação:\n";
        cout << "1. Lutar contra o Dragão.\n";
        cout << "2. Conversar com o Dragão e entender sua situação.\n";
        cout << "Escolha (1 ou 2): ";
        cin >> acao;
        
        if (acao == 1) {
            cout << "\nVocê decide enfrentar o Dragão em um combate feroz!\n";
            cout << "Após uma batalha intensa, você derrota o Dragão e absorve parte de seu poder.\n";
            shereik.setForca(shereik.getForca() + 50);
            cout << "Sua força agora é de " << shereik.getForca() << " pontos!\n";
            cout << "Com esse poder, você desce para enfrentar a Bruxa " << do71.getNome() << ".\n";
        } else {
            cout << "\nVocê opta por conversar com o Dragão.\n";
            cout << "O Dragão revela que foi enfeitiçado pela Bruxa e pede sua ajuda para ser libertado.\n";
            cout << "Com a aliança formada, vocês partem juntos para enfrentar a Bruxa.\n";
            shereik.setForca(shereik.getForca() + 30);
            cout << "Sua força aumentou para " << shereik.getForca() << " pontos!\n";
        }
    }
    else if (escolha == 2) {
        cout << "\nVocê decide ir diretamente ao Castelo.\n";
        // ASCII art do castelo (reexibida)
        cout << R"EOF(
     |-----|   Castelo
    /       \
   |  [] []  |
    \   ^   /
     |-----|
        )EOF" << "\n\n";
        
        cout << "No Castelo, a Bruxa " << do71.getNome() << " já está ameaçando o reino.\n";
        int acao;
        cout << "\nEscolha sua ação:\n";
        cout << "1. Desafiar a Bruxa em combate direto.\n";
        cout << "2. Tentar convencê-la a desistir de seus planos malignos.\n";
        cout << "Escolha (1 ou 2): ";
        cin >> acao;
        
        if (acao == 1) {
            cout << "\nVocê decide enfrentar a Bruxa em um duelo.\n";
            cout << "A luta é dura e você sai ferido, mas consegue derrotá-la.\n";
            shereik.setVida(shereik.getVida() - 30);
            cout << "Sua vida agora é de " << shereik.getVida() << " pontos!\n";
        } else {
            cout << "\nVocê tenta uma abordagem pacífica e conversa com a Bruxa.\n";
            cout << "Surpreendentemente, ela se arrepende e abandona seus planos maléficos.\n";
            cout << "O reino é salvo sem derramamento de sangue.\n";
        }
    }
    else {
        cout << "\nOpção inválida! Mesmo assim, o destino do reino se encaminha...\n";
    }
    
    // Encerramento comum da narrativa
    cout << "\nApós os acontecimentos, você se une à Princesa " << fiona.getNome() 
         << " e juntos restauram a paz no reino.\n";
    cout << R"EOF(
         __   __  _______  __   __ 
        |  |_|  ||   _   ||  |_|  |
        |       ||  |_|  ||       |
        |       ||       ||       |
        | ||_|| ||       || ||_|| |
        |_|   |_||_______||_|   |_|
              FIM
    )EOF" << "\n";
    
    return 0;
}
