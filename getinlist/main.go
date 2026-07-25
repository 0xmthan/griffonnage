package main

import (
	"bufio"
	"encoding/json"
	"flag"
	"fmt"
	"net/http"
	"net/url"
	"os"
	"strconv"
	"strings"
	"time"
)

const (
	tokenURL = "https://api.intra.42.fr/oauth/token"
	usersURL = "https://api.intra.42.fr/v2/cursus/21/users"
	pageSize = 100
	campusID = "49"
)

type User struct {
	ID              int    `json:"id"`
	Login           string `json:"login"`
	Email           string `json:"email"`
	FirstName       string `json:"first_name"`
	LastName        string `json:"last_name"`
	UsualFullName   string `json:"usual_full_name"`
	Kind            string `json:"kind"`
	PoolMonth       string `json:"pool_month"`
	PoolYear        string `json:"pool_year"`
	PrimaryCampusID int    `json:"primary_campus_id"`
	Active          bool   `json:"active?"`
	Alumni          bool   `json:"alumni?"`
}

type tokenResponse struct {
	AccessToken string `json:"access_token"`
	TokenType   string `json:"token_type"`
	ExpiresIn   int    `json:"expires_in"`
}

func main() {
	loadDotEnv(".env")

	year := flag.String("year", "", "Piscine pool year, e.g. 2024 (required)")
	month := flag.String("month", "", "Piscine pool month, e.g. july (required)")
	flag.Parse()

	if *year == "" || *month == "" {
		fmt.Fprintln(os.Stderr, "error: -year and -month are required to identify a piscine, e.g. -year 2024 -month july")
		os.Exit(1)
	}

	clientID := os.Getenv("FT_CLIENT_ID")
	clientSecret := os.Getenv("FT_CLIENT_SECRET")
	if clientID == "" || clientSecret == "" {
		fmt.Fprintln(os.Stderr, "error: FT_CLIENT_ID and FT_CLIENT_SECRET must be set (see .env.example)")
		os.Exit(1)
	}

	token, err := getAccessToken(clientID, clientSecret)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: failed to authenticate: %v\n", err)
		os.Exit(1)
	}

	users, err := fetchPiscineUsers(token, *year, *month)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: failed to fetch users: %v\n", err)
		os.Exit(1)
	}

	for _, u := range users {
		fmt.Println(u.Login)
	}
	fmt.Fprintf(os.Stderr, "total: %d\n", len(users))
}

func getAccessToken(clientID, clientSecret string) (string, error) {
	form := url.Values{
		"grant_type":    {"client_credentials"},
		"client_id":     {clientID},
		"client_secret": {clientSecret},
	}

	resp, err := http.PostForm(tokenURL, form)
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return "", fmt.Errorf("token request returned status %s", resp.Status)
	}

	var tr tokenResponse
	if err := json.NewDecoder(resp.Body).Decode(&tr); err != nil {
		return "", err
	}
	if tr.AccessToken == "" {
		return "", fmt.Errorf("no access_token in response")
	}
	return tr.AccessToken, nil
}

func fetchPiscineUsers(token, year, month string) ([]User, error) {
	var all []User
	client := &http.Client{Timeout: 30 * time.Second}

	for page := 1; ; page++ {
		q := url.Values{}
		q.Set("filter[pool_year]", year)
		q.Set("filter[pool_month]", month)
		q.Set("filter[primary_campus_id]", campusID)
		q.Set("page[size]", strconv.Itoa(pageSize))
		q.Set("page[number]", strconv.Itoa(page))
		q.Set("sort", "login")

		reqURL := usersURL + "?" + q.Encode()

		users, status, err := doUsersRequest(client, reqURL, token)
		if err != nil {
			return nil, err
		}

		if status == http.StatusTooManyRequests {
			time.Sleep(2 * time.Second)
			page--
			continue
		}
		if status != http.StatusOK {
			return nil, fmt.Errorf("unexpected status %d fetching page %d", status, page)
		}

		all = append(all, users...)

		if len(users) < pageSize {
			break
		}

		time.Sleep(500 * time.Millisecond)
	}

	return all, nil
}

func doUsersRequest(client *http.Client, reqURL, token string) ([]User, int, error) {
	req, err := http.NewRequest(http.MethodGet, reqURL, nil)
	if err != nil {
		return nil, 0, err
	}
	req.Header.Set("Authorization", "Bearer "+token)

	resp, err := client.Do(req)
	if err != nil {
		return nil, 0, err
	}
	defer resp.Body.Close()

	if resp.StatusCode == http.StatusTooManyRequests {
		return nil, resp.StatusCode, nil
	}
	if resp.StatusCode != http.StatusOK {
		return nil, resp.StatusCode, nil
	}

	var users []User
	if err := json.NewDecoder(resp.Body).Decode(&users); err != nil {
		return nil, 0, err
	}
	return users, resp.StatusCode, nil
}

func loadDotEnv(path string) {
	f, err := os.Open(path)
	if err != nil {
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" || strings.HasPrefix(line, "#") {
			continue
		}

		key, value, found := strings.Cut(line, "=")
		if !found {
			continue
		}
		key = strings.TrimSpace(key)
		value = strings.TrimSpace(value)
		value = strings.Trim(value, `"'`)

		if _, exists := os.LookupEnv(key); !exists {
			os.Setenv(key, value)
		}
	}
}
