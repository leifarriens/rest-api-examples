use actix_web::{get, App, HttpResponse, HttpServer, Responder};
use serde::Serialize;
use chrono::Utc;

#[derive(Serialize)]
struct Response {
    timestamp: String,
    status: u16,
}

#[get("/")]
async fn hello() -> impl Responder {
    let response = Response {
        timestamp: Utc::now().to_rfc3339(),
        status: 200,
    };
    HttpResponse::Ok().json(response)
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .service(hello)
    })
    .bind(("0.0.0.0", 8080))?
    .run()
    .await
}