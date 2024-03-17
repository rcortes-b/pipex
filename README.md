
<div align="center">
<h1 align="center">
<img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/pipexe.png" alt="Pipex 42 project badge"/>
<br>Pipex</h1>
<h3> A program that replicates bash pipe behaviour </h3>

---

## 📖 Table of Contents
- [📍 Overview 📍](#-overview-)
- [📍 Rules 📍](#-rules-)
- [🔎 What is implemented?](#-what-is-implemented)
- [🚀 Getting Started](#-getting-started--)
    - [🔧 Installation](#-installation)
    - [🤖 Use pipex](#-use-pipex-without-here_doc)
    - [🤖 Use pipex (with heredoc)](#-use-pipex-with-here_doc)
- [Extra: Check out my profile on the Intranet](#--check-out-my-profile-on-the-intra-of-42-school-%EF%B8%8F)

---

## 📍 Overview 📍

This project is an introduction of how to work with child processes and communicate using pipes.


---

## 📍 Rules 📍

The functions have to follow a strict rule. For example, you cannot intitialize a variable in the line where you declare it.


---


## 🔎 _What is implemented?_

This programm is able to replicate the pipe behaviour using a file as input and print the output in other file executing as many commands as you want.

Pipex also replicates the behavior of the heredoc and appends the content to an outfile.

---

## 🚀 Getting Started  🚀 

### 🔧 Installation

1. Clone get_next_line repository:
```sh
git clone https://github.com/rcortes-b/pipex.git
```

2. Change to the project directory:
```sh
cd pipex
```

3. Compile the programm:
```sh
make pipex
```

### 🤖 Use pipex (without here_doc)

1. To exeute the programm:
```sh
./pipex <input_file> <cmd1> <cmd2> <...cmd...> <output_file>
```

### 🤖 Use pipex (with here_doc)

1. To exeute the programm:
```sh
./pipex here_doc <LIMITER> <cmd1> <cmd2> <...cmd...> <output_file>
```

### - Check out my profile on the intra of 42 school ↙️
[https://profile.intra.42.fr/users/rcortes-]

---

[**Return**](#Top)

---
