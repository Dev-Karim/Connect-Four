# Connect-4 — CMPS 241 Systems Programming

<p align="left">
  <img src="https://img.shields.io/badge/Language-C11-A8B9CC?style=for-the-badge&logo=c&logoColor=black"/>
  <img src="https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Course-CMPS%20241%20AUB-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Build-Make-orange?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge"/>
</p>

![Build](https://github.com/Joeehabre/Connect4-240-Project/actions/workflows/build.yml/badge.svg)

A terminal-based **Connect-4** game written in C, built as a team project for **CMPS 241 – Systems Programming** at the **American University of Beirut (AUB)**.

Players alternate turns dropping discs into a 6×7 grid. First to connect four in a row — horizontal, vertical, or diagonal — wins. If the board fills without a winner, the game ends in a draw.

---

## Features

- Two-player turn-based gameplay in the terminal
- Full win detection (horizontal, vertical, both diagonals)
- Draw detection when the board fills
- Clean modular codebase — board logic, game flow, and entry point separated
- Automated setup via `setup_autostart.sh`

---

## Project Structure

```
Connect-Four/
├── src/
│   ├── main.c        # Entry point
│   ├── board.c / .h  # Board state, rendering, column operations
│   └── game.c / .h   # Turn management, win/draw detection
├── tests/            # Test suite
├── docs/             # Project documentation
├── Makefile
└── setup_autostart.sh
```

---

## Build & Run

**Requirements:** GCC, GNU Make

```bash
git clone https://github.com/Joeehabre/Connect4-240-Project.git
cd Connect4-240-Project
make
./connect4
```

```bash
make clean   # remove build artifacts
```

---

## What I Learned

- Structured C project layout — separating board state, game logic, and I/O into modules
- Makefile dependency tracking and incremental builds
- Memory safety, clean compilation with `-Wall -Wextra`, and systematic debugging
- Collaborative development workflow with Git (branching, commits, reviews)

---

## Authors

Developed as a team project for **CMPS 241 – Systems Programming, AUB**.
