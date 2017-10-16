# Key Points

- 静态服务器
- json

# URL

- http://127.0.0.1:9999/
- http://127.0.0.1:9999/foo

# Run

## Server

	go run main.go

## Client

- /

	$ curl http://127.0.0.1:9999/
	  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
	                                 Dload  Upload   Total   Spent    Left  Speed
	100    89  100    89    0     0     89      0  0:00:01 --:--:--  0:00:01 89000<pre>
	<a href="a.txt">a.txt</a>
	<a href="b.txt">b.txt</a>
	<a href="foo/">foo/</a>
	</pre>

- /foo

	$ curl http://127.0.0.1:9999/foo
	  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
	                                 Dload  Upload   Total   Spent    Left  Speed
	100    87  100    87    0     0   5437      0 --:--:-- --:--:-- --:--:--  5437
	{"result_code":100,"message":"success response","data":"{\"Name\":\"Tom\",\"Age\":10}"}

	$


