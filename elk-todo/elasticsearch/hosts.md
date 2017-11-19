elasticsearch - hosts

如果host不是localhost，那么需要设置max files。本地验证的时候，host直接用缺省值localhost。

    [o.e.t.TransportService   ] publish_address {10.xxx.xxx.xxx:xxxx}, bound_addresses {10.xxx.xxx.xxx:xxxx}
    [o.e.b.BootstrapChecks    ] bound or publishing to a non-loopback or non-link-local address, enforcing bootstrap checks
    ERROR: [2] bootstrap checks failed
    [1]: max file descriptors [40960] for elasticsearch process is too low, increase to at least [65536]
    [2]: max virtual memory areas vm.max_map_count [65530] is too low, increase to at least [262144]
    [o.e.n.Node               ] stopping ...
    [o.e.n.Node               ] stopped
    [o.e.n.Node               ] closing ...
    [o.e.n.Node               ] closed
