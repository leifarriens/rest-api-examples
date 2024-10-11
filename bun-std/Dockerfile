FROM oven/bun:1 AS base

FROM base AS runner

WORKDIR /app

COPY package.json .

RUN bun install

COPY src ./src

EXPOSE 3000

CMD ["bun", "/app/src/main.ts"] 