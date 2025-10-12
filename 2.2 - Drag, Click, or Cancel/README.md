# Drag, Click e Cancel

## Descrição

Este programa implementa uma interface interativa com um quadrado branco que pode ser clicado ou arrastado. O programa distingue entre cliques simples e operações de arrastar e soltar (drag and drop), além de permitir o cancelamento da operação.

## Máquina de Estados

O programa usa três estados principais:

* **IDLE:** Estado inicial/repouso do quadrado
* **PRESSED:** Mouse pressionado sobre o quadrado
* **DRAGGING:** Quadrado sendo arrastado

## Funcionalidades

### 1. Clique Simples

* Ao clicar no quadrado sem mover o mouse
* Exibe "Click!" no console
* Retorna ao estado **IDLE**

### 2. Drag and Drop

* Clique + movimento do mouse inicia o arrasto
* O quadrado segue o cursor do mouse
* Ao soltar, exibe "Drop!" no console
* Retorna ao estado **IDLE**

### 3. Cancelamento

* Pressionar **ESC** durante **PRESSED** ou **DRAGGING**
* Retorna o quadrado à posição original
* Exibe "Cancelled!" no console
* Retorna ao estado **IDLE**
