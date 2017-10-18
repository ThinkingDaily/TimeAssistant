def write_file(filename, content):
    f = open(filename, "wb")
    f.write(content)
    f.close()

def foo():
    print "Hello, Python!"
    fn = "/app/test.txt"
    write_file(fn, "Hello, Python!")

if __name__ == "__main__":
    foo()
