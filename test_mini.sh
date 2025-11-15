#!/bin/bash

# ============================================
# MINISHELL TESTER - SOLO MANDATORY
# Sin bonus: sin &&, ||, (), wildcards
# ============================================

MINISHELL="./minishell"

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# Contadores
TOTAL=0
PASSED=0
FAILED=0

# Directorio temporal
TEST_DIR="/tmp/minishell_mandatory_$$"
mkdir -p "$TEST_DIR"
cd "$TEST_DIR"
trap "cd /tmp && rm -rf $TEST_DIR" EXIT

# ============================================
# FUNCIONES DE TEST
# ============================================

run_test() {
    local test_name="$1"
    local command="$2"
    local category="${3:-General}"
    
    TOTAL=$((TOTAL + 1))
    
    # Ejecutar en bash
    echo "$command" | bash > bash_out.txt 2>&1
    bash_exit=$?
    
    # Ejecutar en minishell
    echo "$command" | $MINISHELL > mini_out.txt 2>&1
    mini_exit=$?
    
    # Comparar
    if diff -q bash_out.txt mini_out.txt > /dev/null 2>&1 && [ $bash_exit -eq $mini_exit ]; then
        echo -e "${GREEN}✓${NC} [$category] $test_name"
        PASSED=$((PASSED + 1))
        return 0
    else
        echo -e "${RED}✗${NC} [$category] $test_name"
        echo -e "${YELLOW}  CMD:${NC} $command"
        
        if [ $bash_exit -ne $mini_exit ]; then
            echo -e "${YELLOW}  EXIT:${NC} bash=$bash_exit mini=$mini_exit"
        fi
        
        if ! diff -q bash_out.txt mini_out.txt > /dev/null 2>&1; then
            echo -e "${YELLOW}  BASH:${NC}"
            head -3 bash_out.txt | sed 's/^/    /'
            echo -e "${YELLOW}  MINI:${NC}"
            head -3 mini_out.txt | sed 's/^/    /'
        fi
        echo ""
        FAILED=$((FAILED + 1))
        return 1
    fi
}

run_test_exit() {
    local test_name="$1"
    local command="$2"
    local category="${3:-General}"
    
    TOTAL=$((TOTAL + 1))
    
    bash -c "$command" > /dev/null 2>&1
    bash_exit=$?
    
    echo "$command" | $MINISHELL > /dev/null 2>&1
    mini_exit=$?
    
    if [ $bash_exit -eq $mini_exit ]; then
        echo -e "${GREEN}✓${NC} [$category] $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗${NC} [$category] $test_name"
        echo -e "${YELLOW}  CMD:${NC} $command"
        echo -e "${YELLOW}  EXIT:${NC} bash=$bash_exit mini=$mini_exit"
        echo ""
        FAILED=$((FAILED + 1))
    fi
}

# ============================================
# INICIO DEL TEST
# ============================================

echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║  MINISHELL TESTER - MANDATORY ONLY       ║${NC}"
echo -e "${BLUE}║  Sin bonus (&&, ||, wildcards, etc)      ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo ""

# Crear archivos de prueba
echo "Hello World" > test1.txt
echo -e "line1\nline2\nline3" > test2.txt
echo "content" > input.txt

# ============================================
# 1. COMANDOS SIMPLES
# ============================================
echo -e "${CYAN}[1. COMANDOS SIMPLES]${NC}"

run_test "ls básico" "ls" "Simple"
run_test "ls con flags" "ls -la" "Simple"
run_test "pwd" "pwd" "Simple"
run_test "cat archivo" "cat test1.txt" "Simple"
run_test "grep simple" "grep Hello test1.txt" "Simple"
run_test "wc líneas" "wc -l test2.txt" "Simple"
run_test "head" "head -2 test2.txt" "Simple"
run_test "tail" "tail -1 test2.txt" "Simple"
run_test "comando absoluto" "/bin/ls" "Simple"
run_test "comando relativo" "./test1.txt 2>/dev/null" "Simple"

# ============================================
# 2. ECHO (built-in mandatory)
# ============================================
echo -e "\n${CYAN}[2. ECHO]${NC}"

run_test "echo simple" "echo hello" "Echo"
run_test "echo vacío" "echo" "Echo"
run_test "echo múltiples args" "echo hello world test" "Echo"
run_test "echo espacios" "echo hello     world" "Echo"
run_test "echo -n" "echo -n hello" "Echo"
run_test "echo -n vacío" "echo -n" "Echo"
run_test "echo -nnn" "echo -nnn hello" "Echo"
run_test "echo -n -n" "echo -n -n test" "Echo"
run_test "echo texto largo" "echo este es un texto muy largo con muchas palabras" "Echo"

# ============================================
# 3. QUOTES
# ============================================
echo -e "\n${CYAN}[3. QUOTES]${NC}"

run_test "single quotes básico" "echo 'hello'" "Quotes"
run_test "double quotes básico" "echo \"hello\"" "Quotes"
run_test "single con espacios" "echo 'hello     world'" "Quotes"
run_test "double con espacios" "echo \"hello     world\"" "Quotes"
run_test "single con variable" "echo '\$USER'" "Quotes"
run_test "double con variable" "echo \"\$USER\"" "Quotes"
run_test "quotes vacías single" "echo ''" "Quotes"
run_test "quotes vacías double" "echo \"\"" "Quotes"
run_test "quotes anidadas 1" "echo \"test 'hello' test\"" "Quotes"
run_test "quotes anidadas 2" "echo 'test \"hello\" test'" "Quotes"
run_test "quotes múltiples" "echo 'hello' world 'test'" "Quotes"
run_test "quotes mezcladas" "echo \"hello\"'world'\"test\"" "Quotes"
run_test "quote con newline" "echo 'hello
world'" "Quotes"

# ============================================
# 4. VARIABLES DE ENTORNO
# ============================================
echo -e "\n${CYAN}[4. VARIABLES]${NC}"

run_test "variable USER" "echo \$USER" "Vars"
run_test "variable HOME" "echo \$HOME" "Vars"
run_test "variable PATH" "echo \$PATH" "Vars"
run_test "variable PWD" "echo \$PWD" "Vars"
run_test "variable vacía" "echo \$EMPTY_VAR_XYZ" "Vars"
run_test "variable en medio" "echo pre\${USER}post" "Vars"
run_test "variables múltiples" "echo \$USER \$HOME" "Vars"
run_test "variable en quotes" "echo \"User: \$USER\"" "Vars"
run_test "variable single quote" "echo '\$USER'" "Vars"
run_test "solo dollar" "echo $" "Vars"
run_test "dollar vacío" "echo \$" "Vars"

# ============================================
# 5. EXIT STATUS ($?)
# ============================================
echo -e "\n${CYAN}[5. EXIT STATUS]${NC}"

run_test "exit exitoso" "ls > /dev/null ; echo \$?" "Exit"
run_test "exit fallido" "ls /noexiste 2>/dev/null ; echo \$?" "Exit"
run_test "exit de true" "true ; echo \$?" "Exit"
run_test "exit de false" "false ; echo \$?" "Exit"
run_test "exit múltiple" "echo test ; echo \$? ; echo \$?" "Exit"
run_test "exit en pipe" "cat test1.txt | grep Hello ; echo \$?" "Exit"
run_test "exit después built-in" "echo test ; echo \$?" "Exit"

# ============================================
# 6. REDIRECTIONS
# ============================================
echo -e "\n${CYAN}[6. REDIRECTIONS]${NC}"

# Output redirect (>)
run_test "output simple" "echo test > out1.txt ; cat out1.txt" "Redir"
run_test "output sobrescribir" "echo first > out2.txt ; echo second > out2.txt ; cat out2.txt" "Redir"
run_test "output con comando" "ls -l > out3.txt ; cat out3.txt" "Redir"
run_test "output múltiple" "echo test > o1 > o2 > o3 ; cat o3" "Redir"

# Append redirect (>>)
run_test "append simple" "echo line1 >> app1.txt ; cat app1.txt" "Redir"
run_test "append múltiple" "echo a >> app2.txt ; echo b >> app2.txt ; cat app2.txt" "Redir"
run_test "append después >" "echo x > app3.txt ; echo y >> app3.txt ; cat app3.txt" "Redir"

# Input redirect (<)
run_test "input simple" "cat < test1.txt" "Redir"
run_test "input con comando" "wc -l < test2.txt" "Redir"
run_test "input inexistente" "cat < noexiste.txt" "Redir"

# Combinadas
run_test "in y out" "cat < test1.txt > combo1.txt ; cat combo1.txt" "Redir"
run_test "orden invertido" "> combo2.txt cat < test1.txt ; cat combo2.txt" "Redir"
run_test "in out al inicio" "< test1.txt > combo3.txt cat ; cat combo3.txt" "Redir"

# ============================================
# 7. PIPES
# ============================================
echo -e "\n${CYAN}[7. PIPES]${NC}"

run_test "pipe simple" "echo hello | cat" "Pipes"
run_test "pipe con grep" "cat test2.txt | grep line1" "Pipes"
run_test "pipe con wc" "cat test2.txt | wc -l" "Pipes"
run_test "pipe 2 niveles" "echo test | cat | cat" "Pipes"
run_test "pipe 3 niveles" "echo test | cat | cat | cat" "Pipes"
run_test "pipe 5 niveles" "echo test | cat | cat | cat | cat | cat" "Pipes"
run_test "pipe con head" "cat test2.txt | head -1" "Pipes"
run_test "pipe con tail" "cat test2.txt | tail -1" "Pipes"
run_test "pipe con sort" "echo -e 'c\na\nb' | sort" "Pipes"
run_test "ls pipe grep" "ls | grep test" "Pipes"
run_test "cat pipe grep pipe wc" "cat test2.txt | grep line | wc -l" "Pipes"

# ============================================
# 8. PIPES + REDIRECTS
# ============================================
echo -e "\n${CYAN}[8. PIPES + REDIRECTS]${NC}"

run_test "pipe + output" "echo test | cat > pr1.txt ; cat pr1.txt" "Pipe+Redir"
run_test "input + pipe" "cat < test2.txt | head -2" "Pipe+Redir"
run_test "input + pipe + output" "cat < test1.txt | cat > pr2.txt ; cat pr2.txt" "Pipe+Redir"
run_test "pipe + append" "echo hello | cat >> pr3.txt ; cat pr3.txt" "Pipe+Redir"
run_test "múltiples pipes + redirect" "echo test | cat | cat > pr4.txt ; cat pr4.txt" "Pipe+Redir"

# ============================================
# 9. CD (built-in)
# ============================================
echo -e "\n${CYAN}[9. CD]${NC}"

run_test_exit "cd /tmp" "cd /tmp" "CD"
run_test_exit "cd absoluto" "cd /usr/bin" "CD"
run_test_exit "cd relativo .." "cd .." "CD"
run_test_exit "cd ." "cd ." "CD"
run_test_exit "cd sin args" "cd" "CD"
run_test_exit "cd inexistente" "cd /directorio/que/no/existe" "CD"
run_test_exit "cd -" "cd -" "CD"
run_test "cd + pwd" "cd /tmp ; pwd" "CD"
run_test "cd .. + pwd" "cd .. ; pwd" "CD"

# ============================================
# 10. PWD (built-in)
# ============================================
echo -e "\n${CYAN}[10. PWD]${NC}"

run_test "pwd simple" "pwd" "PWD"
run_test "pwd después cd" "cd /tmp ; pwd" "PWD"
run_test "pwd pipe" "pwd | cat" "PWD"
run_test "pwd redirect" "pwd > pwd_out.txt ; cat pwd_out.txt" "PWD"

# ============================================
# 11. EXPORT (built-in)
# ============================================
echo -e "\n${CYAN}[11. EXPORT]${NC}"

run_test "export simple" "export TEST=hello ; echo \$TEST" "Export"
run_test "export con espacios" "export TEST=\"hello world\" ; echo \$TEST" "Export"
run_test "export vacío" "export TEST= ; echo \$TEST" "Export"
run_test "export sin valor" "export TEST ; echo \$TEST" "Export"
run_test "export reasignar" "export VAR=1 ; export VAR=2 ; echo \$VAR" "Export"
run_test "export múltiple" "export A=1 ; export B=2 ; echo \$A \$B" "Export"
run_test "export y usar" "export MSG=test ; echo \$MSG" "Export"

# ============================================
# 12. UNSET (built-in)
# ============================================
echo -e "\n${CYAN}[12. UNSET]${NC}"

run_test "unset variable" "export VAR=test ; unset VAR ; echo \$VAR" "Unset"
run_test "unset inexistente" "unset NOEXISTE ; echo ok" "Unset"
run_test "unset múltiple" "export A=1 ; export B=2 ; unset A B ; echo \$A \$B" "Unset"
run_test "unset y recrear" "export VAR=1 ; unset VAR ; export VAR=2 ; echo \$VAR" "Unset"

# ============================================
# 13. ENV (built-in)
# ============================================
echo -e "\n${CYAN}[13. ENV]${NC}"

run_test "env básico" "env | grep USER" "Env"
run_test "env pipe wc" "env | wc -l" "Env"
run_test "env redirect" "env > env_out.txt ; cat env_out.txt | grep USER" "Env"

# ============================================
# 14. EXIT (built-in)
# ============================================
echo -e "\n${CYAN}[14. EXIT]${NC}"

run_test_exit "exit 0" "exit 0" "Exit"
run_test_exit "exit 1" "exit 1" "Exit"
run_test_exit "exit 42" "exit 42" "Exit"
run_test_exit "exit 255" "exit 255" "Exit"

# ============================================
# 15. EDGE CASES
# ============================================
echo -e "\n${CYAN}[15. EDGE CASES]${NC}"

run_test "espacios inicio" "     echo test" "Edge"
run_test "espacios final" "echo test     " "Edge"
run_test "tabs" "echo		test" "Edge"
run_test "múltiples espacios" "echo     test     hello" "Edge"
run_test "solo espacios" "     " "Edge"
run_test "comando vacío" "" "Edge"
run_test "newline extra" "echo test
" "Edge"
run_test "quotes vacías" "echo '' \"\" ''" "Edge"
run_test "variable inexistente" "echo \$NOEXISTE_123456" "Edge"

# ============================================
# 16. COMBINACIONES COMPLEJAS
# ============================================
echo -e "\n${CYAN}[16. COMBINACIONES]${NC}"

run_test "combo 1" "export VAR=test ; echo \$VAR | cat" "Combo"
run_test "combo 2" "echo hello | cat > f1 ; cat < f1" "Combo"
run_test "combo 3" "cat < test1.txt | grep Hello > f2 ; cat f2" "Combo"
run_test "combo 4" "echo 'test' | cat | cat | cat > f3 ; cat f3" "Combo"
run_test "combo 5" "export MSG=hello ; echo \$MSG | cat > f4 ; cat f4" "Combo"
run_test "combo 6" "cd /tmp ; pwd | cat" "Combo"
run_test "combo 7" "echo \"\$USER is at \$PWD\"" "Combo"
run_test "combo 8" "cat test2.txt | head -2 | tail -1" "Combo"

# ============================================
# 17. ERRORES Y MANEJO
# ============================================
echo -e "\n${CYAN}[17. MANEJO DE ERRORES]${NC}"

run_test_exit "comando inexistente" "comando_que_no_existe_123" "Errors"
run_test_exit "archivo inexistente" "cat archivo_que_no_existe.txt" "Errors"
run_test_exit "permiso denegado" "cat /etc/shadow" "Errors"
run_test "error en pipe" "comandofalso | cat" "Errors"
run_test "error + exit status" "ls /noexiste 2>/dev/null ; echo \$?" "Errors"

# ============================================
# 18. CASOS ESPECÍFICOS 42
# ============================================
echo -e "\n${CYAN}[18. CASOS ESPECÍFICOS]${NC}"

run_test "echo -n newline" "echo -n test ; echo world" "42"
run_test "PATH relativo" "echo \$PATH | grep usr" "42"
run_test "HOME variable" "echo \$HOME" "42"
run_test "varios comandos" "echo a ; echo b ; echo c" "42"
run_test "redirect /dev/null" "echo test > /dev/null ; echo ok" "42"
run_test "cat sin args stdin" "echo test | cat" "42"
run_test "grep case sensitive" "echo Hello | grep hello" "42"

# ============================================
# 19. STRESS TESTS
# ============================================
echo -e "\n${CYAN}[19. STRESS TESTS]${NC}"

run_test "10 pipes" "echo test$(printf ' | cat%.0s' {1..10})" "Stress"
run_test "string largo" "echo $(printf 'abc%.0s' {1..100})" "Stress"
run_test "muchos args" "echo $(seq 1 50)" "Stress"
run_test "muchos redirects" "echo test > a > b > c > d > e ; cat e" "Stress"
run_test "quotes anidadas deep" "echo \"a'b\"c'\"d'e\"'" "Stress"

# ============================================
# 20. SINTAXIS ROTA (debe dar error)
# ============================================
echo -e "\n${CYAN}[20. SINTAXIS INVÁLIDA]${NC}"

run_test_exit "pipe al inicio" "| cat" "Syntax"
run_test_exit "pipe al final" "echo test |" "Syntax"
run_test_exit "redirect sin archivo" "echo test >" "Syntax"
run_test_exit "quotes sin cerrar" "echo 'hello" "Syntax"
run_test_exit "doble quote sin cerrar" "echo \"hello" "Syntax"

# ============================================
# RESUMEN FINAL
# ============================================

echo ""
echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║           RESUMEN FINAL                  ║${NC}"
echo -e "${BLUE}╠══════════════════════════════════════════╣${NC}"
echo -e "${BLUE}║${NC} Total tests:    $TOTAL"
echo -e "${BLUE}║${NC} ${GREEN}Passed:${NC}         $PASSED"
echo -e "${BLUE}║${NC} ${RED}Failed:${NC}         $FAILED"

if [ $TOTAL -gt 0 ]; then
    PERCENTAGE=$((PASSED * 100 / TOTAL))
    echo -e "${BLUE}║${NC} Success rate:   ${PERCENTAGE}%"
fi

echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║  🎉 PERFECTO! MANDATORY COMPLETO       ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════╝${NC}"
    exit 0
else
    if [ $PERCENTAGE -ge 80 ]; then
        echo -e "${YELLOW}⚠️  Casi perfecto! Revisa los casos fallidos${NC}"
    elif [ $PERCENTAGE -ge 60 ]; then
        echo -e "${YELLOW}⚠️  Vas bien, pero faltan cosas importantes${NC}"
    else
        echo -e "${RED}❌ Muchos tests fallan - revisa la implementación${NC}"
    fi
    echo ""
    exit 1
fi
