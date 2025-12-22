# 🖱️ Caio Clicker (Incremental Game Prototype)

![C++](https://img.shields.io/badge/Language-C++17-blue)
![Engine](https://img.shields.io/badge/Engine-Raylib-orange)
![Build](https://img.shields.io/badge/Build-CMake-green)

Um protótipo de jogo do gênero "Clicker/Incremental" desenvolvido em C++ e Raylib. O foco deste projeto é implementar sistemas de progressão matemática escalável, gerenciamento de estado de UI e persistência de dados.

![Gameplay Demo](https://i.imgur.com/gt0Gb80.gif)

## 🎯 Destaques Técnicos

Este projeto foca na arquitetura de sistemas de progressão e interfaces reativas:

* **Game Loop Incremental:** Lógica de acumulação de recursos independente da taxa de quadros (framerate).
* **Arquitetura de UI:** Separação clara entre a lógica de gameplay (o clicker) e a camada de interface (loja/upgrades).
* **Escalabilidade Numérica:** Estrutura preparada para lidar com cálculos de progressão exponencial e custos de upgrades.
* **Gerenciamento de Estado:** Transição fluida entre telas e atualização em tempo real dos status do jogador.

## 🛒 Interface e Loja

O jogo conta com um sistema de loja funcional para aquisição de itens que influenciam diretamente a jogabilidade.

![Loja do Caio](https://i.imgur.com/z8IFRfU.png)

## 🕹️ Funcionalidades Atuais

- [x] **Core Loop:** Base completa de um jogo clicker (clique e acumulação).
- [x] **Sistema de Economia:** Loja com upgrades e itens funcionais.
- [ ] **Sistema de Conquistas (Achievements):** Recompensas por marcos alcançados.
- [ ] **Polimento Visual:** Implementação de sprites e identidade visual personalizada.
