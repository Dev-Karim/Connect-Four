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


## 2) Linux VM procedure (Alpine Linux)
We used **Alpine Linux** (no GUI) inside a Virtual Machine to satisfy the “small Linux distro” requirement.

### 2.1 Install tools & get the code
```bash
sudo apk update
sudo apk add build-base git

git clone https://github.com/Dev-Karim/Connect-Four
cd Connect-Four
```

### 2.2 Build & run
```bash
make clean
make
./connect4
```

### 2.3 Autostart on boot
To run the game automatically on boot using Alpine’s OpenRC system:

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
After reboot, the game appears automatically.

---

## 3) Conclusion
We delivered a clean two‑player Connect‑4 game with the required console I/O, correct win/draw logic, and a documented Alpine Linux setup including autostart on boot.
