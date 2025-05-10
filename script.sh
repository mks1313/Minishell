#!/bin/bash

# Archivo con los casos de prueba
TEST_CASES_FILE="test_cases.txt"

# Colores para la salida
GREEN='\033[0;32m' # Verde para OK
RED='\033[0;31m'   # Rojo para KO
NC='\033[0m'       # Sin color

# Ejecutables
BASH="/bin/bash"
MINISHELL="./minishell"

# Contador de pruebas
i=0

# Leer cada comando del archivo de casos de prueba
while IFS= read -r cmd; do
    i=$((i + 1))
    
    # Ejecutar el comando en bash
    bash_output=$(echo "$cmd" | $BASH 2>&1 | cat -e)

    # Ejecutar el comando en minishell
    minishell_raw_output=$(echo "$cmd" | $MINISHELL 2>&1 | cat -e)

    # Limpiar el output de minishell
    minishell_output=$(echo "$minishell_raw_output" | sed -e '/^minishell\$/d' -e '/^exit$/d' | sed ':a;N;$!ba;s/\n/ /g')

    # Comparar los outputs
    if [ "$bash_output" == "$minishell_output" ]; then
        echo -e "${GREEN}Test #$i: OK${NC} -> $cmd"
    else
        echo -e "${RED}Test #$i: KO${NC} -> $cmd"
        echo -e "${RED}Bash Output:${NC} \"$bash_output\""
        echo -e "${RED}Minishell Output:${NC} \"$minishell_output\""
    fi
done < "$TEST_CASES_FILE"
