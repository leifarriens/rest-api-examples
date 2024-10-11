import http from 'http';

const server = http.createServer((req, res) => {
  if (req.url === '/' && req.method === 'GET') {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Hello, Node!\n');
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('Not Found\n');
  }
});

const PORT = 8080;

server.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});
