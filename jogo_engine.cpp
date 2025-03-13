// Inclui as definições de classes
#include <iostream>
#include <string>

/*
Game/Engine
Função: Classe principal que gerencia o ciclo do jogo. Ela inicia a aplicação, mantém o loop principal, atualiza o estado do jogo e delega chamadas para outras classes (por exemplo, recebendo input e atualizando a narrativa).
*/
class Game {
    public:
        void run(); // Loop principal do jogo
    private:
        StoryManager storyManager;
        InputHandler inputHandler;
    };

/*
Função: Responsável por gerenciar a sequência da narrativa, definindo qual cena deve ser apresentada a seguir com base nas escolhas do usuário. Essa classe pode armazenar a estrutura narrativa (por exemplo, em forma de árvore ou grafo) e controlar o fluxo da história.
*/
class StoryManager {
    public:
        void startStory();
        void nextScene(int choiceId);
    private:
        std::map<int, Scene> scenes; // Mapeia identificadores de cena
        int currentSceneId;
};

/*
Função: Representa um “capítulo” ou momento da história. Cada cena pode conter o texto narrativo, as descrições do ambiente e uma lista de opções que o jogador pode escolher para avançar a narrativa.
*/
class Scene {
    public:
        std::string getText() const;
        const std::vector<Choice>& getChoices() const;
    private:
        std::string narrativeText;
        std::vector<Choice> choices;
    };


/*
Função: Modela uma opção de interação disponível dentro de uma cena. Cada escolha pode ter uma descrição e uma referência à cena ou efeito que ela provoca, possibilitando a ramificação da narrativa.
NEW: As escolhas podem acionar eventos aleatórios, modificar atributos do jogador ou influenciar o curso da história.
*/
class Choice {
    public:
        Choice(const std::string& text, int nextSceneId)
            : description(text), targetSceneId(nextSceneId) {}
        std::string getDescription() const;
        int getTargetSceneId() const;
    private:
        std::string description;
        int targetSceneId;
    };
       
/*
Função: Responsável por capturar e interpretar a entrada do usuário. Essa classe pode validar as opções digitadas ou selecionadas, transformando a entrada em comandos ou escolhas que serão processadas pelo StoryManager.
*/
class InputHandler {
    public:
        int getUserChoice();
    };

/*
DecisionEngine/BranchingEngine
Função: Se a sua narrativa tiver regras mais complexas ou variáveis que influenciem o curso da história (por exemplo, estados que persistem durante o jogo), uma classe dedicada para processar essas decisões pode ser útil. Ela pode avaliar condições e determinar a próxima cena com base em múltiplos fatores.
*/
class DecisionEngine {
    public:
        int evaluateDecision(const Scene& scene, int choiceId);
    };

/*nas escolhas do jogador pode acontecer eventos aletorios que vao modificar seus 
atributos de forma positiva ou negativa*/

/*
RandomEvent
Função: Representa um evento aleatório que pode ocorrer durante a narrativa. Esses eventos podem afetar as estatísticas do jogador, a história ou o ambiente do jogo de maneira imprevisível.
*/
class RandomEvent {
    public:
        void applyEvent(FormaDeVida& character);
    };



