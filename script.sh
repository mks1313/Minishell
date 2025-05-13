#!/bin/bash

TEST_CASES_FILE="test_cases.txt"

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

BASH="/bin/bash"
MINISHELL="./minishell"

# Compilar
echo "🔧 Compilando Minishell..."
make -s re || { echo -e "${RED}❌ Compilación fallida.${NC}"; exit 1; }

# ⚠️ ¡NO USAMOS ulimit -v porque rompe ASan!
ulimit -t 5 # Limita solo el tiempo de CPU

# Limpiar salida de Minishell
clean_minishell_output() {
	echo "$1" | \
		sed -E 's/\x1b\[[0-9;]*m//g' | \
		grep -v -E '^minishell\$|^exit$' | \
		sed 's/^[[:space:]]*//;s/[[:space:]]*$//' | \
		tr -d '\n'
}

# Contadores
i=0
pass_count=0
fail_count=0

while IFS= read -r cmd || [ -n "$cmd" ]; do
	i=$((i + 1))

	# Bash
	bash_output=$(echo "$cmd" | $BASH 2>&1 | cat -e | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

	# Minishell
	minishell_raw_output=$(echo "$cmd" | $MINISHELL 2>&1 | cat -e)
	minishell_output=$(clean_minishell_output "$minishell_raw_output")

	# Comparar
	if [ "$bash_output" == "$minishell_output" ]; then
		echo -e "${GREEN}Test #$i: OK${NC} -> $cmd"
		pass_count=$((pass_count + 1))
	else
		echo -e "${RED}Test #$i: KO${NC} -> $cmd"
		echo -e "${YELLOW}Bash Output     : \"$bash_output\"${NC}"
		echo -e "${YELLOW}Minishell Output: \"$minishell_output\"${NC}"
		echo -e "${RED}Diff:${NC}"
		diff <(echo "$bash_output") <(echo "$minishell_output")
		fail_count=$((fail_count + 1))
	fi
done < "$TEST_CASES_FILE"

# Resumen
echo -e "\n${GREEN}PASS: $pass_count${NC} - ${RED}FAIL: $fail_count${NC}"

