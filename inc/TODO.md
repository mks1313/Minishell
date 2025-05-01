# TODO
- 2025/03/15
	- Leaks en exit. Cuando ejecutamos minishell y escribimos lineas, al hacer exit o CTRL+D hay leaaks. Mas escribas de lineas mas leaks.

	- Debugear: estaria bien una funcion para veer la tkenizacion.
	- Lexer: que haya alg, una calsificacion usando los definidos en el .h
	- Expansiones de comillas:
```bash
echo "$USER'$USER"$USER'$USER'$USER"$USER'$USER"
```
resultado: `meghribe'meghribemeghribe$USERmeghribemeghribe'meghribe`
