Example:

    "namespaces": {
        "include": ["your_db1.*"],
        "mapping": {"your_db1.*": "prefix_your_db1.*"}
    },

or,

    --namespace-set your_db1.* --dest-namespace-set prefix_your_db1.*
