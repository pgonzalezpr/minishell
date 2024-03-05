# ➡︎ Minishell ⬅︎

### Summary
This project aims to recreate the functionality and user interface of the Bash terminal, 
a popular command-line interface used in Unix-based operating systems. By emulating the 
features of Bash, users will be able to interact with their computer systems through 
a familiar and powerful interface.

### Usage
1) Compile the code
   ```makefile
   make
   ```
2) Execute
   #### Normal mode
   ```bash
   ./minishell
   ```
   #### Memory mode (Valgrind)
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
   ```
   <div align="center"> <h6> <p> <b> ⚠️ Warning: </b> you must have valgrind installed to use this mode ⚠️ </p> </h6> </div>

   #### Memory mode (Midnight Commander) [MAC]
   ```bash
   leaks -atExit -- ./minishell
   ```
   <div align="center"> <h6> <p> <b> ⚠️ Warning: </b> you must have Xcode Command Line Tools installed to use this mode ⚠️ </p> </h6> </div>
   
### Info
◼️ Language: C
<br>
◼️ Compile: Makefile
<br>
◼️ Library: Libft, Readline
