#!/bin/sh

while true
do
    sleep 1
	echo "test"
    echo ON > /dev/relay1
    echo ON > /dev/relay2
    echo ON > /dev/relay3
    echo ON > /dev/relay4
    sleep 1
    echo OFF > /dev/relay1
    echo OFF > /dev/relay2
    echo OFF > /dev/relay3
    echo OFF > /dev/relay4
done

