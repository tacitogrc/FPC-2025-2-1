// Inclui as definições de classes
#include <iostream>
#include <cstring>
#include <locale>

#define coin 2
#define d4 4
#define d6 6
#define d8 8
#define d10 10
#define d12 12
#define d20 20
#define d100 100
#define qtde_caminhos 15

using namespace std;

int roll_dice (int dice_num);

class FormaDeVida 
{
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



class Evento_Randomico
{
unsigned int mod_sala;
unsigned int roll_saver;
unsigned int points;

public:

    unsigned int escolhe_sala()
    {
        unsigned int choice_1;
        cout<<"Escolha a sala entre: (1) Sala Clara || (2) Sala Meio Iluminada || (3) Sala Escura: ";
        cin>>choice_1;

        switch (choice_1)
        {
        case 1:
            mod_sala = 0;
            points = 1;
            break;

        case 2:
            mod_sala = 1;
            points = 2;
            break;

        case 3:
            mod_sala = 3;
            points = 3;
            break;
        
        default:
            roll_saver = roll_dice(d100);
            if(roll_saver<=95)
            {
                cout<<"O grupo caiu no abismo e todos pereceram! GAME OVER! \n\n";
                points = 16;
                return points;
                break;
            }
            if(roll_saver>95)
            {
                cout<<"Uma sala secreta!\n";
                _sleep(500);
                cout<<".";
                _sleep(500);
                cout<<".";
                _sleep(500);
                cout<<".\n";
                _sleep(500);
                cout<<"Mas o quê?! É a Bruxa do 71! ATACAR!";
                points = 16;
                return points;
                break;
            }

        }
        switch (roll_dice(d4))
        {
        case 1:
            cout<<"O grupo entra na sala sem problemas. \n\n";
            break;
        case 2:
            cout<<"Uma armadilha no meio do caminho acerta o grupo! Todos tomam "<<roll_dice(d10)<<" de dano! \n\n";
            break;
        case 3:
            cout<<"Um caminho tranquilo, na medida do possível... \n\n";
            break;
        case 4:
            cout<<"Gases enfraquecedores se abatem sobre o grupo! Vocês estão fracos e causam menos "<<roll_dice(d8)<<" de dano de ataque! \n\n";
            break;

        default:
            cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
            break;
        }

        acontecimento();
        return points;

    }

    void acontecimento()
    {
        switch (roll_dice(d6))
        {
        case 1:
            cout<<"Os heróis encontram uma caixa, querem abrir para conferir o conteúdo? s/n: ";
            _sleep(1);
            randomiza_evento();
            break;

        case 2:
            cout<<"Há uma mesa com itens diversos, querem mexer para conferir se há algo útil? s/n: ";
            _sleep(1);
            randomiza_evento();
            break;    
        
        case 3:
            cout<<"Um buraco foi cavado no chão para esconder algo, querem desenterrar para ver o que é? s/n: ";
            _sleep(1);
            randomiza_evento();
            break;

        case 4:
            cout<<"Um baú os aguarda no fim da sala, desejam abrir? s/n: ";
            _sleep(1);
            randomiza_evento();
            break;

        case 5:
            roll_saver = roll_dice(d4);
            cout<<"Oh, não! A sala tem "<<roll_saver<<" ogro(s)! Vocês precisam lutar para sair! \n\n";
            _sleep(1);
            break;

        case 6:
            cout<<"A sala está vazia... Sorte? Será? \n\n";
            _sleep(1);
            break;

        default:
            cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
            break;
        }
    }   
    void evento_bom()
    {
        _sleep(1);
        switch (roll_dice(d4))
        {
        case 1:
            _sleep(1);
            roll_saver = roll_dice(d6)+mod_sala;
            cout<<"Vocês encontraram comida! Todos curam "<<roll_saver<<" de vida! \n\n";
            break;
        case 2:
            _sleep(1);
            roll_saver = roll_dice(coin)+mod_sala;
            cout<<"Vocês encontraram um tônico! Todos causam mais "<<roll_saver<<" de dano! \n\n";
            break;

        case 3:
            _sleep(1);
            roll_saver = roll_dice(d10)+mod_sala;
            cout<<"Vocês encontraram poções! Todos curam "<<roll_saver<<" de vida! \n\n";
            break;

        case 4:
            _sleep(1);
            roll_saver = roll_dice(d8)+mod_sala;
            cout<<"Vocês são envolvidos por uma magia poderosa! Todos causam mais "<<roll_saver<<" de dano! \n\n";
            break;
        
        default:
            cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
            break;
        }
    }

    void evento_neutro()
    {
        _sleep(1);
        switch (roll_dice(d4))
        {
        case 1:
            _sleep(1);
            cout<<"A curiosidade matou o gato, mas não dessa vez! \n\n";
            break;
        case 2:
            _sleep(1);
            cout<<"Não há nada aqui! \n\n";
            break;

        case 3:
            _sleep(1);
            cout<<"O conteúdo já foi saqueado! \n\n";
            break;

        case 4:
            _sleep(1);
            cout<<"Está vazio! \n\n";
            break;
        
        default:
            cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
            break;
        }
    }

    void evento_ruim()
    {
        _sleep(1);
        switch (roll_dice(d4))
        {
        case 1:
            _sleep(1);
            roll_saver = roll_dice(d8)+mod_sala;
            cout<<"Um fedor enauseante toma a sala! Todos levam "<<roll_saver<<" de dano! \n\n";
            break;
        case 2:
            _sleep(1);
            roll_saver = roll_dice(d6)+mod_sala;
            cout<<"Uma armadilha bem posicionada! Todos levam "<<roll_saver<<" de dano! \n\n";
            break;

        case 3:
            _sleep(1);
            roll_saver = roll_dice(d4)+mod_sala;
            cout<<"Uma maldição se abate sobre o grupo! Todos causam menos "<<roll_saver<<" de dano! \n\n";
            break;

        case 4:
            _sleep(1);
            roll_saver = roll_dice(d10)+mod_sala;
            cout<<"Vocês são envolvidos por um feitiço poderoso! Todos causam menos "<<roll_saver<<" de dano! \n\n";
            break;
        
        default:
            cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
            break;
        }

    }

    void randomiza_evento()
    {
        std::string choice;
        cin>>choice;
        const char *escolha = choice.c_str();
        _sleep(1);

            if(!strcmp("s",escolha)||!strcmp("S",escolha))
            {
                int roll = roll_dice(d100);
                
                if(roll<=33)
                {
                    evento_bom();
                }

                if(roll>33&&roll<=67)
                {
                    evento_neutro();
                }
                if(roll>67)
                {
                    evento_ruim();
                }
                
            }
            else if(!strcmp("n",escolha)||!strcmp("N",escolha))
            {
                switch (roll_dice(d4))
                {
                case 1:
                    cout<<"OK, para próxima sala, então... \n\n";
                    break;

                case 2:
                    cout<<"Poxa... Eu estava curioso, estraga prazeres! \n\n";
                    break;
                
                case 3:
                    cout<<"Ah, eu amo o cheiro de uma oportunidade de exploração ignorada logo pela manhã. \n\n";
                    break;
                case 4:
                    cout<<"Vocês têm um talento especial para evitar justamente as partes mais interessantes da aventura, parabéns! \n\n";
                    break;
                default:
                    cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
                    break;
                }
                
            }
            else
            {
                switch (roll_dice(d4))
                {
                case 1:
                    cout<<"Esta não é uma aventura quântica! Há apenas DUAS opções!";
                    evento_ruim();                    
                    break;
                
                case 2:
                    cout<<"Ora, Ora, temos um engraçadinho aqui! TOME! \n\n";
                    evento_ruim();
                    break;
                
                case 3:
                    cout<<"Vou acreditar que foi um erro inocente, mas só desta vez! \n\n";
                    break;

                case 4:
                    cout<<"'Miss Click', huh? Sei... Sei... Dessa vez passa... \n\n";
                    break;

                default:
                    cout<<"Se vc está lendo isso a rebelião das máquinas já começou! Encontre John Connor, ele saberá o que fazer! \n\n";
                    break;
                
                }
                
            }
    }
    
};


int main (void)
{
    setlocale(LC_ALL,"pt_br.UTF-8");
    Evento_Randomico Entrar_na_sala;

    for (int avancos = 0; avancos <= qtde_caminhos; avancos = avancos + Entrar_na_sala.escolhe_sala()){}
}

int roll_dice (int dice_num)
{
    _sleep(3);
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
