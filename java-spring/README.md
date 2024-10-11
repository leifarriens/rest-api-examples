# spring-rest-sample

## Quickstart

### Install Java 21

Install Java 21:

```sh
sudo apt install openjdk-21-jdk
```

Install maven:

```sh
sudo apt install maven
```

### Run Spring Boot Application

Run the Spring Boot application:

```sh
mvn spring-boot:run
```

### Build Spring Boot Application

Build the Spring Boot application:

```sh
mvn clean package
```

### Build & Run with Docker

Build the Spring Boot application with Docker:

```sh
docker build -t spring-rest-sample .
```

Run the Spring Boot application with Docker:

```sh
docker run -p 8080:8080 spring-rest-sample
```
