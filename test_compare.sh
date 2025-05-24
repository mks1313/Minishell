#!/bin/bash

BASH="/bin/bash"
MINISHELL="./minishell"
TEST_CASES="test_cases.txt"

i=0
ok=0
fail=0

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

while IFS= read -r cmd || [ -n "$cmd" ]; do
	i=$((i+1))

	# Ejecutar en bash
	bash_output=$(echo "$cmd" | $BASH 2>&1 | tail -n 1 | cat -e)

	# Ejecutar en minishell
	minishell_output=$(echo "$cmd" | $MINISHELL 2>/dev/null | tail -n 1 | cat -e)

	if [ "$bash_output" = "$minishell_output" ]; then
		echo -e "${GREEN}[$i] OK${NC} $cmd"
		ok=$((ok+1))
	else
		echo -e "${RED}[$i] FAIL${NC} $cmd"
		echo "  bash     → $bash_output"
		echo "  minishell→ $minishell_output"
		fail=$((fail+1))
	fi

done < "$TEST_CASES"

echo
echo "Resumen: $ok OK, $fail FAIL, Total: $i"
