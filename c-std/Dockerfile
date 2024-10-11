FROM gcc:latest AS builder

WORKDIR /app

COPY . .

RUN gcc -o http main.c

FROM ubuntu:latest AS runtime

WORKDIR /app

COPY --from=builder /app/http .

CMD ["./http"]