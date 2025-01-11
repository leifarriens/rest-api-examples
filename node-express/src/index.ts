import express from 'express';

const app = express();

app.get('/', function (req, res) {
  res.json('Hello express');
});

app.listen(3000, () => {
  console.log('Example app listening on port 3000!');
});
