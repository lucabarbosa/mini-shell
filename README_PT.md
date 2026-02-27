# Minishell
> *Este projeto foi criado como parte do currículo da 42-SP por Luca (lbento) e Ian (iaratang).*

Este projeto é uma versão simplificada de um shell Unix escrita em C, desenvolvida como parte do currículo da 42 School. O **minishell** reproduz o comportamento central do `bash`, incluindo tokenização, execução de comandos, pipelines, redirecionamentos, expansão de variáveis de ambiente e comandos built-in — tudo construído do zero utilizando chamadas de sistema de baixo nível.

O Minishell exige que os estudantes implementem funcionalidades essenciais de um shell, tais como:

- Exibição de um prompt de comando dinâmico
- Interpretação e execução de entradas do usuário
- Gerenciamento de variáveis de ambiente
- Gerenciamento de processos com fork, execve e wait
- Implementação de redirecionamentos de entrada e saída `>`, `>>`, `<`
- Suporte a pipes `|`
- Tratamento de sinais como `ctrl+C`, `ctrl+D` e `ctrl+\`
- Recriação dos comandos built-in essenciais: `echo`, `cd`, `pwd`, `export`, `unset`, `env` e `exit`

Este projeto é um mergulho profundo em como um shell real funciona por baixo dos panos.

---

## Índice

- [Instruções](#instruções)
  - [Requisitos](#requisitos)
  - [Instalação](#instalação)
  - [Compilação](#compilação)
  - [Execução](#execução)
- [Exemplos de Uso](#exemplos-de-uso)
- [Bibliografia](#bibliografia)

---

## Instruções

### Requisitos

Antes de compilar e executar o **minishell**, certifique-se de que sua máquina Linux possui os seguintes itens instalados:

| Dependência | Finalidade |
|---|---|
| `gcc` (≥ 9) ou `cc` | Compilador C (padrão C99) |
| `make` | Automação de build |
| Biblioteca `readline` | Edição de linha e histórico de entrada |
| `libreadline-dev` | Headers de desenvolvimento para readline |

**Observação:** A biblioteca `readline` é **obrigatória**. Sem ela, o projeto não compilará.

### Instalação

Em um sistema Linux baseado em Debian/Ubuntu, instale todas as dependências necessárias com:

```bash
sudo apt update
sudo apt install -y gcc make libreadline-dev
```

Verifique se tudo foi instalado corretamente:

```bash
gcc --version
make --version
pkg-config --libs readline   # deve exibir algo como: -lreadline
```

No MacOS:

```bash
brew install readline make
```

Verifique se a configuração está correta:

```bash
brew --prefix readline        # deve exibir o caminho de instalação do readline
ls $(brew --prefix readline)/include/readline/readline.h   # o header deve existir
```
> Observação: O comando `brew --prefix readline` resolve o caminho correto automaticamente, independentemente de a máquina ser Apple Silicon (M1/M2/M3) ou Intel.

---

### Compilação

Clone o repositório e compile o projeto:

```bash
git clone https://github.com/lbento/minishell.git
cd minishell
make     # Se estiver usando macOS, use: make mac
```

Isso irá gerar o executável `minishell` no diretório raiz do projeto.

Para remover os arquivos objeto:

```bash
make clean
```

Para remover os arquivos objeto e o executável:

```bash
make fclean
```

Para recompilar do zero:

```bash
make re
```

Para recompilar e executar o minishell com valgrind:

```bash
make val
```
---

### Execução

Inicie o shell executando:

```bash
./minishell
```

Ele abrirá com um prompt personalizado. A partir daí, você pode digitar comandos como em um shell Bash normal.

Para sair do shell, digite:

```bash
exit
```

Ou pressione `Ctrl+D` (envia EOF).


## Exemplos de Uso

Abaixo estão alguns comandos que você pode testar dentro do **minishell** para explorar suas funcionalidades:

**Execução básica de comandos:**
```bash
ls -la
echo "Olá, 42!"
pwd
```

**Variáveis de ambiente:**
```bash
echo $HOME
export MINHA_VAR=ola
echo $MINHA_VAR
unset MINHA_VAR
echo $MINHA_VAR
```

**Comandos built-in:**
```bash
cd /tmp
cd -
cd ~
pwd
env
exit 42
```

**Redirecionamentos de entrada e saída:**
```bash
echo "escrevendo no arquivo" > saida.txt
cat < saida.txt
echo "adicionando linha" >> saida.txt
cat saida.txt
ls > f1 > f2 > -la
```

**Pipelines:**
```bash
ls | grep .c
cat Makefile | grep minishell
echo "hello world" | wc -w
cat << a | cat << b | cat << c 
```

**Pipeline combinado com redirecionamentos:**
```bash
ls -la | grep .c > arquivos_c.txt
cat arquivos_c.txt
```

**Here-document (heredoc):**
```bash
cat << eof
linha um
linha dois
eof
```

**Status de saída:**
```bash
ls /inexistente
echo $?
ls /tmp
echo $?
# pressione ctrl + C
echo $?
```

**Sinais:**
- `Ctrl+C` — interrompe o comando ou processo atual
- `Ctrl+\` — não faz nada
- `Ctrl+D` — sai do shell e do processo que recebe EOF
```bash
cat
# pressione ctrl + C
cat
# pressione ctrl + \
cat
# pressione ctrl + D
sleep 90
# pressione ctrl + C
sleep 90
# pressione ctrl + \
sleep 90
# pressione ctrl + D
```

**Aspas:**
```bash
echo "Isto é $USER dentro de aspas duplas"
echo 'Isto é $HOME dentro de aspas simples'
echo "Múltiplos     espaços    preservados"
```

## Bibliografia

Os recursos a seguir foram utilizados durante o desenvolvimento deste projeto e são recomendados para quem deseja entender os conceitos envolvidos:

### Manuais e Documentações Oficiais

- **Bash Reference Manual** — A documentação oficial do GNU Bash, cobrindo tudo, desde sintaxe até built-ins e controle de jobs.
  https://www.gnu.org/software/bash/manual/bash.html

- **POSIX Shell Command Language** — A especificação formal POSIX para o comportamento do shell, útil para entender o que é padrão versus específico do bash.
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

- **Páginas `man` do Linux online** — Referência rápida para todas as chamadas de sistema e funções de biblioteca utilizadas no minishell (`fork`, `execve`, `pipe`, `dup2`, `waitpid`, `readline`, etc.).
  https://man7.org/linux/man-pages/

### Livros

- **"The Linux Programming Interface"** — Michael Kerrisk. A referência mais completa sobre programação de sistemas Linux, cobrindo processos, descritores de arquivo, sinais e muito mais.
  https://man7.org/tlpi/

- **"Advanced Programming in the UNIX Environment"** — W. Richard Stevens & Stephen Rago. Uma referência clássica para programação de sistemas UNIX em C.

### Recursos Adicionais

- **GNU Readline Library** — Documentação oficial da biblioteca readline utilizada para tratamento de entrada e histórico.
  https://tiswww.case.edu/php/chet/readline/rltop.html

---

> *Não desanime, caro cadete — este projeto é verdadeiramente desafiador. Confie no processo!*