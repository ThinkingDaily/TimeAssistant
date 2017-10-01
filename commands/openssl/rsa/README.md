# Encrpytion & Decryption

## Command

### Generate a private key

	openssl genrsa -out test.key 2048

### Export the publish Key

	openssl rsa -in test.key -pubout -out test_pub.key

### Encrypt file with publish key

	openssl rsautl -encrypt -in hello.txt -inkey test_pub.key -pubin -out hello.en 

### Decrpyt file with private key

	openssl rsautl -decrypt -in hello.en -inkey test.key -out hello.de

## Example

	$ openssl genrsa -out test.key 2048
	Generating RSA private key, 2048 bit long modulus
	..................+++
	............+++
	e is 65537 (0x10001)
	$ openssl rsa -in test.key -pubout -out test_pub.key
	writing RSA key
	$ cat test_pub.key 
	-----BEGIN PUBLIC KEY-----
	MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqY5sDVaWmSGDPDnit/bv
	wqTo54wtWjnDYbc9Yc9ykYKiyoCFP9BSKpULPgU7jXom5LtIDY1KJkvNCJjkCHkn
	7GuhPKrGoJOgUsAWs+AXki7ZcqIR9C1sN4SuVdZfLXYXZwsqKK+lQPQnjmp+m3/P
	6v5fzQxj2nN8EdwVqU4WaMTr3hVNJD9ncYQ/QG4ikqGzWBmnbjMJewEPwJX+rajB
	jAjRRGFE9uqhBNl7wlsfVw1upwapwo80Rc3XBewP6u5dq3j1deEAuVzebWzpbmke
	P1N5kGOdnz8m2BiPYaQC3FQVWq4d27jFvssv/d8Rx/OIJLv9yfX/a62ITyD6RK/G
	nQIDAQAB
	-----END PUBLIC KEY-----
	$ echo Hello, world! > hello.txt
	$ openssl rsautl -encrypt -in hello.txt -inkey test_pub.key -pubin -out hello.en 
	$ hexdump -C hello.en
	00000000  59 f2 ca 18 53 2d 9b 95  55 93 d9 90 48 b5 81 97  |Y...S-..U...H...|
	00000010  fd 3f 28 1d f6 fe 3e 06  96 cc e7 b5 b8 a7 d7 96  |.?(...>.........|
	00000020  9e 61 7b 84 67 6b 3c 48  dc 0c 06 da ae 3f 20 61  |.a{.gk<H.....? a|
	00000030  42 bd 5e 4c aa 66 8c 92  09 00 b7 76 f5 75 4a 0d  |B.^L.f.....v.uJ.|
	00000040  7d af e1 38 21 57 a9 a0  09 58 00 75 11 9c 36 48  |}..8!W...X.u..6H|
	00000050  54 9b 67 34 73 52 62 23  14 0c 05 b4 f0 c9 1a 54  |T.g4sRb#.......T|
	00000060  32 1b 93 3c 38 f9 1c 24  72 9a 82 38 b7 61 d1 ed  |2..<8..$r..8.a..|
	00000070  ac c9 ee 1e 55 34 7a d3  fc 65 87 5e 7a 72 58 74  |....U4z..e.^zrXt|
	00000080  c6 d3 cb df bc 44 f2 a1  4e 92 88 15 1f 6e ae b3  |.....D..N....n..|
	00000090  5e e9 f1 19 27 42 f1 b9  0a 03 6a 49 d2 50 59 88  |^...'B....jI.PY.|
	000000a0  d3 10 9c 43 6c 42 a3 68  1c 83 3e 7e 7b 10 b5 c6  |...ClB.h..>~{...|
	000000b0  20 41 64 ff 23 ae 96 8b  a1 02 8f 7e 18 68 bc b7  | Ad.#......~.h..|
	000000c0  a4 f2 bc 52 a9 ee 22 51  a9 12 18 96 4b f7 a6 5d  |...R.."Q....K..]|
	000000d0  03 08 39 87 ce 3f c6 47  09 49 19 ef 89 f9 01 1f  |..9..?.G.I......|
	000000e0  d0 b5 8e 35 60 18 46 63  56 3c 6d 0d 5e e6 45 cc  |...5`.FcV<m.^.E.|
	000000f0  87 33 bd c2 c9 fb 7d 28  74 a2 16 ae d8 77 9d 00  |.3....}(t....w..|
	00000100
	$ openssl rsautl -decrypt -in hello.en -inkey test.key -out hello.de
	$ hexdump -C hello.de
	00000000  48 65 6c 6c 6f 2c 20 77  6f 72 6c 64 21 0a        |Hello, world!.|
	0000000e
	$ diff hello.de hello.txt
	$ 

# Export publish key from certificate

	openssl x509 -in cert.pem -pubkey -noout > public_key.pem

# Signature & Verification

Verify whether the received file is right.

	openssl dgst -sha256 -verify public_key.pem -signature sig.dat test.dat

Parameters:

- public_key.pem: Publish key. Receiver use the publish key to verify the signature. 公钥（接收方用公钥对文件签名进行验证）
- sig.dat: Signature received by receiver. 接收方收到的签名
- test.dat: Received data/file. 接收到的文件

