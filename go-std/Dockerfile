FROM golang:1.22.1-alpine AS build-stage

WORKDIR /app

COPY go.mod ./

COPY . .

RUN go build -x -o /go-std .

FROM gcr.io/distroless/base-debian11 AS build-release-stage

WORKDIR /

COPY --from=build-stage ./go-std ./go-std

ENV ENVIRONMENT=container

EXPOSE 8080

CMD ["./go-std"]