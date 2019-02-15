#!/bin/sh
for img in input/*
do
	./brumm "$img" "output/$(basename "$img")"
done