#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctime> // Include ctime for time function
#include "jogo_personagem.cpp"

/*
Função: Modela uma opção de interação disponível dentro de uma cena. Cada escolha pode ter uma descrição e uma referência à cena ou efeito que ela provoca, possibilitando a ramificação da narrativa.
NEW: As escolhas podem acionar eventos aleatórios, modificar atributos do jogador ou influenciar o curso da história.
*/
class Choice {
    public:
        Choice(const std::string& text, int nextSceneId)
            : description(text), nextSceneId(nextSceneId) {}
        std::string getDescription() const { return description; }
        int getTargetSceneId() const { return nextSceneId; }
    private:
        std::string description;
        int nextSceneId;
};

/*
Função: Representa um “capítulo” ou momento da história. Cada cena pode conter o texto narrativo, as descrições do ambiente e uma lista de opções que o jogador pode escolher para avançar a narrativa.
*/
class Scene {
    public:
        Scene() : asciiArt(""), narrative("") {} // Default constructor
        Scene(const std::string &asciiArt, const std::string &narrative)
            : asciiArt(asciiArt), narrative(narrative) {}
    
        // Adiciona uma escolha à cena
        void addChoice(const std::string &option, int nextSceneId) {
            choices.push_back({option, nextSceneId});
        }
    
        // Exibe a cena na tela
        void display() const {
            std::cout << asciiArt << "\n" << narrative << "\n";
            if (!choices.empty()) {
                std::cout << "\nEscolhas:\n";
                for (size_t i = 0; i < choices.size(); i++) {
                    std::cout << (i + 1) << ": " << choices[i].getDescription() << "\n";
                }
            }
        }
        // Retorna as escolhas da cena
        const std::vector<Choice>& getChoices() const {
            return choices;
        }
    
    private:
        std::string asciiArt;
        std::string narrative;
        std::vector<Choice> choices;
};

/*
Função: Responsável por gerenciar a sequência da narrativa, definindo qual cena deve ser apresentada a seguir com base nas escolhas do usuário. Essa classe pode armazenar a estrutura narrativa (por exemplo, em forma de árvore ou grafo) e controlar o fluxo da história.
*/
class StoryManager {
    public:
        // Adiciona uma cena com um identificador único
        void addScene(int id, const Scene &scene) {
            scenes[id] = scene;
        }
        
        // Retorna um ponteiro para a cena correspondente ao id
        Scene* getScene(int id) {
            auto it = scenes.find(id);
            if (it != scenes.end())
                return &(it->second);
            return nullptr;
        }
    
    private:
        std::map<int, Scene> scenes;
};

/*
Função: Responsável por capturar e interpretar a entrada do usuário. Essa classe pode validar as opções digitadas ou selecionadas, transformando a entrada em comandos ou escolhas que serão processadas pelo StoryManager.
*/
class InputHandler {
    public:
        int getUserChoice() {
            int choice;
            std::cout << "\nDigite sua escolha: ";
            std::cin >> choice;
            return choice;
        }
};

/*
DecisionEngine/BranchingEngine
Função: Se a sua narrativa tiver regras mais complexas ou variáveis que influenciem o curso da história (por exemplo, estados que persistem durante o jogo), uma classe dedicada para processar essas decisões pode ser útil. Ela pode avaliar condições e determinar a próxima cena com base em múltiplos fatores.
*/
class DecisionEngine {
    public:
        int evaluateDecision(const Scene& scene, int choiceId);
};

/*
Game/Engine
Função: Classe principal que gerencia o ciclo do jogo. Ela inicia a aplicação, mantém o loop principal, atualiza o estado do jogo e delega chamadas para outras classes (por exemplo, recebendo input e atualizando a narrativa).
*/
class Game {
    public:
        Game() {
            // Inicializa o map de ASCII arts padrão
            asciiArts["montanhas"] = R"(
         /\          /\          /\
        /  \   /\   /  \   /\   /  \
       /    \ /  \ /    \ /  \ /    \
      /      \    /      \    /      \
     /        \  /        \  /        \
    /  /\      \/          \/      /\   \
   /  /  \      |   ~~~~   |      /  \   \
  /__/____\     |  ~~~~~~  |     /____\___\
                \~~~~~~~~~~/ 
                 \~~~~~~~~/ 
                  \~~~~~~/ 
                   \~~~~/ 
                    \~~/ 
                     \/ 

            )";

            asciiArts["castelo"] = R"(
                                    |>>>                              
                                  |                                 
                    |>>>      _  _|_  _         |>>>                
                    |        |;| |;| |;|        |                   
                _  _|_  _    \\.    .  /    _  _|_  _               
               |;|_|;|_|;|    \\:. ,  /    |;|_|;|_|;|              
               \\..      /    ||;   . |    \\.    .  /              
                \\.  ,  /     ||:  .  |     \\:  .  /               
                 ||:   |_   _ ||_ . _ | _   _||:   |                
                 ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |                
                 ||:   ||.    .     .      . ||:  .|                
                 ||: . || .     . .   .  ,   ||:   |       \,/      
                 ||:   ||:  ,  _______   .   ||: , |            /`\ 
                 ||:   || .   /+++++++\    . ||:   |                
                 ||:   ||.    |+++++++| .    ||: . |                
              __ ||: . ||: ,  |+++++++|.  . _||_   |                
     ____--`~    '--~~__|.    |+++++__|----~    ~`---,              
-~--~                   ~---__|,--~'                  ~~----_____-~'
            )";
            asciiArts["endgame"] = R"(
            ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣻⣿⣿⣿⡟⢁⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⣴⣿⣿⣿⡟⢠⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⡉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢠⡆⢻⣿⣿⣿⡇⡜⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⢀⣿⡄⢄⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠈⢣⡀⠸⣿⣿⢰⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢀⡇⢸⣿⣷⠈⢆⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⢿⣶⣬⡉⢸⡟⠘⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⠛⠋⠉⠉⠛⠻⠿⣿⣿⣿⣿⡇⢸⡇⠸⣿⣿⣇⢸⣦⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠈⠻⡇⢸⣷⠀⢠⣌⡙⠻⢿⣿⣿⣿⣿⣶⣄⡐⢶⣦⣉⠻⣶⣌⠛⣿⣿⣇⠸⣿⡄⢿⣿⣿⡎⣿⣇⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⢸⣿⡐⡈⣿⣿⣿⣶⣤⣉⠙⠻⢿⣿⣿⡌⢿⣿⣿⣌⢻⣿⣌⢻⣿⣄⠹⣿⣄⠹⣿⡇⢹⣿⣧⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢸⣿⡇⢳⠘⢿⣭⡙⠿⣿⣿⣿⣦⣄⡙⠿⡈⢿⣿⣿⡆⢻⣿⣆⠙⢟⡀⠀⢈⠑⠄⠁⢸⣿⣿⡄⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⣧⠈⣦⠀⠉⠻⢶⣌⠻⢿⣿⣿⣿⣷⣄⡈⠻⣿⣿⠀⣿⣿⣦⠉⠰⠞⠉⣀⣀⣰⡄⠻⣿⣿⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢛⣉⡀⣿⣿⣇⠹⣧⡈⢦⣀⠙⢷⣌⠙⠿⣿⣿⣿⣿⣦⡘⠿⠀⣹⣿⡇⣠⡄⠀⣄⠹⣿⣿⣿⣦⡘⣿⡇⢻⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣤⣤⣤⡌⠁⢹⣿⣿⣄⢻⣷⣌⠻⣦⡀⠙⢷⣄⠘⢻⣿⣿⣿⣿⣦⡀⢹⣿⣼⣿⣶⠀⠹⡆⢻⣿⣿⣿⣷⠘⠇⢸⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠛⠋⠡⠶⠈⣿⣿⣿⣆⠻⣿⣦⡘⢿⣦⡈⠻⣧⡀⠛⢿⣿⣿⣿⣿⣄⠙⠻⣿⡇⣴⣦⠙⠀⢿⣿⣿⣿⣆⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠀⠀⠀⢤⣤⣤⣄⡀⠘⢿⣿⣿⣦⡘⢿⣷⣄⠙⡛⠆⠙⣿⡄⠀⣿⣿⣿⣿⠿⠆⠰⠋⠸⣿⣿⣷⠀⢸⣿⣿⣿⣿⡀⢸⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣷⡆⠈⣿⣿⣷⡈⣌⢿⣿⣿⣷⣄⠻⣿⣶⡈⠒⢦⠘⣿⠆⠈⠉⡩⠔⠒⠂⡀⠾⣿⣿⠏⣠⣦⢀⠙⠛⠛⠻⠇⠈⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣡⣾⣿⣿⣿⣧⠘⣦⡙⠿⢿⣿⣦⡙⢿⣿⣦⡀⠀⠀⠰⠂⠀⠀⣠⣤⡴⠄⡀⢈⠉⢴⣿⣿⠟⣁⡀⠨⣀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠉⠁⢀⣀⣉⣉⡉⠉⠉⠉⠀⠘⢿⣄⠀⠉⢿⣷⡌⠻⣟⠻⣿⣦⣀⠀⢠⣾⣿⢋⣴⣷⣶⣦⠘⣶⣿⣵⣿⣿⣿⡦⠈⠳⠀⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⢀⣀⡙⢿⣿⣿⣿⣿⣿⣿⣷⣶⣦⡀⠀⠙⢿⣄⠀⠉⠛⣆⠙⣷⡈⢿⡟⢠⡄⠻⣿⣿⣿⢋⣭⣽⣶⣄⡙⢿⣿⡿⣡⣶⣦⡀⠀⢻⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣡⣶⣿⣿⣿⡟⢠⣿⠿⠿⠿⠿⠿⠿⠟⢉⣤⣤⠀⠀⠈⢿⣶⣄⠀⠳⠘⣿⠀⢠⣿⣿⣦⡈⠻⠇⣾⣿⣿⣿⣟⣛⡂⠰⣤⣿⣿⠿⠃⠀⠸⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⣀⣀⣤⣄⡀⠀⢀⣴⣿⣿⣷⣶⡀⠀⠀⠻⣿⣆⠀⠀⠀⠀⣾⣿⣿⣿⣿⣧⠀⠙⢿⡇⣿⣿⣿⣿⣓⡈⠛⠟⣾⣿⣄⠀⠈⠻⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡟⠁⢀⣠⣶⣿⣿⣿⣿⣿⣿⠟⣰⣿⣿⡿⠿⠟⣁⠀⠀⠀⠀⠻⣿⣶⣶⡄⠀⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠈⠻⠏⢻⣿⣿⣿⣎⣿⣿⣿⣤⡀⠀⢹⣿⣿⣿⣿
⣿⣿⣿⣿⣿⡿⠋⠀⣚⡛⢿⣿⣿⣿⣿⠿⠟⢁⣼⣿⣿⣷⣶⣾⣿⣿⣿⣷⣄⠀⠀⠘⠿⠿⠧⠀⢻⣿⣿⣿⣿⣿⣿⣆⠁⠡⠀⡀⠀⠸⣿⣿⣿⣿⣏⢻⣿⢿⣿⡇⠈⣿⣿⣿⣿
⣿⣿⣿⣿⡿⠃⣠⣾⣿⡿⠸⠿⠋⠉⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⢀⣀⡀⠀⣀⣶⣄⠙⢿⣿⣿⣿⣿⣿⣄⠸⣾⣥⡀⠀⠹⣿⣿⣿⣿⠌⠟⢸⠏⠃⠀⣿⣿⣿⣿
⣿⣿⣿⣿⣷⣾⣿⠟⠋⣀⣤⣶⣾⣿⠏⣠⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⠛⠛⠉⠉⠁⠀⢠⡀⣼⣿⣿⣦⡀⠙⢿⣿⣿⣿⣿⣦⡈⡛⠛⠀⠀⡁⢉⣛⣉⣤⠀⣤⣤⢀⣼⣿⣿⣿⣿
⣿⣿⣿⣿⣿⠟⢀⣴⣾⣿⣿⣿⣿⠏⣸⣿⣿⣿⣿⣿⡿⢛⣩⣤⠔⠋⠁⠀⣤⣴⣿⣇⠘⠇⣿⣿⣿⣿⣿⣦⡈⢿⣿⣿⣿⣿⣿⣶⣄⠀⠠⣿⡈⢿⣿⣿⡄⢹⣧⢸⣿⣿⣿⣿⣿
⣿⣿⣿⣿⠃⢠⣿⣿⣿⣿⣿⠟⠁⣴⣿⣿⣿⣿⠟⣁⣴⡿⠛⠁⠀⣤⣶⣄⠹⣿⣿⣿⣦⡀⢻⣿⣿⣿⣿⣿⣷⣼⣿⣿⣿⣿⣿⣿⣿⣷⠀⡜⣧⣺⣿⣿⣧⢸⣿⢸⣿⣿⣿⣿⣿
⣿⣿⣿⠋⢰⠟⢿⣿⠟⠋⠁⠀⣸⣿⣿⣿⣿⣡⣴⣿⠋⠀⠀⠀⣾⣿⣿⣿⣦⡘⢿⣿⣿⣷⡄⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠜⣿⣿⣿⣯⡈⢿⠈⣿⣿⣿⣿⣿
⣿⣿⡟⠀⣠⣶⠞⠁⢀⣴⣾⢠⣿⣿⣿⣿⣿⣿⡿⠁⠀⣠⣾⡀⢹⣿⣿⣿⣿⡿⢠⣄⠲⣾⣶⣄⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣅⠓⢾⣿⣿⣿⣷⣌⡄⢹⣿⣿⣿⣿
⣿⣿⣇⣾⡿⠁⢠⣴⣿⣿⠃⣿⣿⣿⣿⣿⣿⠟⠀⠀⣾⣿⣿⣿⣦⠙⢿⣿⣿⡇⢿⣿⡷⢈⡙⠛⠻⢁⡉⠻⢿⣿⣿⡏⠛⢿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣷⡈⣿⣿⣿⣿
⣿⣿⣿⡿⠁⣰⣿⣿⣿⠏⣸⣿⣿⣿⣿⣿⠋⠀⠀⠆⠘⣿⣿⣿⣿⣿⣶⣶⣶⣶⣅⠰⣾⣿⠟⢢⣾⣿⣿⣷⣦⣉⠻⣧⣂⡄⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠘⣿⣿⣿
⣿⣿⣿⠀⣼⣿⣿⡿⠃⢠⣿⣿⣿⣿⣿⡏⠀⢀⣾⣿⣧⡘⢿⣿⣿⣿⣧⡈⠿⠿⠛⣁⡀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣷⣆⡙⢿⣶⣌⠙⢿⣿⣿⣿⣿⣿⡋⢰⣶⣦⣉⣻⣧⢨⣉⢻
⣿⣿⡇⠸⢋⡉⠟⠁⠀⢸⣿⣿⣿⣿⡏⠀⠀⣼⣿⣿⣿⣿⣶⣤⡉⣉⣉⣡⡈⣿⣿⠏⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣌⠿⣿⣿⣦⡍⢻⣿⣿⣿⣷⠀⠻⣿⣿⣿⣿⣿⣿⠀
⣿⣿⠃⣠⡿⠁⢀⣴⠇⢸⣿⣿⣿⣿⠃⠀⣆⠸⣿⣿⣿⣿⣿⣿⣷⠹⣿⠿⠗⣠⣴⠂⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡙⠿⣟⢿⣦⠙⢿⣿⡏⠀⠀⠹⣿⣿⣿⣿⣿⡄
⣿⡿⢰⡿⠁⢠⣿⣿⠀⣼⣿⣿⣿⡇⠀⢀⣉⣤⣈⠛⠿⠿⠿⠿⠟⡀⢠⣶⣾⣿⠃⢀⠆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣊⠆⢻⣇⠺⣿⣧⣡⡀⠀⣛⣉⣽⢫⡟⣠
⣿⣿⣿⠁⢠⣿⣿⡏⢀⣿⣿⣿⣿⠀⢠⣿⣿⣿⣿⣿⣶⡆⢰⣾⣿⣷⡈⢛⣛⡋⠀⢸⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠅⣿⣅⠿⢿⣿⣉⣰⣿⣿⣿⢼⠇⣿
⣿⣿⡇⠀⣾⣿⣿⡇⢸⣿⣿⣿⡏⠀⣄⠻⣿⣿⣿⣿⣿⣷⡈⠿⠛⣫⣴⣿⣿⡏⠁⣼⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣿⣿⣿⣆⠈⠻⣷⣤⣍⠛⢿⣿⠿⢃⠐⣰⣿
⣿⣿⠃⢸⣿⣿⣿⡇⢸⣿⣿⣿⠃⠀⣋⣥⣬⡛⠻⠿⠿⠛⣋⠐⢿⣿⣿⣿⣿⡃⠀⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣸⣿⣿⣿⣿⣿⣿⣦⣬⣙⠛⣓⡀⠙⠺⢀⣴⣿⣿
⣿⣿⠀⠋⣡⣤⡌⠃⢸⣿⣿⡟⠀⣰⣿⣿⣿⣿⣷⡆⢲⣿⣿⣷⡌⠛⠛⠋⣡⡄⢰⣿⣇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⣶⣿⣿⣿⣿
⣿⡯⢀⣾⣿⣿⠁⠀⢸⣿⣿⠇⠀⢿⣿⣿⣿⣿⣿⣿⣦⠹⠿⢛⣡⣾⣿⣿⣦⡀⢸⣿⣿⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
            )";
            asciiArts["gameover"] = R"(
            ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁
⠀⠀⠀⠀⠀⠀⣀⣀⣄⣀⠀⠀⠀⠀⣶⣶⣦⠀⠀⠀⠀⣼⣿⣿⡇⠀⣠⣿⣿⣿⠇⣸⣿⣿⣧⣤⠀⠀⠀
⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁⠀⠀
⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀
⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀
⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀
⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆
⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀
⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀
⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀
⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀
⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

            )";
            asciiArts["mago_ataque"] = R"(
                    '             .           .
    o       '   o  .     '   . O
'   .   ' .   _____  '    .      .
    .     .   .mMMMMMMMm.  '  o  '   .
'   .     .MMXXXXXXXXXMM.    .   ' 
.       . /XX77:::::::77XX\ .   .   .
    o  .  ;X7:::''''''':::7X;   .  '
'    . |::'.:'        '::| .   .  .
    .   ;:.:.            :;. o   .
'     . \'.:            /.    '   .
    .     `.':.        .'.  '    .
    '   . '  .`-._____.-'   .  . '  .
    ' o   '  .   O   .   '  o    '
    . ' .  ' . '  ' O   . '  '   '
    . .   '    '  .  '   . '  '
        . .'..' . ' ' . . '.  . '
        `.':.'        ':'.'.'
        `\\_  |     _//'
            \(  |\    )/
            //\ |_\  /\\
            (/ /\(" )/\ \)
            \/\ (  ) /\/
                |(  )|
                | \( \
                |  )  \
                |      \
                |       \
                |        `.__,
                \_________.-'Ojo/gnv
            )";
            asciiArts["dragao"] = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣀⣠⣼⠂⠀⠀⠀⠀⠙⣦⢀⠀⠀⠀⠀⠀⢶⣤⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⠷⢦⠀⣹⣶⣿⣦⣿⡘⣇⠀⠀⠀⢰⠾⣿⣿⣿⣟⣻⣿⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⢺⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⢟⣥⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⢻⣿⣿⡏⢹⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⣝⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢛⣿⣿⣿⡇⠀⠀⠀⠀⠛⣿⣿⣷⡀⠘⢿⣧⣻⡷⠀⠀⠀⠀⠀⠀⣿⣿⣿⣟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣝⢧⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢠⣾⣿⠟⣡⣾⣿⣿⣧⣿⡿⣋⣴⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⢻⣿⣿⣿⣶⡄⠙⠛⠁⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣷⣝⢻⣿⣟⣿⣿⣷⣮⡙⢿⣽⣆⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢀⡿⢋⣴⣿⣿⣿⣿⣿⣼⣯⣾⣿⣿⡿⣻⣿⣿⣿⣦⠀⠀⠀⠀⢀⣹⣿⣿⣿⣿⣶⣤⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⠻⣿⣿⣿⣮⣿⣿⣿⣿⣿⣿⣦⡙⢿⣇⠀⠀⠀⠀
⠀⠀⠀⣠⡏⣰⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿⡿⢋⣼⣿⣿⣿⣿⣿⣷⡤⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⢠⣾⣿⣿⣿⣿⣿⣷⡜⢿⣿⣿⣿⣿⣿⣿⡿⠿⣿⣿⣦⡙⣦⠀⠀⠀
⠀⠀⣰⢿⣿⣿⠟⠋⣠⣾⣿⣿⣿⣿⣿⠛⢡⣾⡿⢻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠻⣿⡟⣿⣿⣿⠻⢿⣿⣿⣿⣿⣿⣿⣿⣟⠻⣿⣆⠙⢿⣿⣿⣿⣿⣿⣦⡈⠻⣿⣿⣟⣧⠀⠀
⠀⣰⢣⣿⡿⠃⣠⡾⠟⠁⠀⣸⣿⡟⠁⢀⣿⠋⢠⣿⡏⣿⣿⣿⣿⣿⢿⠁⢀⣠⣴⢿⣷⣿⣿⣿⠀⠀⠽⢻⣿⣿⣿⣿⡼⣿⡇⠈⢿⡆⠀⠻⣿⣧⠀⠈⠙⢿⣆⠈⠻⣿⣎⢧⠀
⠀⢣⣿⠟⢀⡼⠋⠀⠀⢀⣴⠿⠋⠀⠀⣾⡟⠀⢸⣿⠙⣿⠃⠘⢿⡟⠀⣰⢻⠟⠻⣿⣿⣿⣿⣿⣀⠀⠀⠘⣿⠋⠀⣿⡇⣿⡇⠀⠸⣿⡄⠀⠈⠻⣷⣄⠀⠀⠙⢷⡀⠙⣿⣆⠁
⢀⣿⡏⠀⡞⠁⢀⡠⠞⠋⠁⠀⠀⠀⠈⠉⠀⠀⠀⠿⠀⠈⠀⠀⠀⠀⠀⣿⣿⣰⣾⣿⣿⣿⣿⣿⣿⣤⠀⠀⠀⠀⠀⠉⠀⠸⠃⠀⠀⠈⠋⠀⠀⠀⠀⠙⠳⢤⣀⠀⠹⡄⠘⣿⡄
⣸⡟⠀⣰⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⠿⠿⠟⠁⠀⠹⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣧⠀⢹⣷
⣿⠃⢠⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣄⣤⣀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⡇⠀⣿
⣿⠀⢸⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠋⠉⢻⣧⢀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⢸
⡇⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣧⡀⠀⠀⣿⣾⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⢸
⢸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠿⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾
⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⢀⣾⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡼⣿⣿⣾⣤⣠⡼⠀⠀⠀
            )";
            asciiArts["bruxa"] = R"(
                    Ash nazg durbatulûk
                    agh burzum-ishi
(       "     )   krimpatul
( _  *           Gûlburz agh dûmûrz
    * (     /      \    ___
        "     "        _/ /
        (   *  )    ___/   |
        )   "     _ o)'-./__
        *  _ )    (_, . $$$
        (  )   __ __ 7_ $$$$
        ( :  { _)  '---  $\
    ______'___//__\   ____, \
    )           ( \_/ _____\_
    .'             \   \------''.
    |='           '=|  |         )
    |               |  |  .    _/
    \    (. ) ,   /  /__I_____\
snd  '._/_)_(\__.'   (__,(__,_]
    @---()_.'---@
            )";
            asciiArts["ogro"] = R"(
            __,='`````'=/__
            '//  (o) \(o) \ `'         _,-,
            //|     ,_)   (`\      ,-'`_,-\
        ,-~~~\  `'==='  /-,      \==```` \__
        /        `----'     `\     \       \/
    ,-`                  ,   \  ,.-\       \
    /      ,               \,-`\`_,-`\_,..--'\
    ,`    ,/,              ,>,   )     \--`````\
    (      `\`---'`  `-,-'`_,<   \      \_,.--'`
    `.      `--. _,-'`_,-`  |    \
    [`-.___   <`_,-'`------(    /
    (`` _,-\   \ --`````````|--`
        >-`_,-`\,-` ,          |
    <`_,'     ,  /\          /
    `  \/\,-/ `/  \/`\_/V\_/
        (  ._. )    ( .__. )
        |      |    |      |
        \,---_|    |_---./
        ooOO(_)    (_)OOoo
            )";
            asciiArts["mago"] = R"(
              _,._      
  .||,       /_ _\\     
 \.`',/      |'L'| |    
 = ,. =      | -,| L    
 / || \    ,-'\"/,'`.   
   ||     ,'   `,,. `.  
   ,|____,' , ,;' \| |  
  (3|\    _/|/'   _| |  
   ||/,-''  | >-'' _,\\ 
   ||'      ==\ ,-'  ,' 
   ||       |  V \ ,|   
   ||       |    |` |   
   ||       |    |   \  
   ||       |    \    \ 
   ||       |     |    \
   ||       |      \_,-'
   ||       |___,,--")_\
   ||         |_|   ccc/
   ||        ccc/       
   ||                hjm
            )";
            asciiArts["cavaleiro"] = R"(
    / \
    | |
    |.|
    |.|
    |:|      __
 ,_|:|_,   /  )
   (Oo    / _I_
    +\ \  || __|
       \ \||___|
         \ /.:.\-\
           |.:. /-----\
           |___|::oOo::|
          /   |:<_T_>:|
         |_____\ ::: /
         | |  \ \:/
         | |   | |
         \ /   | \___
         / |   \_____\
            )";
            asciiArts["intro"] = R"(
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;-' ___      '-;;;;;;;;;;;;;;;;
;;;;;;;;;;;;-'    `'-.`'-.      '-;;;;;;;;;;;;
;;;;;;;;;;'           )   `\       ';;;;;;;;;;
;;;;;;;;'            /      \   ^V^  ';;;;;;;;
;;;;;;;           __/________\__       ;;;;;;;
;;;;;;  ^V^      '--/}}}}}}"}}--'       ;;;;;;
;;;;;              {{{{{{  aa\__         ;;;;;
;;;;;              }}}}} ,___ __}        ;;;;;
;;;;;             {{{{{\  \_//           ;;;;;
;;;;;              }}}}//'--u            ;;;;;
;;;;;        _     .--'`U\               ;;;;;
;;;;;   ::::| \   (   _,\\\              ;;;;;
;;;;;;  ::::|  |===\  \\=\))=======D    ;;;;;;
;;;;;;; ::::|_/     `> \\              ;;;;;;;
;;;;;;;;.           /__//            .;;;;;;;;
;;;;;;;;;;.         Y\_\\_         .;;;;;;;;;;
;;;;;;;;;;;;-._                _.-;;;;;;;;;;;;
;;;;;;;jgs;;;;;;-.          .-;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
            )";
            asciiArts["demo"] = R"(
                     ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
eViL        /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'
            )";
            asciiArts["template"] = R"(
            )";
            // Cadastra as cenas utilizando as ASCII arts definidas
            Scene scene1(asciiArts["intro"], "Em um reino muito distante chamado Exandria uma bruxa muito má estava selada em uma rocha e após 100 anos o selo enfraqueceu e ela se libertou...Após se libertar, a Bruxa voou em direção ao reino de Exandria que era comandado pelos descendentes daqueles que a selaram, chegando lá ela percebeu que estava ocorrendo um festival, onde os Reis e rainhas de todos os reinos se reuniam para celebrar a paz entre eles, aproveitando essa oportunidade a bruxa esperou o momento em que o rei e rainha do reino anfitrião apareceriam para declarar inicio ao festival e os matou na frente de todos, declarando guerra ao todos os reinos e avisando para se preparem que voltaria para destruir todos os reinos um a um e saiu. A filha do rei e rainha que foram mortos pela Bruxa, a princesa Fiona, presenciou todo o assassinato e a declaração de guerra e se enfureceu...Você foi convocado para fazer parte do exercito que deseja derrotar a bruxa, você aceita o desafio? < S | N >");
            scene1.addChoice("Sim, aceito a missão de matar a bruxa!", 2);
            scene1.addChoice("Não, vai procurar o que fazer..", 9);
            storyManager.addScene(1, scene1);
    
            Scene scene2(asciiArts["cavaleiro"], "Escolha sua classe:.");
            scene2.addChoice("Cavaleiro", 3);
            scene2.addChoice("Mago", 3);
            storyManager.addScene(2, scene2);

            Scene scene3(asciiArts["ogro"], "Cap I Parte - I: A floresta \n Ao entrar no exército você foi ao castelo da princesa fiona onde todos foram convocados para receber as primeiras instruções...Chegando no castelo, você estranhou, pois só tinha você, um (mago ou cavaleiro, a classe que restou) e um aldeão, e se questionou se estava no lugar certo, e logo em seguida a princesa foi até vocês e se pronunciou: \n-Olá bravos guerreiros, sinto dizer que só restou a nós, tínhamos um exército com mais de 10 mil homens mas todos foram mortos pela Bruxa na primeira tentativa de invasão, mas convoquei vocês aqui porque a morte desses homens não foi em vão, eles nos deixaram um pedaço de pergaminho com um mapa até a Bruxa e todos os possíveis perigos que nós iremos enfrentar.\nE logo o aldeão pergunta:\n -Nós? Você irá conosco? E seremos so nós?\n E a princesa responde:\n -Sim! Não perderei a oportunidade de vingar meus pais, além disso, durante toda minha vida fui treinada por uma feiticeira que aconselhava minha família, então poderei lutar ao lado de vocês.\nE respondendo a sua segunda pergunta, Sim! Seremos só nós, e será o suficiente para acabar com a Bruxa agora que temos esse pergaminho.-\nApós a pequena reunião e sanadas as dúvidas entre o grupo, o mesmo se dirige para floresta em busca do covil da bruxa e é surpreendido por um grupo de ogros atacando aldeões.\n[Missão 01] Derrote os ogros antes que eles matem os aldeões, PREPARE-SE PARA O COMBATE!");

            Monstro inimigo("Ogro");

            while ((personagem.estaVivo() && inimigo.estaVivo())
            {
                cavaleiro.atacar(ogro);
                if (ogro.estaVivo())
                    ogro.atacar(cavaleiro);
            }
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
            scene1.addChoice("Iniciar o combate", 1);
            storyManager.addScene(3, scene3);
            
            Scene scene35(asciiArts["demo"], "Na busca pela bruxa vocês chegam ao labirinto e devem encontrar a entrada do covil, mas agora estão parados em uma bifurcação com 03 salas que não estavam registrados no mapa, qual deseja entrar?");
            scene2.addChoice("Sala Clara", 1);
            scene2.addChoice("Sala meio iluminada", 2);
            scene2.addChoice("Sala Escura", 3);
            storyManager.addScene(35, scene35);

            Scene scene4(asciiArts["bruxa"], "Cap II: A bruxa \n Após a batalha na floresta, vocês viajam por dias em busca do covil, seguindo o mapa que vocês possuem, o cheiro de pântano começa a crescer, a umidade se tora desconfortável, uma névoa vem crescendo ha dias, de repente vocês se deparam com uma criatura na entrada de um covil, aparentemente realizando algum tipo de ritual, o que deseja fazer:");
            scene2.addChoice("Aproximar-se sorrateiramente", 1);
            scene2.addChoice("Atacar com tudo", 2);
            storyManager.addScene(4, scene4);

            Scene scene5(asciiArts["dragao"], "Cap III: A segunda forma \n Vocês lutaram bravamente e derrotaram a bruxa, mas as coisas não são tão fáceis quanto parece, quando olham para o corpo dela desfalecido no chão, percebem que a sua pele começa a mudar, olhos amarelando, dentes afiados e a seu tamanho aumentando, de repente, um dragão aparece.\n[Missão 02: Derrote o dragão]");
            scene1.addChoice("Iniciar o combate", 1);
            storyManager.addScene(5, scene5);
    
            Scene scene6(asciiArts["mago_ataque"], "Percebendo que a luta com o dragão estava bastante perigosa a princesa desperta um poder ancestral e canaliza toda a energia para destruir o dragão, salvando todos do grupo. O dragão se debate, gorgoleja e finalmente é derrotado..");
            scene2.addChoice("Iniciar o combate:", 1);
            storyManager.addScene(6, scene6);
    
            Scene scene7(asciiArts["castelo"], "Parabéns, com a derrota do dragão o reino provou uma paz por alguns anos ! ");
            scene2.addChoice("Pressione para continuar", 1);
            storyManager.addScene(7, scene7);

            Scene scene8(asciiArts["endgame"], "Porém tudo que é bom dura pouco, boatos surgem e parece que a bruxa deixou ovos de dragão escondidos na floresta, que eclodiram com o passar dos anos e agora relatos de diversos dragões atacando outros reinos tem se tornado frequentes, talvez ainda precisaremos da sua ajuda aventureiro.\<<FIM>>");
            scene8.addChoice("Voltar ao início", 1);
            storyManager.addScene(1, scene1);
    
            Scene scene9(asciiArts["gameover"], "Você morreu. Deseja tentar de novo?");
            scene9.addChoice("Sim", 1);
            scene9.addChoice("Não", 2);
            storyManager.addScene(1, scene1);
        }
    
        // Método principal do jogo, que gerencia o fluxo entre as cenas
        void run() {
            int currentSceneId = 1;
            while (true) {
                Scene *currentScene = storyManager.getScene(currentSceneId);
                if (currentScene == nullptr) {
                    std::cout << "Cena não encontrada. Encerrando o jogo.\n";
                    break;
                }
                
                // Exibe a cena atual
                currentScene->display();
                
                // Se a cena não tiver escolhas, finaliza o jogo
                if (currentScene->getChoices().empty()) {
                    std::cout << "\nFim da história.\n";
                    break;
                }
                
                // Processa a escolha do usuário
                int choice = inputHandler.getUserChoice();
                if (choice <= 0 || choice > currentScene->getChoices().size()) {
                    std::cout << "Opção inválida, tente novamente.\n";
                    continue;
                }
                currentSceneId = currentScene->getChoices()[choice - 1].getTargetSceneId();
            }
        }
    
    private:
        StoryManager storyManager;
        InputHandler inputHandler;
        std::map<std::string, std::string> asciiArts; // Map de ASCII arts pré-definidas
};
    
/*nas escolhas do jogador pode acontecer eventos aletorios que vao modificar seus 
atributos de forma positiva ou negativa*/

/*
RandomEvent
Função: Representa um evento aleatório que pode ocorrer durante a narrativa. Esses eventos podem afetar as estatísticas do jogador, a história ou o ambiente do jogo de maneira imprevisível.
*/
class RandomEvent {
    public:
        void applyEvent();
    };