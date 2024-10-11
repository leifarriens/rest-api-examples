package com.example;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import java.util.Map;
import java.util.HashMap;

@RestController
public class HelloController {
    @GetMapping("/")
    public String hello() {
        return "Hello, Java Spring!";
    }
}
