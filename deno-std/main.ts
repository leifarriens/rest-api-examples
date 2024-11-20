Deno.serve(() => {
  return new Response(
    JSON.stringify({
      timestamp: new Date().toISOString(),
      status: 200,
    }),
    {
      status: 200,
      headers: {
        'content-type': 'application/json; charset=utf-8',
      },
    }
  );
});
