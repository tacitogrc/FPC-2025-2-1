// Inclui as definições de classes
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctime> // Include ctime for time function

#define coin 2
#define d4 4
#define d6 6
#define d8 8
#define d10 10
#define d12 12
#define d20 20
#define d100 100

int roll_dice (int dice_num);

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
            asciiArts["template"] = R"(
            )";
            
            // Cadastra as cenas utilizando as ASCII arts definidas
            Scene scene1(asciiArts["intro"], "Bem-vindo à paisagem montanhosa!");
            scene1.addChoice("Ir para a floresta", 2);
            storyManager.addScene(1, scene1);
    
            Scene scene2(asciiArts["gameover"], "Você chegou a uma floresta densa.");
            scene2.addChoice("Voltar à montanha", 1);
            storyManager.addScene(2, scene2);

            Scene scene3(asciiArts["intro"], "Bem-vindo à paisagem montanhosa!");
            scene1.addChoice("Ir para a floresta", 2);
            storyManager.addScene(1, scene1);
    
            Scene scene4(asciiArts["gameover"], "Você chegou a uma floresta densa.");
            scene2.addChoice("Voltar à montanha", 1);
            storyManager.addScene(2, scene2);

            Scene scene5(asciiArts["intro"], "Bem-vindo à paisagem montanhosa!");
            scene1.addChoice("Ir para a floresta", 2);
            storyManager.addScene(1, scene1);
    
            Scene scene6(asciiArts["gameover"], "Você chegou a uma floresta densa.");
            scene2.addChoice("Voltar à montanha", 1);
            storyManager.addScene(2, scene2);
    
            Scene scene7(asciiArts["gameover"], "Você chegou a uma floresta densa.");
            scene2.addChoice("Voltar à montanha", 1);
            storyManager.addScene(2, scene2);

            Scene scene8(asciiArts["gameover"], "Você chegou a uma floresta densa.");
            scene2.addChoice("Voltar à montanha", 1);
            storyManager.addScene(2, scene2);
    
            Scene scene9(asciiArts["gameover"], "Você chegou a uma floresta densa.");
            scene2.addChoice("Voltar à montanha", 1);
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



