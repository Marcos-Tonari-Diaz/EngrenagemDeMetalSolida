# Engrenagem de Metal Sólida: 
## Ação de Espionagem Tática
### METAL GEAR!? Ajude o Snake a escapar para o heliporto! 
#### Abra portas e desvie dos guardas no caminho

### Instruções Multiplayer
1. Rodar em um terminal ./EngrenagemDeMetalSolida
2. Rodar em um terminal ./EngrenagemDeMetalSolida monitor

### Instruções
1. Clonar o repositório
2. Criar a pasta build vazia (mkdir build)
3. Entrar na pasta build (cd build)
4. Criar o makefile (cmake ../) 
5. Compilar (make)
6. Criar a documentacao (make doc)
7. Rodar o jogo (./EngrenagemDeMetalSolida)
8. Aperte Espaço para jogar!
9. Ler a documentacao (dentro de build: firefox html/index.html)

OBS: tecla A abre portas

### Gerador de Mapas
Na pasta assets/maps podemos criar novos mapas em codigo.

Podemos criar um novo arquivo mapa pelo script em tilemapPy.

Legenda:
* wall: 0
* corridor: 1
* porta_fechada: 2
* porta_aberta: 3
* camera_cima: 4
* camera_baixo: 5
* camera_direita: 6
* camera_esquerda: 7
* endEnd: E

#### Dirigido por Marcos e Walker Kojima
