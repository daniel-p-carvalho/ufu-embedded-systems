# Backlog — Sistemas Embarcados I

Lista de pendências identificadas durante a reestruturação do curso. Não está em ordem de prioridade estrita — itens marcados 🔥 são os mais urgentes/bloqueantes.

## 🔥 DECISÃO TOMADA — O curso vai ser costurado em torno de um mini game

Confirmado: o **projeto integrador oficial do curso passa a ser um mini videogame portátil**, substituindo a ideia anterior de projeto com sensor industrial. Cada módulo constrói uma peça dele, dando um fio condutor único pro curso inteiro (em vez de labs isolados sem conexão). Mapeamento acordado:

| Módulo | Conteúdo técnico | Peça do jogo |
|---|---|---|
| 2 — Clocks e GPIO | GPIO digital, EXTI, debounce | Botões/joystick digital (direções) |
| 3 — Temporização e Comunicação Serial | Timers, PWM, UART | Áudio via PWM (bipes estilo 8-bit) + *game loop* no timer |
| 4 — Barramentos de Sensor e DMA | SPI/I2C, DMA | Display (OLED/TFT via SPI, framebuffer via DMA) |
| 5 — Projeto Integrador | Baixo consumo + hardware | Monta tudo — "seu próprio console portátil", com gancho de autonomia de bateria |

Cada módulo também reforça eletrônica no caminho (debounce de botão, pull-up/pull-down, driver de áudio, nível lógico SPI).

- [ ] 🔥 **Próximo passo, depois de fechar os capítulos iniciais do Módulo 1:** planejar o "enxoval" de hardware necessário — display SPI pequeno (OLED/TFT), buzzer/alto-falante passivo, botões/joystick analógico — priorizando opções baratas e disponíveis no Brasil. Ainda não orçado.
- [ ] Atualizar o `Cronograma` e as "Atividades de fechamento" na Introdução (`index.qmd`) e no texto de cada módulo pra refletir essa mudança de projeto (hoje ainda descrevem vagamente "atividade prática" genérica).
- [ ] Decidir se a ideia do "jogo do dinossauro" (Chrome) é literalmente o jogo de referência, ou só uma inspiração de estilo/simplicidade — e se cabe uma aula/seção explicando como funcionam videogames antigos e modernos por dentro (aproveitando o gancho de consoles já na tabela histórica de processadores em `modulo-01/arquitetura-computadores.qmd`).

## Pequenos ajustes de texto/UI pendentes

- [ ] **Título da aba do navegador da "Apresentação"** — ao remover o campo `title:` do YAML de `index.qmd` (necessário pra corrigir a numeração da sidebar, ver seção de memória do assistente), a aba passou a mostrar só "Sistemas Embarcados I - UFU", sem "Apresentação". Achar uma forma de recuperar isso sem reintroduzir o bug da numeração.

## Ajustes visuais de imagens

- [ ] **Duas figuras de arquitetura, no mesmo estilo visual, feitas juntas na mesma sessão:**
  1. **Redesenhar "Modelo de Von Neumann"** (`shared/images/arquitetura-von-neumann.jpeg`, usada em `modulo-01/arquitetura-computadores.qmd`) — está fora do padrão visual do resto do site (estilo diagrama de caixas cinza simples da apostila original, diferente do estilo glossy/neon azul-laranja das outras imagens, como `sistema-embarcado.png` e o gráfico de quadrante/licenciamento).
  2. **Criar figura equivalente para "Arquitetura Harvard"** (mesma seção, logo depois de Von Neumann): diagrama mostrando os dois barramentos separados (instrução e dados), no mesmo estilo da figura de Von Neumann redesenhada. Marcador `<!-- TODO(imagem) -->` já deixado no `arquitetura-computadores.qmd` indicando o lugar exato.
  - Seguir o mesmo processo usado para o gráfico de quadrante/licenciamento (prompt + geração + ajustes iterativos).
- [ ] **Figura para o Gargalo de Von Neumann** (seção "O Gargalo de Von Neumann" / "Arquitetura Harvard" em `modulo-01/arquitetura-computadores.qmd`): pensar numa forma gráfica de ilustrar a "colisão" no barramento único — cogitado formato de tirinha (quadrinhos), mostrando visualmente instrução e dado disputando a mesma via, em contraste com os dois barramentos livres da Harvard. Hoje só existe a tabela de ciclos (texto); uma imagem complementaria bem, tornando a ideia mais intuitiva antes mesmo de ler a tabela.

## Conteúdo — Aula de Fundamentos de Linux

- [ ] **Quebrar o bloco de texto com imagens/screenshots.** A aula ficou densa (texto corrido, poucas imagens). Adicionar capturas de tela reais do terminal (prompt, `ls -la`, `nano`, `vim`, resultado de `find`/`grep`) ao longo do texto, no mesmo espírito das imagens dos labs antigos (`ufu-semb1-lab-01-old`, `lab-02`, `lab-03`).

## Módulo 1 — Estrutura e Conteúdo

- [ ] 🔥 **Reordenar capítulos do Módulo 1** conforme decidido: hoje "Ambiente e Ferramentas de Desenvolvimento" é o primeiro capítulo (prioridade de entrega urgente aos estudantes). A ordem pedagogicamente correta é:
  1. O que é um Sistema Embarcado? (conceitual)
  2. Arquitetura de Computadores / ARM / Cortex-M (teoria)
  3. Ambiente e Ferramentas de Desenvolvimento (atual)
  4. Toolchain e Startup na prática (labs)
- [x] **Escrever capítulo "O que é um Sistema Embarcado?"** — `modulo-01/o-que-e-sistema-embarcado.qmd`, feito.
- [x] **Escrever capítulo "Fundamentos de Arquitetura de Computadores"** — `modulo-01/arquitetura-computadores.qmd` (ISA/Organização/Implementação, Von Neumann, Load-Store vs. Register-Memory, exemplos de arquiteturas), feito.
- [x] **Escrever capítulo "Memória e Registradores"** — `modulo-01/memoria-registradores.qmd` (hierarquia de memória, volátil/não-volátil, registradores, pilha, modos de endereçamento), feito.
- [ ] **Escrever capítulos de Histórico ARM / Cortex-M** — conteúdo-base na `APOSTILA.docx`:
  - Histórico ARM (ARMv1 → ARMv8)
  - Modos/registradores do Cortex-M3/M4
  - **Atenção:** a apostila termina no meio da seção de Registradores — precisa ser complementada (exceções, NVIC) antes de virar capítulo (pilha/stack já foi coberta em `memoria-registradores.qmd`).
  - Imagens já extraídas da apostila (transições Thread/Handler Mode, banco de registradores) — reaproveitar. A imagem de Von Neumann já foi usada em `arquitetura-computadores.qmd`.
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

## Avaliação automatizada (nova frente — ainda em decisão)

- [ ] **Quizzes de autocheck formativos** (sem nota): usar a extensão `webexercises` do Quarto para embutir questionários interativos direto nas páginas (client-side, sem backend). Bom encaixe nas "atividades de fixação" que já existem espalhadas pelo texto (ex.: `modulo-01/linux-basico.qmd`). Não serve para nota que conta, só autoavaliação.
- [ ] **Atividades de programação com correção automatizada:** avaliar **GitHub Classroom** — cada estudante recebe um repositório próprio a partir de um template, com testes automáticos via GitHub Actions a cada `push` (build limpo, verificação de seções do binário via `objdump`/`readelf`, etc.). Camada adicional: um agente de IA revisando qualidade/lógica do código além dos testes automatizados.
- [ ] **Quiz com nota real (precisa de backend):** como o site é estático, avaliar entre Google/Microsoft Forms (simples, já testado, exporta pra planilha) vs. uma função serverless (Cloudflare Pages/Netlify) que salve respostas num banco de fato.
- [ ] **Portar para o Moodle da UFU (decisão futura, não urgente):** três caminhos possíveis, do mais simples ao mais trabalhoso — (1) só linkar o site Quarto a partir de um Recurso URL no Moodle (zero esforço, conteúdo continua fora); (2) copiar manualmente o conteúdo pra dentro da atividade "Livro" do Moodle (esforço médio, por capítulo); (3) exportar como pacote SCORM/IMS Common Cartridge (esforço alto, Quarto não tem exportador nativo). Recomendação: começar pela opção (1) e só migrar se a UFU exigir que o conteúdo viva dentro do Moodle.
- [ ] **Hospedagem paga (se quiser sair do GitHub Pages gratuito):** opções levantadas — domínio próprio + GitHub Pages (mais barato, só paga o domínio); Netlify/Vercel/Cloudflare Pages (tier grátis já cobre o site atual, e abre caminho pra funções serverless se quiser quiz com nota real no futuro); VPS próprio (mais controle, mais responsabilidade de manutenção — faz sentido se quiser hospedar o Moodle também); ou infraestrutura da própria UFU (perguntar ao DTI). Recomendação inicial: Cloudflare Pages ou Netlify.

## Publicação

- [ ] 🔥 **Nada foi publicado no `gh-pages` ainda** — todo o trabalho desta sessão está só no `master`. Rodar `quarto publish gh-pages` quando o conteúdo estiver pronto para os estudantes verem no site público.
- [ ] Considerar habilitar **formato PDF** no `_quarto.yml` do book (`format: { html: ..., pdf: ... }`) para os estudantes poderem baixar/imprimir o material — mencionado como possibilidade, não implementado.

## Infraestrutura / Git

- [ ] O remote `origin` foi trocado de SSH para HTTPS neste ambiente WSL (não havia chave SSH configurada). Se preferir manter SSH entre os ambientes, configurar a chave aqui e reverter o remote.
- [ ] **Nunca abrir `_book/index.html` direto como arquivo** (`file://` / `\\wsl.localhost\`) — quebra o JavaScript do Quarto por CORS. Sempre usar `quarto preview` e abrir via `http://localhost:<porta>/`. (Já documentado na memória do assistente, repetido aqui para quem não tiver acesso a ela.)
