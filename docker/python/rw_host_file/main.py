import json

def load_json_from_file(fn):
    f = open(fn)
    try:
        dict = json.load(f)
        
    except ValueError, e:
        print "Load failed: ", e
        dict = {}

    f.close()
    return dict

def write_file(filename, content):
    f = open(filename, "wb")
    f.write(content)
    f.close()

def foo():
    print "Reading config..."
    fn = "/app/conf/test.json"
    d = load_json_from_file(fn)
    print "values:"
    print d

    write_file("/app/logs/test.log", "OK!")

if __name__ == "__main__":
    foo()
