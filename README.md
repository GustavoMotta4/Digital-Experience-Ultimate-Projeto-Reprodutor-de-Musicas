# Relatório de Projeto: Reprodutor de Músicas (Digital Experience Ultimate)

##  Autores
* **Nome do Integrante 1** Gustavo Motta Barbosa dos Santos - R.A.: 22.0126058-1
* **Nome do Integrante 2** João Victor Silva dos Santos- R.A.: 22.225.071-4

---

## 1. Introdução
O presente projeto descreve o desenvolvimento de um sistema embarcado de reprodução de áudio digital, fundamentado na plataforma Arduino. O dispositivo foi projetado para atuar como um player interativo, permitindo ao usuário selecionar, reproduzir e pausar melodias complexas armazenadas em sua memória interna, oferecendo feedback em tempo real através de componentes visuais e sonoros.

### 1.1 Apresentação do Problema
O desenvolvimento de aplicações multimídia em microcontroladores de baixo custo, como o ATmega328P (Arduino UNO), impõe restrições severas de hardware. O desafio técnico principal reside na **escassez da memória RAM (2 KB)**. Armazenar partituras musicais contendo centenas de frequências e durações em vetores convencionais causaria o transbordamento da pilha de memória (*Stack Overflow*), resultando no travamento do sistema. Além disso, a implementação exige um sistema de controle de fluxo (play/pause/stop) que deve ser processado simultaneamente à geração de tons no buzzer, sem causar latência na interface do usuário.

### 1.2 Objetivos
* **Gerenciamento de Memória:** Implementar uma estratégia de armazenamento que suporte 5 músicas distintas sem esgotar a RAM.
* **Sistema de Controle:** Desenvolver uma lógica de navegação robusta via menu (UP/DOWN) e controle de execução (Play, Pause e Stop).
* **Interface Homem-Máquina (IHM):** Integrar um display LCD 16x2 para exibição de nomes das faixas e estados do sistema, auxiliado por LEDs indicadores de status (Verde para execução e Vermelho para pausa).
* **Fidelidade Sonora:** Garantir a reprodução precisa das frequências musicais em sincronia com o BPM (batidas por minuto) específico de cada canção.

---

## 2. Metodologia

### 2.1 Descrição dos Materiais Utilizados
A arquitetura do hardware foi composta pelos seguintes itens:
* **Microcontrolador:** Arduino UNO.
* **Display:** LCD 16x2.
* **Atuador Sonoro:** Buzzer piezoelétrico.
* **Controles de Entrada:** 4 Botões do tipo Push Button (com Pull-up interno).
* **Indicadores Luminosos:** 1 LED Verde e 1 LED Vermelho.
* **Infraestrutura:** Protoboard, jumpers e resistores.

### 2.2 Métodos de Desenvolvimento
O desenvolvimento foi dividido em hardware e firmware. No firmware, a lógica foi estruturada em uma "Máquina de Estados". Diferente de códigos simples que utilizam `delay()` de forma impeditiva, a estrutura permite a leitura dos botões durante a execução da música. O display LCD é atualizado através da biblioteca `LiquidCrystal`, utilizando uma função dedicada para reescrever informações apenas quando necessário, otimizando o ciclo de processamento.

> **[INSERIR AQUI A FOTO DO PROJETO MONTADO NA PROTOBOARD]**

---

## 3. Experimentos e Resultados
Os testes validaram cada funcionalidade conforme os requisitos técnicos estabelecidos.

### 3.1 Navegação e Seleção
Ao iniciar, o sistema entra em estado de "Aguardando". Os botões UP e DOWN permitem percorrer o vetor de faixas. O sistema garante o "looping" do menu (ao chegar na última música, volta para a primeira).

foto do menu de seleção no lcd

### 3.2 Lógica de Play/Pause e Sinalização
* **Tocando:** Ao pressionar Play, o LED Verde acende e a música inicia no buzzer.
* **Pausado:** Um novo clique no Play pausa a canção no ponto exato, mantendo o LED Vermelho aceso.
* **Stop:** O botão Stop interrompe a música e reseta o sistema para o menu inicial.

video do projeto funcionando

---

## 4. Tecnologias Utilizadas
* **Linguagem C++:** Utilizada com foco em manipulação de tipos de dados otimizados.
* **Biblioteca avr/pgmspace.h:** Tecnologia chave que permitiu o acesso aos dados gravados na memória FLASH (memória de programa).
* **Biblioteca LiquidCrystal:** Padronização da comunicação via 4 bits com o display.

---

## 5. Referências
As melodias e partituras utilizadas neste projeto foram adaptadas do repositório público:
* **Arduino Songs** por Robson Couto. Disponível em: [https://github.com/robsoncouto/arduino-songs](https://github.com/robsoncouto/arduino-songs)

---

## 6. Conclusão: Detalhamento da Solução
A solução definitiva para o problema de memória e controle foi alcançada através de três pilares fundamentais:

1. **Otimização via Memória FLASH (PROGMEM):** Para contornar os limitados 2 KB de RAM, utilizamos o modificador `PROGMEM` em todos os arrays de notas. Isso deslocou os dados pesados das canções para a memória FLASH (32 KB), onde o programa é armazenado. Para ler esses dados, empregamos as funções `pgm_read_word` e `pgm_read_byte`. Esta técnica foi o que permitiu ter 5 músicas complexas sem riscos de instabilidade.

2. **Lógica de Temporização Dinâmica:** A duração real de cada nota foi calculada matematicamente baseada no BPM de cada faixa. Através da fórmula `(60000 * 4) / tempoAtual`, o código traduz o andamento musical em milissegundos precisos. Notas negativas nos arrays foram interpretadas como notas pontuadas (aumentadas em 50%), conferindo musicalidade real ao buzzer.

3. **Gerenciamento de Fluxo Não-Bloqueante:** O código foi estruturado para realizar a leitura dos botões (`digitalRead`) a cada iteração. Isso permitiu que o comando de "Pause" ou "Stop" fosse detectado instantaneamente, interrompendo a sequência sonora de forma responsiva. O projeto final cumpre rigorosamente todos os requisitos de funcionalidade e interface estabelecidos.
