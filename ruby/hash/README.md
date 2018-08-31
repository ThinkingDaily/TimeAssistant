# Hash()

    irb(main):010:0> a = Hash['message' => 'hello, world']
    => {"message"=>"hello, world"}
    irb(main):011:0> a
    => {"message"=>"hello, world"}
    irb(main):012:0> a.length
    => 1
    irb(main):013:0> a['message']
    => "hello, world"
    irb(main):014:0> 

# Iterate, Has Key

    def foo()
        value = Hash['message' => 'hello, world'] # or,
        # value = Hash['message', 'hello, world'] # or,
        # value = {'message' => 'hello, world'}
        for key in ["message", "msg"]
            if value.key?(key) then
                puts "message: #{value[key]}"
            else
                puts "No key: #{key}"
            end
        end
    end

    '''
    message: hello, world
    No key: msg
    '''
    foo()
