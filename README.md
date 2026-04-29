# Modular Trading Bot Engine

A high-performance trading bot written in **C** designed for automated crypto/stock trading. The engine operates on a command-based protocol (reading from `stdin`, writing to `stdout`) and uses a dynamic plugin architecture to evaluate market conditions using various technical indicators.

## Features

* **Modular Plugin System**: Loads trading strategies dynamically at runtime using `dlopen` and `dlsym`.
* **Multi-Strategy Aggregation**: Combines signals from multiple indicators (e.g., RSI, Ichimoku) to calculate a weighted decision cursor.
* **Wallet Management**: Real-time tracking of asset balances (Asset A vs. Asset B) and transaction fee calculations.
* **Technical Indicators**:
    * **RSI (Relative Strength Index)**: Identifies overbought/oversold conditions.
    * **Ichimoku Cloud**: Evaluates trend direction and momentum using Tenkan, Kijun, and Senkou spans.
* **Circular Buffer Logic**: Efficiently manages historical candle data to minimize memory overhead.

## Architecture

The project is divided into several logical modules:

| Module | Description |
| :--- | :--- |
| **Core Engine** (`main.c`, `trade.c`) | Initializes settings, loads plugins, and manages the main execution loop. |
| **Plugin Loader** (`loader.c`) | Scans a directory for `.so` files and registers trading strategies. |
| **Interpreter** (`input.c`) | Parses incoming game commands (updates on stacks, next candles, and action requests). |
| **Decision Logic** (`decision.c`) | Aggregates plugin signals and determines whether to `buy`, `sell`, or `pass`. |
| **Wallet** (`wallet.c`) | Handles currency conversions and ensures trades are viable based on current balance. |
| **Data Utils** (`array.c`, `chart.c`) | Manages OHLCV (Open, High, Low, Close, Volume) data structures. |

## Plugin System

The bot is designed to be extensible. To add a new strategy, you simply create a shared library with a `plugin_entry_point`.

### Included Indicators:
1.  **Ichimoku (`plugin_ichimoku.c`)**: Uses a 9/26/52 period configuration to detect trend reversals.
2.  **RSI (`plugin_rsi.c`)**: Calculates momentum over a 7-period window to find entry/exit points at the 30/70 thresholds.

### Aggregation Logic:
Each plugin returns a `signal` (BUY, SELL, or PASS) and a `strength` (0.0 to 1.0). The engine calculates a **Decision Cursor**:
$$Cursor = \frac{\sum (Signal \times Strength)}{TotalActivePlugins}$$
The bot only executes a trade if the cursor exceeds a pre-defined `SIGNAL_LIMIT`.

## Installation & Usage

### 1. Compilation
Use the provided Makefile (not included in snippet, but standard for this project) to compile the core and the plugins:
```bash
make
```

### 2. Running
The bot reads from standard input. You can test it using a pipe or by running it manually:
```bash
./trade_bot < communication_dump.txt
```

### 3. Plugin Directory
The engine looks for `.so` files in the path defined by `PLUGIN_PATH` (usually `./plugins/`). Ensure your compiled indicators are placed there.

## Communication Protocol

The bot follows a specific line-by-line protocol:
* **Settings**: `settings [key] [value]` (e.g., `settings time_per_move 100`)
* **Updates**: `update game next_candles [data]`
* **Actions**: `action order [time]` -> Bot responds with `buy [pair] [quantity]`, `sell [pair] [quantity]`, or `pass`.
