## :warning: LEIA A TODO-LIST!

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