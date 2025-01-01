var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllers();

var app = builder.Build();

// Map controllers.
app.MapControllers();

// Start the application.
app.Run();
