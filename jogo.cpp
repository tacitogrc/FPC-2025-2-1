#include <iostream>
#include "jogo_engine.cpp"
#include "jogo_parametros.cpp"
#include "jogo_personagens.cpp"

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
