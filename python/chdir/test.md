Python - chdir

# Overview

程序执行过程中，切换当前路径。

Key:

- chdir & getcwd

# Example

foo.py调用可执行程序foo，而foo会读取相对路径下的文件。

## 目录结构

    $ ls -R .
    foo.py  the

    ./the:
    foo

    ./the/foo:
    config  foo foo.cpp

    ./the/foo/config:
    foo.txt

## foo.py

    #!/usr/bin/env python

    import os
    import subprocess

    def run_command(cmd, shell=False):
        print "cmd: ", cmd
        try:
            p = subprocess.Popen(cmd, shell=shell)
            p.communicate()

            if p.returncode != 0:
                print "Return code:", p.returncode
                return False 

            return True
        except Exception, e:
          print "Exception:", e
          return False 
       
    if __name__ == "__main__":
        foo_path = "/your/dir/chdir/the/foo"
        foo_full_name = os.path.join(foo_path, "foo")

        cmd = [foo_full_name]
        cur_dir = os.getcwd()
        print "current dir:", cur_dir
        os.chdir(foo_path)
        print "after chdir(), current dir:", cur_dir
        run_command(cmd)
        os.chdir(cur_dir)
        print "after restore, current dir:", cur_dir
        
## foo.cpp

    /*
    g++ -o foo foo.cpp
    */

    #include <stdbool.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/uio.h>
    #include <unistd.h>
    #include <iostream>
    #include <string>

    bool read_text_file(const std::string& filename, std::string& content)
    {
        int fd = open(filename.c_str(), O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
        if (fd == -1) {
            printf("ERROR: (%d)%s\n", errno, strerror(errno));
            return false;
        }
        
        const size_t BUFFER_SIZE = 4096;
        char buffer[BUFFER_SIZE];
        ssize_t read_count;
        content.clear();
        while ((read_count = read(fd, buffer, BUFFER_SIZE)) > 0) {
            content.append(buffer, read_count);
        }

        close(fd);
        return true;
    }

    int main()
    {
        const std::string CONFIG_FN("./config/foo.txt");
        std::string content;
        if (!read_text_file(CONFIG_FN, content)) {
            std::cout<<"Read failed."<<std::endl;
            return 1;
        }

        std::cout<<content<<std::endl;
        return 0;
    }

## foo.txt

Any content you want it to be.

## Run

    hostname:chdir$ cd the/foo/
    hostname:foo$ g++ -o foo foo.cpp
    hostname:foo$ cd ../..
    hostname:chdir$ ./foo.py 
    current dir: /your/dir/chdir
    after chdir(), current dir: /your/dir/chdir
    cmd:  ['/your/dir/chdir/the/foo/foo']
    Any content you want it to be.
    after restore, current dir: /your/dir/chdir
    hostname:chdir$ 


