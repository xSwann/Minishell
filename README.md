# Minishell (42)

> A minimal Bash-like shell written in **C** as part of the 42 curriculum. Supports command parsing, pipelines, redirections, environment variables and built-in commands.

---

## 🚀 Features

* Execution of simple and piped commands using `|`
* **Redirections**: `<`, `>`, `>>`, `<<` (heredoc without variable expansion)
* **Environment variables**: `$VAR`, `$?`
* **Quote handling**: `'` (literal), `"` (expands variables)
* **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
* **Basic error handling**
* **Signal handling**: `Ctrl-C`, `Ctrl-D`, `Ctrl-\\`

> **Limitations**: no `;`, no logical operators `&&` / `||`, no subshells `( )`, no wildcard expansion `*`, no job control.

---

## 🔧 Compilation

```bash
make            # compile minishell
make clean      # remove .o files
make fclean     # remove .o + binary
make re         # rebuild
```

### Dependency: Readline

Ubuntu/Debian:

```bash
sudo apt install -y libreadline-dev
```

macOS (Homebrew):

```bash
brew install readline
```

---

## ▶️ Usage

```bash
./minishell
minishell$ echo "Hello"
minishell$ ls | grep src
minishell$ echo "test" > file.txt
minishell$ cat << EOF
hello
EOF
minishell$ exit 0
```

---

## 📁 Project structure

```
Minishell/
├── Makefile
├── README.md
├── valgrind-readline.supp
├── read_terminal.c
├── read_terminal_utils.c
│
├── includes/
│   ├── built_ins.h
│   ├── exec.h
│   ├── libft.h
│   ├── parsing.h
│   └── structs.h
│
├── built_ins/
│   ├── ft_cd.c
│   ├── ft_echo.c
│   ├── ft_exit.c
│   ├── ft_pwd.c
│   ├── is_exportable.c
│   ├── ft_env/
│   │   ├── free_env.c
│   │   ├── ft_env.c
│   │   ├── get_env.c
│   │   └── init_env.c
│   ├── ft_export/
│   │   ├── export_loop.c
│   │   └── ft_export.c
│   └── ft_unset/
│       ├── ft_unset.c
│       └── unset_loop.c
│
├── parsing/
│   ├── tokenization.c
│   ├── tokenization_utils.c
│   ├── count_tokens.c
│   ├── put_tokens_in_tab.c
│   ├── command_creator.c
│   ├── here_doc_manipulations.c
│   ├── sanitize/
│   │   ├── sanitize_tokens.c
│   │   ├── sanitize_tokens_utils.c
│   │   ├── sanitize_tokens_utils2.c
│   │   ├── sanitize_tokens_utils3.c
│   │   └── sanitize_tokens_utils4.c
│   └── types.c
│
├── exec/
│   ├── command_executor.c
│   ├── executor_utils.c
│   ├── free_functions.c
│   ├── path_modifiers.c
│   ├── structure_manipulations.c
│   └── variables_modifiers.c
│
├── gnl/
│   ├── get_next_line.c
│   └── get_next_line.h
│
└── libft/
    ├── ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c ...
```

---

## 🧠 Architecture overview

```
readline → tokenization → sanitize → command_creator → executor
                                        │
                                        └─ heredoc (no expansion)
```

* **Tokenization**: splits input into tokens
* **Sanitize**: basic syntax validation
* **Command creator**: builds executable command chains
* **Executor**: handles pipes, redirections, and `execve`
* **Built-ins**: executed without `execve` when necessary

---

## ✅ Quick tests

```bash
echo hello | cat
ls | wc -l
echo test > file.txt
cat << EOF | grep o
hello
EOF
```

---

## 🐞 Error handling

* `command not found` → exit code **127**
* Permission denied → exit code **126**
* Redirection errors → error message to **stderr**
* `$?` updated after each command

---

## 🧼 Norm & memory

* Follows **42 Norminette** rules
* No memory leaks (**Valgrind checked**)
* Uses `valgrind-readline.supp` to suppress readline warnings

---

## 👤 Authors

* Swann — @xSwann
* Flavien — @Flavien-Lebrun

---
