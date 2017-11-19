curl - 判断文件是否存在

# Key Points

使用 -I 选项，然后判断返回状态码。

- 200: 文件存在，此时Content-Length为文件长度
- 404: 文件不存在

# man curl 

    -I, --head
    (HTTP/FTP/FILE) Fetch the HTTP-header only! HTTP-servers feature the command HEAD which this uses to get nothing but the header
    of a document. When used on an FTP or FILE file, curl displays the file size and last modification time only.

# Example

## Valid URL

Command:

    curl -I https://artifacts.elastic.co/downloads/beats/filebeat/filebeat-5.6.4-i386.deb.sha512

Response:

    HTTP/1.1 200 OK
    Accept-Ranges: bytes
    Content-Length: 128
    Content-Type: application/octet-stream
    Date: Tue, 14 Nov 2017 01:15:13 GMT
    ETag: "044ca8bde67d8c549dd820a2d4c7b0ec"
    Last-Modified: Tue, 07 Nov 2017 17:14:19 GMT
    Server: nginx/1.4.6 (Ubuntu)
    x-amz-id-2: 6/q0CXWarfi2SzIRWSzitZfjrVXwrVCoNFgbCa7DSSW/DBxZfnjhrK1q/xeQkcBCJT0QytOMpHA=
    x-amz-request-id: 6030619DBD8ED672
    x-amz-version-id: aYjPhRIfA__ov0b9E3Fq_FFmCf4M6MKI
    x-ngx-hostname: www05
    Connection: keep-alive

## Invalid URL

Command:

    curl -I https://artifacts.elastic.co/downloads/beats/filebeat/filebeat-5.6.4-i386.deb.sha512x

Response:

    HTTP/1.1 404 Not Found
    Content-Type: application/xml
    Date: Tue, 14 Nov 2017 01:15:51 GMT
    Server: nginx/1.4.6 (Ubuntu)
    x-amz-id-2: U/vIrLzybsaoSMp/Jb3erQuUDOC4CbxPX+UDzRcZ9dej/9XcjPR5NR5YV8qbu0MW9vRoahtO51I=
    x-amz-request-id: 287952E878AFA642
    Connection: keep-alive

