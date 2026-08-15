# 📡 Zephyr RTOS-Inspired CAN Telemetry Parser

[![CI Pipeline](https://github.com/nagasena-sys/can-frame-googletest-cicd/actions/workflows/ci.yaml/badge.svg)](https://github.com/nagasena-sys/can-frame-googletest-cicd/actions/workflows/ci.yaml)
[![Language: C11](https://img.shields.io/badge/Language-C11-blue.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A zero-allocation **CAN Bus Frame Parsing & Telemetry Serialization Library** written in pure C (C11). Built using **Zephyr RTOS** error handling conventions, tested with **Google Test (C++)**, and automated using **GitHub Actions CI/CD**.

---

## 🎯 Scope & Technical Features

- **POSIX / Zephyr API Conventions:** Uses standard negative errno return codes (`DRV_OK`, `-EINVAL`, `-EIO`).
- **Defensive Validation:** Validates payload lengths (DLC <= 8), 11-bit vs 29-bit CAN IDs, and null pointer guards to prevent HardFaults.
- **Fixed-Point Serialization:** Packs floating-point telemetry (temperature, battery status) into fixed byte layouts without standard library dynamic allocation (`malloc`).
- **Host-Based Unit Testing:** Isolated testing running offline via GoogleTest framework.

---

