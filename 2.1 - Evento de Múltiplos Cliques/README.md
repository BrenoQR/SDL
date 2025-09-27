# Múltiplos Cliques com Estrelas

## Descrição
Este programa cria uma animação interativa onde o usuário pode gerar estrelas no céu noturno clicando na lua. O número de estrelas geradas depende da quantidade de cliques consecutivos realizados.

## Funcionamento

### Sistema de Múltiplos Cliques
- Um clique múltiplo inicia no primeiro clique
- O sistema conta cliques consecutivos dentro de janelas de 250ms
- A sequência termina após 250ms sem cliques
- Cada sequência gera um evento com o total de cliques

### Interface Visual
- Janela de 400x400 pixels
- Fundo azul escuro simulando céu noturno
- Lua branca centralizada
- Estrelas brancas pequenas

### Comportamento
1. A lua aparece no centro da tela
2. Ao clicar na lua, inicia-se uma sequência
3. Cliques adicionais na lua dentro de 250ms são contabilizados
4. Após 250ms sem cliques:
   - Sistema gera evento com total de cliques
   - Mostra número de cliques no log
   - Cria estrelas aleatórias no céu
5. Número de estrelas criadas = número de cliques na sequência
6. Máximo de 100 estrelas podem ser criadas
