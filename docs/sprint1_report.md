# CMPS 241 — Connect‑4 (Sprint 1) — Report

**Team:** KJE Core  
**Course:** CMPS 241 — Systems Programming (Fall 2025/26)  
**Repository:** https://github.com/Dev-Karim/Connect-Four  

---

## 1) What we built
A console **Connect‑4** game (6×7 grid) in **C**:
- Two players **A** and **B** alternate turns.
- The board updates after each valid move and shows column numbers 1..7.
- Invalid inputs are rejected (out‑of‑range column or full column).
- Win detection in all directions (horizontal, vertical, both diagonals).
- Declares **winner** or **draw**.

**Files**
- `board.c / board.h` — board creation, rendering, placing moves, win/draw checks
- `game.c / game.h` — gameplay loop (prompts, input parsing, turn order)
- `main.c` — entry point that runs `play_human_vs_human()`
- `Makefile` — build/run/clean targets

---

## 2) How to build & run
```bash
make clean
make          # builds ./connect4 with -std=c11 -Wall -Wextra -Wpedantic -O2 -g
make run      # launches the game
```

Expected prompts/messages:
- `Player A, choose a column (1-7):`
- `Invalid move, try again.`
- `Player X wins!` or `It's a draw!`

---

## 3) Linux VM procedure (Alpine Linux)
We used **Alpine Linux** (no GUI) inside a Virtual Machine to satisfy the “small Linux distro” requirement.

### 3.1 Install tools & get the code
```bash
sudo apk update
sudo apk add build-base git

git clone https://github.com/Dev-Karim/Connect-Four
cd Connect-Four
```

### 3.2 Build & run
```bash
make clean
make
./connect4
```

### 3.3 Autostart on boot
We configured the game to start automatically at boot using Alpine’s OpenRC system:

```bash
# Create a local startup script
sudo sh -c 'cat >/etc/local.d/connect4.start <<EOF
#!/bin/sh
cd /home/<youruser>/Connect-Four
./connect4
EOF'

sudo chmod +x /etc/local.d/connect4.start
sudo rc-update add local default
sudo reboot
```

After reboot, the game launches automatically in the console.

---

## 4) Conclusion
We successfully implemented a two‑player Connect‑4 game with correct I/O, win/draw detection, and verified **Alpine Linux autostart** configuration. The game runs automatically at VM startup, fulfilling all Phase‑1 requirements.
