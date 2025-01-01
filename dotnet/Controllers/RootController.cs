using Microsoft.AspNetCore.Mvc;

namespace SimpleApi.Controllers
{
  [ApiController]
  [Route("/")]
  public class RootController : ControllerBase
  {
    [HttpGet]
    public IActionResult Get()
    {
      var response = new
      {
        Timestamp = DateTime.UtcNow.ToString("o"), // RFC 3339 format
        Status = 200 // HTTP Status OK
      };

      return Ok(response);
    }
  }
}