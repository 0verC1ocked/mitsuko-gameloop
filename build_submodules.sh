#!/bin/sh

if [ -d lib/matchengine ]; then
    make -C lib/matchengine release
else
    echo "Directory lib/matchengine does not exist."
fi

if [ -d lib/arenaallocator ]; then
    make -C lib/arenaallocator release
else
    echo "Directory lib/arenaallocator does not exist."
fi

