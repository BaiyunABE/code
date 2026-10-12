#!/bin/bash
typora note.md &
for file in `ls ppt`
do
	open $file
done
