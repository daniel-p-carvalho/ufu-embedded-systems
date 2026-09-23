# Backlog — Sistemas Embarcados I

Lista de pendências identificadas durante a reestruturação do curso. Não está em ordem de prioridade estrita — itens marcados 🔥 são os mais urgentes/bloqueantes.

## Conteúdo — Aula de Fundamentos de Linux

- [ ] **Quebrar o bloco de texto com imagens/screenshots.** A aula ficou densa (texto corrido, poucas imagens). Adicionar capturas de tela reais do terminal (prompt, `ls -la`, `nano`, `vim`, resultado de `find`/`grep`) ao longo do texto, no mesmo espírito das imagens dos labs antigos (`ufu-semb1-lab-01-old`, `lab-02`, `lab-03`).

## Módulo 1 — Estrutura e Conteúdo

- [ ] 🔥 **Reordenar capítulos do Módulo 1** conforme decidido: hoje "Ambiente e Ferramentas de Desenvolvimento" é o primeiro capítulo (prioridade de entrega urgente aos estudantes). A ordem pedagogicamente correta é:
  1. O que é um Sistema Embarcado? (conceitual)
  2. Arquitetura de Computadores / ARM / Cortex-M (teoria)
  3. Ambiente e Ferramentas de Desenvolvimento (atual)
  4. Toolchain e Startup na prática (labs)
- [ ] **Escrever capítulo "O que é um Sistema Embarcado?"** — conteúdo-base já existe na `APOSTILA.docx` (seção "Introdução aos Sistemas Embarcados").
- [ ] **Escrever capítulos de Arquitetura de Computadores / ARM / Cortex-M** — conteúdo-base na `APOSTILA.docx`:
  - Fundamentos (Von Neumann, ISA, Load-Store vs. Register-Memory)
  - Histórico ARM (ARMv1 → ARMv8)
  - Modos/registradores do Cortex-M3/M4
  - **Atenção:** a apostila termina no meio da seção de Registradores — precisa ser complementada (pilha/stack, exceções, NVIC) antes de virar capítulo.
  - Imagens já extraídas da apostila (Von Neumann, transições Thread/Handler Mode, banco de registradores) — reaproveitar.
- [ ] **Migrar conteúdo dos labs 02/03** (`ufu-semb1-lab-02`, `ufu-semb1-lab-03`) para dentro do Módulo 1:
  - lab-02 "Blinky 01": cross-compilation, `startup.c` do zero, Makefile incremental
  - lab-03 "Roteiro-01": GPIO por registrador, análise de ELF, linker script do zero
- [ ] **Decidir o que fazer com `lab-04`**: hoje é uma cópia quase idêntica do `lab-03` (só muda 1 comentário e o valor de `LED_DELAY`). Definir o que deveria estar lá de fato.
- [ ] **Confirmar placa oficial do curso**: os labs reais usam **STM32F411 Blackpill**, mas ainda existe código órfão de uma **Nucleo-L432KC** vindo do merge da branch antiga `semana-01` (`shared/week-01/nucleo-l432kc/`). Decidir: manter Blackpill como oficial e remover o código da Nucleo, ou dar suporte às duas placas.

## Módulos 2, 3 e 4 — ainda vazios

- [ ] Módulo 2 — Clocks e GPIO (RCC, AHB/APB, EXTI, NVIC)
- [ ] Módulo 3 — Temporização e Comunicação Serial (Timers, PWM, UART)
- [ ] Módulo 4 — Barramentos de Sensor e DMA (SPI, I2C, ADC)

## Estrutura do site / navegação

- [ ] **Link quebrado em `pt-br/contents.qmd`** → aponta para `semana-01/intro.qmd`, que não existe (o arquivo real é `01-sistemas-embarcados.qmd`).
- [ ] `pt-br/_metadata.yml` está vazio — revisar se deveria conter algo (idioma, formatação específica) ou pode ser removido.
- [ ] Avaliar se/quando criar a versão **em inglês** (`en/`) — a landing page bilíngue original previa isso, mas nunca foi implementada; o projeto hoje é só PT-BR.

## Avaliação

- [ ] **Fechar os pesos definitivos** da composição de nota (hoje em `index.qmd` como rascunho: Prova 1 30pts + Trabalho 1 20pts + Prova 2 30pts + Trabalho 2/Projeto Integrador 20pts + recuperação até 20pts extra). Marcado como "em fase de ajuste" no texto.
- [ ] Detalhar cada atividade de módulo (enunciado, critérios de correção, prazos) — hoje só prometido no texto da Introdução.

## Publicação

- [ ] 🔥 **Nada foi publicado no `gh-pages` ainda** — todo o trabalho desta sessão está só no `master`. Rodar `quarto publish gh-pages` quando o conteúdo estiver pronto para os estudantes verem no site público.
- [ ] Considerar habilitar **formato PDF** no `_quarto.yml` do book (`format: { html: ..., pdf: ... }`) para os estudantes poderem baixar/imprimir o material — mencionado como possibilidade, não implementado.

## Infraestrutura / Git

- [ ] O remote `origin` foi trocado de SSH para HTTPS neste ambiente WSL (não havia chave SSH configurada). Se preferir manter SSH entre os ambientes, configurar a chave aqui e reverter o remote.
- [ ] **Nunca abrir `_book/index.html` direto como arquivo** (`file://` / `\\wsl.localhost\`) — quebra o JavaScript do Quarto por CORS. Sempre usar `quarto preview` e abrir via `http://localhost:<porta>/`. (Já documentado na memória do assistente, repetido aqui para quem não tiver acesso a ela.)
