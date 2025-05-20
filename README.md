# RTL to CFG Converter and Graph Visualizer

A full-stack web application for converting Register Transfer Level (RTL) Verilog code to its Control Flow Graph (CFG) and visualizing the result interactively.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Quick Start (Docker)](#quick-start-docker)
  - [Manual Setup](#manual-setup)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Tech Stack](#tech-stack)
- [Authors](#authors)
- [License](#license)

---

## Overview

This project provides a seamless way to upload Verilog RTL files, convert them to a Control Flow Graph (CFG) using custom C++ tools, and visualize the resulting graph in an interactive frontend. The backend is powered by Django REST Framework and orchestrates the conversion pipeline.

## Features

- Upload Verilog (.v) RTL files via a modern web UI
- Automatic parsing and sanitization of RTL code
- Generation of CFG using custom C++ tools
- Interactive graph visualization (SVG)
- Downloadable graph images
- Syntax-highlighted code viewer
- Light/Dark theme toggle

## Architecture

- **Frontend:** React + TypeScript (Vite, TailwindCSS)
- **Backend:** Django REST Framework (Python 3.12)
- **C++ Tools:** Custom parser and CFG generator
- **Containerization:** Docker & Docker Compose

### Data Flow

1. User uploads a Verilog RTL file in the frontend.
2. File is sent to the backend via REST API.
3. Backend saves the file, runs the C++ parser and CFG generator.
4. The generated CFG and DOT graph are returned to the frontend.
5. The frontend displays the code and renders the graph interactively.

## Getting Started

### Prerequisites

- [Docker](https://www.docker.com/) (recommended)
- Or: Python 3.12, Node.js (v18+), npm, C++ build tools (g++)

### Quick Start (Docker)

1. Clone the repository:
   ```cmd
   git clone <repo-url>
   cd dc_work
   ```
2. Build and start the backend (Django + C++ tools):

   ```cmd
   docker-compose up --build
   ```

   The backend will be available at `http://localhost:8000`.

3. Start the frontend:
   ```cmd
   cd frontend/rtl-cfg-frontend
   npm install
   npm run dev
   ```
   The frontend will be available at `http://localhost:5173` (default Vite port).

### Manual Setup

#### Backend

1. Install Python dependencies:
   ```cmd
   cd backend
   pip install -r requirements.txt
   ```
2. Build C++ tools:
   ```cmd
   cd ../cpp_tools
   make
   ```
3. Start Django server:
   ```cmd
   cd ../backend
   python manage.py migrate
   python manage.py runserver
   ```

#### Frontend

1. Install dependencies:
   ```cmd
   cd frontend/rtl-cfg-frontend
   npm install
   ```
2. Start development server:
   ```cmd
   npm run dev
   ```

## Usage

- Open the frontend in your browser.
- Upload a `.v` Verilog RTL file.
- View the sanitized code and the generated CFG graph.
- Download the graph as SVG if desired.

## Project Structure

```
dc_work/
├── backend/           # Django backend (API, pipeline)
│   ├── api/           # API views, utils
│   ├── rtl2cfg/       # Django project config
│   ├── manage.py      # Django entrypoint
│   └── ...
├── cpp_tools/         # C++ parser and CFG generator
│   ├── parser.cpp
│   ├── loop_cfg.cpp
│   └── Makefile
├── frontend/
│   └── rtl-cfg-frontend/ # React + TS frontend
│       ├── src/
│       ├── public/
│       └── ...
├── Dockerfile         # Multi-stage build for backend + C++
├── docker-compose.yml # Compose for backend
└── ...
```

## Tech Stack

- **Frontend:** React, TypeScript, Vite, TailwindCSS, PrismJS, React Flow, HPCC Graphviz
- **Backend:** Django, Django REST Framework, Gunicorn, CORS, Whitenoise
- **C++ Tools:** Custom parser and CFG generator
- **Containerization:** Docker, Docker Compose

## Authors

- [Avanti Mittal (B22ES021)](https://github.com/avantimittal)
- [Shivanshu Verma (B22ES010)](https://shivanshu.site/)

---

## License

This project is for educational and research purposes. All rights reserved.
