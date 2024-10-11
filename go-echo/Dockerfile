FROM golang:1.22.1-alpine AS build-stage

WORKDIR /app

COPY go.mod go.sum ./

RUN go mod download

COPY . .

RUN go build -x -o /go-echo .

FROM gcr.io/distroless/base-debian11 AS build-release-stage

WORKDIR /

COPY --from=build-stage ./go-echo ./go-echo

ENV ENVIRONMENT=container

EXPOSE 1323

CMD ["./go-echo"]