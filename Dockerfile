# ---------- BUILD STAGE ----------
FROM ubuntu:22.04 AS builder

WORKDIR /app

RUN apt update && apt install -y g++

COPY scanner.cpp .

RUN g++ scanner.cpp -o scanner


# ---------- FINAL STAGE ----------
FROM python:3.10-slim

WORKDIR /app

COPY --from=builder /app/scanner /app/build/scanner
COPY . .

RUN pip install flask

EXPOSE 5000

CMD ["python", "app.py"]

