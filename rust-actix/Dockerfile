
# Build stage
FROM rust:1.81-slim-bullseye AS builder

WORKDIR /app

COPY . .

RUN cargo build --release

FROM debian:buster-slim AS runner

WORKDIR /usr/local/bin

COPY --from=builder /app/target/release/rust-actix .

CMD ["./rust-actix"]
