# Key Point

用如下方法来解析request body:

	json.NewDecoder().Decode()

# Code Snippet

	func testHandler(w http.ResponseWriter, req *http.Request) {
	    e := &Employee{}
	    json.NewDecoder(req.Body).Decode(e)
	    log.Println(*e)
	    ...
	}

# Run

## Step 1

Run server:

	go run main.go

## Step 2

Client send request to server:

	curl -v -H "Content-Type: application/json" http://localhost:8000/test --data "{\"name\":\"Tom\",\"age\":10}"

## Result

- Server:

	2017/10/16 20:55:47 {Tom 10 }

- Client:

	$ curl -v -H "Content-Type: application/json" http://localhost:8000/test --data "{\"name\":\"Tom\",\"age\":10}"
	* timeout on name lookup is not supported
	*   Trying 127.0.0.1...
	  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
	                                 Dload  Upload   Total   Spent    Left  Speed
	  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0* Connected to localhost (127.0.0.1) port 8000 (#0)
	> POST /test HTTP/1.1
	> Host: localhost:8000
	> User-Agent: curl/7.44.0
	> Accept: */*
	> Content-Type: application/json
	> Content-Length: 23
	>
	} [23 bytes data]
	* upload completely sent off: 23 out of 23 bytes
	< HTTP/1.1 200 OK
	< Content-Type: application/json
	< Date: Mon, 16 Oct 2017 12:55:47 GMT
	< Content-Length: 23
	<
	{ [23 bytes data]
	100    46  100    23  100    23    489    489 --:--:-- --:--:-- --:--:--  1533{"code":0,"message":""}
	* Connection #0 to host localhost left intact

简化情况：(去掉-v)

	$ curl -H "Content-Type: application/json" http://localhost:8000/test --data "{\"name\":\"Tom\",\"age\":10}"
	  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
	                                 Dload  Upload   Total   Spent    Left  Speed
	100    46  100    23  100    23   1533   1533 --:--:-- --:--:-- --:--:-- 23000
	{"code":0,"message":""}
