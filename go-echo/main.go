package main

import (
	"net/http"
	"time"

	"github.com/labstack/echo/v4"
)

type Response struct {
	Timestamp string `json:"timestamp"`
	Status    int    `json:"status"`
}

func main() {
	e := echo.New()

	e.GET("/", func(c echo.Context) error {
		response := Response{
			Timestamp: time.Now().Format(time.RFC3339),
			Status:    http.StatusOK,
		}
		return c.JSON(http.StatusOK, response)
	})

	e.Logger.Fatal(e.Start(":1323"))
}
