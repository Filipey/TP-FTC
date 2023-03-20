## Como rodar 🏃‍♂️

### Debug
```bash
make debug # Compilar em modo de debug
gdb ./afdtool # Neste exemplo, usamos o GDB como debugger
break "main.c":8 # Adiciona um breakpoint no arquivo main.c na linha 8
run # Inicia o modo de depuração
print <nome_da_variavel> # Imprime na tela o valor da variável e sua posição em memória no momento atual
step # Executa um passo
continue # Realiza execução até o próximo breakpoint
```

### Clean
```bash
make clean # Remove todos os arquivos de compilação já existentes
```

### Build
```bash
make # Será gerado o executável afdtool
```

## Operações
É importante salientar que para as executar as operações, os arquivos de entrada devem estar no diretório inputs. Arquivos que não estejam neste diretório não serão aceitos. Para gerar visualizações dos arquivos de saída, é necessário estar no diretório outputs. A extensão de arquivo aceita como entrada é a .txt. As extensões aceitas para saída são .dot e .txt.

### Visualização
```bash
./afdtool --visualizacao <arquivo_afd>.txt <extensao_de_saida> <nome_arquivo_saida>
```
Esta execução irá gerar um novo arquivo que representa o arquivo de entrada no formato de saída.

### Complemento
```bash
./afdtool --complemento <arquivo_afd>.txt <extensao_de_saida> <nome_arquivo_saida>
```
Esta execução irá gerar um novo AFD que representa o complemento do AFD de entrada.

### Interseção
```bash
./afdtool --intersecao <arquivo_afd1>.txt <arquivo_afd2>.txt <extensao_de_saida> <nome_arquivo_saida>
```
Esta execução irá gerar um novo AFD capaz de reconhecer a interseção das linguagens dos AFDs de entrada. Internamente, é usado o algoritmo de produto de AFDs.

### União
```bash
./afdtool --uniao <arquivo_afd1>.txt <arquivo_afd2>.txt <extensao_de_saida> <nome_arquivo_saida>
```
Esta execução irá gerar um novo AFD capaz de reconhecer a união das linguagens dos AFDs de entrada. Internamente, é usado o algoritmo de produto de AFDs.

### Reconhecimento de Palavras
```bash
./afdtool --reconhecer <arquivo_de_palavras> <nome_arquivo_saida>.txt <arquivo_afd>.txt
```
Esta execução irá gerar um novo arquivo .txt com respostas de reconhecimento para cada palavra no arquivo de palavras usado como entrada. A resposta para cada palavra no arquivo resultante é espelhada com a linha onde se encontra a palavra no arquivo de entrada. Caso a palavra seja reconhecida, é escrito 1. Caso contrário, 0.
