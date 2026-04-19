# Hanabatake Timer 🌸

A minimal, terminal-native productivity timer with a visual twist: your focus sessions grow into a digital flower garden.

## Overview

**Hanabatake Timer** is a CLI-based Pomodoro-style productivity tool written in C++. It prioritizes:

- Zero friction (runs directly from terminal)
- Lightweight execution (no heavy dependencies)
- Visual feedback (ASCII + future 3D visualization)

The core idea:  
Each completed focus session contributes to a persistent dataset, which is later visualized as a **garden of flowers** via a web interface.

---

## Philosophy

Most productivity tools optimize for features.  
This project optimizes for:

- Speed of access → type `Hanabatake`, start immediately  
- Low cognitive load → no GUI distractions  
- Delayed gratification → progress visualized over time, not instantly gamified  

---

## Features (Current)

### CLI Interface
- Interactive menu navigation using arrow keys
- ANSI-colored selection UI
- ASCII art rendering

### Commands

```bash
Hanabatake            # Launch app with art
Hanabatake --no-art   # Launch without ASCII art
Hanabatake --help     # Show help menu
```

### Input Handling
- Real-time keyboard input via `_getch()`
- Navigation using arrow keys (UP/DOWN)
- Selection via ENTER

---

## Tech Stack

| Layer        | Technology |
|-------------|----------|
| Core CLI    | C++ |
| Terminal UI | ANSI escape sequences |
| OS API      | Windows API (`windows.h`, `conio.h`) |
| Future Web  | Three.js (planned) |
| Data Format | JSON (planned) |

---

## Planned Architecture

```
[ CLI Timer ]
      ↓
[ Session Logger ]
      ↓
[ JSON Storage ]
      ↓
[ Web Visualization (Three.js) ]
      ↓
[ Flower Garden Representation ]
```

---

## Core Concept: “Garden as Data”

Each focus session becomes a unit of growth:

| Metric            | Visual Representation |
|------------------|----------------------|
| Session count     | Number of flowers |
| Focus duration    | Flower size |
| Consistency       | Garden density |
| Streaks           | Rare/unique flowers |

---

## Roadmap

### Phase 1 — Functional Timer
- [ ] Implement actual Pomodoro timer (25/5 cycles)
- [ ] Add pause/resume
- [ ] Configurable durations

### Phase 2 — Persistence
- [ ] Export sessions to JSON
- [ ] Local file storage
- [ ] Session history tracking

### Phase 3 — CLI UX Improvements
- [ ] Cross-platform support (Linux/windows)
- [ ] Replace `windows.h` dependency
- [ ] Better terminal rendering (ncurses or similar)

### Phase 4 — Visualization Layer
- [ ] Web dashboard using Three.js
- [ ] Render flowers procedurally
- [ ] Timeline-based garden evolution

---

## High-Value Feature Ideas

### 1. Session Classification
Tag sessions:

```
Work / Study / Coding / Reading
```

---

### 2. Streak Decay Model
Instead of binary streaks:
- Missing days reduces growth rate instead of resetting
- More realistic behavioral modeling

---

### 3. CLI-first Analytics

```
Hanabatake stats
```

Show:
- Total focus time
- Weekly trend
- Average session length

---

### 4. “Dead Garden” Feedback
If inactive:
- Garden withers visually (in web UI)
- Introduces consequence without notifications

---

### 5. Export/Import

```
Hanabatake export
Hanabatake import
```

---

### 6. Background Timer Mode

```
Hanabatake start --bg
```

---

### 7. Sound / Notification Hook
- Terminal bell or OS notification when session ends

---

### 8. Config System

```
~/.hanabatake/config.json
```

Control:
- Timer durations
- Themes
- Output format

---

### 9. Plugin System (Advanced)
Expose hooks:
- Custom exporters
- Alternative visualizations

---

## Limitations (Current)

- Windows-only (due to `windows.h`)
- No actual timer logic yet
- No persistence layer
- UI tightly coupled to rendering logic

---

## Suggested Refactor (Important)

You’re currently mixing concerns. Long-term maintainability improves if you separate:

- UI rendering
- input handling
- business logic (timer)
- data persistence

Minimal structure:

```
/core       → timer logic
/ui         → CLI rendering
/input      → keyboard handling
/storage    → JSON handling
```

---

## Build & Run (Example)

for seemless terminal call, make a directory in you drive C: (or whatever it is your windows root drive)
search for Environment variables, on User variables click "New..." add the project directory.
