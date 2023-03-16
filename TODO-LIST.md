### Lista de Tarefas e como rodar

---

## Requisitos

- [x] Ler arquivo de entrada no formato .txt e alocar AFD em memória
- [ ] Exportar este AFD em um arquivo no formato .dot
- [ ] Realizar operação de complemento de uma linguagem de um AFD e exportar um novo AFD de saída
- [ ] Ler dois AFDs e exportar um novo AFD que reconheça a união entre as suas respectivas linguagens
- [ ] Ler dois AFDs e exportar um novo AFD que reconheça a interseção entre suas respectivas linguagens
- [ ] Ler um AFD e exportar um novo AFD minimizado
- [ ] Ler um AFD e palavras testes e posteriormente exportar um novo arquivo que responde se a palavra pertence ou não à linguagem

---

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
make # Compila o projeto
./afdtool # Executa o arquivo gerado, pode variar conforme as implementações na lista de tarefas
```