#! /bin/bash

if ! [[ -x main ]]; then
    echo "main executable does not exist"
    exit 1
fi

../tester/run-tests.sh -v $*