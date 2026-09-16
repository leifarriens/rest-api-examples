FROM gcc:14 AS builder

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o http main.cpp

FROM ubuntu:24.04 AS runtime

WORKDIR /app

COPY --from=builder /app/http .

EXPOSE 8080

CMD ["./http"]
