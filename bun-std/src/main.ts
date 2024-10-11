const server = Bun.serve({
  port: 3000,
  fetch() {
    return new Response('Hello, Bun!');
  },
});

console.log(`Listening on http://localhost:${server.port}`);