package main

import (
    "bytes"
    "encoding/json"
    "fmt"
    "net/http"
)

const (
    tokenUrl   = "https://xrenn.ai/api/v1/auth_xrenn_token/obtain/"
    refreshUrl = "https://xrenn.ai/api/v1/auth_xrenn_token/refresh/"
)

func obtainToken(username, password string) (map[string]interface{}, error) {
    data := map[string]string{
        "username": username,
        "password": password,
    }
    jsonData, _ := json.Marshal(data)

    resp, err := http.Post(tokenUrl, "application/json", bytes.NewBuffer(jsonData))
    if err != nil {
        return nil, err
    }
    defer resp.Body.Close()

    var result map[string]interface{}
    json.NewDecoder(resp.Body).Decode(&result)

    if resp.StatusCode != http.StatusOK {
        return nil, fmt.Errorf("error: %v", result)
    }

    return result, nil
}

func refreshToken(refresh string) (map[string]interface{}, error) {
    data := map[string]string{
        "refresh": refresh,
    }
    jsonData, _ := json.Marshal(data)

    resp, err := http.Post(refreshUrl, "application/json", bytes.NewBuffer(jsonData))
    if err != nil {
        return nil, err
    }
    defer resp.Body.Close()

    var result map[string]interface{}
    json.NewDecoder(resp.Body).Decode(&result)

    if resp.StatusCode != http.StatusOK {
        return nil, fmt.Errorf("error: %v", result)
    }

    return result, nil
}