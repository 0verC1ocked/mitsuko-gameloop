#!/bin/sh

if [ -d lib/matchengine ]; then
    make -C lib/matchengine release
else
    echo "Directory lib/matchengine does not exist."
fi

if [ -d lib/payloadbuilder ]; then
    make -C lib/payloadbuilder release
else
    echo "Directory lib/payloadbuilder does not exist."
fi

