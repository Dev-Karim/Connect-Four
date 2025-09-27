Connect-4 — CMPS 241 Systems Programming Project

📖 Overview

Implementation of the classic Connect-4 game in C as part of CMPS 241 (Systems Programming).
The project is delivered in four sprints, starting with a two-player console game and ending with progressively stronger bots, plus a final report and presentation.

⸻

🚀 Features (Sprint 1)
	•	Console-based 6×7 board.
	•	Two human players (A and B) take turns.
	•	Board updates and re-renders after each move.
	•	Invalid moves (full column, out of range, bad input) are rejected with a clear message.
	•	Detects wins horizontally, vertically, and diagonally.
	•	Declares winner or draw.
	•	Sample playthrough screenshots provided in docs/.

⸻

🛠️ Compilation & Run Instructions

Build

make clean
make

Run

make run

Clean

make clean

Optional targets
	•	make debug → build with -O0 -g for debugging
	•	make release → optimized build with -O2

⸻

📅 Sprint Deliverables
	•	Sprint 1 (Oct 4): Two-player console game ✅
	•	Sprint 2 (Oct 18): Easy bot (random valid moves)
	•	Sprint 3 (Nov 1): Medium bot + complexity analysis
	•	Sprint 4 (Nov 15): Hard bot + complexity analysis + final report + slides + demo
⸻
⸻

👥 Team & Integrity

Developed by KJE Core for CMPS 241 (Fall 2025/26).
All work follows AUB’s academic integrity policy — this repo is the result of our team’s understanding and development process.
